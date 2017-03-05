#ifndef VERTEX_H
#define VERTEX_H

#include <utility>
#include <QString>
using std::rel_ops::operator !=;
using std::rel_ops::operator <=;
using std::rel_ops::operator >;
using std::rel_ops::operator >=;
class Vertex
{
private:
    int nearVertex;
    int distance;
    bool isPassed;
public:
    Vertex() = default;
    Vertex(int near, int dis, bool status = false);
    Vertex(const Vertex& srcVertex) = default;
    Vertex& operator=(const Vertex& srcVertex) = default;
    bool operator==(const Vertex& srcVertex) const;
    bool operator <(const Vertex& srcVertex) const;
    int getNear() const;
    int getDistance() const;
    bool checkPassed() const;
    void setNear(int near);
    void setDistance(int dis);
    void setPassed(bool status);
    ~Vertex() = default;
};

#endif // VERTEX_H
