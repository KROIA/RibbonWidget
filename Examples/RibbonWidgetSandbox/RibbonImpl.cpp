#include "RibbonImpl.h"


RibbonImpl::RibbonImpl(QWidget* parent)
	: RibbonWidget::Ribbon(parent)
{
	Q_INIT_RESOURCE(RibbonIcons); // Init the resource file
	// Create tabs
	RibbonWidget::RibbonTab* tabSettings	= new RibbonWidget::RibbonTab("Settings", ":/icons/developerTool.png", this);
	RibbonWidget::RibbonTab* tabEdit		= new RibbonWidget::RibbonTab("Editing", ":/icons/create_new_2.png", this);

	// Create groups
	RibbonWidget::RibbonButtonGroup* groupSettings	= new RibbonWidget::RibbonButtonGroup("group\nSettings", tabSettings);
	RibbonWidget::RibbonButtonGroup* groupWork		= new RibbonWidget::RibbonButtonGroup("groupWork", tabEdit);
	RibbonWidget::RibbonButtonGroup* groupEdit		= new RibbonWidget::RibbonButtonGroup("groupEdit", tabEdit);

	// Create buttons
	m_settingsButtons.settings1		= new RibbonWidget::RibbonButton("Settings 1", "Settings 1", ":/icons/engineering_1.png", true, groupSettings);
	m_settingsButtons.settingsOK	= new RibbonWidget::RibbonButton("Settings OK", "Settings OK", ":/icons/accept.png", true, groupSettings);
	m_settingsButtons.settingsCancel= new RibbonWidget::RibbonButton("Cancel", "Cancel", ":/icons/close.png", true, groupSettings);
	m_settingsButtons.settingsSave	= new RibbonWidget::RibbonButton("Settings Save", "Settings Save", ":/icons/floppy_disk.png", true, groupSettings);

	m_workButtons.open = new RibbonWidget::InformativeToolButton("Open", "Open", ":/icons/document.png", true, groupWork);
	m_workButtons.save = new RibbonWidget::InformativeToolButton("Save", "Save", ":/icons/floppy_disk.png", true, groupWork);

	m_editButtons.undo = new RibbonWidget::RibbonButton("Undo", "Undo", ":/icons/arrowCClockwise.png", true, groupEdit);
	m_editButtons.redo = new RibbonWidget::RibbonButton("Redo", "Redo", ":/icons/arrowClockwise.png", true, groupEdit);

	// Add tabs
	addTab(tabSettings);
	addTab(tabEdit);
}

RibbonImpl::SettingsButtons& RibbonImpl::settingsButtons()
{
	return m_settingsButtons;
}
RibbonImpl::WorkButtons& RibbonImpl::workButtons()
{
	return m_workButtons;
}
RibbonImpl::EditButtons& RibbonImpl::editButtons()
{
	return m_editButtons;
}