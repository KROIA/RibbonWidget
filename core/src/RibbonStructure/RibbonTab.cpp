#include "ui_RibbonTab.h"
#include "RibbonStructure/RibbonButtonGroup.h"
#include "RibbonStructure/RibbonTab.h"
#include "RibbonStructure/RibbonButton.h"
#include "RibbonStructure/Ribbon.h"
#include "Utilities/DefaultIconLoader.h"
#include <QSpacerItem>


namespace RibbonWidget
{
	RibbonTab::RibbonTab(Ribbon* parent)
		: QWidget(parent->getTabWidget())
		, ui(new Ui::RibbonTab)
		, m_title("")
		, m_orientation(Qt::Orientation::Horizontal)
	{
		ui->setupUi(this);
		if(parent)
			parent->addTab(this);
		m_layout = dynamic_cast<QGridLayout*>(ui->ribbonTabScrollAreaContent->layout());
		m_spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
		m_layout->addItem(m_spacer, 0, m_layout->count());
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
		, m_orientation(Qt::Orientation::Horizontal)
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
		m_layout = dynamic_cast<QGridLayout*>(ui->ribbonTabScrollAreaContent->layout());
		m_spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
		m_layout->addItem(m_spacer, 0, m_layout->count());
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
		, m_orientation(Qt::Orientation::Horizontal)
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
		m_layout = dynamic_cast<QGridLayout*>(ui->ribbonTabScrollAreaContent->layout());
		m_spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
		m_layout->addItem(m_spacer, 0, m_layout->count());
	}
	RibbonTab::RibbonTab(
		const QString& tabTitle,
		const QString& iconPath,
		Ribbon* parent)
		: QWidget(parent->getTabWidget())
		, ui(new Ui::RibbonTab)
		, m_title("")
		, m_icon()
		, m_orientation(Qt::Orientation::Horizontal)
	{
		ui->setupUi(this);
		setTitle(tabTitle);
		setIcon(DefaultIconLoader::getIcon(iconPath));
		if (parent)
			parent->addTab(this);
		m_layout = dynamic_cast<QGridLayout*>(ui->ribbonTabScrollAreaContent->layout());
		m_spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
		m_layout->addItem(m_spacer, 0, m_layout->count());
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
		m_layout->removeItem(m_spacer);
		switch (m_orientation)
		{
			case Qt::Orientation::Horizontal:
			{
				m_layout->addWidget(group, 0, m_layout->count());
				m_layout->addItem(m_spacer, 0, m_layout->count());
				break;
			}
			case Qt::Orientation::Vertical:
			{
				m_layout->addWidget(group, m_layout->count(), 0);
				m_layout->addItem(m_spacer, m_layout->count(), 0);
				break;
			}
		}
	}

	void RibbonTab::removeGroup(RibbonButtonGroup* group)
	{
		// Find ribbon group
		for (int i = 0; i < m_layout->count(); i++)
		{
			RibbonButtonGroup* containedGroup = qobject_cast<RibbonButtonGroup*>(m_layout->itemAt(i)->widget());
			if (containedGroup == group)
			{
				m_layout->removeWidget(group); /// \todo :( No effect
				//delete group;
				break;
			}
		}

		/// \todo  What if the group still contains buttons? Delete manually?
		// Or automaticly deleted by Qt parent() system.
	}

	int RibbonTab::groupCount() const
	{
		return m_layout->count()-1;
	}

	void RibbonTab::addButton(const QString& groupName, RibbonButton* button)
	{
		// Find ribbon group
		RibbonButtonGroup* ribbonButtonGroup = nullptr;
		for (int i = 0; i < m_layout->count(); i++)
		{
			RibbonButtonGroup* group = qobject_cast<RibbonButtonGroup*>(m_layout->itemAt(i)->widget());
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
		for (int i = 0; i < m_layout->count(); i++)
		{
			RibbonButtonGroup* group = qobject_cast<RibbonButtonGroup*>(m_layout->itemAt(i)->widget());
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
	void RibbonTab::onOrientationChanged(Qt::Orientation o)
	{
		if (o == m_orientation)
			return;
		m_orientation = o;
		std::vector<RibbonButtonGroup*> widgets;
		widgets.reserve(m_layout->count());
		m_layout->removeItem(m_spacer);
		delete m_spacer;
		for (int i = 0; i < m_layout->count(); i++)
		{
			RibbonButtonGroup* group = qobject_cast<RibbonButtonGroup*>(m_layout->itemAt(i)->widget());
			widgets.push_back(group);
		}

		for (int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->onOrientationChanged(m_orientation);
			m_layout->removeWidget(widgets[i]);
		}
		switch (m_orientation)
		{
			case Qt::Orientation::Horizontal:
			{				
				for (int i = 0; i < widgets.size(); i++)
				{
					m_layout->addWidget(widgets[i], 0, i);
				}
				m_spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
				m_layout->addItem(m_spacer, 0, widgets.size());
				break;
			}
			case Qt::Orientation::Vertical:
			{
				for (int i = 0; i < widgets.size(); i++)
				{
					m_layout->addWidget(widgets[i], i, 0);
				}
				m_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
				m_layout->addItem(m_spacer, widgets.size(), 0);
				break;
			}
		}
	}
}