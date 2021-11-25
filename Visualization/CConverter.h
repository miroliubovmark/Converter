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

struct ConvertOptions
{
    BOOL IgnoreTXTheader;
    BOOL AddCSVheader;
};

class CConverter
{
public:
	CConverter();
	~CConverter();

    static S32 s32ConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName, ConvertOptions* pOptions = NULL, S8 s8SourceDelimeter = 0x20, S8 s8DestDelimeter = ',');
};

} /* End of namespace Visualization */

#endif // CConverter_H
