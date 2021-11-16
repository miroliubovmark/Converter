#ifndef CDlgWarning_H
#define CDlgWarning_H

#include "VisualizationStable.h"

namespace Visualization
{

enum WarningStatus
{
	None = 0x00,
	Warning,
	Error
};

class CDlgWarning : protected QMessageBox
{
	Q_OBJECT

public:
	CDlgWarning();
	~CDlgWarning();
	
	void Init();
	BOOL SetMessage(std::string strMessage, WarningStatus WS = WarningStatus::None);
	
private:
	BOOL UpdateSettings();
	
	/** QString message */
	QString m_qstrMessage;
	
	/** Message warning status */
	WarningStatus m_Status;
	
};

} /* End of namespace Visualization */

#endif // CDlgWarning_H
