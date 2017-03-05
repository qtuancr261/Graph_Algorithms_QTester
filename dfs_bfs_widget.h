#ifndef DFS_BFS_Widget_H
#define DFS_BFS_Widget_H

#include <QWidget>
#include <QFileDialog>
#include <QSpinBox>
#include <QScopedPointer>
#include "basewidget.h"
#include "dfs_bfs_module.h"
#include "inputdialog.h"
namespace Ui {
class DFS_BFS_Widget;
}

class DFS_BFS_Widget final : public QWidget, public BaseWidget
{
    Q_OBJECT

private:
    QScopedPointer<Ui::DFS_BFS_Widget> ui;
    int startVertex;
    int endVertex;
    QScopedPointer<InputDialog> inputDialog;
public:
    explicit DFS_BFS_Widget(QWidget *parent = nullptr);
    ~DFS_BFS_Widget();
signals:
    void gotFilePath(QString);
    void callInputDialog(int);
public slots:
    virtual void openFileDialog() override;
    virtual void setFilePath(QString path) override;
    virtual void setDataStructure() override;
    virtual void setGraphType() override;
    virtual bool checkInputData() const override;
    virtual bool loadGraphData() override;
    virtual void getAnalysisAlgorithm() const override;
    virtual void getAppsAlgorithm() const override;
    virtual void getInfoAlgorithm() const;
    void setStartEnd(int startValue, int endValue);
    void setAlgorithm();
    void getStartEnd();
    void travelGraph();
    void findConnectedComponents();
    void simplifyGraph();
};

#endif // DFS_BFS_Widget_H
