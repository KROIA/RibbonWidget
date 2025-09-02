#pragma once

#include "RibbonWidget_base.h"
#include <QWidget>


namespace Ui {
	class RibbonButtonGroup;
}

namespace RibbonWidget
{
	class RibbonButton;
	class RibbonTab;
	class RIBBON_WIDGET_EXPORT RibbonButtonGroup : public QWidget
	{
		Q_OBJECT

	public:
		explicit RibbonButtonGroup(RibbonTab* parent = nullptr);
		RibbonButtonGroup(
			const QString& groupTitle,
			const std::vector<RibbonButton*>& buttons,
			RibbonTab* parent = nullptr);
		RibbonButtonGroup(
			const QString& groupTitle,
			RibbonTab* parent = nullptr);

		virtual ~RibbonButtonGroup();

		/// Set the title of the button group.
		/// The title is shown underneath the buttons.
		///
		/// \param[in] title The title
		void setTitle(const QString& title);

		/// Get the title of the button group.
		///
		/// \return The title
		QString getTitle() const;

		/// Get the number of buttons in the button group.
		///
		/// \return The number of buttons
		int buttonCount() const;

		/// Add a button to the group.
		///
		/// \param[in] button The button
		void addButton(RibbonButton* button);

		/// Remove a button from the group.
		///
		/// \param[in] button The button
		void removeButton(RibbonButton* button);

	public slots:
		void onOrientationChanged(Qt::Orientation o);

	protected:
		//void paintEvent(QPaintEvent* event) override;
		//QSize sizeHint() const override;
	private:
		Ui::RibbonButtonGroup* ui;
		Qt::Orientation m_orientation;
	};
}
