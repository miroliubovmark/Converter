#ifndef CWdgFileNamesReader_H
#define CWdgFileNamesReader_H

#include "VisualizationStable.h"

namespace Visualization
{

class CWdgFileNamesReader : public QWidget
{
	Q_OBJECT

public:
	CWdgFileNamesReader();
	~CWdgFileNamesReader();
	
	void Init();
	
	QString GetSourceFileText();
	QString GetDestFileText();
	QString GetSourcePlaceholder();
	QString GetDestPlaceholder();
	
	BOOL SetSourceText(const std::string &crstrText);
	BOOL SetSourceText(const QString& crqstrText);
	BOOL SetDestText(const std::string &crstrText);
	BOOL SetDestText(const QString& crqstrText);
	BOOL SetSourcePlaceholder(const std::string &crstrPlaceholder);
	BOOL SetDestPlaceholder(const std::string &crstrPlaceholder);
	
private:	
	/** Pointer to Main Window instance */
	CMainWindow* m_pMainWindow;
	
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
	
private slots:
	void BrowseSourceFileClicked();
	void BrowseDestFileClicked();
	
	void SourceFileEditor_handle(const QString&);
	void DestFileEditor_handle(bool bHasFocus);
	
};

} /* End of namespace Visualization */

#endif // CWdgFileNamesReader_H
