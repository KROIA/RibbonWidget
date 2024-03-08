#include "RibbonStructure/RibbonButton.h"
#include "RibbonStructure/RibbonButtonGroup.h"
#include "Utilities/DefaultIconLoader.h"

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

	RibbonButton::~RibbonButton()
	{

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