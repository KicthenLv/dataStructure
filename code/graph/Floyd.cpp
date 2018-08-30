#include<iostream>
#include<string>
using namespace std;

class Graph_DG {
private:
    int vexnum;   //图的顶点个数
    int edge;     //图的边数
    int **arc;   //邻接矩阵
    int ** dis;   //记录各个顶点最短路径的信息
    int ** path;  //记录各个最短路径的信息
public:
    //构造函数
    Graph_DG(int vexnum, int edge);
    //析构函数
    ~Graph_DG();
    // 判断我们每次输入的的边的信息是否合法
    //顶点从1开始编号
    bool check_edge_value(int start, int end, int weight);
    //创建图
    void createGraph(int);
    //打印邻接矩阵
    void print();
    //求最短路径
    void Floyd();
    //打印最短路径
    void print_path();
};
//构造函数
Graph_DG::Graph_DG(int vexnum, int edge) {
    //初始化顶点数和边数
    this->vexnum = vexnum;
    this->edge = edge;
    //为邻接矩阵开辟空间和赋初值
    arc = new int*[this->vexnum];
    dis = new int*[this->vexnum];
    path = new int*[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new int[this->vexnum];
        dis[i] = new int[this->vexnum];
        path[i] = new int[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //邻接矩阵初始化为无穷大
            arc[i][k] = INT_MAX;
        }
    }
}
//析构函数
Graph_DG::~Graph_DG() {

    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
        delete this->dis[i];
        delete this->path[i];

    }
    delete dis;
    delete arc;
    delete path;
}

// 判断我们每次输入的的边的信息是否合法
//顶点从1开始编号
bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph(int kind) {
    cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
    int start;
    int end;
    int weight;
    int count = 0;
    while (count != this->edge) {
        cin >> start >> end >> weight;
        //首先判断边的信息是否合法
        while (!this->check_edge_value(start, end, weight)) {
            cout << "输入的边的信息不合法，请重新输入" << endl;
            cin >> start >> end >> weight;
        }
        //对邻接矩阵对应上的点赋值
        arc[start - 1][end - 1] = weight;
        //无向图添加上这行代码
        if(kind==2)
        arc[end - 1][start - 1] = weight;
        ++count;
    }
}

void Graph_DG::print() {
    cout << "图的邻接矩阵为：" << endl;
    int count_row = 0; //打印行的标签
    int count_col = 0; //打印列的标签
                       //开始打印
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout << "∞" << " ";
            else
                cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::Floyd() {
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dist[i][j] = gra[i][j], pre[i][j] = j;  //初始化
		for(int k = 1; k <= n; k++) {   //尝试经过 k 个点对每对顶点之间的距离进行更新
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n; j++) {
					if(dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
						 dist[i][j] = dist[i][k] + dist[k][j];
						 pre[i][j] = pre[i][k];
					}
				}
			}
		}
}

void Graph_DG::print_path() {
    cout << "各个顶点对的最短路径：" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = 0; row < this->vexnum; row++) {
        for (col = row + 1; col < this->vexnum; col++) {
            cout << "v" << row+1 << "---" << "v" << col+1 << " weight: "
                << this->dis[row][col] << " path: " << " v" << row + 1;
            temp = path[row][col];
            //循环输出途径的每条路径。
            while (temp != col) {
                cout << "-->" << "v" << temp + 1;
                temp = path[temp][col];
            }
            cout << "-->" << "v" << col + 1 << endl;
        }

        cout << endl;
    }
}
//检验输入边数和顶点数的值是否有效，可以自己推算为啥：
//顶点数和边数的关系是：((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 ||  edge > Vexnum*(Vexnum-1))
        return false;
    return true;
}
int main() {
    int vexnum; int edge;
    cout << "输入图的种类：1代表有向图，2代表无向图" << endl;
    int kind;
    cin >> kind;
    //判读输入的kind是否合法
    while (1) {
        if (kind == 1 || kind == 2) {
            break;
        }
        else {
            cout << "输入的图的种类编号不合法，请重新输入：1代表有向图，2代表无向图" << endl;
            cin >> kind;
        }
    }

    cout << "输入图的顶点个数和边的条数：" << endl;
    cin >> vexnum >> edge;
    while (!check(vexnum, edge)) {
        cout << "输入的数值不合法，请重新输入" << endl;
        cin >> vexnum >> edge;
    }
    Graph_DG graph(vexnum, edge);
    graph.createGraph(kind);
    graph.print();
    graph.Floyd();
    graph.print_path();
    system("pause");
    return 0;
}