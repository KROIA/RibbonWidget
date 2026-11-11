#pragma once

#include "UnitTest.h"
#include "RibbonWidget.h"
#include <QToolBar>
#include <QAction>
#include <QPointer>
#include <vector>

using namespace RibbonWidget;

class TST_ribbon : public UnitTest::Test
{
	TEST_CLASS(TST_ribbon)
public:
	TST_ribbon()
		: Test("TST_ribbon")
	{
		ADD_TEST(TST_ribbon::tabWithoutParent);
		ADD_TEST(TST_ribbon::doubleAddTab);
		ADD_TEST(TST_ribbon::destructionOrder);
		ADD_TEST(TST_ribbon::hideShowTab);
		ADD_TEST(TST_ribbon::currentTab);
		ADD_TEST(TST_ribbon::removeTab);
		ADD_TEST(TST_ribbon::actionButton);
	}

private:

	TEST_FUNCTION(tabWithoutParent)
	{
		TEST_START;
		RibbonTab* a = new RibbonTab();
		RibbonTab* b = new RibbonTab("t", "icon");
		TEST_ASSERT(a->parent() == nullptr);
		TEST_ASSERT(b->getTitle() == "t");

		// Added later
		QToolBar toolBar;
		Ribbon* ribbon = new Ribbon(&toolBar);
		ribbon->addTab(a);
		TEST_COMPARE(ribbon->getTabWidget()->count(), 1);
		delete b;
	}

	TEST_FUNCTION(doubleAddTab)
	{
		TEST_START;
		QToolBar toolBar;
		Ribbon* ribbon = new Ribbon(&toolBar);
		RibbonTab* tab = new RibbonTab("Tab", QIcon(), {}, ribbon);
		ribbon->addTab(tab);
		ribbon->addTab(nullptr);
		TEST_COMPARE(ribbon->getTabWidget()->count(), 1);

		tab->setTitle("Renamed");
		TEST_ASSERT(ribbon->getTabWidget()->tabText(0) == "Renamed");
	}

	TEST_FUNCTION(destructionOrder)
	{
		TEST_START;
		{
			// Toolbar first: the ribbon is a child of the toolbar
			QToolBar* toolBar = new QToolBar;
			QPointer<Ribbon> ribbon = new Ribbon(toolBar);
			new RibbonTab("Tab", QIcon(), {}, ribbon);
			QPointer<QTabWidget> tabWidget = ribbon->getTabWidget();
			delete toolBar;
			TEST_ASSERT(ribbon.isNull());
			TEST_ASSERT(tabWidget.isNull());
		}
		{
			// Ribbon first
			QToolBar* toolBar = new QToolBar;
			Ribbon* ribbon = new Ribbon(toolBar);
			new RibbonTab("Tab", QIcon(), {}, ribbon);
			QPointer<QTabWidget> tabWidget = ribbon->getTabWidget();
			delete ribbon;
			TEST_ASSERT(tabWidget.isNull());
			delete toolBar;
		}
		{
			// Tab widget deleted by someone else first
			QToolBar* toolBar = new QToolBar;
			Ribbon* ribbon = new Ribbon(toolBar);
			delete ribbon->getTabWidget();
			TEST_ASSERT(ribbon->getTabWidget() == nullptr);
			RibbonTab* tab = new RibbonTab();
			ribbon->addTab(tab);
			delete tab;
			delete ribbon;
			delete toolBar;
		}
		{
			// No toolbar
			Ribbon* ribbon = new Ribbon();
			QPointer<QTabWidget> tabWidget = ribbon->getTabWidget();
			new RibbonTab("Tab", QIcon(), {}, ribbon);
			delete ribbon;
			TEST_ASSERT(tabWidget.isNull());
		}
	}

	TEST_FUNCTION(hideShowTab)
	{
		TEST_START;
		QToolBar toolBar;
		Ribbon* ribbon = new Ribbon(&toolBar);
		RibbonTab* a = new RibbonTab("A", QIcon(), {}, ribbon);
		RibbonTab* b = new RibbonTab("B", QIcon(), {}, ribbon);
		RibbonTab* c = new RibbonTab("C", QIcon(), {}, ribbon);
		RibbonButtonGroup* group = new RibbonButtonGroup("Group", b);
		new RibbonButton("Btn", "Btn", QIcon(), true, group);
		QTabWidget* tw = ribbon->getTabWidget();

		ribbon->setTabVisible(b, false);
		TEST_ASSERT_FALSE(ribbon->isTabVisible(b));
		TEST_ASSERT(ribbon->isTabVisible(a));
		TEST_COMPARE(tw->count(), 3);
		ribbon->setTabVisible(b, true);
		TEST_ASSERT(ribbon->isTabVisible(b));
		TEST_COMPARE(tw->indexOf(b), 1);
		TEST_COMPARE(b->groupCount(), 1);
		TEST_COMPARE(group->buttonCount(), 1);
		TEST_COMPARE(tw->indexOf(c), 2);

		// Unknown / null tab
		RibbonTab* foreign = new RibbonTab();
		ribbon->setTabVisible(foreign, false);
		ribbon->setTabVisible(nullptr, false);
		TEST_ASSERT_FALSE(ribbon->isTabVisible(foreign));
		TEST_ASSERT_FALSE(ribbon->isTabVisible(nullptr));
		delete foreign;
	}

	TEST_FUNCTION(currentTab)
	{
		TEST_START;
		for (Qt::Orientation orientation : { Qt::Horizontal, Qt::Vertical })
		{
			QToolBar toolBar;
			Ribbon* ribbon = new Ribbon(&toolBar);
			RibbonTab* a = new RibbonTab("A", QIcon(), {}, ribbon);
			RibbonTab* b = new RibbonTab("B", QIcon(), {}, ribbon);
			RibbonTab* c = new RibbonTab("C", QIcon(), {}, ribbon);
			toolBar.setOrientation(orientation);
			TEST_ASSERT(ribbon->currentTab() == a);

			std::vector<RibbonTab*> emitted;
			bool stale = false;
			QObject::connect(ribbon, &Ribbon::currentTabChanged, ribbon, [&](RibbonTab* tab) {
				emitted.push_back(tab);
				if (tab && (!ribbon->isTabVisible(tab) || ribbon->currentTab() != tab))
					stale = true;
				});

			ribbon->setCurrentTab(b);
			TEST_ASSERT(ribbon->currentTab() == b);
			TEST_COMPARE(emitted.size(), size_t(1));
			TEST_ASSERT(emitted.back() == b);

			ribbon->setCurrentTab(b); // no change, no signal
			TEST_COMPARE(emitted.size(), size_t(1));

			// Hiding the current tab moves to the next visible one
			ribbon->setTabVisible(b, false);
			TEST_ASSERT(ribbon->currentTab() == c);
			TEST_ASSERT(emitted.back() == c);

			// Hidden / unknown / null tab cannot become current
			ribbon->setCurrentTab(b);
			ribbon->setCurrentTab(nullptr);
			TEST_ASSERT(ribbon->currentTab() == c);

			// Last tab hidden: previous visible one
			ribbon->setTabVisible(c, false);
			TEST_ASSERT(ribbon->currentTab() == a);

			// All hidden: no current tab
			ribbon->setTabVisible(a, false);
			TEST_ASSERT(ribbon->currentTab() == nullptr);
			TEST_ASSERT(emitted.back() == nullptr);

			ribbon->setTabVisible(b, true);
			TEST_ASSERT(ribbon->currentTab() != nullptr);
			TEST_ASSERT(emitted.back() == ribbon->currentTab());
			TEST_ASSERT_FALSE(stale);

			if (orientation == Qt::Vertical)
				TEST_ASSERT(ribbon->getTabWidget()->tabPosition() == QTabWidget::West);
		}
	}

	TEST_FUNCTION(removeTab)
	{
		TEST_START;
		QToolBar toolBar;
		Ribbon* ribbon = new Ribbon(&toolBar);
		RibbonTab* a = new RibbonTab("A", QIcon(), {}, ribbon);
		RibbonTab* b = new RibbonTab("B", QIcon(), {}, ribbon);
		QTabWidget* tw = ribbon->getTabWidget();

		ribbon->removeTab(a);
		TEST_COMPARE(tw->count(), 1);
		TEST_ASSERT(a->parent() == nullptr);
		TEST_ASSERT(ribbon->currentTab() == b);
		a->setTitle("A2"); // disconnected: must not touch the ribbon
		TEST_ASSERT(tw->tabText(0) == "B");

		ribbon->removeTab(a); // not in ribbon: no-op
		ribbon->addTab(a);
		TEST_COMPARE(tw->count(), 2);
		TEST_COMPARE(tw->indexOf(a), 1);
		a->setTitle("A3");
		TEST_ASSERT(tw->tabText(1) == "A3");
	}

	TEST_FUNCTION(actionButton)
	{
		TEST_START;
		QToolBar toolBar;
		Ribbon* ribbon = new Ribbon(&toolBar);
		RibbonTab* tab = new RibbonTab("Tab", QIcon(), {}, ribbon);
		RibbonButtonGroup* group = new RibbonButtonGroup("Group", tab);

		QAction action("Undo");
		action.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));
		const QString shortcut = action.shortcut().toString(QKeySequence::NativeText);

		RibbonButton* button = new RibbonButton(&action, group);
		InformativeToolButton* infoButton = new InformativeToolButton(&action, group);

		for (RibbonButton* btn : { button, static_cast<RibbonButton*>(infoButton) })
		{
			// Ribbon styling kept
			TEST_ASSERT(btn->iconSize() == QSize(32, 32));
			TEST_ASSERT(btn->toolButtonStyle() == Qt::ToolButtonTextUnderIcon);
			TEST_ASSERT(btn->autoRaise());
			TEST_ASSERT(btn->minimumSize() == QSize(48, 48));
			TEST_ASSERT(btn->text() == "Undo");
			TEST_ASSERT(btn->toolTip() == "Undo (" + shortcut + ")");
		}

		action.setEnabled(false);
		TEST_ASSERT_FALSE(button->isEnabled());
		action.setEnabled(true);
		TEST_ASSERT(button->isEnabled());

		action.setText("Undo typing");
		TEST_ASSERT(button->text() == "Undo typing");
		TEST_ASSERT(button->toolTip() == "Undo typing (" + shortcut + ")");

		action.setToolTip("Revert");
		TEST_ASSERT(button->toolTip() == "Revert (" + shortcut + ")");
		action.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y));
		TEST_ASSERT(button->toolTip() == "Revert (" + action.shortcut().toString(QKeySequence::NativeText) + ")");
		TEST_ASSERT(infoButton->toolTip() == button->toolTip());

		int triggered = 0;
		QObject::connect(&action, &QAction::triggered, [&triggered]() { ++triggered; });
		button->click();
		TEST_COMPARE(triggered, 1);

		action.setCheckable(true);
		TEST_ASSERT(button->isCheckable());
		action.setChecked(true);
		TEST_ASSERT(button->isChecked());
		button->click();
		TEST_COMPARE(triggered, 2);
		TEST_ASSERT_FALSE(action.isChecked());
		TEST_ASSERT_FALSE(button->isChecked());

		// Styling still intact after action changes
		TEST_ASSERT(button->iconSize() == QSize(32, 32));
		TEST_ASSERT(button->toolButtonStyle() == Qt::ToolButtonTextUnderIcon);
	}
};
