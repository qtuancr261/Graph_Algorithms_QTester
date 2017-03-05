#include <QApplication>
#include <QScopedPointer>
#include "dfs_bfs_widget.h"
#include "euler_hamilton_widget.h"
#include "kpmodulewidget.h"
#include "ga_tester_mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QScopedPointer<DFS_BFS_Widget> ioWidget{new DFS_BFS_Widget{}};
    //ioWidget->show();
    //KPModuleWidget kpWidget{};
    //kpWidget.show();
    //QScopedPointer<Euler_Hamilton_Widget> ehWidget{new Euler_Hamilton_Widget()};
    //ehWidget->show();
    GA_Tester_mainWindow w;
    w.showMaximized();
    return a.exec();
}
