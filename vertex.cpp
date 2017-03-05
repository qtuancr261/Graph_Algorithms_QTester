#include "vertex.h"
Vertex::Vertex(int near, int dis, bool status) : nearVertex{near}, distance{dis}, isPassed{status}
{

}

bool Vertex::operator==(const Vertex &srcVertex) const
{
    return (distance == srcVertex.distance);
}

bool Vertex::operator <(const Vertex &srcVertex) const
{
    return (distance < srcVertex.distance);
}

int Vertex::getNear() const
{
    return nearVertex;
}

int Vertex::getDistance() const
{
    return distance;
}

bool Vertex::checkPassed() const
{
    return isPassed;
}

void Vertex::setNear(int near)
{
    nearVertex = near;
}

void Vertex::setDistance(int dis)
{
    distance = dis;
}

void Vertex::setPassed(bool status)
{
    isPassed = status;
}

