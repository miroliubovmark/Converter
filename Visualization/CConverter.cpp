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

S32 CConverter::ReadTXT(const std::string& crstrSourceFileName, const FileOptions& crFileOptions)
{
	/** Stream for source file reading */
	std::ifstream SourceFile;
	
	SourceFile.open(crstrSourceFileName);
	
	if(!SourceFile.is_open())
	{
		/* File does not exist */
		return 1;
	}
	
	std::string strReadLine;
	
	/* Ignore header */
	if(crFileOptions.IgnoreHeader)
	{
		std::getline(SourceFile, strReadLine);
	}
	
	/* File interations */
	while(std::getline(SourceFile, strReadLine))
	{
		
	}
}

} /* End of namespace VISUALIZATION */
