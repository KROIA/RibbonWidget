#include "RibbonStructure/RibbonButtonGroup.h"
#include "RibbonStructure/RibbonButton.h"
#include "RibbonStructure/RibbonTab.h"
#include "ui_ribbonbuttongroup.h"

#include <QToolButton>
namespace RibbonWidget
{
	RibbonButtonGroup::RibbonButtonGroup(RibbonTab* parent)
		: QWidget(parent)
		, ui(new Ui::RibbonButtonGroup)
	{
		ui->setupUi(this);
		if(parent)
			parent->addGroup(this);
	}
	RibbonButtonGroup::RibbonButtonGroup(
		const QString& groupTitle,
		const std::vector<RibbonButton*>& buttons,
		RibbonTab* parent)
		: QWidget(parent)
		, ui(new Ui::RibbonButtonGroup)
	{
		ui->setupUi(this);
		setTitle(groupTitle);
		for (auto button : buttons)
		{
			addButton(button);
		}
		if (parent)
			parent->addGroup(this);
	}
	RibbonButtonGroup::RibbonButtonGroup(
		const QString& groupTitle,
		RibbonTab* parent)
		: QWidget(parent)
		, ui(new Ui::RibbonButtonGroup)
	{
		ui->setupUi(this);
		setTitle(groupTitle);
		if (parent)
			parent->addGroup(this);
	}

	RibbonButtonGroup::~RibbonButtonGroup()
	{
		delete ui;
	}

	void RibbonButtonGroup::setTitle(const QString& title)
	{
		ui->label->setText(title);
		ui->label->adjustSize();
	}

	QString RibbonButtonGroup::getTitle() const
	{
		return ui->label->text();
	}

	int RibbonButtonGroup::buttonCount() const
	{
		return ui->horizontalLayout->count();
	}

	void RibbonButtonGroup::addButton(RibbonButton* button)
	{
		button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		button->setMinimumSize(48, 48);
		button->setAutoRaise(true);
		button->setIconSize(QSize(32, 32));
		button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

		//button->setParentGroup(this);
		ui->horizontalLayout->addWidget(button);
	}

	void RibbonButtonGroup::removeButton(RibbonButton* button)
	{
		/// \todo What happens if button is not part of the layout?

		//button->setParentGroup(nullptr);
		ui->horizontalLayout->removeWidget(button);
	}
}