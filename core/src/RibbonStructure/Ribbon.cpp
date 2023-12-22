#include "RibbonStructure/Ribbon.h"
#include "RibbonStructure/RibbonTab.h"
#include <QApplication>
#include <QLayout>
#include <QFrame>

namespace RibbonWidget
{
	Ribbon::Ribbon(QWidget* parent)
		: m_tabWidget(parent)
	{
		setup();
	}
	Ribbon::Ribbon(const std::vector<RibbonTab*>& tabs, QWidget* parent)
		: m_tabWidget(parent)
	{
		setup();
		for (auto tab : tabs)
		{
			addTab(tab);
		}
	}
	Ribbon::~Ribbon()
	{

	}


	void Ribbon::addTab(RibbonTab* tab)
	{
		m_tabWidget.addTab(tab, tab->getIcon(), tab->getTitle());
		connect(tab, &RibbonTab::titleChanged, this, &Ribbon::onTabTitleChanged);
		connect(tab, &RibbonTab::iconChanged, this, &Ribbon::onTabIconChanged);
	}
	QTabWidget* Ribbon::getTabWidget()
	{
		return &m_tabWidget;
	}
	const QTabWidget* Ribbon::getTabWidget() const
	{
		return &m_tabWidget;
	}

	void Ribbon::setup()
	{
		QLayout* layout = nullptr;
		if(m_tabWidget.parentWidget())
			layout = m_tabWidget.parentWidget()->layout();
		if (!layout)
			layout = new QVBoxLayout;
		layout->setContentsMargins(0, 0, 0, 0);
		m_tabWidget.parentWidget()->setLayout(layout);
		layout->addWidget(&m_tabWidget);

		// Creating a horizontal line using QFrame
		QFrame* horizontalLine = new QFrame();
		horizontalLine->setFrameShape(QFrame::HLine);
		horizontalLine->setFrameShadow(QFrame::Sunken);

		layout->addWidget(horizontalLine);

		
		//m_tabWidget.setMinimumHeight(100);
		if (m_tabWidget.parentWidget())
		{
			m_tabWidget.parentWidget()->setFixedHeight(130);
		}


		// Determine default colors
		QColor bg = qApp->palette().color(QPalette::Window);
		QColor mid = qApp->palette().color(QPalette::Mid);

		// Note: the order in which the background/palette/stylesheet functions are
		// called does matter. Should be same as in Qt designer.
		m_tabWidget.setAutoFillBackground(true);

		// Set stylesheet
		QString styleSheetText = QString(
			"QTabWidget::pane {"
			"  border-top: 1px solid rgb(%4, %5, %6);"
			"  position: absolute;"
			"  top: -1px;"
			"}"
			""
			"QTabBar::tab {"
			"  padding-top: 5px;"
			"  padding-bottom: 5px;"
			"  padding-left: 10px;"
			"  padding-right: 10px;"
			"  margin-top: 1px;"
			"}"
			""
			"QTabBar::tab::!selected {"
			"  border-bottom: 1px solid rgb(%4, %5, %6);"
			"  background-color:#ffffff;"
			"}"
			""
			"QTabBar::tab:selected {"
			"  background-color: rgb(%1, %2, %3);"
			"  border-top: 1px solid rgb(%4, %5, %6);"
			"  border-right: 1px solid rgb(%4, %5, %6);"
			"  border-left: 1px solid rgb(%4, %5, %6);"
			"  border-bottom: 1px solid rgb(%1, %2, %3);"
			"}"
			""
			"QTabBar::tab:hover"
			"{"
			"  background-color: rgb(205, 232, 255);"
			"}"
			""
			"QTabBar::tab:selected:hover {"
			"  background-color: rgb(%1, %2, %3);"
			"}"
		).arg(bg.red()).arg(bg.green()).arg(bg.blue())
			.arg(mid.red()).arg(mid.green()).arg(mid.blue());

		m_tabWidget.setStyleSheet(styleSheetText);

		// Set background color
		QPalette pal = m_tabWidget.palette();
		pal.setColor(QPalette::Window, Qt::white);
		m_tabWidget.setPalette(pal);
	}

	void Ribbon::onTabTitleChanged(const QString& title)
	{
		RibbonTab* tab = qobject_cast<RibbonTab*>(sender());
		if (!tab)
			return;
		int index = m_tabWidget.indexOf(tab);
		m_tabWidget.setTabText(index, title);
	}
	void Ribbon::onTabIconChanged(const QIcon& icon)
	{
		RibbonTab* tab = qobject_cast<RibbonTab*>(sender());
		if (!tab)
			return;
		int index = m_tabWidget.indexOf(tab);
		m_tabWidget.setTabIcon(index, icon);
	}

	/*
	void Ribbon::addTab(const QString& tabName)
	{
		// Note: superclass QTabWidget also has a function addTab()
		RibbonTab* ribbonTab = new RibbonTab;
		QTabWidget::addTab(ribbonTab, tabName);
	}

	void Ribbon::addTab(const QIcon& tabIcon, const QString& tabName)
	{
		// Note: superclass QTabWidget also has a function addTab()
		RibbonTab* ribbonTab = new RibbonTab;
		QTabWidget::addTab(ribbonTab, tabIcon, tabName);
	}

	void Ribbon::removeTab(const QString& tabName)
	{
		// Find Ribbon tab
		for (int i = 0; i < count(); i++)
		{
			if (tabText(i).toLower() == tabName.toLower())
			{
				// Remove tab
				QWidget* tab = QTabWidget::widget(i);
				QTabWidget::removeTab(i);
				delete tab;
				break;
			}
		}
	}

	void Ribbon::addGroup(const QString& tabName, const QString& groupName)
	{
		// Find Ribbon tab
		QWidget* tab = nullptr;
		for (int i = 0; i < count(); i++)
		{
			if (tabText(i).toLower() == tabName.toLower())
			{
				tab = QTabWidget::widget(i);
				break;
			}
		}

		if (tab != nullptr)
		{
			// Tab found
			// Add Ribbon group
			RibbonTab* ribbonTab = qobject_cast<RibbonTab*>(tab);
			RibbonButtonGroup* group = new RibbonButtonGroup(ribbonTab);
			ribbonTab->addGroup(group);
		}
		else
		{
			// Tab not found
			// Create tab
			addTab(tabName);

			// Add Ribbon group
			addGroup(tabName, groupName);
		}
	}

	void Ribbon::addButton(const QString& tabName, const QString& groupName, RibbonButton* button)
	{
		// Find Ribbon tab
		QWidget* tab = nullptr;
		for (int i = 0; i < count(); i++)
		{
			if (tabText(i).toLower() == tabName.toLower())
			{
				tab = QTabWidget::widget(i);
				break;
			}
		}

		if (tab != nullptr)
		{
			// Tab found
			// Add Ribbon button
			RibbonTab* ribbonTab = static_cast<RibbonTab*>(tab);
			ribbonTab->addButton(groupName, button);
		}
		else
		{
			// Tab not found.
			// Create tab
			addTab(tabName);

			// Add Ribbon button
			addButton(tabName, groupName, button);
		}
	}

	void Ribbon::removeButton(const QString& tabName, const QString& groupName, RibbonButton* button)
	{
		// Find Ribbon tab
		QWidget* tab = nullptr;
		for (int i = 0; i < count(); i++)
		{
			if (tabText(i).toLower() == tabName.toLower())
			{
				tab = QTabWidget::widget(i);
				break;
			}
		}

		if (tab != nullptr)
		{
			// Tab found
			// Remove Ribbon button
			RibbonTab* ribbonTab = static_cast<RibbonTab*>(tab);
			ribbonTab->removeButton(groupName, button);

			if (ribbonTab->groupCount() == 0)
			{
				removeTab(tabName);
			}
		}
	}*/
}