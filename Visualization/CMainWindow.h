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

private:
	void SetStatusBar(std::string strMessage);
	void ClearStatusBar();

    void Trim(std::string* str);
	
	BOOL GenerateDestFileNameFromSource(const std::string& crstrSourceFileName, std::string* pstrDestFileName);
	BOOL AddFileOptions(FileOptions& rSourceOptions, FileOptions& rDestOptions);
	
	/** Main widget */
	QWidget* m_pMainWidget;
	
	QFont* m_pFont;
	
	/** QFontMetrics instance */
	QFontMetrics* m_pFontMetrics;
	
	/** Source file label */
	QLabel* m_pSourceFileLabel;
	
	/** Destination file label */
	QLabel* m_pDestFileLabel;
	
	/** Source file name Line Edit */
	QLineEdit* m_pSourceFileEdit;
	
	/** Destination file name Line Edit */
	CLineEdit* m_pDestFileEdit;
	
	/** Browse source file button */
	QPushButton* m_pBrowseSourceFileButton;
	
	/** Browse destination file button */
	QPushButton* m_pBrowseDestFileButton;
	
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
	void BrowseSourceFileClicked();
	void BrowseDestFileClicked();
	
	void SourceFileEditor_handle(const QString&);
	void DestFileEditor_handle(bool bHasFocus);
};

} /* End of namespace Visualization */

#endif // CMainWindow_H
