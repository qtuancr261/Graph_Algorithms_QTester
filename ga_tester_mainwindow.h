#ifndef GA_TESTER_MAINWINDOW_H
#define GA_TESTER_MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QTextBrowser>
#include <QPushButton>
#include <QGroupBox>
#include <QScopedPointer>
#include <dfs_bfs_widget.h>
#include <euler_hamilton_widget.h>
class GA_Tester_mainWindow : public QMainWindow
// Graph Algorithms Tester Main Window
{
    Q_OBJECT
private:
    // Children Widgets
    QScopedPointer<QTextBrowser> browser;
    QScopedPointer<DFS_BFS_Widget>  dfs_bfs_widget;
    QGroupBox*  leftButtonBar;
    QScopedPointer<QDockWidget>  leftDocWidget;
    // File Menu Actions
    QAction* newFileAction;
    QAction* newWindowAction;
    QAction* openFileAction;
    QAction* openFolderAction;
    QAction* quitApp;
    //Tools Menu Actions
    QAction* graphDesignModeAction;
    QAction* optionAction;
    // Help Menu Actions
    QAction* viewContentsAction;
    QAction* aboutTesterAction;
    QAction* aboutQtAction;
    //
    QPushButton* welcome;
    QPushButton* mainFunct;
    QPushButton* designMode;
    QPushButton* helpMode;
     //Private Functions
     void createActions();
     void createMenus();
     void createToolBars();
     void createDockWidgets();
public:
    explicit GA_Tester_mainWindow(QWidget *parent = 0);
    ~GA_Tester_mainWindow() = default;
     void setButtonStyle(QPushButton* button);
signals:

public slots:
     void displayFuntionsScreen();
     void displayWelcomeScreen();
     void displayAppInfo();
};

#endif // GA_TESTER_MAINWINDOW_H
