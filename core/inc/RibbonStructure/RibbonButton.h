#pragma once

#include "RW_base.h"
#include <QToolButton>
#include <QString>
#include <QIcon>

namespace RibbonWidget
{
	class RibbonButtonGroup;
	class RIBBONWIDGET_EXPORT RibbonButton : public QToolButton
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

		virtual ~RibbonButton();

		//void setParentGroup(RibbonButtonGroup* parentGroup);
		//RibbonButtonGroup* parentGroup() const;


	protected:

	private:
		//RibbonButtonGroup* m_parentGroup = nullptr;
	};

	
}
