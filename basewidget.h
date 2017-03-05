#ifndef BaseWidget_H
#define BaseWidget_H
#include <QVector>
#include <QFileDialog>
class BaseWidget
{
protected:
    QString filePath;
    QString algorithm;
    QString dataStructure;
    QString graphType;
    QVector<QVector<int>>matrix;
    QVector<int>vertices;
    QVector<int>pass;
    int totalNumVertices;
public:
    virtual void openFileDialog() = 0;
    virtual void setFilePath(QString path) = 0;
    virtual void setDataStructure() = 0;
    virtual void setGraphType() = 0;
    virtual bool checkInputData() const = 0;
    virtual bool loadGraphData() = 0;
    virtual void getInfoAlgorithm() const = 0;
    virtual void getAnalysisAlgorithm() const = 0;
    virtual void getAppsAlgorithm() const = 0;
    virtual ~BaseWidget() = default;

};
#endif // BaseWidget_H

