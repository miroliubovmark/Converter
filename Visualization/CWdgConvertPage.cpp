#include "CWdgConvertPage.h"

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CWdgConvertPage::CWdgConvertPage() \n
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
CWdgConvertPage::CWdgConvertPage()
	: QWidget(NULL)
	, m_pMainWindow(NULL)
{
	m_pWarningBox = new CDlgWarning;
		
	m_pConvertButton = new QPushButton("Convert");
	m_pConvertButton->setMaximumSize(m_pConvertButton->sizeHint());
	connect(m_pConvertButton, SIGNAL(clicked()), this, SLOT(ConvertButtonClicked()));
	
	m_pWdgFileNamesReader = new CWdgFileNamesReader;

    /* Check boxes */
    m_pCheckIgnoreTXTheader = new QCheckBox("Ignore TXT header");
    m_pCheckAddCSVheader = new QCheckBox("Add CSV header");

    m_pCheckIgnoreTXTheader->setCheckState(Qt::Checked);
    m_pCheckAddCSVheader->setCheckState(Qt::Checked);

    QHBoxLayout* pCheckBoxLayout = new QHBoxLayout;

    pCheckBoxLayout->addWidget(m_pCheckIgnoreTXTheader);
    pCheckBoxLayout->addWidget(m_pCheckAddCSVheader);
	
	QLayout* pMainLayout = new QVBoxLayout;
	//pMainLayout->addItem(pGridLayout);
	pMainLayout->addWidget(m_pWdgFileNamesReader);
	pMainLayout->setSpacing(20);
    pMainLayout->addItem(pCheckBoxLayout);
    pMainLayout->setSpacing(20);
	pMainLayout->addWidget(m_pConvertButton);
	pMainLayout->setAlignment(m_pConvertButton, Qt::AlignCenter);
	
	setLayout(pMainLayout);
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CWdgConvertPage::~CWdgConvertPage() \n
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
CWdgConvertPage::~CWdgConvertPage()
{
}

void CWdgConvertPage::Connect(CMainWindow* pMainWindow)
{
	m_pMainWindow = pMainWindow;
}

void CWdgConvertPage::Init()
{
	show();
}

BOOL CWdgConvertPage::AddFileOptions(FileOptions& rSourceOptions, FileOptions& rDestOptions)
{
	if(m_pCheckIgnoreTXTheader->checkState() == Qt::Checked)
	{
		rSourceOptions.HeaderOpt = TRUE;
	}
	else
	{
		rSourceOptions.HeaderOpt = FALSE;
	}
	
	if(m_pCheckAddCSVheader->checkState() == Qt::Checked)
	{
		rDestOptions.HeaderOpt = TRUE;
	}
	else
	{
		rDestOptions.HeaderOpt = FALSE;
	}
	
	rSourceOptions.FType = FT_TXT;
	rSourceOptions.s8Delimeter = '\t';
	
	rDestOptions.FType = FT_CSV;
	rDestOptions.s8Delimeter = ',';
	
	return TRUE;
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
void CWdgConvertPage::ConvertButtonClicked()
{
	/** Name of source file */
	std::string strSourceFileName(m_pWdgFileNamesReader->GetSourceFileText().toStdString());
	
	/** Name of destination file */
	std::string strDestFileName;
	
	m_pMainWindow->ClearStatusBar();
	
	if(strSourceFileName.empty())
	{
		m_pMainWindow->SetStatusBar("Warning: TXT file name is empty");
		
		m_pWarningBox->SetMessage("TXT file name is empty", WarningStatus::Warning);
		m_pWarningBox->Init();
		
		return;
	}
	
	if((m_pWdgFileNamesReader->GetDestFileText().size() == 0) && (m_pWdgFileNamesReader->GetDestPlaceholder().size() == 0))
	{
		m_pMainWindow->SetStatusBar("Warning: CSV file name is empty");
		
		m_pWarningBox->SetMessage("CSV file name is empty", WarningStatus::Warning);
		m_pWarningBox->Init();
		
		return;
	}
	
	if(m_pWdgFileNamesReader->GetDestFileText().size() != 0)
	{
		strDestFileName = m_pWdgFileNamesReader->GetDestFileText().toStdString();
	}
	else
	{
		strDestFileName = m_pWdgFileNamesReader->GetDestPlaceholder().toStdString();
		m_pWdgFileNamesReader->SetDestText(strDestFileName);
		m_pWdgFileNamesReader->SetDestPlaceholder("");
	}

    CConverter::Trim(&strSourceFileName);
    CConverter::Trim(&strDestFileName);

    /* Add CSV extanion */
    size_t zPos_csv = strDestFileName.find(".csv");

    if((zPos_csv == std::string::npos) || (zPos_csv != strDestFileName.size() - 4))
    {
        strDestFileName += ".csv";
    }

    /* Create file options */
	FileOptions SourceOptions, DestOptions;
	
	AddFileOptions(SourceOptions, DestOptions);
	
	/* Convert */
	CConverter Converter;
	
    ErrorCode Code = Converter.TXTtoCSV(strSourceFileName, strDestFileName, SourceOptions, DestOptions, false);
	
	switch (Code)
	{
	case EC_OK:
	{
		m_pMainWindow->SetStatusBar("Converted to " + strDestFileName);
		break;
	}
		
	case EC_SourceFileDoesNotExist:
	{
		m_pMainWindow->SetStatusBar("File \"" + strSourceFileName + "\" does not exist");
		m_pWarningBox->SetMessage("File \"" + strSourceFileName + "\" does not exist", WarningStatus::Warning);
		m_pWarningBox->Init();
		
		break;
	}

	case EC_DestFileAlreadyExist:
	{
        m_pMainWindow->SetStatusBar("Destination \"" + strDestFileName + "\" already exists");
        m_pWarningBox->SetMessage("Destination \"" + strDestFileName + "\" already exists", WarningStatus::Warning);
		m_pWarningBox->Init();

		break;
	}

	default:
	{
		m_pMainWindow->SetStatusBar("Unknown error");
		m_pWarningBox->SetMessage("Unknown error", WarningStatus::Error);
		m_pWarningBox->Init();
	}
	}
	
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


} /* End of namespace VISUALIZATION */
