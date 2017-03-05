#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T22:39:20
#
#-------------------------------------------------

QT       += core gui
QT       += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph_Algorithms_QTester
TEMPLATE = app


SOURCES += main.cpp \
    dfs_bfs_module.cpp \
    euler_hamilton_module.cpp \
    kpmodulewidget.cpp \
    vertex.cpp \
    spanning_tree_module.cpp \
    edge.cpp \
    ga_tester_mainwindow.cpp \
    dfs_bfs_widget.cpp \
    euler_hamilton_widget.cpp \
    inputdialog.cpp

HEADERS  += \
    dfs_bfs_module.h \
    euler_hamilton_module.h \
    kpmodulewidget.h \
    vertex.h \
    spanning_tree_module.h \
    edge.h \
    ga_tester_mainwindow.h \
    basewidget.h \
    dfs_bfs_widget.h \
    euler_hamilton_widget.h \
    inputdialog.h

FORMS += \
    Euler_Hamilton_Widget.ui \
    DFS_BFS_Widget.ui \
    kpmodulewidget.ui \
    DFS_BFS_Widget.ui \
    dfs_bfs_widget.ui \
    euler_hamilton_widget.ui

RESOURCES += \
    resource.qrc
