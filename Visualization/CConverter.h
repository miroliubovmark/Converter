#ifndef CConverter_H
#define CConverter_H

#include "VisualizationStable.h"

namespace Visualization
{

enum ConvertionResult
{
    Success = 0,
    NoSoure,
    DestAlreadyExist
};

enum FileType
{
	FT_TXT,
	FT_CSV
};


struct FileOptions
{
	FileType FType;
    BOOL HeaderOpt;
	S8 s8Delimeter;
};

enum ErrorCode
{
	EC_OK = 0,
	EC_SourceFileDoesNotExist,
	EC_DestFileAlreadyExist,
	EC_DataSeriesDoesNotExist,
	EC_UnknownError = 101
};


class CConverter
{
public:
	CConverter();
	~CConverter();
	
	ErrorCode TXTtoCSV(const std::string& crstrSourceFileName, const std::string& crstrDestFileName, 
				 const FileOptions& crSourecOpt, const FileOptions& crDestcOpt, U32 u32PointCount = 10000);

    //static S32 s32ConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName, ConvertOptions* pOptions = NULL, S8 s8SourceDelimeter = 0x20, S8 s8DestDelimeter = ',');
	
	
private:
	CDataSeries<F64, F64>* m_pDataSeries;
	
	void Clear();
	
	ErrorCode ReadTXT(const std::string& crstrSourceFileName, const FileOptions& crFileOptions);
    ErrorCode WriteCSV(const std::string& crstrDestFileName, const FileOptions& crFileOptions);
    ErrorCode InterpolateData(U32 u32PointCount);
};

} /* End of namespace Visualization */

#endif // CConverter_H
