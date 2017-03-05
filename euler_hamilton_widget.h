#ifndef Euler_Hamilton_Widget_H
#define Euler_Hamilton_Widget_H

#include <QWidget>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "dfs_bfs_module.h"
#include "basewidget.h"
#include "euler_hamilton_module.h"
namespace Ui
{
class Euler_Hamilton_Widget;
}
class Euler_Hamilton_Widget final : public QWidget, public BaseWidget
{
    Q_OBJECT
private:
    Ui::Euler_Hamilton_Widget* ui;
    QVector<int>hamilton;
public:
    explicit Euler_Hamilton_Widget(QWidget *parent = nullptr);
    ~Euler_Hamilton_Widget();
signals:
    void gotFilePath(QString);
    void gotAllData() const;
public slots:
    virtual void openFileDialog() override;
    virtual void setFilePath(QString) override;
    virtual void setDataStructure() override;
    virtual void setGraphType() override;
    virtual bool loadGraphData() override;
    virtual bool checkInputData() const override;
    virtual void getInfoAlgorithm() const override;
    virtual void getAnalysisAlgorithm() const override;
    virtual void getAppsAlgorithm() const override;
    void setAlgorithm(int);
    void solveEulerAlgorithm();
    void solveHamiltonAlgorithm();
    void solveTravellingProblem();
};

#endif // Euler_Hamilton_Widget_H
