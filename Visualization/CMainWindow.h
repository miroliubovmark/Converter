#ifndef CMainWindow_H
#define CMainWindow_H

#include "VisualizationStable.h"

#define LineEdit_Length (35)

namespace Visualization
{

class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow();
	~CMainWindow();
	
	void SetStatusBar(std::string strMessage);
	void ClearStatusBar();

private:	
	/** Main widget */
	QWidget* m_pMainWidget;
	
	/** Stacked widget */
	QStackedWidget* m_pStackedWidget;
	
	/** Combo box for pages switching */
	QComboBox* m_pBoxPages;
	
	/** Tab widget for pages switching */
	QTabWidget* m_pTabPages;
	
	/** Convert page */
	CWdgConvertPage* m_pWdgConvertPage;
	
	/** Group delay page */
	CWdgGroupDelayPage* m_pWdgGroupDelayPage;
};

} /* End of namespace Visualization */

#endif // CMainWindow_H
