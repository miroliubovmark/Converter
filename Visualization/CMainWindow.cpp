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
	
	/* Stacked widget and Combo box */
	m_pWdgConvertPage = new CWdgConvertPage; 
	m_pWdgGroupDelayPage = new CWdgGroupDelayPage;
	
	m_pWdgConvertPage->Connect(this);
	m_pWdgGroupDelayPage->Connect(this);
//	m_pStackedWidget = new QStackedWidget;
	
//	m_pStackedWidget->addWidget(m_pWdgConvertPage);
//	m_pStackedWidget->addWidget(m_pWdgGroupDelayPage);
	
	m_pTabPages = new QTabWidget;
	
	m_pTabPages->addTab(m_pWdgConvertPage, "Conver");
	m_pTabPages->addTab(m_pWdgGroupDelayPage, "Group delay");
	
//	m_pBoxPages = new QComboBox;
//	m_pBoxPages->addItem("Converter");
//	m_pBoxPages->addItem("Group delay");
	
	/* Connect Combo box to stacked widget */
	//connect(m_pBoxPages, QOverload<int>::of(&QComboBox::activated), m_pStackedWidget, &QStackedWidget::setCurrentIndex);
	
	QVBoxLayout* pMainLayout = new QVBoxLayout;
//	pMainLayout->addWidget(m_pBoxPages);
//	pMainLayout->addWidget(m_pStackedWidget);
	
	pMainLayout->addWidget(m_pTabPages);
	
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


} /* End of namespace VISUALIZATION */
