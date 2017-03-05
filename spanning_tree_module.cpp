#include "spanning_tree_module.h"
void SpanningTreeModule::readEdgeList(QString fileName, QVector<Edge> &edges, QVector<int>& roots, int& totalNumVertices)
{
    QFile file{fileName};
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        edges.clear();
        QTextStream read(&file);
        int startVertex{}, endVertex{}, weightIndex{};
        read >> totalNumVertices;
        roots = QVector<int>(totalNumVertices + 1, 0);
        while(!read.atEnd())
        {
            read >> startVertex >> endVertex >> weightIndex;
            if (startVertex == 0 || endVertex == 0 || weightIndex == 0) break;
            edges.push_back(Edge{startVertex, endVertex, weightIndex});
        }
        file.close();
    }
}

int SpanningTreeModule::findRoot(QVector<int> roots, int vertex)
{
    while(roots[vertex] != 0)
        vertex = roots[vertex];
    return vertex;
}
int SpanningTreeModule::findLabel(const QString& label,const QVector<QString>& labels)
{
    for (int i{}; i < labels.size(); i++)
        if (labels[i] == label) return i;
    return 0;
}

// Kruskal
QString SpanningTreeModule::solveMinSpanningTree_Kruskal(QVector<Edge> &edges, QVector<int> &roots, const int& totalNumvertices)
{
    QString solution{};
    std::sort(std::begin(edges), std::end(edges));
    int countEdges{}, vertexA{}, vertexB{}, SumOfWeight{};
    solution = QString("Cây khung ngắn nhât theo thuật toán Krukal: ");
    for (Edge& i:edges)
    {
        vertexA = findRoot(roots, i.getStart());
        vertexB = findRoot(roots, i.getEnd());
        if (vertexA != vertexB)
        {
            roots[vertexA] = vertexB;
            solution.append("(" +QString::number(i.getStart()) + ", " + QString::number(i.getEnd()) + ") ");
            countEdges++;
            SumOfWeight += i.getWeight();
        }
        if (countEdges == totalNumvertices - 1) break;
    }
    solution.append("Chi phí tối ưu: " + QString::number(SumOfWeight) + '\n');
    return solution;
}

void SpanningTreeModule::readComNetwork(QString fileName, QVector<Edge> &edges, QVector<int> &roots, int &totalNumVertices)
{
    QFile file{fileName};
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        edges.clear();
        QTextStream read{&file};
        QString startCity{}, endCity{};
        int startNum{}, endNum{}, cost{};
        QVector<QString> labels;
        labels.push_back(QString("Unknown"));
        read >> totalNumVertices;
        roots = QVector<int>(totalNumVertices + 1, 0);
        while(!read.atEnd())
        {
            read >> startCity;
            startNum =  findLabel(startCity, labels);
            if (startNum == 0) {startNum = labels.size(); labels.push_back(startCity);}
            read >> endCity;
            endNum = findLabel(endCity, labels);
            if (endNum == 0) {endNum = labels.size(); labels.push_back(endCity);}
            read >> cost;
            if (cost == 0) break;
            edges.push_back(Edge(startCity, endCity, cost, startNum, endNum));
        }
        file.close();
    }
}

QString SpanningTreeModule::solveComputerNetwork(QVector<Edge> &edges, QVector<int> &roots, const int &totalNumVertices)
{
    QString solution{};
    std::sort(std::begin(edges), std::end(edges));
    int countEdges{}, vertexA{}, vertexB{}, SumOfWeight{};
    solution = QString("Hệ thống kết nối mạng lan tối ưu theo thuật toán Krukal: \n");
    for (Edge& i:edges)
    {
        vertexA = findRoot(roots,i.getStart());
        vertexB = findRoot(roots, i.getEnd());
        if (vertexA != vertexB)
        {
            roots[vertexA] = vertexB;
            solution.append(i.getStartCity() + " -> " + i.getEndCity() + '\n');
            countEdges++;
            SumOfWeight += i.getWeight();
        }
        if (countEdges == totalNumVertices - 1) break;
    }
    solution.append("Chi phí tối ưu: " + QString::number(SumOfWeight) + '\n');
    return solution;
}
void SpanningTreeModule::readVertexList(QString fileName, Q_AdjaMatrix &matrix, int &totalNumVertices)
{
    QFile file{fileName};
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        matrix.clear();
        QTextStream read{&file};
        read >> totalNumVertices;
        matrix = Q_AdjaMatrix(totalNumVertices + 1, QVector<int>(totalNumVertices + 1, MIN));
        int i{}, j{}, k{};
        while(!read.atEnd())
        {
            read >> i >> j >> k;
            matrix[i][i] = matrix[j][j] = 0;
            matrix[i][j] = matrix[j][i] = k;
        }
        file.close();
    }
}

QString SpanningTreeModule::solveMinSpanningTree_Prim(Q_AdjaMatrix &matrix, const int &totalNumVertices)
{
    QString solution("Cây khung nhỏ nhất theo thuật toán Prim: ");
    QVector<Vertex> vertex;
    vertex.push_back(Vertex(0,0, false));
    for (int i{1}; i <= totalNumVertices; i++)
    {
        int dis = matrix[1][i];
        vertex.push_back(Vertex(1, dis, false));
        //out << vertex[i].getNear() << " " << vertex[i].getDistance() << " " << vertex[i].checkPassed() << endl;
    }
    vertex[1].setPassed(true);
    int nextVertex{}, minDistance{}, totalDistance{};
    for (int i{1}; i < totalNumVertices; i++)
    {
        minDistance = MIN;
        for (int index{1}; index <= totalNumVertices; index++)
            if (vertex[index].getDistance() < minDistance && vertex[index].checkPassed() == false)
            {
                minDistance = vertex[index].getDistance();
                nextVertex = index;
            }
        vertex[nextVertex].setPassed(true);
        solution.append("( " + QString::number(nextVertex) + ", " + QString::number(vertex[nextVertex].getNear()) + ")  ");
        //out << nextVertex << endl;
        totalDistance += vertex[nextVertex].getDistance();
        for (int index{1}; index <= totalNumVertices; index++)
            if (vertex[index].checkPassed() == false && matrix[nextVertex][index] < vertex[index].getDistance())
            {
                vertex[index].setDistance(matrix[nextVertex][index]);
                vertex[index].setNear(nextVertex);
            }
    }
    solution.append("\n Chiều dài của cây khung: " + QString::number(totalDistance) + "\n" );
    return solution;
}

QString SpanningTreeModule::Prim_info()
{
    return " ";
}

QString SpanningTreeModule::Kruskal_info()
{
    return " ";
}
