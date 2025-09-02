#include "RibbonStructure/RibbonButtonGroup.h"
#include "RibbonStructure/RibbonButton.h"
#include "RibbonStructure/RibbonTab.h"
#include "ui_ribbonbuttongroup.h"

#include <QToolButton>
#include <QPainter>
namespace RibbonWidget
{
	RibbonButtonGroup::RibbonButtonGroup(RibbonTab* parent)
		: QWidget(parent)
		, ui(new Ui::RibbonButtonGroup)
		, m_orientation(Qt::Orientation::Horizontal)
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
		, m_orientation(Qt::Orientation::Horizontal)
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
		, m_orientation(Qt::Orientation::Horizontal)
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

	void RibbonButtonGroup::onOrientationChanged(Qt::Orientation o)
	{
		m_orientation = o;
	}

	/*void RibbonButtonGroup::paintEvent(QPaintEvent* event)
	{
		
		switch (m_orientation)
		{
			case Qt::Orientation::Horizontal:
			{
				QWidget::paintEvent(event);
				break;
			}
			case Qt::Orientation::Vertical:
			{
				QPainter p(this);
				p.translate(width() / 2, height() / 2); // move to center
				p.rotate(-90);                       // rotate everything
				p.translate(-height() / 2, -width() / 2);

				// Render child into the rotated painter
				for (QObject* obj : children()) {
					if (QWidget* child = qobject_cast<QWidget*>(obj)) {
						child->render(&p);
					}
				}
				break;
			}
		}		
	}

	QSize RibbonButtonGroup::sizeHint() const 
	{
		switch (m_orientation)
		{
			case Qt::Orientation::Horizontal:
			{
				return QWidget::sizeHint();
			}
			case Qt::Orientation::Vertical:
			{
				return QSize(QWidget::height(), QWidget::width()); // swapped
			}
		}
		return QWidget::sizeHint();
	}*/
}