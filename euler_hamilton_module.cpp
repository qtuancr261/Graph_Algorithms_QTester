#include "euler_hamilton_module.h"
void EulerHamiltonModule::DFS_1(QVector<int>& pass, const Q_AdjaMatrix& matrix, const int& num, int vertex)
{
    pass[vertex] = 1;
    for (int nextVertex{1}; nextVertex <= num; nextVertex++)
        if (pass[nextVertex] == 0 && matrix[vertex][nextVertex] == 1) DFS_1(pass, matrix, num, nextVertex);
}
bool EulerHamiltonModule::checkConnectivityUGraph(QVector<int>& pass, const Q_AdjaMatrix& matrix, const int& num)
{
    pass = QVector<int>(num+1);
    DFS_1(pass, matrix, num);
    for (int i{1}; i <= num; i++) if (pass[i] == 0) return false;
    return true;
}
bool EulerHamiltonModule::checkEulerConditionUGraph(const Q_AdjaMatrix& matrix, QVector<int>& vertices, const int& num)
{
    int degree{};
    vertices.clear();
    for (int i{1}; i <= num; i++)
    {
        degree = 0;
        for (int j{1}; j <= num; j++)
            if (matrix[i][j] == 1) degree++;
        if (degree % 2 == 1) vertices.push_back(i);
    }
    if (vertices.size() == 0 || vertices.size() == 2) return true;
    return false;
}
bool EulerHamiltonModule::checkConnectivityDGraph(QVector<int>& pass, const Q_AdjaMatrix& matrix, const int& num)
{
    for (int vertex{1}; vertex <= num; vertex++)
    {
        pass = QVector<int>(num+1);
        DFS_1(pass, matrix, num, vertex);
        for (int i{1}; i <= num; i++) if (pass[i] == 0) return false;
    }
    return true;
}
bool EulerHamiltonModule::checkEulerConditionDGraph(const Q_AdjaMatrix& matrix, QVector<int>& vertices, const int& num)
{
    vertices.clear();
    int inDegree{}, outDegree{}, sameIODegree{}, startVertex{};
    for (int i{1}; i <= num; i++)
    {
        inDegree = outDegree = 0;
        for (int j{1}; j <= num; j++)
        {
            if (matrix[i][j] == 1) outDegree++;
            if (matrix[j][i] == 1) inDegree++;
        }
        if (inDegree-outDegree == 1) vertices.push_back(i);
        if (outDegree - inDegree == 1) {vertices.push_back(i); startVertex = i;}
        if (inDegree == outDegree) sameIODegree++;
    }
    if (vertices.size() == 2)
    {
        if (vertices[0] != startVertex) std::swap(vertices[0], vertices[1]);
        return true;
    }
    if (vertices.size() == 0 && sameIODegree == num) return true;
    return false;
}
QString EulerHamiltonModule::solveEulerUGraph(QTextBrowser* browser,QVector<int> &pass, Q_AdjaMatrix matrix, QVector<int>& vertices, const int &num)
{
    if (checkConnectivityUGraph(pass, matrix, num) && checkEulerConditionUGraph(matrix, vertices, num))
    {
        QString answer{};
        int vertex{}, nextVertex{};
        if (vertices.size() == 0)
        {
            browser->setHtml("<i> Đồ thị tồn tại chu trình Euler.<i>");
            vertex = QInputDialog::getInt(nullptr, "Chọn đỉnh", "Đỉnh xuất phát bất kỳ: ", 1, 1, num);
            answer = QString("<p><b>Chu trình Euler xuất phát từ đỉnh: ") + QString::number(vertex) + QString("</b></p>");
        }
        else if (vertices.size() == 2)
        {
            int min{std::min(vertices[0], vertices[1])};
            int max{std::max(vertices[0], vertices[1])};
            int step{max - min};

            browser->setHtml("<i> Đồ thị tồn tại đường đi Euler.<i>");
            vertex = QInputDialog::getInt(nullptr,   "Chọn đỉnh", "Đỉnh xuất phát (<b>" + QString::number(vertices[0]) + " hoặc " + QString::number(vertices[1]) + "): </b>", min, min, max, step);
            answer = QString("<p><b>Đường đi xuất phát từ đỉnh: ") + QString::number(vertex) +   QString("</b></p>");
        }
        QStack<int>list;
        QVector<int>euler;
        list.push(vertex);
        while(!list.isEmpty())
        {
            for (nextVertex = 1; nextVertex <= num; nextVertex++)
                if (matrix[list.top()][nextVertex] == 1)
                {
                    matrix[list.top()][nextVertex] = matrix[nextVertex][list.top()] = 0;
                    list.push(nextVertex);
                    break;
                }
            if (nextVertex > num)   euler.push_front(list.pop());
        }
        answer.append(QString("<ul>"
                              "    <li> "));
        for (auto& i:euler) answer.append(QString::number(i) + " -> ");
        answer.append(QString("    </li>"
                              "</ul>"));
        return answer;
    }
    else return QString("<p><b> Đồ thị không tồn tại chu trình/đường đi Euler.</b></p>");
}
QString EulerHamiltonModule::solveEulerDGraph(QTextBrowser* browser,QVector<int> &pass, Q_AdjaMatrix matrix, QVector<int> &vertices, const int &num)
{
    if (checkConnectivityDGraph(pass, matrix, num) && checkEulerConditionDGraph(matrix, vertices, num))
    {
        QString answer{};
        int vertex{}, nextVertex{};
        if (vertices.size() == 0)
        {
            browser->setHtml("<i> Đồ thị tồn tại chu trình Euler.<i>");
            vertex = QInputDialog::getInt(nullptr, "Chọn đỉnh", "Đỉnh xuất phát bất kỳ: ", 1, 1, num);
            answer = QString("<p><b>Chu trình Euler xuất phát từ đỉnh: ") + QString::number(vertex) + QString("</b></p>");
        }
        else if (vertices.size() == 2)
        {
            browser->setHtml("<i> Đồ thị tồn tại đường đi Euler.<i>");
            answer = QString("<p><b>Đường đi Euler xuất phát từ đỉnh: ") + QString::number(vertices[0]) + QString("</b></p>");
            vertex = vertices[0];
        }
        QStack<int>list;
        QVector<int>euler;
        list.push(vertex);
        while(!list.isEmpty())
        {
            for (nextVertex = 1; nextVertex <= num; nextVertex++)
                if (matrix[list.top()][nextVertex] == 1)
                {
                    matrix[list.top()][nextVertex] = 0;
                    list.push(nextVertex);
                    break;
                }
            if (nextVertex > num)   euler.push_front(list.pop());
        }
        answer.append(QString("<ul>"
                              "    <li> "));
        for (auto& i:euler) answer.append(QString::number(i) + " -> ");
        answer.append(QString("    </li>"
                              "</ul>"));
        return answer;
    }
    else return QString("<p><b> Đồ thị không tồn tại chu trình/đường đi Euler.</b></p>");
}

QString EulerHamiltonModule::solveHamilton(QVector<int> &pass, const Q_AdjaMatrix &matrix, QVector<int> &hamilton, const int &num)
{
    int startVertex{QInputDialog::getInt(nullptr, "Chọn đỉnh", "Đỉnh xuất phát bất kỳ: ", 1, 1, num)};
    QString answer{QString("<h2> Chu trình/đường đi Hamilton thuộc đồ thị đã cho từ đỉnh %1: </h2>"
                   "   <ul>").arg(QString::number(startVertex))};
    pass = QVector<int>(num+1);
    pass[startVertex] = 1;
    hamilton.clear();
    hamilton.push_back(0);
    hamilton.push_back(startVertex);
    tryStepHamilton(2, pass, matrix, hamilton, answer, num);
    answer.append("</ul>");
    return answer;
}

void EulerHamiltonModule::tryStepHamilton(int stepIndex, QVector<int> &pass, const Q_AdjaMatrix& matrix, QVector<int> &hamilton, QString& answer,  const int &num)
{
    for (int vertex{1}; vertex <= num; vertex++)
    {
        if (pass[vertex] == 0 && matrix[hamilton[stepIndex - 1]][vertex] == 1)
        {
            pass[vertex] = 1;
            hamilton.push_back(vertex);
            if (stepIndex == num)
            {
                if (matrix[hamilton[stepIndex]][hamilton[1]] == 1) hamiltonCircuit(hamilton, answer, num);
                else                                               hamiltonPath(hamilton, answer, num);
            }
            else tryStepHamilton(stepIndex + 1, pass, matrix, hamilton, answer, num);
            pass[vertex] = 0;
            hamilton.pop_back();
        }
    }
}

void EulerHamiltonModule::hamiltonPath(const QVector<int> &hamilton, QString& answer,  const int &num)
{
   answer.append("<li> Đường đi: ");
   for (int i{1}; i <= num; i++) answer.append(QString::number(hamilton[i]) +  " -> ");
   answer.append("</li>");
}

void EulerHamiltonModule::hamiltonCircuit(const QVector<int> &hamilton, QString& answer, const int &num)
{
    answer.append("<li> Chu trình : ");
    for (int i{1}; i <= num; i++) answer.append(QString::number(hamilton[i]) + " -> ");
    answer.append(QString::number(hamilton[1]) + "</li>");
}

void EulerHamiltonModule::tryStepTravelling(int stepIndex, QVector<int> &pass, const Q_AdjaMatrix& matrix, QVector<int>& vertices, QVector<int>& optimizePath,int& minCost, const int &num)
{
    for (int vertex{1}; vertex <= num; vertex++)
    {
        if (matrix[vertices[stepIndex - 1]][vertex] != 0 && pass[vertex] == 0)
        {
            pass[vertex] = 1;
            vertices.push_back(vertex);
            if (stepIndex == num && matrix[vertices[stepIndex]][vertices[1]] != 0)
                findOptimizePath(matrix, vertices, optimizePath, minCost, num);
            else tryStepTravelling(stepIndex + 1, pass, matrix, vertices, optimizePath, minCost, num);
            pass[vertex] = 0;
            vertices.pop_back();
        }
    }
}

void EulerHamiltonModule::findOptimizePath(const Q_AdjaMatrix& matrix, QVector<int> &vertices, QVector<int> &optimizePath, int& minCost, const int &num)
{
    int tempCost{};
    for (int i{1}; i < num; i++)
        tempCost += matrix[vertices[i]][vertices[i+1]];
    tempCost += matrix[vertices[num]][vertices[1]];
    if (tempCost < minCost)
    {
        minCost = tempCost;
        optimizePath = vertices;
    }

}

QString EulerHamiltonModule::solveTravellingProblem(QVector<int> &pass, const Q_AdjaMatrix& matrix, QVector<int> &vertices, const int &num)
{
    int startVertex{QInputDialog::getInt(nullptr, "Chọn thành phố", "Thành phố xuất phát: ", 1, 1, num)};
    QString answer{};
    QVector<int>optimizePath;
    int minCost{9999};
    pass = QVector<int>(num+1);
    pass[startVertex] = 1;
    vertices.clear();
    vertices.push_back(0);
    vertices.push_back(startVertex);
    tryStepTravelling(2, pass, matrix, vertices, optimizePath, minCost, num);
    answer.append(QString("<h2>Lộ trình có chi phí tối ưu khi xuất phát từ đỉnh %1 : </h2>").arg(QString::number(startVertex)));
    for (int i{1}; i < optimizePath.size(); i++) answer.append(QString::number(optimizePath[i]) + " -> ");
    answer.append(QString::number(startVertex) + " |<i> Chi phí tối ưu:</i> " + QString::number(minCost));
    return answer;
}

QString EulerHamiltonModule::EulerInfo()
{
    return QString("<h2><b>Người nghiên cứu thuật toán</b></h2>"
                   "    <p> LEONHARD EULER (1707–1783) là một nhà toán học và nhà vật lý học nổi tiếng người Thụy Sĩ, có một kho tàng"
                   " nghiên cứu đồ sộ nhất mọi thời đại. Ông có đóng góp to lớn trong nhiều lĩnh vực của toán học như lý thuyết số, xác xuất thống kê - tổ hợp, topo học, lý thuyết "
                   " đồ thị... Ông đã viết gần 1100 cuốn sách và các bản ghi chép về nhiều công trình. Theo như ước tính, người ta cần tới gần 50 năm sau khi ông mất để nghiên cứu và công bố"
                   " các công trình chưa được xuất bản của Euler. Trong 17 năm cuối đời, Euler bị mù hoàn toàn, nhưng nhờ có một trí nhớ siêu phàm,"
                   " ông vẫn có thể tiếp tục nghiên cứu về các công trình toán học của mình.</p>"
                   "    <p> Năm 1736, Euler giải được bài toán <i>Bảy cây cầu ở thành phố Konigsberg</i>. Đây là một bài toán cực kỳ nổi tiếng,"
                   " thứ đã làm cho Euler trở nên say mê môn topo học. Vào thời của Euler, có 7 cây cầu bắc qua sông Pregel thuộc thành phố Konigsberg. Dưới đây là sơ đồ mô tả vị trí các cây cầu đó."
                   " <img src=:/images/EulerFigure1.png/></p>"
                   "    <p> Euler đặt vấn đề rằng liệu có cách nào đi qua hết cả 7 cây cầu mà mỗi cây cầu chỉ được đi qua đúng 1 lần. Ông đã chứng minh rằng không thể thực hiện được điều đó !</p>");
}

QString EulerHamiltonModule::EulerAnalysis()
{
    return QString("<h2>Bài toán bảy cây cầu ở Konigsberg và thuật toán của Euler để tìm lời giải </h2>"
                   "<ul><p><b>Các khái niệm cơ bản về đồ thị Euler:</b></p>"
                   "    <li>Đường đi Euler: là đường đi qua tất cả các cạnh trong một đồ thị liên thông, mỗi cạnh đi qua đúng 1 lần.</li>"
                   "    <li>Chu trình Euler: là một đường đi Euler khép kín, đỉnh xuất phát và kết thúc trùng nhau.</li>"
                   "    <li>Đồ thị được gọi là Euler nếu nó tồn tại chu trình Euler, đồ thị tồn tại đường đi Euler thì được gọi là đồ thị nửa Euler.</li>"
                   "    <li>Mọi đồ thị Euler đều là nửa Euler nhưng điều ngược lại thì không luôn đúng.</li>"
                   "    <li>Bậc của một đỉnh trong một đồ thị vô hướng là số cạnh được nối với đỉnh đó.</li>"
                   "</ul>"
                   "<ol><p><b>Euler đã chứng minh được rằng:</b></p>"
                   "    <li><ul><i>Đối với đồ thị vô hướng:</i>"
                   "            <li>Đồ thị không có đỉnh bậc lẻ thì bao giờ cũng vẽ được bằng một nét khép kín - chu trình Euler.</li>"
                   "            <li>Đồ thị có đúng 2 đỉnh bậc lẻ thì bao giờ cũng vẽ được bằng một nét xuất phát từ một trong hai đỉnh đó và kết thúc tại đỉnh còn lại.</li>"
                   "            <li>Đồ thị có 2n đỉnh bậc lẻ thì không thể vẽ được với ít hơn n nét.</li>"
                   "        </ul></li>"
                   "    <li><ul><i>Đối với đồ thị có hướng:</i>"
                   "            <li>Đồ thị phải có tính chất <i>liên thông mạnh</i> - từ một đỉnh bất kỳ trong đồ thị có thể thăm được tất cả các đỉnh còn lại.</li>"
                   "            <li>Đồ thị với tất cả các đỉnh đều có số bậc vào bằng với bậc ra thì tồn tại chu trình Euler.</li>"
                   "            <li>Đồ thị có đúng 2 đỉnh sao cho chênh lệch giữa số bậc vào và bậc ra là 1 thì tồn tại đường đi Euler xuất phát từ đỉnh có bậc vào < bậc ra và kết thúc tại đỉnh còn lại.</li>"
                   "        </ul></li>"
                   "</ol>");
}

QString EulerHamiltonModule::EulerApp()
{
    return QString("<h2> Ứng dụng của chu trình và đường đi Euler</h2>"
                   "<p> Thuật toán để tìm chu trình và đường đi của Euler có rất nhiều ứng dụng trong thực tế: tìm đường đi hoặc chu trình"
                   " đi qua từng con đường trong một khu vực, trong một mạng lưới đường giao thông,.. mỗi con đường đi qua đúng 1 lần."
                   " Việc tìm được chu trình hoặc đường đi ứng với từng đồ thị tương ứng sẽ giải quyết được những vấn đề này. Nếu như một người"
                   " đưa thư tìm được một chu trình hoặc đường đi Euler trên một đồ thị biểu diễn những con đường mà anh ta sẽ đi qua thì anh ta có thể có"
                   " được một lộ trình hoàn hảo để đưa thư, mỗi con đường chỉ đi qua đúng 1 lần duy nhất. Nếu không thì sẽ có một số con đường phải đi qua nhiều hơn 1 lần."
                   " Bài toán tìm chu trình ngắn nhất đi qua tất cả các cạnh của một đồ thị cho trước - bài toán <i> Người đưa thư Trung Hoa</i> được đưa ra vào năm 1962 có thể được giải bằng thuật toán Euler.</p>"
                   "<p><ul>Một số ứng dụng trong các lĩnh vực khác của chu trình và đường đi Euler: "
                   "      <li>Thiết kế mạch.</li>"
                   "      <li>Truyền gửi dữ liệu thông qua mạng.<li>"
                   "      <li>Sắp xếp các chuỗi DNA trong sinh học phân tử.</li>"
                   "   </ul>"
                   "</p>");

}

QString EulerHamiltonModule::HamiltonInfo()
{
    return QString("<h2>William Ronaw Hamilton(1805 - 1865)</h2>"
                   "<p><img src = :/images/WilliamRowanHamilton.jpg/></p>"
                   "<p>Một trong những nhà khoa học nổi tiếng nhất Ai-len, ông sinh ta tại Dublin vào năm 1805, bố ông là một luật sư thành đạt, mẹ ông có xuất thân từ một gia đình có tiếng thông minh, ông được xem như một đứa trẻ thiên tài."
                   " Năm 3 tuổi, ông đã là một độc giả tài năng, thông thạo các kiến thức nâng cao về môn số học. Đến năm 17 tuổi đã học được nhiều ngôn ngữ khác nhau: tiếng Latin , tiếng Pháp, tiếng Ý, tiếng Hy Lạp và một số ngôn ngữ từ phương Đông."
                   " Hamilton có nhiều đóng góp quan trọng trong các lĩnh vực như quang học, đại số, khám phá về các <i>quaternion</i>,......</p>"
                   "<p> Năm 1857, ông phát minh ra trò chơi Icosian, thách thức người chơi tìm một chu trình Hamilton trên một khối 12 mặt, mỗi đỉnh của khối chỉ được đi qua 1 lần và không được có cạnh nào được đi qua 2 lần, đỉnh cuối phải trùng với"
                   " đỉnh xuất phát.</p>"
                   "<p><img src = :/images/icoGame.jpg"
                   "        height = 275"
                   "        width = 300"
                   "        alt = Icosian/></p>");
}

QString EulerHamiltonModule::HamiltonAnalysis()
{
    return QString("<h2>Đồ thị Hamilton và các vấn đề liên quan</h2>"
                   "<ol>"
                   "    <li>Các khái niệm cơ bản:"
                   "        <ul>"
                   "            <li>Đường đi qua tất cả các đỉnh của đồ thị, mỗi đỉnh đúng 1 lần thì được gọi là đường đi Hamilton.</li>"
                   "            <li>Chu trình bắt đầu từ một đỉnh bất kỳ, đi qua tất cả các đỉnh khác của đồ thị, mỗi đỉnh đúng 1 lần rồi quay trở về đỉnh xuất phát được gọi là chu trình Hamilton.</li>"
                   "            <li>Đồ thị G được gọi là đồ thị Hamilton nếu nó chứa chu trình Hamilton và gọi là đồ thị nửa Hamilton nếu nó có đường đi Hamilton.</li>"
                   "            <li>Đồ thị Hamilton là nửa Hamilton, nhưng điều ngược lại không  đúng.</li>"
                   "        </ul>"
                   "    </li>"
                   "    <p>Các khái niệm trên bắt nguồn từ trò chơi Icosian của nhà toán học William Rowan Hamilton. Trò chơi bao gồm một khối 12 mặt được làm bằng gỗ(khối đa diện gồm 12 mặt ngũ giác đều),"
                   " 20 đỉnh của khối đa diện được đặt tên theo tên các thành phố trên toàn thế giới. Yêu của của trò chơi là chọn một thành phố xuất phát, đi qua các cạnh của khối 12 mặt, thăm 19 thành phố còn lại đúng 1 lần"
                   " và quay trở về thành phố xuất phát.</p>"
                   "    <p><img src = :/images/icosianPuzze.png"
                   "            height=274"
                   "            width=751"
                   "            alt=Icosian_Puzzle/></p>"
                   "    <li>Điều kiện tồn tại của chu trình Hamilton: "
                   "        <ul>"
                   "            <li><b>Định lý Dirac: </b>G là một đồ thị vô hướng với <i>n</i> đỉnh (n>=3), nếu mọi đỉnh của G đều có bậc ít nhất là <i>n/2</i> thì G tồn tại chu trình Hamilton.</li>"
                   "            <li><b>Định lý Ore: </b>G là một đồ thị vô hướng với <i>n</i> đỉnh (n>=3), nếu tổng bậc của hai đỉnh không kề nhau bất kỳ lớn hơn hoặc bằng <i>n</i> thì G tồn tại chu trình Hamilton.</li>"
                   "        </ul>"
                   "    </li>"
                   "    <p><u>Chú ý:</u> cả hai định lý trên cung cấp điều kiện đủ cho một đồ thị liên thông vô hướng có chu trình Hamilton nhưng lại không cung cấp"
                   "        một điều kiện cần để có một chu trình Hamilton, nhiều đồ thị tồn tại chu trình Hamilton nhưng không thỏa mãn hai định lý này.</p>"
                   "    <p>Thời gian để thuật toán tôt nhất hiện nay phát hiện hoặc tìm chu trình Hamilton tăng rất nhanh theo số lượng đỉnh của đồ thị cần tìm, vì thế"
                   "        việc tìm ra một thuật toán mới tối ưu hơn hiện tại sẽ là một thành tựu đáng ghi nhận của ngành khoa học máy tính và toán học.</p>"
                   "</ol>");
}

QString EulerHamiltonModule::HamiltonApp()
{
    return QString("<h2>Ứng dụng của chu trình Hamilton</h2>"
                   "<p>Trong thực tế, nhiều vấn đề được đặt ra như tìm đường đi qua tất cả các giao lộ trong thành phố, nơi giao nhau của các đường ống dẫn trong mạng lưới cấp nước, khí đốt,... "
                   "   có thể được giải quyết bằng cách tìm chu trình hoặc đường đi Hamilton. Một trong những vấn đề nổi tiếng nhất là bài toán <b>Người bán hàng</b> (Travelling salesman problem),"
                   " đặt ra yêu cầu tìm một lộ trình tối ưu mà người bán hàng nên dùng để đi thăm các thành phố, điều này tương đương với việc tìm một chu trình Hamilton trong một đồ thị đầy đủ sao cho chu trình"
                   " tìm được có tổng trọng số của các cạnh đi qua là nhỏ nhất.</p>"
                   "<p>Một số ứng dụng khác của chu trình Hamilton: mã Gray, bài toán mã đi tuần,.........</p> ");
}
