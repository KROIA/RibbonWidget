# Qt-Ribbon-Widget
A Ribbon widget for Qt

![Ribbon widget in a QMainWindow on Windows](docs/image_windows1.png)

![Ribbon widget in a QMainWindow on Linux](docs/image_linux1.png)

## Requirements
C++23, CMake >= 3.20, Qt 5.15+ or Qt 6 (Widgets).

## Build
```
build.bat                 # configure + build x64-Debug and x64-Release
build.bat x64-Release     # build a single CMake preset
build.bat list            # list presets
```
Or use the CMake presets directly (`cmake --preset x64-Release`, `cmake --build --preset x64-Release`).
Available presets: `x64-Debug`, `x64-Release`, `x64-Debug-Profile`, `x64-Release-Profile`.

To use the library in another CMake project, include `RibbonWidget.cmake` (a `FetchContent` wrapper that
adds `RibbonWidget_shared` / `RibbonWidget_static` to your dependency lists). Set `RibbonWidget_NO_EXAMPLES`
and `RibbonWidget_NO_UNITTESTS` to skip examples and tests.

## Usage
Everything is available through one header and the `RibbonWidget` namespace:
```cpp
#include "RibbonWidget.h"
```

The `Ribbon` is a `QObject` child of the `QToolBar` you pass in, so it needs no manual delete.
Place a `QToolBar` in your `QMainWindow` (e.g. in Qt Designer) and construct the ribbon with it:

```cpp
Q_INIT_RESOURCE(RibbonIcons); // register the bundled ":/icons/..." resources (once, e.g. before creating the ribbon)

auto* ribbon = new RibbonWidget::Ribbon(ui.mainToolBar);
```

### Tabs, groups and buttons
Passing a parent adds the new object to it automatically: a `RibbonTab` with a `Ribbon*` parent is added to
that ribbon, a `RibbonButtonGroup` with a `RibbonTab*` parent to that tab, a button with a
`RibbonButtonGroup*` parent to that group. Calling `addTab()` / `addGroup()` / `addButton()` explicitly
for an already added object is a harmless no-op.

```cpp
using namespace RibbonWidget;

RibbonTab* tabEdit = new RibbonTab("Editing", ":/icons/create_new_2.png", ribbon);

RibbonButtonGroup* groupEdit = new RibbonButtonGroup("Edit", tabEdit);

// Plain button: text, tooltip, icon, enabled
auto* undo = new RibbonButton("Undo", "Undo last step", ":/icons/arrowCClockwise.png", true, groupEdit);
connect(undo, &QToolButton::clicked, this, &MainWindow::onUndo);
```

### Buttons bound to a QAction
A button created from a `QAction` follows the action's text, tooltip, icon, enabled, checkable and
checked state. Clicking the button triggers the action, and the tooltip shows the action's shortcut.

```cpp
QAction* saveAction = new QAction(QIcon(":/icons/floppy_disk.png"), "Save", this);
saveAction->setShortcut(QKeySequence::Save);
connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);

new RibbonButton(saveAction, groupEdit);   // appears in the group, tooltip "Save (Ctrl+S)"
```

### InformativeToolButton: progress and loading circle
`InformativeToolButton` is a `RibbonButton` that can draw a progress bar, a loading circle and a flashing
overlay on top of its icon. It also has an action constructor: `InformativeToolButton(QAction*, RibbonButtonGroup*)`.

```cpp
auto* open = new InformativeToolButton("Open", "Open", ":/icons/document.png", true, groupEdit);
open->setLoadingCircleColor(QColor(255, 0, 0));
open->enableLoadingCircle(true);       // spinning circle while busy

auto* export_ = new InformativeToolButton("Export", "Export", ":/icons/file_2.png", true, groupEdit);
export_->setProgressColor(QColor(0, 255, 255));
export_->setProgress(0.5f);            // update this while the work runs
```
Other helpers: `setLoadingCircleSpeed()`, `setLoadingCircleAngle()`, `setOverlayColor()`,
`setOverlayEnable()`, `overlayFlash()`.

### Switching tab sets
Tabs can be hidden and shown without losing their groups and buttons; a hidden tab reappears at its
original position. Use this to swap between e.g. an edit mode and a simulation mode:

```cpp
RibbonTab* tabEdit = new RibbonTab("Editing",    ":/icons/create_new_2.png",  ribbon);
RibbonTab* tabSim  = new RibbonTab("Simulation", ":/icons/developerTool.png", ribbon);

void MainWindow::setSimulationMode(bool sim)
{
    ribbon->setTabVisible(tabEdit, !sim);
    ribbon->setTabVisible(tabSim,  sim);
    ribbon->setCurrentTab(sim ? tabSim : tabEdit);
}

connect(ribbon, &Ribbon::currentTabChanged, this, [](RibbonTab* tab) { /* ... */ });
```

Other `Ribbon` functions: `isTabVisible(tab)`, `currentTab()`, `removeTab(tab)` (detaches the tab without
deleting it, so it can be added again with `addTab`).

A complete example is in `examples/RibbonWidgetSandbox`.

## License
This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
- Icons from [icons8.com](https://icons8.com/)
