#include "dfs_bfs_module.h"
// Lưa thông tin của đồ thị vào ma trận kề có cấu trúc QVector<QVector<int>>matrix
// Chứa các hàm xuất nhập thông tin biểu diễn đồ thị, một số thuật toán duyệt đồ thị như DFS-BFS
QTextStream out{stdout};
void IOModule::readUGEdgeList(QString fileName, Q_AdjaMatrix& matrix, int& num, mode modeName) // Đọc file chứa đồ thị vô hướng ở dạng d/s cạnh cung thành ma trận kề
{
    QFile file{fileName};
    for (QVector<int>& i: matrix) i.clear();
    matrix.clear();
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream read{&file};
        read >> num;
        matrix = (Q_AdjaMatrix(num + 1, QVector<int>(num + 1))); // tạo 1 ma trận có kính thước (num+1)*(num+1), toàn bộ các phần tử có giá trị là 0
        int i{}, j{};
        while (!read.atEnd())
        {
            read >> i >> j;
            if (i > matrix.size()|| j > matrix.size() || (i == j && j > 0))
            {throw QString("Dữ liệu không chính xác, hãy kiểm tra lại cấu trúc dữ liệu của tập tin đầu vào !") + QString::number(i) + QString::number(j); file.close();}
            matrix[i][j] = matrix[j][i] = 1;
        }
        file.close();
    }
    else throw(QString("Tập tin không tồn tại!"));
}
void IOModule::readDGEdgeList(QString fileName, Q_AdjaMatrix& matrix, int& num, mode modeName) // đọc file chứa đồ thị có hướng ở dạng d/s cạnh cung thành ma trận kề
{
    QFile file{fileName};
    for (QVector<int>& i:matrix) i.clear();
    matrix.clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read{&file};
        read >> num;
        int i{}, j{};
        matrix = (Q_AdjaMatrix(num+1, QVector<int>(num+1))); // tạo 1 ma trận có kính thước (num+1)*(num+1), toàn bộ các phần tử có giá trị là 0
        while(!read.atEnd())
        {
            read >> i >> j;
            if (i > matrix.size() || j > matrix.size() || (i == j && j > 0))
            {throw QString("Dữ liệu không chính xác, hãy kiểm tra lại cấu trúc dữ liệu của tập tin đầu vào !") + QString::number(i) + QString::number(j); file.close();}
            matrix[i][j] = 1;
        }
        file.close();
    }
    else throw(QString("Tập tin không tồn tại!"));
}
void IOModule::readAdjaMatrix(QString fileName, Q_AdjaMatrix& matrix, int& num, mode modeName) // đọc file chứa đồ thị ở dạng ma trận kề vào ma trận kề
{
    QFile file{fileName};
    for (QVector<int>& i: matrix) i.clear();
    matrix.clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read{&file};
        int value{};
        read >> num;
        matrix.push_back(QVector<int>(num+1)); // nạp vào ma trận hàng có thứ tự là 0 gồm num+1 phần tử 0---> bỏ qua hàng này trong các thuật toán khác(xuất, duyệt)
        for (int i{1}; i <= num; i++)
        {
            QVector<int>list;
            list.push_back(0); // nạp vào cột có thứ tự là 0 gồm num+1 phần tử 0---> bỏ qua cột này trong các thuật toán khác(xuất, duyệt)
            for (int j{1}; j <= num; j++)
            {
                read >> value;
                if (modeName == mode::dfs_bfs &&(value > 1 || value < -1)) {throw QString("Dữ liệu không chính xác, hãy kiểm tra lại cấu trúc dữ liệu của tập tin đầu vào !"); file.close();}
                list.push_back(value); // bắt đầu nạp các phần tử đọc từ file txt
            }
            matrix.push_back(list);
        }
        file.close();
    }else throw(QString("Tập tin không tồn tại!"));
}
void IOModule::DFS_1(QVector<int>&pass,const Q_AdjaMatrix& matrix,const int& num, QString& answer, int vertex)
{
    answer.append(QString::number(vertex) + " -->");
    pass[vertex] = 1;
    for (int nextVertex{1}; nextVertex <= num; nextVertex++)
        if (pass[nextVertex] == 0 && matrix[vertex][nextVertex]) DFS_1(pass, matrix, num, answer, nextVertex);
}
QString IOModule::DFS(QVector<int>&pass, Q_AdjaMatrix& matrix,const int&num)// Depth First Search
{
    QString answer{};
    pass = QVector<int>(num+1);
    answer = "<p>Thứ tự duyệt các đỉnh của đồ thị theo thuật toán DFS:</p>"
             "<p>";
    for (int vertex{1}; vertex <= num; vertex++)
        if (pass[vertex] == 0) DFS_1(pass, matrix, num, answer, vertex);
    answer.append("kết thúc.</p>");
    return answer;
}
void IOModule::BFS_1(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num, QString& answer, int vertex)
{
    QQueue<int>queue;
    queue.push_back(vertex);
    pass[vertex] = 1;
    while(!queue.empty())
    {
        answer.append( QString::number(queue.front()) + " --> ");
        for (int nextVertex{1}; nextVertex <= num; nextVertex++)
        {
            if (pass[nextVertex] == 0 && matrix[queue.front()][nextVertex] == 1)
            {
                queue.push_back(nextVertex);
                pass[nextVertex] = 1;
            }
        }
        queue.pop_front();
    }
}
QString IOModule::BFS(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num) // Breadth First Search
{
    QString answer{};
    answer.append("<p>Thứ tự duyệt đồ thị theo thuật toán BFS:</p>"
                  "<p>");
    pass = QVector<int>(num+1);
    for (int vertex{1}; vertex <= num; vertex++)
        if (pass[vertex] == 0) BFS_1(pass, matrix, num, answer, vertex);
    answer.append("kết thúc.</p>");
    return answer;
}
QString IOModule::outputMatrix(const Q_AdjaMatrix& matrix, const int& num)
{
    QString matrixData;
    QString rowColumn;
    for (int i{1}; i <= num; i++)
    {
        rowColumn.clear();
        for (int j{1}; j <= num; j++)
        {
            rowColumn += QString::number(matrix[i][j]) + " ";
        }
        rowColumn.append("\n");
        matrixData.append(rowColumn);
    }
    return matrixData;
}

void IOModule::DFS_1_Simplify(QVector<int>&pass, Q_AdjaMatrix& matrix, const int& num, int vertex)
{
    pass[vertex] = 1;
    for (int nextVertex{1}; nextVertex <= num; nextVertex++)
    {
        if (pass[nextVertex] == 0 && matrix[vertex][nextVertex] == 1)
        {
            matrix[vertex][nextVertex] = matrix[nextVertex][vertex] = 2;
            DFS_1_Simplify(pass, matrix, num, nextVertex);
        }
    }
}
void IOModule::BFS_1_Simplify(QVector<int>&pass, Q_AdjaMatrix& matrix, const int& num, int vertex)
{
    QQueue<int>queue;
    pass[vertex] = 1;
    queue.push_back(vertex);
    while(!queue.empty())
    {
        for (int nextVertex{1}; nextVertex <= num; nextVertex++)
            if (pass[nextVertex] == 0 && matrix[queue.front()][nextVertex] == 1)
            {
                matrix[queue.front()][nextVertex] = matrix[nextVertex][queue.front()] = 2;
                pass[nextVertex] = 1;
                queue.push_back(nextVertex);
            }
        queue.pop_front();
    }
}
QString IOModule::simplifyGraph(QVector<int>&pass,Q_AdjaMatrix matrix, const int& num, void(*AlgorithmSimplify)(QVector<int>&, Q_AdjaMatrix&, const int&, int))
{
    QString answer{};
    answer.append("<p><b>Đồ thị đã cho có thể rút gọn qua việc loại bỏ các cạnh sau mà vẫn đảm bảo tính liên thông:</b></p>"
                  "<ol>");
    pass = QVector<int>(num+1);
    AlgorithmSimplify(pass, matrix, num, 1);
    for (int i{1}; i <= num; i++)
        for (int j{1}; j <= num; j++)
            if (matrix[i][j] == 1)
            {
                answer.append("<li>(" + QString::number(i) + ", " + QString::number(j) + ")</li>");
                matrix[i][j] = matrix[j][i] = 0;
            }
    answer.append("</ol>");
    return answer;
}

QString IOModule::checkConectivityUGraph(QVector<int>&pass, const Q_AdjaMatrix& matrix, const int& num)
{
    QString answer{};
    answer =  "<p><b>Các thành phần liên thông của đồ thị:</b></p>"
              "<ol>";
    pass = QVector<int>(num+1);
    for (int vertex{1}; vertex <= num; vertex++)
        if (pass[vertex] == 0)
        {
            answer.append("<li>");
            DFS_1(pass, matrix, num, answer, vertex);
            answer.append("</li>");
        }
    return answer;
}
/*void checkConectivityDGraph(QVector<int>&pass, const QVector<QVector<int>>&matrix, const int& num)
{

}*/
void IOModule::DFS_1_Find(int vertex, int endVertex, QVector<int>&pass, QVector<int>&path, const Q_AdjaMatrix& matrix, QString& answer, const int& num)
{
    pass[vertex] = 1;
    path.push_back(vertex);
    if (vertex == endVertex)
    {
        answer.append("<li>");
        for (int i{}; i < path.size(); i++) answer.append(QString::number(path[i]) + " -> ")  ;
        answer.append("</li>");
    }
    else
        for (int nextVertex{1}; nextVertex <= num; nextVertex++)
            if (pass[nextVertex] == 0 && matrix[vertex][nextVertex] == 1)
            {
                DFS_1_Find(nextVertex, endVertex, pass, path, matrix, answer, num);
                path.pop_back();
                pass[nextVertex] = 0;
            }
}
QString IOModule::findWayBetween2Vertices(int startVertex, int endVertex, QVector<int>&pass, const Q_AdjaMatrix& matrix, int num)
{
    QString answer{};
    answer = "<p><b>Các con đường từ đỉnh " + QString::number(startVertex) + " đến đỉnh " + QString::number(endVertex) + " :</b></p>"
                                                                                                                         "<ol>";
    pass = QVector<int>(num+1);
    QVector<int>path;
    DFS_1_Find(startVertex, endVertex, pass, path, matrix,answer, num);
    answer.append("</ol>");
    return answer;
}

QString IOModule::BFS_Analysis()
{
    return QString("Trong đồ thị không có trọng số, thuật toán tìm kiếm theo chiều rộng."
                   "luôn tìm ra đường đi ngắn nhất có thể. Thuật toán BFS bắt đầu từ đỉnh gốc và lần lượt thăm các đỉnh kề với đỉnh gốc.  "
                   "Sau đó, với mỗi đỉnh trong số đó, thuật toán lại lần lượt thăm các đỉnh kề với nó mà chưa được thăm trước đó và lặp lại."
                   "");

}

QString IOModule::BFS_Applications()
{
    return QString("<p><b>Tìm kiếm theo chiều rộng - BFS có nhiều ứng dụng trong lý thuyết đồ thị:</b></p>"
                   "<ul>"
                   "    <li> Xác định các thành phần liên thông của đồ thị, xác đinh tính liên thông của đồ thị có hướng. </li>"
                   "    <li> Tìm đường đi ngắn nhất giữa hai đỉnh trong một đồ thị không có trọng số. </li>"
                   "    <li> Kiếm tra một đồ thị có phải là đồ thị hai phía. </li>"
                   "    <li> Xác định đường đi giữa các đỉnh trong đồ thị, phục vụ cho nhiều thuật toán khác. </li>"
                   "</ul>"
                   " ..............");
}
