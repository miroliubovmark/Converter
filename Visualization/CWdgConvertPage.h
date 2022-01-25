#ifndef CWdgConvertPage_H
#define CWdgConvertPage_H

#include "VisualizationStable.h"

namespace Visualization
{

class CWdgConvertPage : public QWidget
{
	Q_OBJECT

public:
	CWdgConvertPage();
	~CWdgConvertPage();
	
	void Init();
	void Connect(CMainWindow* pMainWindow);
	
private:	
	BOOL AddFileOptions(FileOptions& rSourceOptions, FileOptions& rDestOptions);
	
	/** Pointer to Main Window instance */
	CMainWindow* m_pMainWindow;
	
	/** File names reader */
	CWdgFileNamesReader* m_pWdgFileNamesReader;
	
	/** Convert button */
	QPushButton* m_pConvertButton;

    /** Ignore TXT header check box */
    QCheckBox* m_pCheckIgnoreTXTheader;

    /** Add CSV header check box */
    QCheckBox* m_pCheckAddCSVheader;
		
	/** Warning box */
	CDlgWarning* m_pWarningBox;
	
private slots:
	void ConvertButtonClicked();	
};

} /* End of namespace Visualization */

#endif // CWdgConvertPage_H
