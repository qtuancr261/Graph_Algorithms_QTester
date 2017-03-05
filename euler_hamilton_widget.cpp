#include "euler_hamilton_widget.h"
#include "ui_euler_hamilton_widget.h"
Euler_Hamilton_Widget::Euler_Hamilton_Widget(QWidget *parent) : QWidget{parent}, ui{new Ui::Euler_Hamilton_Widget}
{  
    // Initialize Widget UI
    ui->setupUi(this);
    setFont(QFont("Tahoma", 11)); // for windows version
    //setFont(QFont("Ubuntu", 11)); // for linux version
    setWindowIcon(QIcon(":/images/molecules13.png"));
    setWindowTitle("Euler-Hamilton Module Widget");
    //ui->filePathLineEdit->setText(QDir::currentPath());
    algorithm = "Euler";
    // Input Data
    QObject::connect(ui->dataStructures, SIGNAL(buttonClicked(int)), this, SLOT(setDataStructure()));
    QObject::connect(ui->graphTypes, SIGNAL(buttonClicked(int)), this, SLOT(setGraphType()));
    QObject::connect(ui->tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(setAlgorithm(int)));
    QObject::connect(ui->loadFileButton, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    QObject::connect(this, SIGNAL(gotFilePath(QString)), ui->filePathLineEdit, SLOT(setText(QString)));
    QObject::connect(ui->filePathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setFilePath(QString)));
    // Euler Algorithm
    QObject::connect(ui->infoEulerButton, SIGNAL(clicked(bool)), this, SLOT(getInfoAlgorithm()));
    QObject::connect(ui->analysisEulerButton, SIGNAL(clicked(bool)), this, SLOT(getAnalysisAlgorithm()));
    QObject::connect(ui->appEulerButton, SIGNAL(clicked(bool)), this, SLOT(getAppsAlgorithm()));
    QObject::connect(ui->solveEulerButton, SIGNAL(clicked(bool)), this, SLOT(solveEulerAlgorithm()));
    // Hamilton Algorithm
    QObject::connect(ui->infoHalButton, SIGNAL(clicked(bool)), this, SLOT(getInfoAlgorithm()));
    QObject::connect(ui->analysisHalButton, SIGNAL(clicked(bool)), this, SLOT(getAnalysisAlgorithm()));
    QObject::connect(ui->appHalButton, SIGNAL(clicked(bool)), this, SLOT(getAppsAlgorithm()));
    QObject::connect(ui->solveHalButton, SIGNAL(clicked(bool)), this, SLOT(solveHamiltonAlgorithm()));
    QObject::connect(ui->solveTravellingButton, SIGNAL(clicked(bool)), this, SLOT(solveTravellingProblem()));
}

Euler_Hamilton_Widget::~Euler_Hamilton_Widget()
{
    delete ui;
}

void Euler_Hamilton_Widget::setAlgorithm(int index)
{
   if (index == 0)
       algorithm = "Euler";
   else algorithm = "Hamilton";
}

void Euler_Hamilton_Widget::openFileDialog()
{
    QString fileName{};
    fileName = QFileDialog::getOpenFileName(this, "Chọn tệp chứa thông tin về đồ thị", QDir::currentPath(), "text file(*.txt)");
    if (!fileName.isEmpty())
    {
        emit gotFilePath(fileName);
    }
}

void Euler_Hamilton_Widget::setFilePath(QString path)
{
    filePath = path;
}

void Euler_Hamilton_Widget::setDataStructure()
{
    dataStructure = ui->dataStructures->checkedButton()->text();
}

void Euler_Hamilton_Widget::setGraphType()
{
    graphType = ui->graphTypes->checkedButton()->text();
}

bool Euler_Hamilton_Widget::loadGraphData()
{
    static QString preFilePath{};
    static QString preStructure{};
    static QString preGraphType{};
    static bool isNotSafe{false};
    try
    {
        if (filePath != preFilePath || dataStructure != preStructure || graphType != preGraphType)
        {
            preFilePath = filePath;
            preStructure = dataStructure;
            preGraphType = graphType;
            if (dataStructure == "Ma trận kề") IOModule::readAdjaMatrix(filePath, matrix, totalNumVertices, mode::euler_hamilton);
            else if (dataStructure == "Danh sách cạnh cung")
            {
                if (graphType == "Vô hướng") IOModule::readUGEdgeList(filePath, matrix, totalNumVertices, mode::euler_hamilton);
                else                         IOModule::readDGEdgeList(filePath, matrix, totalNumVertices, mode::euler_hamilton);
            }
            isNotSafe = false;
            return true;
        }
        if (isNotSafe) throw(QString("Hãy cập nhật lại dữ liệu đầu vào!"));
        return true;
    }catch(const QString error)
    {
        QMessageBox::critical(this, "Error", error);
        isNotSafe = true;
        return false;
    }
}
bool Euler_Hamilton_Widget::checkInputData() const
{
    QTextBrowser* currentBrowser{nullptr};
    if (algorithm == "Euler") currentBrowser = ui->textBrowserEuler;
    else                      currentBrowser = ui->textBrowserHal;
    currentBrowser->clear();
    if (filePath.isEmpty())
    {
        currentBrowser->setHtml("<i>Bạn chưa chọn tệp chứa thông tin về đồ thị.</i>");
        return false;
    }
    if(dataStructure.isEmpty())
    {
        currentBrowser->setHtml("<i>Bạn chưa chọn kiểu biểu diễn của đồ thị.</i>");
        return false;
    }
    if(graphType.isEmpty())
    {
        currentBrowser->setHtml("<i>Bạn chưa chọn dạng của đồ thị.</i>");
        return false;
    }
    emit gotAllData();
    return true;
}

void Euler_Hamilton_Widget::getInfoAlgorithm() const
{
    if (algorithm == "Euler")
    {
        ui->textBrowserEuler->clear();
        ui->textBrowserEuler->setHtml(EulerHamiltonModule::EulerInfo());
    }
    else
    {
        ui->textBrowserHal->clear();
        ui->textBrowserHal->setHtml(EulerHamiltonModule::HamiltonInfo());
    }
}

void Euler_Hamilton_Widget::getAnalysisAlgorithm() const
{
    if (algorithm == "Euler")
    {
        ui->textBrowserEuler->clear();
        ui->textBrowserEuler->setHtml(EulerHamiltonModule::EulerAnalysis());
    }
    else
    {
        ui->textBrowserHal->clear();
        ui->textBrowserHal->setHtml(EulerHamiltonModule::HamiltonAnalysis());
    }
}

void Euler_Hamilton_Widget::getAppsAlgorithm() const
{
    if (algorithm == "Euler")
    {
        ui->textBrowserEuler->clear();
        ui->textBrowserEuler->setHtml(EulerHamiltonModule::EulerApp());
    }
    else
    {
        ui->textBrowserHal->clear();
        ui->textBrowserHal->setHtml(EulerHamiltonModule::HamiltonApp());
    }
}

void Euler_Hamilton_Widget::solveEulerAlgorithm()
{
    if (checkInputData() == true && loadGraphData() == true)
    {
        ui->textBrowserEuler->clear();
        if (graphType == "Vô hướng")
            ui->textBrowserEuler->setHtml(EulerHamiltonModule::solveEulerUGraph(ui->textBrowserEuler, pass, matrix, vertices, totalNumVertices));
        else
            ui->textBrowserEuler->setHtml(EulerHamiltonModule::solveEulerDGraph(ui->textBrowserEuler, pass, matrix, vertices, totalNumVertices));
    }
}

void Euler_Hamilton_Widget::solveHamiltonAlgorithm()
{
    if (checkInputData() == true && loadGraphData() == true)
    {
        ui->textBrowserHal->clear();
        ui->textBrowserHal->setHtml(EulerHamiltonModule::solveHamilton(pass, matrix, hamilton, totalNumVertices));
    }
}

void Euler_Hamilton_Widget::solveTravellingProblem()
{
    if (checkInputData() == true && loadGraphData() == true)
    {
        ui->textBrowserHal->clear();
        ui->textBrowserHal->setHtml(EulerHamiltonModule::solveTravellingProblem(pass, matrix, vertices, totalNumVertices));
    }
}


