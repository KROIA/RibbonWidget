#pragma once

#include "RibbonWidget_base.h"
#include <QToolButton>
#include <QString>
#include <QIcon>

class QAction;
class QActionEvent;

namespace RibbonWidget
{
	class RibbonButtonGroup;
	class RIBBON_WIDGET_API RibbonButton : public QToolButton
	{

	public:
		explicit RibbonButton(RibbonButtonGroup* parent = nullptr);
		RibbonButton(const QString& text,
			const QString& toolTip,
			const QIcon& icon,
			bool enabled,
			RibbonButtonGroup* parent = nullptr);
		RibbonButton(const QString& text,
			const QString& toolTip,
			const QString& iconPaht,
			bool enabled,
			RibbonButtonGroup* parent = nullptr);

		/// Create a button bound to an action (via QToolButton::setDefaultAction()).
		/// The button follows the action's text, tooltip, icon, enabled, checkable and checked state,
		/// and a click triggers the action.
		/// The tooltip also shows the action's shortcut, e.g. "Undo (Ctrl+Z)".
		/// The ribbon styling set by RibbonButtonGroup::addButton() is kept.
		///
		/// \param[in] action The action, not owned by the button
		/// \param[in] parent The group the button is added to
		explicit RibbonButton(QAction* action, RibbonButtonGroup* parent = nullptr);

		virtual ~RibbonButton();

		//void setParentGroup(RibbonButtonGroup* parentGroup);
		//RibbonButtonGroup* parentGroup() const;


	protected:
		/// Keeps the shortcut in the tooltip when the default action changes.
		void actionEvent(QActionEvent* event) override;

	private:
		/// Set the tooltip to the default action's tooltip plus its shortcut.
		void updateActionToolTip();

		//RibbonButtonGroup* m_parentGroup = nullptr;
	};

	
}
