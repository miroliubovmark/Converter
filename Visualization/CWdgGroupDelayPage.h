#ifndef CWdgGroupDelayPage_H
#define CWdgGroupDelayPage_H

#include "VisualizationStable.h"

namespace Visualization
{

class CWdgGroupDelayPage : public QWidget
{
	Q_OBJECT

public:
	CWdgGroupDelayPage();
	~CWdgGroupDelayPage();
	
	void Init();
	void Connect(CMainWindow* pMainWindow);
	
private:	
	/** Pointer to Main Window instance */
	CMainWindow* m_pMainWindow;
	
	/** Pointer to FileNmaesReader widget */
	CWdgFileNamesReader* m_pWdgFileNamesReader;
	
	/** Button for group delay calculation */
	QPushButton* m_pCalculateButton;
	
	/** Warning box */
	CDlgWarning* m_pWarningBox;
	
private slots:
	void CalculateButtonClicked();
};

} /* End of namespace Visualization */

#endif // CWdgGroupDelayPage_H
