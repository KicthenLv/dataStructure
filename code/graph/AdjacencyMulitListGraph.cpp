#include<iostream>
#include<string>
using namespace std;

//表结点
struct ArcNode
{
    int mark; //标志位
    int ivex; //输入边信息的那个起点
    ArcNode * ilink; //依附在顶点ivex的下一条边的信息
    int jvex;   //输入边信息的那个终点
    ArcNode * jlink; //依附在顶点jvex的下一条边的信息
    int weight;
};

//头结点
struct VexNode {
    string data;   //顶点的信息，如顶点名称
    ArcNode * firstedge; //第一条依附顶点的边
};

struct Graph {
    int vexnum;   //顶点的个数
    int edge;    //边的个数
    VexNode *node; //保存顶点信息
};

void createGraph(Graph & g)
{
    cout << "请输入顶点的个数：" << endl;
    cin >> g.vexnum;
    cout << "请输入边的个数（无向图/网要乘2）：" << endl;
    cin >> g.edge;
    g.node = new VexNode[g.vexnum];

    int i;
    cout << "输入每个顶点的信息：" << endl;//记录每个顶点的信息
    for (i = 0; i < g.vexnum; i++)
    {
        cin >> g.node[i].data;
        g.node[i].firstedge = NULL;
    }

    cout << "请输入每条边的起点和终点的编号：" << endl;
    for (i = 0; i < g.edge; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;

        ArcNode * next = new ArcNode;
        next->mark = 0;
        next->ivex = a - 1; //首先是弧头的下标
        next->jvex = b - 1; //弧尾的下标
        next->weight = -1;
        next->ilink = NULL;
        next->jlink = NULL;

        //更新顶点表a-1的信息
        if (g.node[a - 1].firstedge == NULL)
        {
            g.node[a - 1].firstedge = next;
        }
        else {
            ArcNode * now;
            now = g.node[a - 1].firstedge;
            while (1) {
                if (now->ivex == (a - 1) && now->ilink == NULL)
                {
                    now->ilink = next;
                    break;
                }
                else if (now->ivex == (a - 1) && now->ilink != NULL) {
                    now = now->ilink;
                }
                else if (now->jvex == (a - 1) && now->jlink == NULL)
                {
                    now->jlink = next;
                    break;
                }
                else if (now->jvex == (a - 1) && now->jlink != NULL) {
                    now = now->jlink;
                }
            }
        }
        //更新顶点表b-1
        if (g.node[b - 1].firstedge == NULL)
        {
            g.node[b - 1].firstedge = next;
        }
        else {
            ArcNode * now;
            now = g.node[b - 1].firstedge;
            while (1) {
                if (now->ivex == (b - 1) && now->ilink == NULL)
                {
                    now->ilink = next;
                    break;
                }
                else if (now->ivex == (b - 1) && now->ilink != NULL) {
                    now = now->ilink;
                }
                else if (now->jvex == (b - 1) && now->jlink == NULL)
                {
                    now->jlink = next;
                    break;
                }
                else if (now->jvex == (b - 1) && now->jlink != NULL) {
                    now = now->jlink;
                }
            }
        }

    }
}

void print(Graph g)
{
    int i;
    for (i = 0; i < g.vexnum; i++)
    {
        cout << g.node[i].data << " ";
        ArcNode * now;
        now = g.node[i].firstedge;
        while (now)
        {
            cout << "ivex=" << now->ivex << " jvex=" << now->jvex << " ";
            if (now->ivex == i)
            {
                now = now->ilink;
            }
            else if (now->jvex == i)
            {
                now = now->jlink;
            }
        }
        cout << endl;
    }
}
int main()
{
    Graph g;
    createGraph(g);
    print(g);
    system("pause");
    return 0;

}