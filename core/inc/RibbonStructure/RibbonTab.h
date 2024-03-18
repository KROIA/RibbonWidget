#pragma once

#include "RibbonWidget_base.h"
#include <QWidget>
#include <QIcon>


namespace Ui {
class RibbonTab;
}
namespace RibbonWidget
{
	class RibbonButtonGroup;
	class RibbonButton;
	class Ribbon;
	class RIBBON_WIDGET_EXPORT RibbonTab : public QWidget
	{
		Q_OBJECT
	public:
		explicit RibbonTab(Ribbon* parent = nullptr);
		explicit RibbonTab(
			const QString& tabTitle,
			const QIcon& tabIcon,
			const std::vector<RibbonButtonGroup*>& groups,
			Ribbon* parent = nullptr);
		explicit RibbonTab(
			const QString& tabTitle,
			const QString& iconPath,
			const std::vector<RibbonButtonGroup*>& groups,
			Ribbon* parent = nullptr);

		explicit RibbonTab(
			const QString& tabTitle,
			const QString& iconPath,
			Ribbon* parent = nullptr);

		virtual ~RibbonTab();



		/// Set the title of the tab.
		void setTitle(const QString& title);

		/// Get the title of the tab.
		QString getTitle() const;

		/// Set the icon of the tab.
		void setIcon(const QIcon& icon);

		/// Get the icon of the tab.
		QIcon getIcon() const;

		/// Add a group to the tab content.
		///
		/// \param[in] group
		void addGroup(RibbonButtonGroup* group);

		/// Remove a group from the tab content.
		///
		/// \param[in] group
		void removeGroup(RibbonButtonGroup* group);

		/// Get the number of button groups in this tab content.
		///
		/// \return The number of button groups
		int groupCount() const;

		/// Add a button to the specified group.
		/// The group is created if it does not exist.
		///
		/// \param[in] groupName Name of the group
		/// \param[in] button The button
		void addButton(const QString& groupName, RibbonButton* button);

		/// Remove a button from the specified group.
		/// The group is also removed if it's empty.
		///
		/// \param[in] groupName Name of the group
		/// \param[in] button The button
		void removeButton(const QString& groupName, RibbonButton* button);

	signals: 
		void titleChanged(const QString& title);
		void iconChanged(const QIcon& icon);
	private:
		Ui::RibbonTab* ui;
		QString m_title; ///< Name of the tab
		QIcon m_icon; ///< Icon of the tab
	};
}
