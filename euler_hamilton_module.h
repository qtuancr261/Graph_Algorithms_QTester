#ifndef EULER_HAMILTON_MODULE_H
#define EULER_HAMILTON_MODULE_H
#include "dfs_bfs_module.h"
#include <QInputDialog>
#include <QStack>
#include <QTextBrowser>
#include <QDir>
namespace EulerHamiltonModule
{
// Euler
void DFS_1(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num, int vertex = 1);
QString EulerInfo();
QString EulerAnalysis();
QString EulerApp();
bool checkConnectivityUGraph(QVector<int>&pass,const Q_AdjaMatrix& matrix, const int& num);
bool checkEulerConditionUGraph(const Q_AdjaMatrix& matrix, QVector<int>&vertices, const int& num);

bool checkConnectivityDGraph(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num);
bool checkEulerConditionDGraph(const Q_AdjaMatrix& matrix, QVector<int>&vertices, const int& num);

QString solveEulerUGraph(QTextBrowser* browser,QVector<int>& pass,Q_AdjaMatrix matrix, QVector<int>& vertices, const int& num);
QString solveEulerDGraph(QTextBrowser* browser,QVector<int>& pass,Q_AdjaMatrix matrix, QVector<int>& vertices, const int& num);
// Hamilton
QString HamiltonInfo();
QString HamiltonAnalysis();
QString HamiltonApp();
QString solveHamilton(QVector<int>& pass,const Q_AdjaMatrix& matrix, QVector<int>& hamilton, const int& num);
void tryStepHamilton(int stepIndex, QVector<int>& pass, const Q_AdjaMatrix&  matrix, QVector<int>& hamilton,QString& answer, const int& num);
void hamiltonPath(const QVector<int>& hamilton, QString& answer, const int& num);
void hamiltonCircuit(const QVector<int>& hamilton, QString& answer, const int& num);
void tryStepTravelling(int stepIndex, QVector<int>&pass, const Q_AdjaMatrix& matrix, QVector<int>&vertices, QVector<int>& optimizePath,int& minCost, const int& num);
void findOptimizePath(const Q_AdjaMatrix& matrix, QVector<int>& vertices, QVector<int>&optimizePath, int& minCost, const int& num);
QString solveTravellingProblem(QVector<int>& pass, const Q_AdjaMatrix& matrix, QVector<int>& vertices, const int& num);
}
#endif // EULER_HAMILTON_MODULE_H
