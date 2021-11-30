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
    BOOL IgnoreHeader;
	S8 s8Delimeter;
};


class CConverter
{
public:
	CConverter();
	~CConverter();

    //static S32 s32ConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName, ConvertOptions* pOptions = NULL, S8 s8SourceDelimeter = 0x20, S8 s8DestDelimeter = ',');
	S32 ReadTXT(const std::string& crstrSourceFileName, const FileOptions& crFileOptions);
	
private:
	CDataSeries<F64, F64>* m_pDataSeries;
};

} /* End of namespace Visualization */

#endif // CConverter_H
