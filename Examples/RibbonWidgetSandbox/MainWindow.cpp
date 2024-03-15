#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_ribbon = new RibbonImpl(ui.ribbon_widget);

	ui.pushButton->setIcon(RibbonWidget::DefaultIconLoader::getIcon(":/icons/arrowCClockwise.png"));
	//ui.pushButton->setIcon(QIcon(":/icons/live_folder_2.png"));

	auto buttons = m_ribbon->workButtons();
	connect(buttons.open, &QToolButton::clicked, this, &MainWindow::onOpenClicked);
	connect(buttons.save, &QToolButton::clicked, this, &MainWindow::onSaveClicked);

	connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTimerFinished);
	m_timer.start(50);
}

MainWindow::~MainWindow()
{
	delete m_ribbon;
}

void MainWindow::onOpenClicked()
{
	auto buttons = m_ribbon->workButtons();
	buttons.open->enableLoadingCircle(!buttons.open->isLoadingCircleEnabled());
	buttons.open->setLoadingCircleAngle(0);
}
void MainWindow::onSaveClicked()
{
	auto buttons = m_ribbon->workButtons();
	buttons.save->enableLoadingCircle(!buttons.save->isLoadingCircleEnabled());
	buttons.save->setLoadingCircleAngle(0);
	buttons.save->setLoadingCircleSpeed(-0.2);
}
void MainWindow::onTimerFinished()
{
	RibbonImpl::ViewButtons buttons = m_ribbon->viewButtons();
	static float progress = 0.0f;
	progress += 0.05f;
	if (progress > 1.0f)
		progress = 0.0f;
	//buttons.view1->enableLoadingCircle(false);
	buttons.view2->setProgress(progress);
	//buttons.view3->enableLoadingCircle(false);
}