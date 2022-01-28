#include "CWdgFileNamesReader.h"

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CWdgFileNamesReader::CWdgFileNamesReader() \n
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
CWdgFileNamesReader::CWdgFileNamesReader(S8 s8Parent)
	: QWidget(NULL)
	, m_S8Parent(s8Parent)
{	
	m_pFont = new QFont;
	m_pFontMetrics = new QFontMetrics(*m_pFont);

	/* Source file properties */
	m_pSourceFileLabel = new QLabel("File:");
	m_pSourceFileEdit = new QLineEdit;
	m_pSourceFileEdit->setMinimumWidth(m_pFontMetrics->width("U") * LineEdit_Length);
	connect(m_pSourceFileEdit, SIGNAL(textChanged(const QString&)), this, SLOT(SourceFileEditor_handle(const QString&)), Qt::QueuedConnection);
	
    m_pBrowseSourceFileButton = new QPushButton("Browse...");
	connect(m_pBrowseSourceFileButton, SIGNAL(clicked()), this, SLOT(BrowseSourceFileClicked()), Qt::QueuedConnection);
	
	/* Destination file properties */
	m_pDestFileLabel = new QLabel("Destination:");
	m_pDestFileEdit = new CLineEdit;
	m_pDestFileEdit->setMinimumWidth(m_pFontMetrics->width("U") * LineEdit_Length);
	connect(m_pDestFileEdit, SIGNAL(focussed(bool)), this, SLOT(DestFileEditor_handle(bool)), Qt::QueuedConnection);
	
    m_pBrowseDestFileButton = new QPushButton("Browse...");
	connect(m_pBrowseDestFileButton, SIGNAL(clicked()), this, SLOT(BrowseDestFileClicked()), Qt::QueuedConnection);

	QGridLayout* pGridLayout = new QGridLayout;

	pGridLayout->addWidget(m_pSourceFileLabel, 0, 0, Qt::AlignRight);
	pGridLayout->addWidget(m_pSourceFileEdit, 0, 1);
	pGridLayout->addWidget(m_pBrowseSourceFileButton, 0, 2);

	pGridLayout->addWidget(m_pDestFileLabel, 1, 0, Qt::AlignRight);
	pGridLayout->addWidget(m_pDestFileEdit, 1, 1);
	pGridLayout->addWidget(m_pBrowseDestFileButton, 1, 2);

	pGridLayout->setHorizontalSpacing(20);

	setLayout(pGridLayout);
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CWdgFileNamesReader::~CWdgFileNamesReader() \n
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
CWdgFileNamesReader::~CWdgFileNamesReader()
{
}

void CWdgFileNamesReader::Init()
{
	show();
}

InlineFileType CWdgFileNamesReader::GetExtension(const std::string& crstrText)
{
	std::string strText(crstrText);
	CConverter::Trim(&strText);
	
	size_t zSize = strText.size();
	
	if(zSize < 4)
	{
		return IFT_UNKNOWN;
	}
	
	std::string strExtension(strText.substr(zSize - 4, 4));
	
	if(strExtension == ".csv")
	{
		return IFT_CSV;
	}
	else if(strExtension == ".txt")
	{
		return IFT_TXT;
	}
	else
	{
		return IFT_UNKNOWN;
	}
}

BOOL CWdgFileNamesReader::GetSourceFileName(std::string* pstrSourceFileName, InlineFileType *pFT)
{
	pstrSourceFileName->clear();
	
	std::string strRawText = m_pSourceFileEdit->text().toStdString();
	CConverter::Trim(&strRawText);
	
	/* Set file name */
	if(strRawText.size() == 0)
	{
		return FALSE;
	}
	
	*pstrSourceFileName = strRawText;

	/* Get extension */
	*pFT = GetExtension(strRawText);
	
	return TRUE;
}

BOOL CWdgFileNamesReader::GetDestFileName(std::string* pstrDestFileName, InlineFileType *pFT)
{
	pstrDestFileName->clear();
	
	std::string strRawText = m_pDestFileEdit->text().toStdString();
	CConverter::Trim(&strRawText);
	
	/* Text is empty, consider placeholder */
	if(strRawText.size() == 0)
	{
		strRawText = m_pDestFileEdit->placeholderText().toStdString();
		CConverter::Trim(&strRawText);
	}
	
	if(strRawText.size() == 0)
	{
		return FALSE;
	}
	
	*pstrDestFileName = strRawText;

	/* Get extension */
	*pFT = GetExtension(strRawText);
	
	return TRUE;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              void BrowseSourceFileClicked() \n
 *
 *   \par Purpose:
 * 				Handle "BrowseSourceFile" button \n
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
 * 				private SLOTE \n
 *
 *******************************************************************************
 */
void CWdgFileNamesReader::BrowseSourceFileClicked()
{
	QString qstrFileName = QFileDialog::getOpenFileName(0, "Select file", "", "TXT files (*.txt);; All (*)", 
														0, QFileDialog::DontUseNativeDialog);

	if(qstrFileName.size() != 0)
	{
		m_pSourceFileEdit->setText(qstrFileName);
	}
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              void BrowseDestFileClicked() \n
 *
 *   \par Purpose:
 * 				Handle "BrowseDestFile" button \n
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
 * 				private SLOTE \n
 *
 *******************************************************************************
 */
void CWdgFileNamesReader::BrowseDestFileClicked()
{
    QString qstrFileName = QFileDialog::getOpenFileName(0, "Select file", "", "TXT files (*.txt);; CSV files (*.csv);; All (*)",
														0, QFileDialog::DontUseNativeDialog);
	
	if(qstrFileName.size() != 0)
	{
		m_pDestFileEdit->setText(qstrFileName);
	}
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              BOOL GenerateDestFileNameFromSource(std::string& strSourceFileName, std::string* pstrDestFileName) \n
 *
 *   \par Purpose:
 * 				Generate destination file name from source file name \n
 *
 *   \par Inputs:
 * 				crstrSourceFileName - const reference to source file name \n
 *				std::string* pstrDestFileName - pointer to destination file name \n
 *
 *   \par Outputs:
 * 				std::string* pstrDestFileName - pointer to destination file name \n
 *
 *   \par Returns:
 * 				TRUE \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
BOOL CWdgFileNamesReader::GenerateDestFileNameFromSource(const std::string& crstrSourceFileName, std::string* pstrDestFileName)
{
	size_t zSize;
	InlineFileType Source_FT = GetExtension(crstrSourceFileName);
	
	zSize = crstrSourceFileName.size();
	
	if(Source_FT == IFT_UNKNOWN)
	{
		pstrDestFileName->clear();
		pstrDestFileName->append(crstrSourceFileName.c_str(), zSize);
		
		if(m_S8Parent == 1)
		{
			pstrDestFileName->append(".csv");
		}	
	}
	
	else if(Source_FT == IFT_TXT)
	{
		zSize -= 4;
		
		pstrDestFileName->clear();
		pstrDestFileName->append(crstrSourceFileName.c_str(), zSize);
		
		if(m_S8Parent == 1)
		{
			pstrDestFileName->append(".csv");
		}
		
		else if(m_S8Parent == 2)
		{
			pstrDestFileName->append("(1).txt");
		}
	}
	
	else if(Source_FT == IFT_CSV)
	{
		zSize -= 4;
		
		pstrDestFileName->clear();
		pstrDestFileName->append(crstrSourceFileName.c_str(), zSize);
		
		if(m_S8Parent == 1)
		{
			pstrDestFileName->append(".txt");
		}
		
		else if(m_S8Parent == 2)
		{
			pstrDestFileName->append("(1).csv");
		}
	}
	
	return TRUE;
}


/**
 *******************************************************************************
 *
 *   \par Name:
 *              void SourceFileEditor_handle(const QString&) \n
 *
 *   \par Purpose:
 * 				Handle SourceFileEdit content changing \n
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
 *				If destination file name is empty, source file name is placed 
 *				to destination file name as placeholder text \n
 *
 *******************************************************************************
 */
void CWdgFileNamesReader::SourceFileEditor_handle(const QString&)
{
	if(m_pDestFileEdit->text().size() == 0)
	{
		std::string strDestFileName;
		GenerateDestFileNameFromSource(m_pSourceFileEdit->text().toStdString(), &strDestFileName);
		
		m_pDestFileEdit->setPlaceholderText(QString(strDestFileName.c_str()));
	}
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              void DestFileEditor_handle(bool bHasFocus) \n
 *
 *   \par Purpose:
 * 				Handle focus swithing to destination file nema edit \n
 *
 *   \par Inputs:
 * 				bool bHasFocus \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 *				If destination file name has placeholder text, the placeholder text 
 *				switches to real text and became selected \n
 *
 *******************************************************************************
 */
void CWdgFileNamesReader::DestFileEditor_handle(bool bHasFocus)
{
	if(bHasFocus)
	{
		if(m_pDestFileEdit->placeholderText().size() == 0)
		{
			return;
		}
		
		if(m_pDestFileEdit->placeholderText().size() > 0)
		{
			m_pDestFileEdit->setText(m_pDestFileEdit->placeholderText());
			m_pDestFileEdit->setPlaceholderText("");
			m_pDestFileEdit->selectAll();
		}
	}
}

} /* End of namespace VISUALIZATION */
