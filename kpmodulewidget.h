#ifndef KPMODULEWIDGET_H
#define KPMODULEWIDGET_H

#include <QWidget>
#include "basewidget.h"
#include "dfs_bfs_module.h"
namespace Ui {
class KPModuleWidget;
}
class KPModuleWidget final: public QWidget, public BaseWidget
{
    Q_OBJECT
private:
    Ui::KPModuleWidget* ui;
public:
    explicit KPModuleWidget(QWidget *parent = nullptr);
public slots:
    virtual void setDataStructure() override;
    virtual void setGraphType() override;
    virtual bool loadGraphData() override;
    virtual void getAnalysisAlgorithm()const override;
    virtual void getAppsAlgorithm()const override;
    virtual void getInfoAlgorithm()const override;
    virtual bool checkInputData()const override;
    virtual void openFileDialog() override;
signals:
    void gotFilePath(QString);
};

#endif // KPMODULEWIDGET_H
