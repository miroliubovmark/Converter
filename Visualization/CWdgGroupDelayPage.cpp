#include "CWdgGroupDelayPage.h"

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CWdgGroupDelayPage::CWdgGroupDelayPage() \n
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
CWdgGroupDelayPage::CWdgGroupDelayPage()
	: QWidget(NULL)
{
	
	m_pWdgFileNamesReader = new CWdgFileNamesReader;
	
	m_pCalculateButton = new QPushButton("Calculate");
	m_pCalculateButton->setMaximumSize(m_pCalculateButton->sizeHint());
	connect(m_pCalculateButton, SIGNAL(clicked()), this, SLOT(CalculateButtonClicked()));
	
	QLayout* pMainLayout = new QVBoxLayout;
	
	pMainLayout->addWidget(m_pWdgFileNamesReader);
	pMainLayout->addWidget(m_pCalculateButton);
	
	pMainLayout->setAlignment(m_pCalculateButton, Qt::AlignCenter);
	
	setLayout(pMainLayout);
	
	m_pWarningBox = new CDlgWarning;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CWdgGroupDelayPage::~CWdgGroupDelayPage() \n
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
CWdgGroupDelayPage::~CWdgGroupDelayPage()
{
}

void CWdgGroupDelayPage::Connect(CMainWindow* pMainWindow)
{
	m_pMainWindow = pMainWindow;
}

void CWdgGroupDelayPage::Init()
{
	show();
}

void CWdgGroupDelayPage::CalculateButtonClicked()
{
	/** Name of source file */
	std::string strSourceFileName(m_pWdgFileNamesReader->GetSourceFileText().toStdString());
	
	/** Name of destination file */
	std::string strDestFileName;
	
	m_pMainWindow->ClearStatusBar();
	
	if(strSourceFileName.empty())
	{
		m_pMainWindow->SetStatusBar("Warning: SOURCE file name is empty");
		
		m_pWarningBox->SetMessage("SOURCE file name is empty", WarningStatus::Warning);
		m_pWarningBox->Init();
		
		return;
	}
	
	if((m_pWdgFileNamesReader->GetDestFileText().size() == 0) && (m_pWdgFileNamesReader->GetDestPlaceholder().size() == 0))
	{
		m_pMainWindow->SetStatusBar("Warning: DESTINATION file name is empty");
		
		m_pWarningBox->SetMessage("DESTINATION file name is empty", WarningStatus::Warning);
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
	
	CConverter Converter;
	
	/* Here should be code for calculating group delay */
	
	/* strSourceFileName - name of source file
	 * strDestFileName - name of destination file
	 */
	
	
}

} /* End of namespace VISUALIZATION */
