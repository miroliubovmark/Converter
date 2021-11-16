#include "CDlgWarning.h"

namespace Visualization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CDlgWarning::CDlgWarning() \n
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
CDlgWarning::CDlgWarning()
	: QMessageBox(NULL)
{
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CDlgWarning::~CDlgWarning() \n
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
CDlgWarning::~CDlgWarning()
{
}

void CDlgWarning::Init()
{
	show();
}

BOOL CDlgWarning::SetMessage(std::string strMessage, WarningStatus WS)
{
	m_qstrMessage = strMessage.c_str();
	m_Status = WS;

	UpdateSettings();
	
	return TRUE;
}

BOOL CDlgWarning::UpdateSettings()
{
	/* Update Message */
	setText(m_qstrMessage);
	
	
	/* Update Window Title and Icon */
	switch(m_Status)
	{
	case WarningStatus::None:
	{
		break;
	}
	
	case WarningStatus::Warning:
	{
		setIcon(QMessageBox::Warning);
		setWindowTitle("Warning");
		
		break;
	}

	case WarningStatus::Error:
	{
		setIcon(QMessageBox::Critical);
		setWindowTitle("Error");
	}

	default:
	{
		return FALSE;
	}
	}

	return TRUE;
}

} /* End of namespace VISUALIZATION */
