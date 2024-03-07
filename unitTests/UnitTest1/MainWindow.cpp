#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_ribbon = new RibbonImpl(ui.ribbon_widget);

	ui.pushButton->setIcon(RibbonWidget::DefaultIconLoader::getIcon("arrowCClockwise"));
	//ui.pushButton->setIcon(QIcon(":/icons/live_folder_2.png"));

	auto buttons = m_ribbon->workButtons();
	connect(buttons.open, &QToolButton::clicked, this, &MainWindow::onOpenClicked);
	connect(buttons.save, &QToolButton::clicked, this, &MainWindow::onSaveClicked);
}

MainWindow::~MainWindow()
{
	delete m_ribbon;
}

void MainWindow::onOpenClicked()
{
	auto buttons = m_ribbon->workButtons();
	buttons.open->enableLoadingCircle(!buttons.open->isLoadingCircleEnabled());
}
void MainWindow::onSaveClicked()
{
	auto buttons = m_ribbon->workButtons();
	buttons.save->enableLoadingCircle(!buttons.save->isLoadingCircleEnabled());
}