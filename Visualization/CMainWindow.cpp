#include "CMainWindow.h"

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CMainWindow::CMainWindow() \n
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
CMainWindow::CMainWindow()
	: QMainWindow(NULL)
{
	m_pMainWidget = new QWidget;
	m_pWarningBox = new CDlgWarning;
	
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
	
	m_pConvertButton = new QPushButton("Convert");
	m_pConvertButton->setMaximumSize(m_pConvertButton->sizeHint());
	connect(m_pConvertButton, SIGNAL(clicked()), this, SLOT(ConvertButtonClicked()));

    /* Check boxes */
    m_pCheckIgnoreTXTheader = new QCheckBox("Ignore TXT header");
    m_pCheckAddCSVheader = new QCheckBox("Add CSV header");

    m_pCheckIgnoreTXTheader->setCheckState(Qt::Checked);
    m_pCheckAddCSVheader->setCheckState(Qt::Checked);
	
	QGridLayout* pGridLayout = new QGridLayout;
	
	pGridLayout->addWidget(m_pSourceFileLabel, 0, 0, Qt::AlignRight);
	pGridLayout->addWidget(m_pSourceFileEdit, 0, 1);
	pGridLayout->addWidget(m_pBrowseSourceFileButton, 0, 2);
	
	pGridLayout->addWidget(m_pDestFileLabel, 1, 0, Qt::AlignRight);
	pGridLayout->addWidget(m_pDestFileEdit, 1, 1);
	pGridLayout->addWidget(m_pBrowseDestFileButton, 1, 2);
	
	pGridLayout->setHorizontalSpacing(20);

    QHBoxLayout* pCheckBoxLayout = new QHBoxLayout;

    pCheckBoxLayout->addWidget(m_pCheckIgnoreTXTheader);
    pCheckBoxLayout->addWidget(m_pCheckAddCSVheader);
	
	QLayout* pMainLayout = new QVBoxLayout;
	pMainLayout->addItem(pGridLayout);
	pMainLayout->setSpacing(20);
    pMainLayout->addItem(pCheckBoxLayout);
    pMainLayout->setSpacing(20);
	pMainLayout->addWidget(m_pConvertButton);
	pMainLayout->setAlignment(m_pConvertButton, Qt::AlignCenter);
	
	m_pMainWidget->setLayout(pMainLayout);
	
	setCentralWidget(m_pMainWidget);
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CMainWindow::~CMainWindow() \n
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
CMainWindow::~CMainWindow()
{
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              SetStatusBar(std::string strMessage) \n
 *
 *   \par Purpose:
 * 				Update status bar message \n
 *
 *   \par Inputs:
 * 				std::string strMessage - message \n
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
void CMainWindow::SetStatusBar(std::string strMessage)
{
	statusBar()->showMessage(strMessage.c_str());
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              ClearStatusBar() \n
 *
 *   \par Purpose:
 * 				Clear status bar \n
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
void CMainWindow::ClearStatusBar()
{
	statusBar()->showMessage("");
}

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
void CMainWindow::Trim(std::string* str)
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
 *              void ConvertButtonClicked() \n
 *
 *   \par Purpose:
 * 				Handle "Convert" button \n
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
void CMainWindow::ConvertButtonClicked()
{
	/** Name of source file */
	std::string strSourceFileName(m_pSourceFileEdit->text().toStdString());
	
	/** Name of destination file */
	std::string strDestFileName;
	
	ClearStatusBar();
	
	if(strSourceFileName.empty())
	{
		SetStatusBar("Warning: TXT file name is empty");
		
		m_pWarningBox->SetMessage("TXT file name is empty", WarningStatus::Warning);
		m_pWarningBox->Init();
		
		return;
	}
	
	if((m_pDestFileEdit->text().size() == 0) && (m_pDestFileEdit->placeholderText().size() == 0))
	{
		SetStatusBar("Warning: CSV file name is empty");
		
		m_pWarningBox->SetMessage("CSV file name is empty", WarningStatus::Warning);
		m_pWarningBox->Init();
		
		return;
	}
	
	if(m_pDestFileEdit->text().size() != 0)
	{
		strDestFileName = m_pDestFileEdit->text().toStdString();
	}
	else
	{
		strDestFileName = m_pDestFileEdit->placeholderText().toStdString();
		m_pDestFileEdit->setText(m_pDestFileEdit->placeholderText());
		m_pDestFileEdit->setPlaceholderText("");
	}

    Trim(&strSourceFileName);
    Trim(&strDestFileName);

    /* Add CSV extanion */
    size_t zPos_csv = strDestFileName.find(".csv");

    if((zPos_csv == std::string::npos) || (zPos_csv != strDestFileName.size() - 4))
    {
        strDestFileName += ".csv";
    }

    /* Create Convert options */
//    ConvertOptions CO;

//    if(m_pCheckIgnoreTXTheader->checkState() == Qt::Checked)
//    {
//        CO.IgnoreTXTheader = TRUE;
//    }
//    else
//    {
//        CO.IgnoreTXTheader = FALSE;
//    }

//    if(m_pCheckAddCSVheader->checkState() == Qt::Checked)
//    {
//        CO.AddCSVheader = TRUE;
//    }
//    else
//    {
//        CO.AddCSVheader = FALSE;
//    }

//	S32 s32Status;
//    s32Status = CConverter::s32ConvertTXTtoCSV(strSourceFileName, strDestFileName, &CO);

//	switch(s32Status)
//	{
//	case 0:
//	{
//		SetStatusBar("Converted to " + strDestFileName);
//		break;
//	}

//	case 1:
//	{
//		SetStatusBar("File \"" + strSourceFileName + "\" does not exist");
//		m_pWarningBox->SetMessage("File \"" + strSourceFileName + "\" does not exist", WarningStatus::Warning);
//		m_pWarningBox->Init();
		
//		break;
//	}

//	case 2:
//	{
//		SetStatusBar("Destination \"" + strDestFileName + "\" already exist");
//		m_pWarningBox->SetMessage("Destination \"" + strDestFileName + "\" already exist", WarningStatus::Warning);
//		m_pWarningBox->Init();
//		break;
//	}

//	default:
//	{
//		SetStatusBar("Unknown error");
//		m_pWarningBox->SetMessage("Unknown error", WarningStatus::Error);
//		m_pWarningBox->Init();
//	}
//	}
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
void CMainWindow::BrowseSourceFileClicked()
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
void CMainWindow::BrowseDestFileClicked()
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
BOOL CMainWindow::GenerateDestFileNameFromSource(const std::string& crstrSourceFileName, std::string* pstrDestFileName)
{	
	size_t zPos, zSize;
	zPos = crstrSourceFileName.find(".txt");
	
	if(zPos != std::string::npos)
	{
		zSize = zPos;
	}
	else
	{
		zSize = crstrSourceFileName.size();
	}
	
	pstrDestFileName->clear();
	pstrDestFileName->append(crstrSourceFileName.c_str(), zSize);
	
	pstrDestFileName->append(".csv");
	
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
void CMainWindow::SourceFileEditor_handle(const QString&)
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
void CMainWindow::DestFileEditor_handle(bool bHasFocus)
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
