#pragma once

#include "RibbonWidget.h"

class RibbonImpl : public RibbonWidget::Ribbon
{
	Q_OBJECT
	public:
		RibbonImpl(QWidget* parent = nullptr);


	private:
		struct SettingsButtons
		{
			RibbonWidget::RibbonButton* settings1;
			RibbonWidget::RibbonButton* settingsOK;
			RibbonWidget::RibbonButton* settingsCancel;
			RibbonWidget::RibbonButton* settingsSave;
		};

		struct WorkButtons
		{
			RibbonWidget::RibbonButton* open;
			RibbonWidget::RibbonButton* save;
		};

		struct EditButtons
		{
			RibbonWidget::RibbonButton* undo;
			RibbonWidget::RibbonButton* redo;
		};


		SettingsButtons m_settingsButtons;
		WorkButtons m_workButtons;
		EditButtons m_editButtons;
};