#include "ui_RibbonTab.h"
#include "RibbonStructure/RibbonButtonGroup.h"
#include "RibbonStructure/RibbonTab.h"
#include "RibbonStructure/RibbonButton.h"
#include "RibbonStructure/Ribbon.h"
#include "Utilities/DefaultIconLoader.h"


namespace RibbonWidget
{
	RibbonTab::RibbonTab(Ribbon* parent)
		: QWidget(parent->getTabWidget())
		, ui(new Ui::RibbonTab)
		, m_title("")
	{
		ui->setupUi(this);
		if(parent)
			parent->addTab(this);
	}
	RibbonTab::RibbonTab(
		const QString& tabTitle,
		const QIcon& tabIcon,
		const std::vector<RibbonButtonGroup*>& groups,
		Ribbon* parent)
		: QWidget(parent->getTabWidget())
		, ui(new Ui::RibbonTab)
		, m_title("")
		, m_icon()
	{
		ui->setupUi(this);
		setTitle(tabTitle);
		setIcon(tabIcon);
		for (auto group : groups)
		{
			addGroup(group);
		}
		if (parent)
			parent->addTab(this);
	}
	RibbonTab::RibbonTab(
		const QString& tabTitle,
		const QString& iconPath,
		const std::vector<RibbonButtonGroup*>& groups,
		Ribbon* parent)
		: QWidget(parent->getTabWidget())
		, ui(new Ui::RibbonTab)
		, m_title("")
		, m_icon()
	{
		ui->setupUi(this);
		setTitle(tabTitle);
		setIcon(DefaultIconLoader::getIcon(iconPath));
		for (auto group : groups)
		{
			addGroup(group);
		}
		if (parent)
			parent->addTab(this);
	}
	RibbonTab::RibbonTab(
		const QString& tabTitle,
		const QString& iconPath,
		Ribbon* parent)
		: QWidget(parent->getTabWidget())
		, ui(new Ui::RibbonTab)
		, m_title("")
		, m_icon()
	{
		ui->setupUi(this);
		setTitle(tabTitle);
		setIcon(DefaultIconLoader::getIcon(iconPath));
		if (parent)
			parent->addTab(this);
	}


	RibbonTab::~RibbonTab()
	{
		delete ui;
	}

	void RibbonTab::setTitle(const QString& title)
	{
		if(m_title != title)
			emit titleChanged(title);
		m_title = title;
	}
	QString RibbonTab::getTitle() const
	{
		return m_title;
	}

	void RibbonTab::setIcon(const QIcon& icon)
	{
		m_icon = icon;
		emit iconChanged(m_icon);
	}
	QIcon RibbonTab::getIcon() const
	{
		return m_icon;
	}

	void RibbonTab::addGroup(RibbonButtonGroup* group)
	{
		ui->ribbonHorizontalLayout->addWidget(group);
	}

	void RibbonTab::removeGroup(RibbonButtonGroup* group)
	{
		// Find ribbon group
		for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
		{
			RibbonButtonGroup* containedGroup = qobject_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
			if (containedGroup == group)
			{
				ui->ribbonHorizontalLayout->removeWidget(group); /// \todo :( No effect
				//delete group;
				break;
			}
		}

		/// \todo  What if the group still contains buttons? Delete manually?
		// Or automaticly deleted by Qt parent() system.
	}

	int RibbonTab::groupCount() const
	{
		return ui->ribbonHorizontalLayout->count();
	}

	void RibbonTab::addButton(const QString& groupName, RibbonButton* button)
	{
		// Find ribbon group
		RibbonButtonGroup* ribbonButtonGroup = nullptr;
		for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
		{
			RibbonButtonGroup* group = qobject_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
			if (group->getTitle().toLower() == groupName.toLower())
			{
				ribbonButtonGroup = group;
				break;
			}
		}

		if (ribbonButtonGroup != nullptr)
		{
			// Group found
			// Add ribbon button
			ribbonButtonGroup->addButton(button);
		}
		else
		{
			// Group not found
			// Add ribbon group
			RibbonButtonGroup* group = new RibbonButtonGroup(this);
			group->addButton(button);
			addGroup(group);
		}
	}

	void RibbonTab::removeButton(const QString& groupName, RibbonButton* button)
	{
		// Find ribbon group
		RibbonButtonGroup* ribbonButtonGroup = nullptr;
		for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
		{
			RibbonButtonGroup* group = qobject_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
			if (group->getTitle().toLower() == groupName.toLower())
			{
				ribbonButtonGroup = group;
				break;
			}
		}

		if (ribbonButtonGroup != nullptr)
		{
			// Group found
			// Remove ribbon button
			ribbonButtonGroup->removeButton(button);

			if (ribbonButtonGroup->buttonCount() == 0)
			{
				// Empty button group
				// Remove button group
				removeGroup(ribbonButtonGroup);
			}
		}
	}
}