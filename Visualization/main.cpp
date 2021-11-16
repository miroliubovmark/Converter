#include "VisualizationStable.h"

#define AppName "Converter"

using namespace Visualization;

int main(int argc, char* argv[])
{
	QApplication QApp(argc, argv);
	QApp.setApplicationName(AppName);
	
	CMainWindow MainWindow;
	
	MainWindow.show();
	
	QApp.exec();
	
	return 0;
}
