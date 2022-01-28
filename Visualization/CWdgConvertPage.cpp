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
	
	m_pWdgFileNamesReader = new CWdgFileNamesReader(1);

    /* Check boxes */
    m_pCheckIgnoreTXTheader = new QCheckBox("Ignore SOURCE header");
    m_pCheckAddCSVheader = new QCheckBox("Add DESTINATION header");

    m_pCheckIgnoreTXTheader->setCheckState(Qt::Checked);
    m_pCheckAddCSVheader->setCheckState(Qt::Checked);

    QHBoxLayout* pCheckBoxLayout = new QHBoxLayout;

    pCheckBoxLayout->addWidget(m_pCheckIgnoreTXTheader);
    pCheckBoxLayout->addWidget(m_pCheckAddCSVheader);
	
	QLayout* pMainLayout = new QVBoxLayout;
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

BOOL CWdgConvertPage::AddFileOptions(FileOptions& rSourceOptions, FileOptions& rDestOptions, InlineFileType Source_FT, InlineFileType Dest_FT)
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
	
	if(Source_FT == IFT_TXT)
	{
		rSourceOptions.FType = FT_TXT;
		rSourceOptions.s8Delimeter = '\t';
	}
	else if(Source_FT == IFT_CSV)
	{
		rSourceOptions.FType = FT_CSV;
		rSourceOptions.s8Delimeter = ',';
	}
	
	if(Dest_FT == IFT_CSV)
	{
		rDestOptions.FType = FT_CSV;
		rDestOptions.s8Delimeter = ',';
	}
	else if(Dest_FT == IFT_TXT)
	{
		rDestOptions.FType = FT_TXT;
		rDestOptions.s8Delimeter = '\t';
	}
	
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
	std::string strSourceFileName, strDestFileName;
	InlineFileType SourceFileType, DestFileType;
	
	m_pWdgFileNamesReader->GetSourceFileName(&strSourceFileName, &SourceFileType);
	m_pWdgFileNamesReader->GetDestFileName(&strDestFileName, &DestFileType);
	
	/* Unknown source file type */
	if(SourceFileType == IFT_UNKNOWN)
	{
		m_pWarningBox->SetMessage("\"" + strSourceFileName + "\" - extension unknown", WarningStatus::Warning);
		m_pWarningBox->Init();
		m_pMainWindow->SetStatusBar("\"" + strSourceFileName + "\" - extension unknown");
		
		return;
	}
	
	/* Add destination file extension */
	if(DestFileType == IFT_UNKNOWN)
	{
		/* TXT -> CSV */
		if(SourceFileType == IFT_TXT)
		{
			strDestFileName += ".csv";
		}
		
		/* CSV -> TXT */
		if(SourceFileType == IFT_CSV)
		{
			strDestFileName += ".txt";
		}
	}
	
	/* Convertion validation */
	if(SourceFileType == DestFileType)
	{
		m_pWarningBox->SetMessage("Invalid conversion", WarningStatus::Warning);
		m_pWarningBox->Init();
		m_pMainWindow->SetStatusBar("Invalid conversion");
	}

	/* Create file options */
	FileOptions SourceOptions, DestOptions;
	AddFileOptions(SourceOptions, DestOptions, SourceFileType, DestFileType);
	
	/* Convert */
	CConverter Converter;
	
	/* Error code */
	ErrorCode Code;
	
	if((SourceFileType == IFT_TXT) && (DestFileType == IFT_CSV))
	{
		Code = Converter.TXTtoCSV(strSourceFileName, strDestFileName, SourceOptions, DestOptions, false);
	}
    
	if((SourceFileType == IFT_CSV) && (DestFileType == IFT_TXT))
	{
		Code = Converter.CSVtoTXT(strSourceFileName, strDestFileName, SourceOptions, DestOptions, false);
	}
	
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
}


} /* End of namespace VISUALIZATION */
