#ifndef DFS_BFS_MODULE_H
#define DFS_BFS_MODULE_H
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <QQueue>
extern QTextStream out;
using Q_AdjaMatrix = QVector<QVector<int>>;
enum class mode{dfs_bfs,euler_hamilton, spanning_tree};
namespace IOModule
{
// read file
void readUGEdgeList(QString fileName, Q_AdjaMatrix& matrix, int& num, mode modeName);
void readDGEdgeList(QString fileName, Q_AdjaMatrix& matrix, int& num, mode modeName);
void readAdjaMatrix(QString fileName, Q_AdjaMatrix& matrix, int& num, mode modeName);
// DFS Algorithm
void DFS_1(QVector<int>&pass,const Q_AdjaMatrix& matrix,const int& num,QString& answer, int vertex = 1);
QString DFS(QVector<int>&pass, Q_AdjaMatrix& matrix,const int&num);
// BFS Algorithm
void BFS_1(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num, QString& answer, int vertex = 1);
QString BFS(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num);
QString BFS_Info();
QString BFS_Analysis();
QString BFS_Applications();
// Simplify Graph
void DFS_1_Simplify(QVector<int>&pass, Q_AdjaMatrix& matrix, const int& num, int vertex = 1);
void BFS_1_Simplify(QVector<int>&pass, Q_AdjaMatrix& matrix, const int& num, int vertex = 1);
QString simplifyGraph(QVector<int>&pass, Q_AdjaMatrix matrix, const int& num, void(*AlgorithmSimplify)(QVector<int>&, Q_AdjaMatrix&, const int&, int));
// Check Graph Connectivity
QString checkConectivityUGraph(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num);
// Find ways Between 2 vertices using DFS algorithm
void DFS_1_Find(int vertex, int endVertex, QVector<int>&pass, QVector<int>&path, const Q_AdjaMatrix& matrix, QString& answer, const int& num);
QString findWayBetween2Vertices(int startVertex, int endVertex, QVector<int>&pass, const Q_AdjaMatrix& matrix, int num);
// output Adjacency Matrix
QString outputMatrix(const Q_AdjaMatrix& matrix, const int& num);
}

#endif // DFS_BFS_MODULE_H
