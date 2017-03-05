#include "dfs_bfs_widget.h"
#include "ui_dfs_bfs_widget.h"

DFS_BFS_Widget::DFS_BFS_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DFS_BFS_Widget),
    inputDialog(new InputDialog())
{
    // Initialize
    ui->setupUi(this);
    algorithm = "None";
    setWindowIcon(QIcon(":/images/dfsbfs.ico"));
    //setFont(QFont("Tahoma", 12));// for windows version
    setFont(QFont("Ubuntu", 10));// for linux version
    setWindowTitle("DFS - BFS Module Widget");
    // Input Data signal-slot
    QObject::connect(ui->algorithmsBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setAlgorithm()));
    QObject::connect(ui->dataStructures, SIGNAL(buttonClicked(int)), this, SLOT(setDataStructure()));
    QObject::connect(ui->graphTypes, SIGNAL(buttonClicked(int)), this, SLOT(setGraphType()));
    QObject::connect(ui->loadFileButton, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    QObject::connect(this, SIGNAL(gotFilePath(QString)), ui->filePathLineEdit, SLOT(setText(QString)));
    QObject::connect(ui->filePathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setFilePath(QString)));
    QObject::connect(this, SIGNAL(callInputDialog(int)), inputDialog.data(), SLOT(setValue(int)));
    QObject::connect(inputDialog.data(), SIGNAL(gotAllValues(int,int)), this, SLOT(setStartEnd(int,int)));
    // Process signal-slot
    QObject::connect(ui->analysisButton, SIGNAL(clicked(bool)), this, SLOT(getAnalysisAlgorithm()));
    QObject::connect(ui->sourceCodeButton, SIGNAL(clicked(bool)), this, SLOT(getAppsAlgorithm()));
    QObject::connect(ui->travelButton, SIGNAL(clicked(bool)), this, SLOT(travelGraph()));
    QObject::connect(ui->connectedComButton,  SIGNAL(clicked(bool)), this, SLOT(findConnectedComponents()));
    QObject::connect(ui->findWayButton,  SIGNAL(clicked(bool)), this, SLOT(getStartEnd()));
    QObject::connect(ui->simplifyButton, SIGNAL(clicked(bool)), this, SLOT(simplifyGraph()));
}

DFS_BFS_Widget::~DFS_BFS_Widget()
{
    // the compiler will do everyhting for you
}

void DFS_BFS_Widget::setAlgorithm()
{
    algorithm = ui->algorithmsBox->currentText();
}

void DFS_BFS_Widget::setDataStructure()
{
    dataStructure = ui->dataStructures->checkedButton()->text();
}

void DFS_BFS_Widget::setGraphType()
{
    graphType = ui->graphTypes->checkedButton()->text();
}

void DFS_BFS_Widget::setStartEnd(int startValue, int endValue)
{
    startVertex = startValue;
    endVertex = endValue;
    ui->solutionView->clear();
    ui->solutionView->setHtml(IOModule::findWayBetween2Vertices(startVertex, endVertex, pass, matrix, totalNumVertices));

}

void DFS_BFS_Widget::setFilePath(QString path)
{
    filePath = path;
}

void DFS_BFS_Widget::openFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Chọn tệp chứa thông tin về đồ thị", QDir::currentPath(), "text file(*.txt)");
    if (!fileName.isEmpty())
    {
        emit gotFilePath(fileName);
    }
}

bool DFS_BFS_Widget::checkInputData() const
{
    ui->solutionView->clear();
    if (algorithm == "None")
    {
        ui->solutionView->setHtml("<i>Bạn chưa chọn thuật toán.</i>");
        return false;
    }
    else if (filePath.isEmpty())
    {
        ui->solutionView->setHtml("<i>Bạn chưa chọn tệp chứa thông tin về đồ thị.</i>");
        return false;
    }
    else  if (dataStructure.isEmpty())
    {
        ui->solutionView->setHtml("<i>Bạn chưa chọn kiểu biểu diễn cho đồ thị.</i>");
        return false;
    }
    else if (graphType.isEmpty())
    {
        ui->solutionView->setHtml("<i>Bạn chưa chọn loại đồ thị.</i>");
        return false;
    }
    else
    {
        ui->solutionView->setHtml(algorithm);
        ui->solutionView->append("Dạng đồ thị: " + dataStructure);
        ui->solutionView->append("Loại đồ thị: " + graphType);
        return true;
    }
}

bool DFS_BFS_Widget::loadGraphData()
{
    static QString preFilePath{};
    static QString preStructure{};
    static QString preGraphType{};
    static bool isNotSafe{false};
    try
    {
        if (filePath != preFilePath || dataStructure != preStructure || graphType != preGraphType)
            // Anything was changed will cause the program to reload the adjacent matrix
        {
            preFilePath = filePath;
            preStructure = dataStructure;
            preGraphType = graphType;
            if (dataStructure == "Ma trận kề") IOModule::readAdjaMatrix(filePath, matrix, totalNumVertices, mode::dfs_bfs);
            else if (dataStructure == "Danh sách cạnh/cung")
            {
                if (graphType == "Vô hướng") IOModule::readUGEdgeList(filePath, matrix, totalNumVertices, mode::dfs_bfs);
                else                         IOModule::readDGEdgeList(filePath, matrix, totalNumVertices, mode::dfs_bfs);
            }
            isNotSafe = false; // without exceptions, it will be safe to start doing something
            return true;
        }
        if (isNotSafe) throw(QString("Hãy cập nhật lại dữ liệu đầu vào!"));
        return true;
    }catch(const QString error)
    {
        QMessageBox::critical(this, "Error", error);
        isNotSafe = true;
        return false; // exceptions
    }
}

void DFS_BFS_Widget::getAnalysisAlgorithm() const
{
    ui->solutionView->clear();
    if (algorithm == "None")                                ui->solutionView->setHtml("<i>Bạn chưa chọn thuật toán.</i>");
    else if (algorithm == "Thuật toán DFS")  ui->solutionView->setSource(QUrl::fromLocalFile(":/url/dfs.html"));
    else if (algorithm == "Thuật toán BFS")  ui->solutionView->setHtml(IOModule::BFS_Analysis());
}

void DFS_BFS_Widget::getAppsAlgorithm() const
{
    ui->solutionView->clear();
    if (algorithm == "None")                 ui->solutionView->setHtml("<i>Bạn chưa chọn thuật toán.</i>");
    else if (algorithm == "Thuật toán DFS")  ui->solutionView->setSource(QUrl::fromLocalFile(":/url/dfs_code.html"));
    else if (algorithm == "Thuật toán BFS")  ui->solutionView->setHtml(IOModule::BFS_Applications());
}

void DFS_BFS_Widget::getInfoAlgorithm() const
{
 // nothing to do here
}

void DFS_BFS_Widget::travelGraph()
{
    if (checkInputData() == true && loadGraphData() == true)
    {
        ui->solutionView->clear();
        if (algorithm == "Thuật toán DFS") ui->solutionView->setHtml(IOModule::DFS(pass, matrix, totalNumVertices));
        else                               ui->solutionView->setHtml(IOModule::BFS(pass, matrix, totalNumVertices));
    }
}

void DFS_BFS_Widget::findConnectedComponents()
{
    if (checkInputData() == true && loadGraphData() == true)
    {
        ui->solutionView->clear();
        ui->solutionView->setHtml(IOModule::checkConectivityUGraph(pass, matrix, totalNumVertices));
        //ui->solutionView->setHtml(IOModule::outputMatrix(matrix, totalNumVertices));
    }
}

void DFS_BFS_Widget::simplifyGraph()
{
    if (checkInputData() == true && loadGraphData() == true)
    {
        ui->solutionView->clear();
        if (algorithm == "Thuật toán DFS") ui->solutionView->setHtml(IOModule::simplifyGraph(pass, matrix, totalNumVertices, IOModule::DFS_1_Simplify));
        else                               ui->solutionView->setHtml(IOModule::simplifyGraph(pass, matrix, totalNumVertices, IOModule::BFS_1_Simplify));
    }
}

void DFS_BFS_Widget::getStartEnd()
{
    if (checkInputData() == true && loadGraphData() == true)
    emit callInputDialog(totalNumVertices);
}

