#include "CConverter.h"

namespace Visualization
{

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

/**
 *******************************************************************************
 *
 *   \par Name:
 *              S32 bConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName) \n
 *
 *   \par Purpose:
 * 				Convert file from TXT to CSV \n
 *
 *   \par Inputs:
 * 				std::string strSourceFileName - source file name \n
 *				std::string strDestFileName - destination file name \n
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
S32 CConverter::s32ConvertTXTtoCSV(std::string strSourceFileName, std::string strDestFileName, S8 s8SourceDelimeter, S8 s8DestDelimeter)
{
	/** Stream for source file reading */
	std::ifstream rSourceFile;
	
	std::ifstream rDestFileChecker;
	
	/** Stream for destination file writing */
	std::ofstream wDestFile;
	
	/* Validation */
	rSourceFile.open(strSourceFileName);
	rDestFileChecker.open(strDestFileName);
	
	/* Source file does not exist */
	if(!rSourceFile.is_open())
	{
		return 1;
	}
	
	/* Destination file already exists */
	if(rDestFileChecker.is_open())
	{
		return 2;
	}
	
	
	/* Converting */
	
	/** Line from source file */
	std::string strReadLine;
	
	/** Line to destination file */
	std::string strWriteLine;
	
	std::string strSubstr;
	
	size_t zPos1, zPos2;
	BOOL bFlag;
	
	strReadLine.reserve(100);
	strWriteLine.reserve(100);
	strSubstr.reserve(100);
	
	wDestFile.open(strDestFileName);
	
	/* Line interations */
	while(std::getline(rSourceFile, strReadLine))
	{
		bFlag = FALSE;
		strSubstr.clear();
		strWriteLine.clear();
		
		zPos1 = 0;
		
		/* Make strWriteLine */
		while(!bFlag)
		{
			zPos2 = strReadLine.find(s8SourceDelimeter, zPos1);
			
			//printf("Pos2 = %zd\n", zPos2);
			
			if(zPos2 == std::string::npos)
			{
				strSubstr = strReadLine.substr(zPos1);
				bFlag = TRUE;
			}
			else
			{
				strSubstr = strReadLine.substr(zPos1, zPos2);
			}
			
			if(zPos1 > 0)
			{
				strWriteLine.append(",");
			}
			
			strWriteLine.append(strSubstr);
			zPos1 = zPos2 + 1;
			
			//printf(".%s.\n", strWriteLine.data());
		}
		
		/* Write to file */
		strWriteLine.push_back('\n');
		wDestFile.write(strWriteLine.c_str(), strWriteLine.size());
	}
	
//	try
//	{
//		SourceFile.open(strSourceFileName);
//	}
//	catch(...)
//	{
//		/* Unable to open Source file */
//		return 1;
//	}
	
//	try
//	{
//		DestFile.open(strDestFileName);
//	}
//	catch(...)
//	{
//		/* Unable to open Destination file */
//		return 2;
//	}
	
	return 0;
}

} /* End of namespace VISUALIZATION */
