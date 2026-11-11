#pragma once

#include "RibbonWidget_base.h"
#include <QTabWidget>
#include <QToolBar>
#include <QPointer>

namespace RibbonWidget
{
	class RibbonTab;

	/// The ribbon: a tab widget placed in a QToolBar.
	///
	/// The tab widget is owned by the toolbar (if one is given), otherwise by the ribbon.
	/// The ribbon itself is a QObject child of the toolbar, so it is deleted together with the toolbar.
	/// Deleting the ribbon before the toolbar is also safe.
	class RIBBON_WIDGET_API Ribbon: public QObject
	{
		Q_OBJECT
	public:
		explicit Ribbon(QToolBar* parent = nullptr);
		Ribbon(const std::vector<RibbonTab*> &tabs, QToolBar* parent = nullptr);
		virtual ~Ribbon();

		/// Add a tab to the ribbon.
		/// A RibbonTab constructed with a Ribbon* parent already adds itself to that ribbon,
		/// so calling addTab() for it again is not needed.
		/// Adding a tab that is already in the ribbon, or a nullptr, is a no-op.
		///
		/// \param[in] tab The tab
		void addTab(RibbonTab* tab);

		/// Remove a tab from the ribbon without deleting it.
		/// The tab loses its parent, so the caller owns it afterwards. It can be added again with addTab().
		/// Does nothing if the tab is not in the ribbon.
		///
		/// \param[in] tab The tab
		void removeTab(RibbonTab* tab);

		/// Show or hide a tab in the tab bar.
		/// A hidden tab keeps its groups and buttons and reappears at its original position.
		/// If the current tab is hidden, the next visible tab (or else the previous one) becomes current.
		/// Does nothing if the tab is not in the ribbon.
		///
		/// \param[in] tab The tab
		/// \param[in] visible true to show the tab, false to hide it
		void setTabVisible(RibbonTab* tab, bool visible);

		/// Check whether a tab is visible in the tab bar.
		///
		/// \param[in] tab The tab
		/// \return false if the tab is hidden or not in the ribbon
		bool isTabVisible(const RibbonTab* tab) const;

		/// Make a tab the current tab.
		/// Does nothing if the tab is hidden or not in the ribbon.
		///
		/// \param[in] tab The tab
		void setCurrentTab(RibbonTab* tab);

		/// Get the current tab.
		///
		/// \return The current tab, or nullptr if there is no visible current tab
		RibbonTab* currentTab() const;

		QTabWidget* getTabWidget();
		const QTabWidget* getTabWidget() const;

		/*
		/// Add a tab to the ribbon.
		///
		/// \param[in] tabName Name of the tab
		void addTab(const QString& tabName);

		/// Add a tab to the ribbon.
		///
		/// \param[in] tabIcon Icon of the tab
		/// \param[in] tabName Name of the tab
		void addTab(const QIcon& tabIcon, const QString& tabName);

		/// Remove a tab from the ribbon.
		///
		/// \param[in] tabName Name of the tab
		void removeTab(const QString& tabName);

		/// Add a group to the specified tab.
		/// The specified tab is created if it does not exist.
		///
		/// \param[in] tabName Name of the tab
		/// \param[in] groupName Name of the group
		void addGroup(const QString& tabName, const QString& groupName);

		/// Add a button to the specified group.
		/// The specified group and tab are created if they do not exist.
		///
		/// \param[in] tabName Name of the tab
		/// \param[in] groupName Name of the group
		/// \param[in] button The button
		void addButton(const QString& tabName, const QString& groupName, RibbonButton* button);

		/// Remove a button from the specified group.
		/// Do nothing if the button, group or tab doesn't exist.
		/// The button group and tab are also removed if they become empty due to
		/// the removal of the button.
		///
		/// \param[in] tabName Name of the tab
		/// \param[in] groupName Name of the group
		/// \param[in] button The button
		void removeButton(const QString& tabName, const QString& groupName, RibbonButton* button);
		*/
	signals:
		void orientationChanged(Qt::Orientation o);

		/// Emitted when the current tab changes.
		///
		/// \param[in] tab The new current tab, or nullptr if there is no visible current tab
		void currentTabChanged(RibbonTab* tab);

	private slots:
		void onTabTitleChanged(const QString& title);
		void onTabIconChanged(const QIcon& icon);
		void updateCurrentTab();
	private:



		void setup();

		/// Make the nearest visible tab after (or else before) the given index current.
		void selectVisibleNeighbour(int index);

		QPointer<QTabWidget> m_tabWidget;
		QPointer<RibbonTab> m_currentTab; ///< Last value sent with currentTabChanged()
		QToolBar* m_parent = nullptr;
	};
}