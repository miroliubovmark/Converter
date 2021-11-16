#ifndef CConverter_H
#define CConverter_H

#include "VisualizationStable.h"

namespace Visualization
{

class CConverter
{
public:
	CConverter();
	~CConverter();

	static S32 s32ConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName, S8 s8SourceDelimeter = 0x20, S8 s8DestDelimeter = ',');
};

} /* End of namespace Visualization */

#endif // CConverter_H
