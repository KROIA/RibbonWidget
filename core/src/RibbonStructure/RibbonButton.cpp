#include "RibbonStructure/RibbonButton.h"
#include "RibbonStructure/RibbonButtonGroup.h"
#include "Utilities/DefaultIconLoader.h"
#include <QAction>
#include <QActionEvent>

namespace RibbonWidget
{
	RibbonButton::RibbonButton(RibbonButtonGroup* parent)
		: QToolButton(parent)
	{
		if(parent)
			parent->addButton(this);
	}
	RibbonButton::RibbonButton(const QString& text,
		const QString& toolTip,
		const QIcon& icon,
		bool enabled,
		RibbonButtonGroup* parent)
		: QToolButton(parent)
	{
		setText(text);
		setToolTip(toolTip);
		setIcon(icon);
		setEnabled(enabled);
		if (parent)
			parent->addButton(this);
	}

	RibbonButton::RibbonButton(const QString& text,
		const QString& toolTip,
		const QString& iconPath,
		bool enabled,
		RibbonButtonGroup* parent)
		: QToolButton(parent)
	{
		setText(text);
		setToolTip(toolTip);
		setIcon(DefaultIconLoader::getIcon(iconPath));
		setEnabled(enabled);
		if (parent)
			parent->addButton(this);
	}

	RibbonButton::RibbonButton(QAction* action, RibbonButtonGroup* parent)
		: QToolButton(parent)
	{
		// setDefaultAction() only syncs text, icon, tooltip, enabled and check state,
		// so the styling applied by RibbonButtonGroup::addButton() is not affected
		setDefaultAction(action);
		updateActionToolTip();
		if (parent)
			parent->addButton(this);
	}

	RibbonButton::~RibbonButton()
	{

	}

	void RibbonButton::actionEvent(QActionEvent* event)
	{
		// QToolButton re-applies the action's plain tooltip on ActionChanged
		QToolButton::actionEvent(event);
		if (event->action() && event->action() == defaultAction())
			updateActionToolTip();
	}

	void RibbonButton::updateActionToolTip()
	{
		QAction* action = defaultAction();
		if (!action)
			return;
		QString tip = action->toolTip();
		if (!action->shortcut().isEmpty())
			tip += QStringLiteral(" (%1)").arg(action->shortcut().toString(QKeySequence::NativeText));
		setToolTip(tip);
	}


	/*void RibbonButton::setParentGroup(RibbonButtonGroup* parentGroup)
	{
		m_parentGroup = parentGroup;
	}

	RibbonButtonGroup* RibbonButton::parentGroup() const
	{
		return m_parentGroup;
	}*/
}