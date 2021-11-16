#ifndef CLineEdit_H
#define CLineEdit_H

#include "VisualizationStable.h"

namespace Visualization
{

class CLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	CLineEdit(QWidget *pParent = NULL);
	~CLineEdit();
	
signals:
	void focussed(bool HasFocus);
	
protected:
	virtual void focusInEvent(QFocusEvent* pEvent);
	//virtual void focusOutEvent(QFocusEvent* pEvent);
	
};

} /* End of namespace Visualization */

#endif // CLineEdit_H
