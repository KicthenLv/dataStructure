#include<iostream>
#include<string.h>
#include<queue>
using namespace std;


enum Graphkind{ DG, DN, UDG, UDN }; //{有向图，无向图，有向网，无向网}

typedef struct  Node
{
    int * vex;  //顶点数组
    int vexnum; //顶点个数
    int edge;   //图的边数
    int ** adjMatrix; //图的邻接矩阵
	int **dis; //Floyd算法使用到的距离数组
	int **path;//floyd算法使用到的最短路径
    enum Graphkind kind;
	string *infromation;
}MGraph;
typedef struct Dis{
	int value;
	bool visit;
	string path;
	Dis(){
		visit = false;
		value = 0;
	};
};
typedef struct Edge{
	int start;
	int end;
	int weight;
}Edge;
void createGraph(MGraph & G,enum Graphkind kind)
{
    cout << "输入顶点的个数" << endl;
    cin >> G.vexnum;
    cout << "输入边的个数" << endl;
    cin >> G.edge;
    //输入种类

    //cout << "输入图的种类：DG:有向图 DN：无向图，UDG：有向网,UDN:无向网" << endl;
    G.kind = kind;
    //为两个数组开辟空间
    G.vex = new int[G.vexnum];
    G.adjMatrix = new int*[G.vexnum];
    cout << G.vexnum << endl;
    int i;
	G.dis = new int*[G.vexnum];
	G.path = new int*[G.vexnum];
    for (i = 0; i < G.vexnum; i++)
    {
		G.dis[i] = new int[G.vexnum];
		G.path[i] = new int[G.vexnum];
        G.adjMatrix[i] = new int[G.vexnum];
    }
    for (i = 0; i < G.vexnum; i++)
    {
        for (int k = 0; k < G.vexnum; k++)
        {
            if (G.kind == DG || G.kind == DN)
            {
                G.adjMatrix[i][k] = 0;
            }
            else {
                G.adjMatrix[i][k] = INT_MAX;
            }
        }

    }



    /*//输入每个元素的信息,这个信息，现在还不需要使用
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vex[i];
    }*/
    cout << "请输入两个有关系的顶点的序号：例如：有向图中1 2 代表1号顶点指向2号顶点，无向图中则表示1 和 2之间有边" << endl;
    for (i = 0; i < G.edge; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;
        if (G.kind == DN) {
            G.adjMatrix[b - 1][a - 1] = 1;
            G.adjMatrix[a - 1][b - 1] = 1;
        }
        else if (G.kind == DG)
        {
            G.adjMatrix[a - 1][b - 1] = 1;
        }
        else if (G.kind == UDG)
        {
            int weight;
            cout << "输入该边的权重：" << endl;
            cin >> weight;
            G.adjMatrix[a - 1][b - 1] = weight;
        }
        else {
            int weight;
            cout << "输入该边的权重：" << endl;
            cin >> weight;
            G.adjMatrix[b - 1][a - 1] = weight;
            G.adjMatrix[a - 1][b - 1] = weight;
        }   
    }
}


void print(MGraph g)
{
    int i, j;
    for (i = 0; i < g.vexnum; i++)
    {
        for (j = 0; j < g.vexnum; j++)
        {
            if (g.adjMatrix[i][j] == INT_MAX)
                cout << "∞" << " ";
            else
            cout << g.adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void clear(MGraph G)
{
    delete G.vex;
    G.vex = NULL;
    for (int i = 0; i < G.vexnum; i++)
    {
        delete G.adjMatrix[i];
        G.adjMatrix[i] = NULL;
    }
    delete G.adjMatrix;
}
void DFS_store_array(MGraph g,int v,bool * & visit) {
    cout << v << " ";
    visit[v] = true;
    for (int i = 0; i < g.vexnum; i++) {//找出下一个位被访问的顶点
        if (g.adjMatrix[v][i] == 0 || g.adjMatrix[v][i] == INT_MAX) { //如果两个顶点不存在边
            continue;
        }
        else if (!visit[i]) {//如果没有被访问，访问该结点
            DFS_store_array(g, i, visit);
        }
    }
}
//DFS 深度优先遍历邻接矩阵图
void DFSTraverse(MGraph g,int begin){
	bool * visit;
    visit = new bool[g.vexnum];
    int i;
    for (i = 0; i < g.vexnum; i++) {
        visit[i] = false;
    }
    cout << "图的DFS遍历结果：" << endl;
    DFS_store_array(g,begin - 1,visit);
    //如果图是非联通同，那么我们这里还需要对每个顶点遍历一次，保证
    //全部顶点都被访问了
    for (i = 0; i < g.vexnum; i++) {
        if (!visit[i])
            DFS_store_array(g, i,visit);
    }	
	cout << endl;
}
//BFS 广度优先遍历
void BFSTraverse(MGraph g,int begin){
	bool * visit;
    visit = new bool[g.vexnum];
    int i;
    for (i = 0; i < g.vexnum; i++) {
        visit[i] = false;
    }
    cout << "图的BFS遍历结果：" << endl;
    //通过我们之前说的算法思路，我们可以知道
    //我们需要使用先进先出的数据存储结构实现我们的BFS，其实那就是队列
    queue<int>  q;
    for (int v = 0; v < g.vexnum; v++) {//这重循环是为了保证非连通同的情况下，每个顶点都可以被访问
        if (!visit[(begin-1 + v) % g.vexnum])//注意起点不一定是v1
        {
            cout << (begin - 1 + v) % g.vexnum << " ";
            visit[(begin - 1 + v) % g.vexnum] = true;
            q.push((begin - 1 + v) % g.vexnum);//初始化我们的队列
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int j = 0; j < g.vexnum; j++) {
                    if (g.adjMatrix[u][j] == 0 || g.adjMatrix[u][j] == INT_MAX) { //如果两个顶点不存在边
                        continue;
                    }
                    else if (!visit[j] ) {//先访问所有和u相连的顶点，并且把它们加入队列
                        cout << j <<" ";
                        visit[j] = true;
                        q.push(j);
                    }
                }
            }
        }

    }
    cout << "完成" << endl;
}
struct Assis_array {
    int start; //边的终点
    int end;  //边的起点
    int weight;  //边的权重
};
//利用prim算法实现邻接矩阵求最小生成树
//事件复杂度为O(n*n)
void Prim(MGraph g,int begin) {
	//使用一个数组来存放每个顶点所关联的权值最小的边
	//初始化数组
	Assis_array *edges = new Assis_array[g.vexnum];
	for(int i = 0 ; i < g.vexnum ; i ++){
		edges[i].weight =  g.adjMatrix[begin-1][i];
		edges[i].start = begin -1 ;
		edges[i].end = i;
	}
	//将入口节点设置为-1表示已被访问
	edges[begin-1].weight = -1;
	//遍历所有节点来查找权值最小的边
	int j = 0;
	for(i = i ; i < g.vexnum ; i++ ){
		int min = INT_MAX;
		int index = 0 ; //设置一个索引来输出和更新边集合
		//每轮从边的集合里查找出权值最小的边输出
		for(j = 0 ; j < g.vexnum ; j++){
			if(edges[j].weight != -1){
				if(edges[j].weight < min){
					min = edges[j].weight;
					index = j;
				}
			}
		}
		edges[index].weight = -1;
		//输出生成树的节点信息
		cout << "v" << (edges[index].start+1) << "---->"
			<< "v" << (edges[index].end+1) << "----"
			<< edges[index].weight <<endl;
		
		//更新边集合信息 ，将已遍历的节点内最小的权值边更新到边集合
		for(j = 0 ; j < g.vexnum ; j++){
			if(g.adjMatrix[edges[index].end][j] < edges[j].weight){
				edges[j].weight = g.adjMatrix[edges[index].end][j];
				edges[j].start = edges[index].end;
				edges[j].end = j;	
			}
		}
	}
 
}
//使用第杰斯特拉算法实现求最小路径
void Dijkstra(MGraph g,int begin){
	//新建路径数组
	Dis *dis = new Dis[g.vexnum];
	//设置入口初始值
	for(int i = 0 ; i < g.vexnum ;i++){
		dis[i].value = g.adjMatrix[begin-1][i]; 
		dis[i].path = begin-1 + "-->" + (i+1);
	}
	dis[begin-1].value = 0;
	dis[begin-1].visit = true;
	//循环查找出吗到每个节点的最小路径
	int count = 0 ;
	while(count!=g.vexnum){
		//找到起点到其他节点的最小并且违背访问的节点下标
		int min = INT_MAX;
		int index = 0;
		for(int j = 0 ; j < g.vexnum ; j ++){
			if(!dis[j].visit&&dis[j].value < min){
				min = dis[j].value;
				index = j;
			}
		}
		//把此节点的访问、赋值为true
		dis[index].visit = true;
		++count;
		//遍历当前路径最小的头弧结点的所有路径，与头结点与被查找头结点的头弧结点相加路径小于原路径的路径值
		for(i = 0 ; i <g.vexnum ; i ++){
			if(!dis[i].visit&& g.adjMatrix[index][i]!=INT_MAX && (dis[i].value>g.adjMatrix[index][i]+dis[index].value)){
				dis[i].value = g.adjMatrix[index][i]+dis[index].value;
			}
		}
	}
	//输出dis内的数据
	for(i = 0 ; i < g.vexnum ; i++){
		if(dis[i].value == INT_MAX){
			cout << "v" << begin << "---->" << "v" << i+1 << ": ∞" <<endl;
		}else{
			cout << "v" << begin << "---->" << "v" << i+1 << ": " << dis[i].value <<endl;
		}
	}
}
//利用Floyd算法求解没两个顶点之间的最短路径

void floyd(MGraph G) {
	int row = 0;
    int col = 0;
    for (row = 0; row < G.vexnum; row++) {
        for (col = 0; col < G.vexnum; col++) {
            //把矩阵D初始化为邻接矩阵的值
            G.dis[row][col] = G.adjMatrix[row][col];
            //矩阵P的初值则为各个边的终点顶点的下标
            G.path[row][col] = col;
        }
    }

    //三重循环，用于计算每个点对的最短路径
    int temp = 0;
    int select = 0;
    for (temp = 0; temp < G.vexnum; temp++) {
        for (row = 0; row < G.vexnum; row++) {
            for (col = 0; col < G.vexnum; col++) {
                //为了防止溢出，所以需要引入一个select值
                select = (G.dis[row][temp] == INT_MAX || G.dis[temp][col] == INT_MAX) ? INT_MAX : (G.dis[row][temp] + G.dis[temp][col]);
                if (G.dis[row][col] > select) {
                    //更新我们的D矩阵
                    G.dis[row][col] = select;
                    //更新我们的P矩阵
                    G.path[row][col] = G.path[row][temp];
                }
            }
        }
    }
}
void print_path(MGraph G) {
    cout << "各个顶点对的最短路径：" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = 0; row < G.vexnum; row++) {
        for (col = 0; col < G.vexnum; col++) {
			if(row == col) continue;
            cout << "v" << row + 1 << "---" << "v" << col+1 << " weight: "
                << G.dis[row][col] << " path: " << " v" << row + 1;
            temp = G.path[row][col];
            //循环输出途径的每条路径。
            while (temp != col) {
                cout << "-->" << "v" << temp + 1;
                temp = G.path[temp][col];
            }
            cout << "-->" << "v" << col + 1 << endl;
        }

        cout << endl;
    }
}
int main()
{
	while(true){
		cout << "请输入图的类型：有向图:1 , 无向图:2 , 有向网:3 , 无向网:4" <<endl;
		int kind = 1;
		cin >> kind;
		MGraph G;
		switch(kind){
			case 1:createGraph(G, DG);break;
			case 2:createGraph(G, DN);break;
			case 3:createGraph(G, UDG);break;
			case 4:createGraph(G, UDN);break;
			default:createGraph(G, DG);break;
		}
		print(G);
	    //DFSTraverse(G,1);
		//BFSTraverse(G,1);
		Prim(G,1);
		//clear(G);
		//Dijkstra(G,1);
		floyd(G);
		print_path(G);
		cout << endl;
	}
    return 0;
}