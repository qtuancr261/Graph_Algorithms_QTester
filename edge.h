#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include <utility>
#include <QString>
using std::rel_ops::operator !=;
using std::rel_ops::operator <=;
using std::rel_ops::operator >;
using std::rel_ops::operator >=;
class Edge
{
private:
    int start;
    int end;
    int weight;
    QString eCity;
    QString sCity;
public:
    Edge() = default;
    explicit Edge(int startVertex, int endVertex, int weightValue, QString strStartVertex = "None", QString strEndVertex = "None");
    explicit Edge(QString strStartVertex, QString strEndVertex, int weightValue, int startVertex = 0, int endVertex = 0);
    Edge(const Edge& anEdge) = default;
    Edge& operator=(const Edge& anEdge) = default;
    bool operator==(const Edge& anEdge) const;
    bool operator<(const Edge& anEdge) const;
    int getStart() const;
    QString getStartCity() const;
    int getEnd() const;
    QString getEndCity() const;
    int getWeight() const;
    ~Edge() = default;
};
#endif // EDGE_H
