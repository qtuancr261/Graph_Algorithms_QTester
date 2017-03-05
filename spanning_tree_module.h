#ifndef SPANNING_TREE_MODULE_H
#define SPANNING_TREE_MODULE_H
#include <algorithm>
#include <iterator>
#include "dfs_bfs_module.h"
#include "edge.h"
#include "vertex.h"
namespace SpanningTreeModule
{
    const int MIN{999};
    QString Kruskal_info();
    QString Prim_info();
    void readEdgeList(QString fileName, QVector<Edge>& edges, QVector<int>& roots, int& totalNumVertices);
    void readComNetwork(QString fileName, QVector<Edge>& edges, QVector<int>& roots, int& totalNumVertices);
    int findRoot(QVector<int>roots, int vertex);
    int findLabel(const QString& label,const QVector<QString>& labels);
    QString solveMinSpanningTree_Kruskal(QVector<Edge>& edges, QVector<int>&roots, const int& totalNumVertices);
    QString solveComputerNetwork(QVector<Edge>& edges, QVector<int>&roots, const int& totalNumVertices);
    void readVertexList(QString fileName, Q_AdjaMatrix& matrix, int& totalNumVertices);
    QString solveMinSpanningTree_Prim(Q_AdjaMatrix& matrix, const int& totalNumVertices);
}
#endif // SPANNING_TREE_MODULE_H
