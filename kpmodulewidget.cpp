#include "kpmodulewidget.h"
#include "ui_kpmodulewidget.h"
KPModuleWidget::KPModuleWidget(QWidget *parent) : QWidget(parent), ui{new Ui::KPModuleWidget}
{
    ui->setupUi(this);
    setWindowTitle(tr("Kruskal - Prim Module Widget"));
    setFont(QFont("Ubuntu", 11));
    algorithm = "None";
    //ui->groupBox_2->hide();
    //ui->IODataBox->layout()->setSizeConstraint(QLayout::SetMinimumSize);
    //layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void KPModuleWidget::setDataStructure()
{
    dataStructure = ui->dataTypes->checkedButton()->text();
}

void KPModuleWidget::setGraphType()
{
    graphType = ui->graphTypes->checkedButton()->text();
}

bool KPModuleWidget::loadGraphData()
{
    static QString preFilePath{};
    static QString preStructure{};
    static QString preGraphType{};
    if (filePath != preFilePath || dataStructure != preStructure || graphType != preGraphType)
    {
        if (dataStructure == "Ma trận kề") IOModule::readAdjaMatrix(filePath, matrix, totalNumVertices, mode::spanning_tree);
        else if (dataStructure == "Danh sách cạnh cung")
        {
            if (graphType == "Vô hướng") IOModule::readUGEdgeList(filePath, matrix, totalNumVertices, mode::spanning_tree);
            else                         IOModule::readDGEdgeList(filePath, matrix, totalNumVertices, mode::spanning_tree);
        }
        preFilePath = filePath;
        preStructure = dataStructure;
        preGraphType = graphType;
    }
    return true;
}

void KPModuleWidget::getAnalysisAlgorithm() const
{

}

void KPModuleWidget::getAppsAlgorithm() const
{

}

void KPModuleWidget::getInfoAlgorithm() const
{

}

bool KPModuleWidget::checkInputData() const
{
    return true;
}

void KPModuleWidget::openFileDialog()
{
    QString fileName{};
    filePath = QFileDialog::getOpenFileName(this, "Chọn file chứa thông tin về đô thị", QDir::currentPath(), "Text file(*.txt)");
    if (!filePath.isEmpty())
    {
        fileName  = filePath;
        emit gotFilePath(filePath);
    }
}

