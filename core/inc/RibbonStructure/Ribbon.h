#pragma once

#include "RW_base.h"
#include <QTabWidget>

namespace RibbonWidget
{
	class RibbonTab;
	class RIBBONWIDGET_EXPORT Ribbon: public QObject
	{
		Q_OBJECT
	public:
		explicit Ribbon(QWidget* parent = nullptr);
		Ribbon(const std::vector<RibbonTab*> &tabs, QWidget* parent = nullptr);
		virtual ~Ribbon();

		void addTab(RibbonTab* tab);
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

	private slots:
		void onTabTitleChanged(const QString& title);
		void onTabIconChanged(const QIcon& icon);
	private:

		

		void setup();


		QTabWidget m_tabWidget;
	};
}