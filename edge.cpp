#include "edge.h"
Edge::Edge(int startVertex, int endVertex, int weightValue, QString strStartVertex, QString strEndVertex)
    : start{startVertex}, end{endVertex}, weight{weightValue}, sCity(strStartVertex), eCity(strEndVertex)
{

}

Edge::Edge(QString strStartVertex, QString strEndVertex, int weightValue, int startVertex, int endVertex)
    : sCity(strStartVertex), eCity(strEndVertex), weight{weightValue}, start{startVertex}, end{endVertex}
{

}

bool Edge::operator==(const Edge &anEdge) const
{
    return (weight == anEdge.weight);
}

bool Edge::operator<(const Edge &anEdge) const
{
    return (weight < anEdge.weight);
}

int Edge::getEnd() const
{
    return end;
}

QString Edge::getEndCity() const
{
    return eCity;
}

int Edge::getStart() const
{
    return start;
}

QString Edge::getStartCity() const
{
    return sCity;
}

int Edge::getWeight() const
{
    return weight;
}
