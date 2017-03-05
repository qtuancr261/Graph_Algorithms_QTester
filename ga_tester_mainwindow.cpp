#include "ga_tester_mainwindow.h"

void GA_Tester_mainWindow::createActions()
{
    newFileAction = new QAction(QIcon(":/images/newFileAct.ico"), tr("Tạo tập tin mới"), this);
    newWindowAction = new QAction(QIcon(":/images/newWinAct.ico"), tr("Tạo cửa sổ mới"), this);

    openFileAction = new QAction(QIcon(":/images/openFileAct.ico"), tr("Mở tập tin"), this);

    openFolderAction = new QAction(QIcon(":/images/openFolderAct.ico"), tr("Mở thư mục"), this);

    quitApp = new QAction(QIcon(":/images/quitApp.ico"), tr("Thoát"), this);
    QObject::connect(quitApp, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    graphDesignModeAction = new QAction(QIcon(":/images/graphDesignMode.ico"), tr("Thiết kế đồ thị"), this);
    graphDesignModeAction->setCheckable(true);
    optionAction = new QAction(QIcon(":/images/optionsAct.ico"), tr("Tùy chỉnh..."), this);

    viewContentsAction = new QAction(QIcon(":/images/viewContentsAct.ico"), tr("Tra cứu tài liệu"), this);

    aboutTesterAction = new QAction(QIcon(":/images/aboutAppAct.ico"), tr("Thông tin về chương trình G.A.QT"), this);

    aboutQtAction = new QAction(QIcon(":/images/QtIcon.png"), tr("Thông tin về Qt Framework"), this);
    QObject::connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void GA_Tester_mainWindow::createMenus()
{
    QMenu* menu;
    menu = menuBar()->addMenu(tr("&Tập tin"));
    menu->addAction(newFileAction);
    menu->addAction(newWindowAction);
    menu->addAction(openFileAction);
    menu->addAction(openFolderAction);
    menu->addSeparator();
    menu->addAction(quitApp);

    menu = menuBar()->addMenu(tr("&Xem"));

    menu = menuBar()->addMenu(tr("&Công cụ"));
    menu->addAction(graphDesignModeAction);
    menu->addAction(optionAction);

    menu = menuBar()->addMenu(tr("Trợ &giúp"));
    menu->addAction(viewContentsAction);
    menu->addSeparator();
    menu->addAction(aboutTesterAction);
    menu->addAction(aboutQtAction);
}

void GA_Tester_mainWindow::createToolBars()
{
    //
}

void GA_Tester_mainWindow::createDockWidgets()
{
    welcome = new QPushButton(QIcon(":/images/welcomeScreenAct.ico"), tr("Giới thiệu"));
    setButtonStyle(welcome);
    mainFunct = new QPushButton(QIcon(":/images/mainFunctAct.ico"), tr("Phân tích đồ thị"));
    setButtonStyle(mainFunct);
    designMode = new QPushButton(QIcon(":/images/graphDesignMode.ico"), tr("Thiết kế đồ thị"));
    designMode->addAction(graphDesignModeAction);
    setButtonStyle(designMode);

    helpMode = new QPushButton(QIcon(":/images/helpAct.ico"), tr("Trợ giúp"));
    setButtonStyle(helpMode);

    QSpacerItem* verticalSpacer{new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding)};
    QVBoxLayout* leftLayout{new QVBoxLayout()};
    leftLayout->addWidget(mainFunct);
    leftLayout->addWidget(designMode);
    leftLayout->addWidget(welcome);
    leftLayout->addWidget(helpMode);
    leftLayout->addItem(verticalSpacer);
    leftButtonBar->setLayout(leftLayout);
    leftDocWidget->setWidget(leftButtonBar);
    //leftDocWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, leftDocWidget.data());
}
GA_Tester_mainWindow::GA_Tester_mainWindow(QWidget *parent)
    : QMainWindow(parent) ,
      browser{new QTextBrowser()},
      dfs_bfs_widget{new DFS_BFS_Widget()},
      leftButtonBar{new QGroupBox("Công cụ chính")},
      leftDocWidget{new QDockWidget()}
{
   createActions();
   createMenus();
   createDockWidgets();
   setFont(QFont("Ubuntu", 10));
   setWindowIcon(QIcon(":/images/appIcon.ico"));
   setWindowTitle(tr("Graph Algorithms QTester"));
   browser->setSource(QUrl("qrc:/url/dfs.html"));
   setCentralWidget(dfs_bfs_widget.data());
   //setCentralWidget(browser);
}

void GA_Tester_mainWindow::setButtonStyle(QPushButton *button)
{
    button->setIconSize(QSize(32, 32));
    button->setCheckable(true);
    button->setAutoExclusive(true);
}

void GA_Tester_mainWindow::displayFuntionsScreen()
{

}

void GA_Tester_mainWindow::displayWelcomeScreen()
{

}

void GA_Tester_mainWindow::displayAppInfo()
{

}
