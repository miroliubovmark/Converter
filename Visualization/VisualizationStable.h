#ifndef	VISUALIZATIONSTABLE_H
#define VISUALIZATIONSTABLE_H

#include <vector>

#include "stdint.h"
#include "stdio.h"
#include "iostream"
#include <math.h>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>

#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QFont>
#include <QtCore>
#include <QMessageBox>

namespace Visualization
{
	class CDlgWarning;
	class CLineEdit;
	class CMainWindow;
	class CConverter;
	
	template<class TX, class TY> class CDataSeries;

    struct FileOptions;
} /* End of namespace Tools */

#include "UBaseTypes.h"
#include "CDlgWarning.h"
#include "CLineEdit.h"
#include "CMainWindow.h"
#include "CMathUtils.h"
#include "CConverter.h"

#endif /* VISUALIZATIONSTABLE_H */
