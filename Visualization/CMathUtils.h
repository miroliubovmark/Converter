#ifndef CMATHUTILS_H
#define CMATHUTILS_H

#include <memory>

#include <complex>
#include <cmath>

#include "UBaseTypes.h"

namespace Visualization
{


//////////////////////////////////////////////////////////////////////////////////////////////////////
///                             Interface                                                          ///
//////////////////////////////////////////////////////////////////////////////////////////////////////

class EIncorrectDataSeriesFormat : std::runtime_error{
public:
    EIncorrectDataSeriesFormat(const char* msg) : std::runtime_error(msg) {}
};

class EInterpolationError : std::runtime_error{
public:
    EInterpolationError(const char* msg) : std::runtime_error(msg) {}
};

enum DifferentiationMethod {
    DM_Fourier,
    DM_Polynomial
};

enum InterpolationMethod {
    IM_Linear,
    IM_Fourier,
    IM_Polynomial
};

template<class TX, class TY> class CDataSeries {
public:
    TX tGetX(size_t zIndex) const;
    TY tGetY(size_t zIndex) const;
    size_t zGetSize() const;

    void SetX(size_t zIndex, TX tVal);
    void SetY(size_t zIndex, TY tVal);

    void EnsureAccendingX() const;

    CDataSeries(size_t zSize) :
        zSize(zSize),
        pXValues(std::make_unique<TX[]>(zSize)),
        pYValues(std::make_unique<TY[]>(zSize)) {};

    inline void print(std::ostream& ostream)
    {

        ostream << "X\tY\n";
        for (int i = 0; i < zSize; i++) {
            ostream << pXValues[i] <<  "\t" <<  pYValues[i] << '\n';
        }
    }
private:
    std::unique_ptr<TX[]> pXValues;
    std::unique_ptr<TY[]> pYValues;
    size_t zSize;
};

template<class T> class CLinearSystem {
protected:
    std::unique_ptr<T[]> pData;
    size_t zSize;

    void MultiplyInplace(size_t zTarget, T factor);
    void AddMultiplied(size_t zTarget, size_t zSource, T factor);
    void SwapRows(T* r1, T* r2);
public:
    size_t zGetSize();

    T* pGetRow(size_t zIndex);
    T tGet(size_t zRow, size_t zCol);

    void Set(size_t zRow, size_t zColStart, size_t zLen, T* zVals);
    void Set(size_t zRow, size_t zCol, T tVal);
    void SetRight(size_t ZRow, T tVal);

    void FillZeros();

    CLinearSystem(size_t ZSize);

    void SolveGauss(T* pOutput);
    T* operator[](size_t zIndex);

    inline void print(std::ostream& ostream)
    {
        for (int i = 0; i < zSize; i++) {
            for (int j = 0; j < zSize; j++) {
                ostream << tGet(i, j) << '\t';
            }
            ostream << "|\t" << tGet(i, zSize) << '\n';
        }
    }
};


class CMathUtils {
public:

    template<class T> static void FourierDirect(const CDataSeries<T, T>* pInput, CDataSeries<T, std::complex<T>>* pOutput);
    template<class T> static void FourierReverse(const CDataSeries<T, std::complex<T>>* pInput, CDataSeries<T, T>* pOutput);

    template<class T> static void PolynomialDirect(const CDataSeries<T, T>* pInput, CDataSeries<U16, T>* pOutput);
    template<class T> static void PolynomialReverse(const CDataSeries<U16, T>* pInput, CDataSeries<T, T>* pOutput);

    template<class T> static void ComputeDerivatives(const CDataSeries<T, T>* pInput, CDataSeries<T, T>* pOutput, DifferentiationMethod eMethod, U16 u16Order);
    template<class T> static void Interpolate(const CDataSeries<T, T>* pInput, CDataSeries<T, T>* pOutput, InterpolationMethod eMethod, U16 u16Order);
};



//////////////////////////////////////////////////////////////////////////////////////////////////////
///                             Implementations                                                    ///
//////////////////////////////////////////////////////////////////////////////////////////////////////



template<class TX, class TY> inline TX CDataSeries<TX, TY>::tGetX(size_t zIndex) const {
    return pXValues[zIndex];
}

template<class TX, class TY> inline TY CDataSeries<TX, TY>::tGetY(size_t zIndex) const {
    return pYValues[zIndex];
}
template<class TX, class TY> inline void CDataSeries<TX, TY>::SetX(size_t zIndex, TX tVal){
    pXValues[zIndex] = tVal;
}
template<class TX, class TY> inline void CDataSeries<TX, TY>::SetY(size_t zIndex, TY tVal){
    pYValues[zIndex] = tVal;
}
template<class TX, class TY> inline size_t CDataSeries<TX, TY>::zGetSize() const{
    return zSize;
}
template<class TX, class TY> inline void CDataSeries<TX, TY>::EnsureAccendingX() const{
    for(int zI = 0; zI < zSize-1; zI++){
        if(pXValues[zI+1] < pXValues[zI]){
            throw EIncorrectDataSeriesFormat("Values of X are expected to be in accending order");
        }
    }
}

template<class T> inline void CMathUtils::FourierDirect(const CDataSeries<T, T>* pInput, CDataSeries<T, std::complex<T>>* pOutput) {
    pInput->EnsureAccendingX();

    size_t zOutSize = pOutput->zGetSize();
    size_t zInSize = pInput->zGetSize();
    T input_max = pInput->tGetX(pInput->zGetSize()-1);

    for(int zI = 0; zI < zOutSize; zI++) {
        T tOmega = 2 * PI / input_max * zI;
        std::complex<T> tP = std::complex<T>(0, -tOmega);

        std::complex<T> tSum = 0;
        for(int zJ = 0; zJ < zInSize - 1; zJ++) {
            T x0 = pInput->tGetX(zJ); T x1 = pInput->tGetX(zJ+1);
            T y0 = pInput->tGetY(zJ); T y1 = pInput->tGetY(zJ+1);

            tSum +=  (y1 * std::exp(tP * x1) + y0 * std::exp(tP * x0)) * (x1 - x0);
        }
        tSum /= input_max;

        pOutput->SetX(zI, tOmega);
        pOutput->SetY(zI, tSum);
    }
}

template<class T> inline void CMathUtils::FourierReverse(const CDataSeries<T, std::complex<T>>* pInput, CDataSeries<T, T>* pOutput) {

    size_t zOutSize = pOutput->zGetSize();
    size_t zInSize = pInput->zGetSize();

    for(int zI = 0; zI < zOutSize; zI++) {
        T tXVal = pOutput->tGetX(zI);
        std::complex<T> tSum = 0;

        for(int zJ = 0; zJ < zInSize; zJ++) {
            std::complex<T> tP = std::complex<T>(0, pInput->tGetX(zJ));
            std::complex<T> tAmpl = pInput->tGetY(zJ);

            tSum +=  std::exp(tP * tXVal) *  tAmpl;
        }

        pOutput->SetY(zI, tSum.real());
    }
}

template<class T> inline void CMathUtils::PolynomialDirect(const CDataSeries<T, T>* pInput, CDataSeries<U16, T>* pOutput) {
    pInput->EnsureAccendingX();

    size_t zOutSize = pOutput->zGetSize();
    size_t zInSize = pInput->zGetSize();

    CLinearSystem<T> oSys(zOutSize);

    T tInputMax = pInput->tGetX(pInput->zGetSize()-1);
    T tInputMin = pInput->tGetX(0);


    for(U16 zI = 0; zI < zOutSize; zI++){
        for(int zJ = 0; zJ < zOutSize; zJ++) {
            U16 pow = zI + zJ + 1;
            oSys.Set(zI, zJ, (std::pow(tInputMax, pow) - std::pow(tInputMin, pow)) / pow );
        }
    }

    for(U16 zI = 0; zI < zOutSize; zI++) {
        T tSum = 0;
        for(int zJ = 0; zJ < zInSize - 1; zJ++) {
            T x0 = pInput->tGetX(zJ); T x1 = pInput->tGetX(zJ+1);
            T y0 = pInput->tGetY(zJ); T y1 = pInput->tGetY(zJ+1);

            tSum +=  (y1 * std::pow(x1,zI) + y0 * std::pow(x0,zI)) * (x1 - x0) / 2;
        }

        oSys.SetRight(zI, tSum);
    }

    oSys.print(std::cout);

    std::unique_ptr<T[]> pResult = std::make_unique<T[]>(zOutSize);
    oSys.SolveGauss(pResult.get());


    oSys.print(std::cout);

    for(U16 zI = 0; zI < zOutSize; zI++){
        pOutput->SetX(zI, zI);
        pOutput->SetY(zI, pResult[zI]);
    }


}

template<class T> inline void CMathUtils::PolynomialReverse(const CDataSeries<U16, T>* pInput, CDataSeries<T, T>* pOutput) {
    size_t zOutSize = pOutput->zGetSize();
    size_t zInSize = pInput->zGetSize();


    for(size_t zI = 0; zI < zOutSize; zI++) {
        T tSum = 0;
        for(U16 zJ = 0; zJ < zInSize; zJ++) {
            tSum += pInput->tGetY(zJ) * std::pow(pOutput->tGetX(zI), pInput->tGetX(zJ));
        }
        pOutput->SetY(zI, tSum);
    }
}

template<class T> inline void CMathUtils::ComputeDerivatives(const CDataSeries<T, T>* pInput, CDataSeries<T, T>* pOutput, DifferentiationMethod eMethod, U16 u16Order){
    switch (eMethod) {
    case DM_Fourier: {
        CDataSeries<T, std::complex<T>> oTemp(u16Order);
        FourierDirect(pInput, &oTemp);
        oTemp.print(std::cout);

        for(int u16I = 0; u16I < u16Order; u16I++) {
            oTemp.SetY(u16I, oTemp.tGetY(u16I) * std::complex<T>(0, oTemp.tGetX(u16I)));
        }
        oTemp.print(std::cout);
        FourierReverse(&oTemp, pOutput);

    } break;
    case DM_Polynomial: {

        CDataSeries<U16, T> oTemp(u16Order);
        PolynomialDirect(pInput, &oTemp);
        for(int u16I = 0; u16I < u16Order - 1; u16I++) {
            oTemp.SetY(u16I, oTemp.tGetY(u16I + 1) * oTemp.tGetX(u16I + 1));
        }
        oTemp.SetY(u16Order - 1, 0);
        PolynomialReverse(&oTemp, pOutput);

    } break;
    }
}

template<class T> inline void CMathUtils::Interpolate(const CDataSeries<T, T>* pInput, CDataSeries<T, T>* pOutput, InterpolationMethod eMethod, U16 u16Order){
    switch (eMethod) {
    case IM_Fourier: {
        CDataSeries<T, std::complex<T>> oTemp(u16Order);
        FourierDirect(pInput, &oTemp);
        FourierReverse(&oTemp, pOutput);

    } break;
    case IM_Polynomial: {

        CDataSeries<U16, T> oTemp(u16Order);
        PolynomialDirect(pInput, &oTemp);
        PolynomialReverse(&oTemp, pOutput);

    } break;
    case IM_Linear: {
        pInput->EnsureAccendingX();
        pOutput->EnsureAccendingX();

        size_t zOutSize = pOutput->zGetSize();
        size_t zInSize = pInput->zGetSize();

        size_t zInIndex = 0;

        T tXMin = pInput->tGetX(zInIndex);
        T tXMax = pInput->tGetX(zInIndex+1);
        for(size_t zI = 0; zI < zOutSize; zI++) {
            T tXVal = pOutput->tGetX(zI);
            while(tXMax < tXVal && zInIndex < zInSize - 1) {
                zInIndex++;
                tXMin = pInput->tGetX(zInIndex);
                tXMax = pInput->tGetX(zInIndex+1);
            }
            T tC0 = (tXVal-tXMin)/(tXMax-tXMin);
            T tC1 = (tXMax-tXVal)/(tXMax-tXMin);
            pOutput->SetY(zI, pInput->tGetY(zI) * tC0 + pInput->tGetY(zI+1) * tC1);
        }
    } break;
    }
}




template<class T> inline void CLinearSystem<T>::AddMultiplied(size_t zTarget, size_t zSource, T factor) {
    T* target_ptr = pGetRow(zTarget);
    T* source_ptr = pGetRow(zSource);

    for (int i = 0; i < zSize + 1; i++) {
        target_ptr[i] += source_ptr[i] * factor;
    }
}

template<class T> inline void CLinearSystem<T>::MultiplyInplace(size_t target, T factor) {
    T* target_ptr = pGetRow(target);
    for (int i = 0; i < zSize + 1; i++) {
        target_ptr[i] *= factor;
    }
}

template<class T> inline void CLinearSystem<T>::SwapRows(T* r1, T* r2) {
    for (int i = 0; i < zSize + 1; i++) {
        T t = r1[i];
        r1[i] = r2[i];
        r2[i] = t;
    }
}

template<class T> inline size_t CLinearSystem<T>::zGetSize() {
    return zSize;
}

template<class T> inline T* CLinearSystem<T>::pGetRow(size_t index) {
    return pData.get() + index * (zSize + 1);
}

template<class T> inline T CLinearSystem<T>::tGet(size_t row, size_t col) {
    return pData[row * (zSize + 1) + col];
}

template<class T> inline void CLinearSystem<T>::Set(size_t row, size_t col_start, size_t len, T* vals) {
    int i_start = row * (zSize + 1) + col_start;
    for (int i = 0; i < len; i++) {
        pData[i + i_start] = vals[i];
    }
}


template<class T> inline void CLinearSystem<T>::Set(size_t zRow, size_t zCol, T tVal)
{
    pData[zRow * (zSize + 1) + zCol] = tVal;
}


template<class T> inline void CLinearSystem<T>::SetRight(size_t row, T val)
{
    pData[(row + 1) * (zSize + 1) - 1] = val;
}

template<class T> inline void CLinearSystem<T>::FillZeros()
{
    for (int i = 0; i < zSize * (zSize + 1); i++) {
        pData[i] = 0;
    }
}


template<class T> inline CLinearSystem<T>::CLinearSystem(size_t sz) :
    pData(std::make_unique<T[]>(sz * (sz + 1)))
{
    zSize = sz;
}


template<class T> inline void CLinearSystem<T>::SolveGauss(T* result_to)
{
    for (int i = 0; i < zSize; i++) {

        int unempty = i;
        while (tGet(unempty, i) == 0) {
            unempty++;
            if (unempty == zSize) {
                std::cout << "Unsolvable\n";
                return;
            }
        }

        if (unempty != i) {
            SwapRows(pGetRow(unempty), pGetRow(i));
        }

        MultiplyInplace(i, 1 / tGet(i, i));
        for (int j = 0; j < zSize; j++) {
            if (j == i) {
                continue;
            }
            AddMultiplied(j, i, -tGet(j, i));
        }
    }


    for (int i = 0; i < zSize; i++) {
        result_to[i] = pData[(i + 1) * (zSize + 1) - 1];
    }
}



template<class T> inline T* CLinearSystem<T>::operator[](size_t index)
{
    return pData + (zSize + 1) * index;
}




}


#endif // CMATHUTILS_H

