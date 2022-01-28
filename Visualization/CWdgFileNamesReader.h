#ifndef CWdgFileNamesReader_H
#define CWdgFileNamesReader_H

#include "VisualizationStable.h"



namespace Visualization
{

class CWdgFileNamesReader : public QWidget
{
	Q_OBJECT

public:
	CWdgFileNamesReader(S8 s8Parent = 0);
	~CWdgFileNamesReader();
	
	void Init();
	
	BOOL GetSourceFileName(std::string* pstrSourceFileName, InlineFileType* pFT);
	BOOL GetDestFileName(std::string* pstrDestFileName, InlineFileType *pFT);
	
	InlineFileType GetExtension(const std::string& crstrText);
	
private:
	BOOL GenerateDestFileNameFromSource(const std::string& crstrSourceFileName, std::string* pstrDestFileName);
	
	/** Parent widget:
	 * 0 - Unknown
	 * 1 - ConvertPage
	 * 2 - GroupDelay
	 */
	S8 m_S8Parent = 0;
	
	/** Pointer to Main Window instance */
	CMainWindow* m_pMainWindow;
	
	/** Pointer to QFont instance */
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
	
	InlineFileType IFT_Source;
	
	InlineFileType IFT_Dest;
	
private slots:
	void BrowseSourceFileClicked();
	void BrowseDestFileClicked();
	
	void SourceFileEditor_handle(const QString&);
	void DestFileEditor_handle(bool bHasFocus);
	
};

} /* End of namespace Visualization */

#endif // CWdgFileNamesReader_H
