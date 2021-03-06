#include "CConverter.h"
#include <vector>

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              void Trim(std::string* str) \n
 *
 *   \par Purpose:
 * 				Trim \n
 *
 *   \par Inputs:
 * 				None \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
void CConverter::Trim(std::string* str)
{
    BOOL bFlag = FALSE;

    while(str->size() > 0)
    {
        bFlag = FALSE;
        size_t zSize = str->size();

        if(str->at(0) == ' ' || str->at(0) == '\t' || str->at(0) == '\n')
        {
            str->erase(0, 1);
            bFlag = TRUE;
        }

        zSize = str->size();

        if(str->at(zSize - 1) == ' ' || str->at(zSize - 1) == '\t' || str->at(zSize - 1) == '\n')
        {
            *str = str->substr(0, zSize - 1);
            bFlag = TRUE;
        }

        if(!bFlag)
        {
            break;
        }
    }
}


/**
 *******************************************************************************
 *
 *   \par Name:
 *              CConverter::CConverter() \n
 *
 *   \par Purpose:
 * 				Constructor \n
 *
 *   \par Inputs:
 * 				None \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
CConverter::CConverter()
	: m_pDataSeries(NULL)
{
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CConverter::~CConverter() \n
 *
 *   \par Purpose:
 * 				Destructor \n
 *
 *   \par Inputs:
 * 				None \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
CConverter::~CConverter()
{
}

void CConverter::Clear()
{
	delete m_pDataSeries;
	m_pDataSeries = NULL;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              S32 bConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName,
 *              ConvertOptions* pOptions = NULL, S8 s8SourceDelimeter = 0x20, S8 s8DestDelimeter = ',') \n
 *
 *   \par Purpose:
 * 				Convert file from TXT to CSV \n
 *
 *   \par Inputs:
 * 				std::string strSourceFileName - source file name \n
 *				std::string strDestFileName - destination file name \n
 *              ConvertOptions* pOptions = NULL - pointer to ConvertOptions \n
 *				S8 s8DestDelimeter = ',' - delimeter for CSV file \n
 *				S8 s8SourceDelimeter = 0x20 - delimeter in TXT file \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				0 - Ok \n
 *				1 - source file does not exist \n
 *				2 - destination file already exists \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
//S32 CConverter::s32ConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName, ConvertOptions* pOptions,
//								   S8 s8SourceDelimeter, S8 s8DestDelimeter)
//{
//	/** Stream for source file reading */
//	std::ifstream rSourceFile;
	
//	std::ifstream rDestFileChecker;
	
//	/** Stream for destination file writing */
//	std::ofstream wDestFile;
	
//	/* Validation */
//	rSourceFile.open(strSourceFileName);
//	rDestFileChecker.open(strDestFileName);
	
//	/* Source file does not exist */
//	if(!rSourceFile.is_open())
//	{
//		return 1;
//	}
	
//	/* Destination file already exists */
//	if(rDestFileChecker.is_open())
//	{
//		return 2;
//	}

//	/* Converting */	
//	/** Line from source file */
//	std::string strReadLine;
	
//	/** Line to destination file */
//	std::string strWriteLine;

//	std::string strSubstr;

//    size_t zPos1, zPos2, zPos3;
//	BOOL bFlag;

//	strReadLine.reserve(100);
//	strWriteLine.reserve(100);
//	strSubstr.reserve(100);

//	wDestFile.open(strDestFileName);

//	if(pOptions->IgnoreTXTheader)
//	{
//		std::getline(rSourceFile, strReadLine);
//	}

//	if(pOptions->AddCSVheader)
//	{
//		std::string strHeader = "X--Trace 1::[CH1],Y--Trace 1::[CH1]\n";
//		wDestFile.write(strHeader.c_str(), strHeader.size());
//	}
	
//	/* Line interations */
//	while(std::getline(rSourceFile, strReadLine))
//	{
//		bFlag = FALSE;
//		strSubstr.clear();
//		strWriteLine.clear();
		
//		zPos1 = 0;
		
//		/* Make strWriteLine */
//		while(!bFlag)
//		{
//			zPos2 = strReadLine.fi/** Stream for source file reading */
//	std::ifstream rSourceFile;nd(s8SourceDelimeter, zPos1);
//            zPos3 = strReadLine.find('\t', zPos1);  /* LTSpice save chart with '\t' delimeter */

//            zPos2 = zPos2 < zPos3 ? zPos2 : zPos3;
						
//			if(zPos2 == std::string::npos)
//			{
//				strSubstr = strReadLine.substr(zPos1);
//				bFlag = TRUE;
//			}
//			else
//			{
//				strSubstr = strReadLine.substr(zPos1, zPos2);
//			}
			
//			if(zPos1 > 0)
//			{
//				strWriteLine.append(",");
//			}
			
//			strWriteLine.append(strSubstr);
//			zPos1 = zPos2 + 1;
			
//			//printf(".%s.\n", strWriteLine.data());
//		}
		
//		/* Write to file */
//		strWriteLine.push_back('\n');
//		wDestFile.write(strWriteLine.c_str(), strWriteLine.size());
//	}

//	return 0;
//}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              ErrorCode ReadTXT(const std::string& crstrSourceFileName, const FileOptions& crFileOptions)
 *
 *   \par Purpose:
 * 				Parse TXT file into internal CDataSeries object \n
 *
 *   \par Inputs:
 * 				const std::string& crstrSourceFileName - source file name \n
 *              const FileOptions& crFileOptions - parsing options \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				Error code \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
ErrorCode CConverter::Read(const std::string& crstrSourceFileName, const FileOptions& crFileOptions, BOOL bThreeCols)
{
	/** Stream for source file reading */
    std::ifstream rSourceFile;
	
    rSourceFile.open(crstrSourceFileName);
	
    if(!rSourceFile.is_open())
	{
		/* File does not exist */
		return EC_SourceFileDoesNotExist;
	}
	
	std::string strReadLine;
	
	/* Ignore header */
	if(crFileOptions.HeaderOpt)
	{
        std::getline(rSourceFile, strReadLine);
	}

    std::vector<std::string> strFileContents;
	
    /* File interations */
    while(std::getline(rSourceFile, strReadLine))
	{
        strFileContents.push_back(strReadLine);
	}

    m_pDataSeries = new CDataSeries<F64,F64>(strFileContents.size());

    /* Input parsing */
    for(size_t zI = 0; zI < strFileContents.size(); zI++)
    {
        size_t zDelim1Pos = strFileContents[zI].find(crFileOptions.s8Delimeter);

        std::string strXVal = strFileContents[zI].substr(0, zDelim1Pos);
        std::string strYVal = strFileContents[zI].substr(zDelim1Pos + 1);

        if(bThreeCols){
            size_t zDelim2Pos = strYVal.find(crFileOptions.s8Delimeter);
            strYVal = strYVal.substr(zDelim2Pos + 1);
        }
        F64 f64XVal = std::stod(strXVal);
        F64 f64YVal = std::stod(strYVal);
        m_pDataSeries->SetX(zI, f64XVal);
        m_pDataSeries->SetY(zI, f64YVal);
    }

    return EC_OK;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              S32 WriteCSV(const std::string& crstrDestFileName, const FileOptions& crFileOptions)
 *
 *   \par Purpose:
 * 				Record current data (the contents of CDataSeries instance) into a file \n
 *
 *   \par Inputs:
 * 				const std::string& crstrDestFileName - destination file name \n
 *              const FileOptions& crFileOptions - options for saving \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				0 - Ok \n
 *				1 - m_pDataSeries does not point to an object (no series created just yet) \n
 *				2 - Destination file already exists \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
ErrorCode CConverter::Write(const std::string& crstrDestFileName, const FileOptions& crFileOptions)
{
    if(m_pDataSeries == NULL)
    {
        return EC_DataSeriesDoesNotExist;
    }

    std::ifstream rDestFileChecker;
    rDestFileChecker.open(crstrDestFileName);

    if(rDestFileChecker.is_open())
    {
        return EC_DestFileAlreadyExist;
    }
	
    rDestFileChecker.close();

    /** Stream for file writing */
    std::ofstream wDestFile;

    wDestFile.open(crstrDestFileName);

    /* Ignore header */
	if(crFileOptions.HeaderOpt)
    {
        std::string strHeader;
        switch(crFileOptions.FType) {
        case FT_TXT:
            strHeader = "time\tV(n001)\n";
            break;
        case FT_CSV:
            strHeader = "X--Trace 1::[CH1],Y--Trace 1::[CH1]\n";
            break;
        default:
            return EC_UnknownError;
        }
        wDestFile.write(strHeader.c_str(), strHeader.size());
    }

    for(size_t zI = 0; zI < m_pDataSeries->zGetSize(); zI++)
    {
        wDestFile << m_pDataSeries->tGetX(zI) << crFileOptions.s8Delimeter << m_pDataSeries->tGetY(zI) << std::endl;
    }

    return EC_OK;
}

ErrorCode CConverter::InterpolateData(U32 u32PointCount)
{
    CDataSeries<F64, F64>* pNewSeries = new CDataSeries<F64, F64>(u32PointCount);
    F64 f64InputMin = m_pDataSeries->tGetX(0);
    F64 f64InputMax = m_pDataSeries->tGetX(m_pDataSeries->zGetSize()-1);

    for(U32 u32I = 0; u32I < u32PointCount; u32I++)
    {
        pNewSeries->SetX(u32I, f64InputMin + (f64InputMax - f64InputMin) * (1.0 * u32I / (u32PointCount - 1)));
    }
	CMathUtils::Interpolate(m_pDataSeries, pNewSeries, IM_Linear, 0);

    delete m_pDataSeries;
    m_pDataSeries = pNewSeries;
	
	return EC_OK;
}

ErrorCode CConverter::DifferenciateData(U32 u32Order)
{
    CMathUtils::ComputeDerivatives(m_pDataSeries, m_pDataSeries, DM_Polynomial, u32Order);

    return EC_OK;
}

ErrorCode CConverter::TXTtoCSV(const std::string& crstrSourceFileName, const std::string& crstrDestFileName,
             const FileOptions& crSourecOpt, const FileOptions& crDestcOpt, BOOL bCalculateTau, U32 u32PointCount)
{
	Clear();
	
    ErrorCode Code = Read(crstrSourceFileName, crSourecOpt, bCalculateTau);
	
	if(Code != EC_OK)
	{
		return Code;
	}

    m_pDataSeries->print(std::cout);
	
    if(bCalculateTau) {
        DifferenciateData(4);
    } else{
        InterpolateData(u32PointCount);
    }

	
    Code = Write(crstrDestFileName, crDestcOpt);
	
	if(Code != EC_OK)
	{
		return Code;
	}
	
	return EC_OK;
}

ErrorCode CConverter::CSVtoTXT(const std::string& crstrSourceFileName, const std::string& crstrDestFileName,
             const FileOptions& crSourecOpt, const FileOptions& crDestcOpt, BOOL bCalculateTau, U32 u32PointCount)
{
	Clear();
	
	ErrorCode Code = Read(crstrSourceFileName, crSourecOpt, bCalculateTau);
	
	if(Code != EC_OK)
	{
		return Code;
	}
	
	Code = Write(crstrDestFileName, crDestcOpt);
	
	if(Code != EC_OK)
	{
		return Code;
	}
	
	return EC_OK;
}

} /* End of namespace VISUALIZATION */
