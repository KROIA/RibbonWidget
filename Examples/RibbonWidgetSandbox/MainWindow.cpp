#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_ribbon = new RibbonImpl(ui.ribbon_widget);

	ui.pushButton->setIcon(RibbonWidget::DefaultIconLoader::getIcon("arrowCClockwise"));
	//ui.pushButton->setIcon(QIcon(":/icons/live_folder_2.png"));
}

MainWindow::~MainWindow()
{
	delete m_ribbon;
}
