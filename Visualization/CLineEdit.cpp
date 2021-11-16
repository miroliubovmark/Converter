#include "CLineEdit.h"

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CLineEdit::CLineEdit() \n
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
CLineEdit::CLineEdit(QWidget* pParent)
	: QLineEdit(pParent)
{
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CLineEdit::~CLineEdit() \n
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
CLineEdit::~CLineEdit()
{
}

void CLineEdit::focusInEvent(QFocusEvent* pEvent)
{
	QLineEdit::focusInEvent(pEvent);
	emit(focussed(TRUE));
}

} /* End of namespace VISUALIZATION */
