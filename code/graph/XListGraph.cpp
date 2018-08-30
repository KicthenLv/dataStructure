#include<iostream>
#include<string>
using namespace std;

typedef string Vertextype;
//表结点结构
struct ArcNode {
    int tailvex;   //弧尾的下标，一般都是和对应的头结点下标相同
    int headvex;   //弧头的下标
    ArcNode * hlink; //指向下一个弧头同为headvex的表结点 ，边是箭头的那边
    ArcNode * tlink;  //指向下一个弧尾为tailvex的表结点,边不是箭头的那边
    int weight;  //只有网才会用这个变量

};

//头结点
struct Vnode
{
    Vertextype data;  //这个是记录每个顶点的信息（现在一般都不需要怎么使用）
    ArcNode *firstin; //指向第一条（入度）在该顶点的表结点
    ArcNode *firstout; //指向第一条（出度）在该顶点的表结点
};

struct Graph
{
    int kind;  //图的种类(有向图：0，有向网：1)
    int vexnum; //图的顶点数
    int edge;  //图的边数
    Vnode * node; //图的（顶点）头结点数组
};

void createGraph(Graph & g,int kind)
{
    cout << "请输入顶点的个数：" << endl;
    cin >> g.vexnum;
    cout << "请输入边的个数（无向图/网要乘2）：" << endl;
    cin >> g.edge;
    g.kind = kind; //决定图的种类
    g.node = new Vnode[g.vexnum];
    int i;
    cout << "输入每个顶点的信息：" << endl;//记录每个顶点的信息
    for (i = 0; i < g.vexnum; i++)
    {
        cin >> g.node[i].data;
        g.node[i].firstin = NULL;
        g.node[i].firstout = NULL;
    }

    cout << "请输入每条边的起点和终点的编号：" << endl;
    for (i = 0; i < g.edge; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;

        ArcNode * next = new ArcNode;
        next->tailvex = a - 1; //首先是弧头的下标
        next-> headvex = b - 1; //弧尾的下标
        //只有网图需要权重信息
        if(kind==0)
        next->weight = -1;
        else
        {
            cout << "输入该边的权重：" << endl;
            cin >> next->weight;
        }
        next->tlink = NULL;
        next->hlink = NULL;
        //该位置的顶点的出度还为空时，直接让你fisrstout指针指向新的表结点
        //记录的出度信息
        if (g.node[a - 1].firstout == NULL)
        {
            g.node[a - 1].firstout = next;
        }
        else
        {
            ArcNode * now;
            now = g.node[a - 1].firstout;
            while (now->tlink)
            {
                now = now->tlink;
            }
            now->tlink = next;
        }
        //记录某个顶点的入度信息
        if (g.node[b - 1].firstin == NULL)
        {
            g.node[b - 1].firstin = next;
        }
        else {
            ArcNode * now;
            now = g.node[b - 1].firstin;
            while (now->hlink)//找到最后一个表结点
            {
                now = now->hlink;
            }
            now->hlink = next;//更新最后一个表结点
        }
    }
}

void print(Graph g)
{
    int i;
    cout << "各个顶点的出度信息" << endl;
    for (i = 0; i < g.vexnum; i++)
    {
        cout << g.node[i].data << " ";
        ArcNode * now;
        now = g.node[i].firstout;
        while (now)
        {
            cout << now->headvex << " ";
            now = now->tlink;
        }
        cout << "^" << endl;
    }

    cout << "各个顶点的入度信息" << endl;

    for (i = 0; i < g.vexnum; i++)
    {
        cout << g.node[i].data << " ";
        ArcNode * now;
        now = g.node[i].firstin;
        while (now)
        {
            cout << now->tailvex << " ";
            now = now->hlink;
        }
        cout << "^" << endl;

    }
}


int main()
{
    Graph g;
    cout << "有向图的例子" << endl;
    createGraph(g, 0);
    print(g);
    cout << endl;
    return 0;
}