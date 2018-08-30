#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

typedef string Vertextype;
//表结点结构
struct ArcNode {
    int adjvex;   //某条边指向的那个顶点的位置（一般是数组的下标）。
    ArcNode * nextarc; //指向下一个表结点
    int weight;   //这个只有网图才需要使用。
};

//头结点
struct Vnode
{
    Vertextype data;  //这个是记录每个顶点的信息（现在一般都不需要怎么使用）
    ArcNode * firstarc; //指向第一条依附在该顶点边的信息（表结点）
};

//
struct Graph
{
    int kind;  //图的种类(有向图：0,无向图：1，有向网：2，无向网：3)
    int vexnum; //图的顶点数
    int edge;  //图的边数
	int *indegree; //各个顶点的入度情况
    stack<int> List; //拓扑序列中各个边的情况
    int * ve;  //记录每个顶点的最早发生时间
    int * vl;  //记录每个顶点最迟发生时间
    Vnode * node; //图的（顶点）头结点数组
};

void createGraph(Graph & g,int kind)
{
    cout << "请输入顶点的个数：" << endl;
    cin >> g.vexnum;
    cout << "请输入边的个数：" << endl;
    cin >> g.edge;
    g.kind = kind; //决定图的种类
    g.node = new Vnode[g.vexnum];
    int i;
    cout << "输入每个顶点的信息：" << endl;//记录每个顶点的信息
    for (i = 0; i < g.vexnum; i++)
    {
        cin >> g.node[i].data;
        g.node[i].firstarc=NULL;
    }

    cout << "请输入每条边的起点和终点的编号：" << endl;
    for (i = 0; i < g.edge; i++)
    {
        int a;
        int b;
        cin >> a; //起点
        cin >> b; //终点
        ArcNode * next=new ArcNode;
        next->adjvex = b - 1;
        if(kind==0 || kind==1)
			next->weight = -1;
        else {//如果是网图，还需要权重
            cout << "输入该边的权重：" << endl;
            cin >> next->weight;
        }
        next->nextarc = NULL;

        //将边串联起来
        if (g.node[a - 1].firstarc == NULL) {
            g.node[a - 1].firstarc=next;

        }
        else 
        {
            ArcNode * p;
            p = g.node[a - 1].firstarc;
            while (p->nextarc)//找到该链表的最后一个表结点
            {
                p = p->nextarc;
            }
            p->nextarc = next;
        }
		if(g.kind == 3|| g.kind ==1){
			ArcNode * next_2 = new ArcNode;
			next_2->adjvex = a-1;
			next_2->weight = next->weight;
			next_2->nextarc = NULL;

			//如果第一个依附的边为空
			if (g.node[b - 1].firstarc == NULL) {
				g.node[b - 1].firstarc = next_2;
			}
			else {
				ArcNode * temp; //临时表结点
				temp = g.node[b - 1].firstarc;
				while (temp->nextarc) {//找到表结点中start-1这个结点的链表的最后一个顶点
					temp = temp->nextarc;
				}
				temp->nextarc = next_2;  //在该链表的尾部插入一个结点
			}
		}
    }
	g.ve = new int[g.vexnum];
	g.vl = new int[g.vexnum];
	g.indegree = new int[g.vexnum];
	for(i = 0 ; i < g.vexnum ; i++){
		g.ve[i] = 0;
		g.vl[i] = 0;
		g.indegree[i] = 0;
	}
}
void DFS_Show(Graph g,int v,bool *visit){
	cout << v << " ";
	visit[v] = true;
	ArcNode *next = g.node[v].firstarc;
	while(next){
		if(!visit[next->adjvex]){
			DFS_Show(g,next->adjvex,visit);	
		}else{
			next = next->nextarc;	
		}
	}
}
//DFS深度优先遍历邻接链表图
void DFSTraverse(Graph g, int begin){
	bool *visit = new bool[g.vexnum];
	for(int i = 0 ; i < g.vexnum ; i++){
		visit[i] = false;
	}
	cout << "图的DFS遍历结果：" << endl;
	DFS_Show(g,begin-1,visit);
	cout << endl;
}
//BFS广度优先遍历图
void BFSTraverse(Graph g, int begin){
	bool *visit = new bool[g.vexnum];
	for(int i = 0 ; i < g.vexnum ; i++){
		visit[i] = false;
	}
	cout << "图的BFS遍历结果：" << endl;
	queue<int>  q;
	for(int j = 0 ; j < g.vexnum ; j++){
		if(!visit[begin-1+j]){
			cout << begin-1+j << " ";
			visit[begin-1+j] = true;
			q.push(begin-1+j);
			while(!q.empty()){
				int u = q.front();
				q.pop();
				ArcNode *next;
				next = g.node[u].firstarc;
				while(next){
					if(!visit[next->adjvex]){
						cout << next->adjvex << " ";
						visit[next->adjvex] = true;
						q.push(next->adjvex);
					}
					next = next->nextarc;
				}
			}
		}
	}
}
void print(Graph  g)
{
    int i;
    cout << "图的邻接表为：" << endl;
    for (i = 0; i < g.vexnum; i++)
    {
        cout << g.node[i].data<<" ";
        ArcNode * now;
        now = g.node[i].firstarc;
        while (now)
        {
            cout << now->adjvex+1 << " ";
            now = now->nextarc;
        }
        cout << endl;
    }
}
//创建一个结构来存放边
typedef struct{
	int start;
	int end;
	int weight;
}edge;

//prim算法实现最小生成树 ,事件复杂度为O(n*n)
void prim(Graph g, int begin){
	//创建一个边数组来存放权值最小的那些变
	edge *edges = new edge[g.vexnum];
	//初始化边集合
	for(int i = 0 ; i < g.vexnum ; i++){
		edges[i].weight = INT_MAX;
	}
	//初始化边集合，先将入口节点的所有关联边的数据载入到集合中，后面会在更新每个顶点相关联的边的数据
	ArcNode* node = g.node[begin-1].firstarc;
	while(node){
		edges[node->adjvex].start = begin - 1;
		edges[node->adjvex].end = node->adjvex;
		edges[node->adjvex].weight = node->weight;
		node = node->nextarc;
	}
	edges[begin-1].weight = -1;
	for( i = 1 ; i < g.vexnum ; i++){
		int j = 0 ;
		int min = INT_MAX;
		int index = 0 ; //存放当前边集合内最小的权值的边索引
		for(j = 0; j < g.vexnum ; j++){
			if(edges[j].weight != - 1){
				if(edges[j].weight < min){
					min = edges[j].weight;
					index = j;
				}		
			}
		}
		
		cout << "v" << (edges[index].start+1) << "---->"
			<< "v" << (edges[index].end+1) << "----"
			<< edges[index].weight <<endl;
		edges[index].weight  = -1 ; //表示此节点已经被访问，方便后续更新与查找
		//从新的节点的相关联的边权值小于当前边集合的权值更新到边集合
		ArcNode *update = g.node[index].firstarc;
		while(update){
			if(update->weight < edges[update->adjvex].weight){
				edges[update->adjvex].weight = update->weight;
				edges[update->adjvex].start = index;
				edges[update->adjvex].end = update->adjvex;
			}
			update = update->nextarc;
		}
	}
}
//按权值排序边集
void sort(edge *edges,int edgeNum){
	//使用冒泡排序
	for(int i = 0 ; i < edgeNum ; i++){
		for(int j = 0 ; j < edgeNum - i -1 ; j++){
			if(edges[j].weight > edges[j+1].weight){
				int start = edges[j].start;
				int end = edges[j].end;
				int weight = edges[j].weight;
				edges[j].start = edges[j+1].start;
				edges[j].end = edges[j+1].end;
				edges[j].weight = edges[j+1].weight;
				edges[j+1].start = start;
				edges[j+1].end = end;
				edges[j+1].weight = weight;
			}
		}
	}
}
//查找节点的根节点下标
int findRoot(int index , int *parent){
	if(index == parent[index]) //如果节点下标等于父节点集合内的该节点下标
		return index;
	//否则递归查找根节点
	parent[index] = findRoot(parent[index],parent);
	return parent[index];
}
//实现kruskal算法 来生成最小生成树 事件复杂度为O(eloge)e表示图的边数
void kruskal(Graph g,int begin){
	//将图内的边存放到边集数组内
	edge *edges = new edge[g.edge];
	int index = 0 ;
	for(int i = 0 ; i < g.vexnum ; i++){
		ArcNode *node = g.node[i].firstarc;
		while(node){
			if(node->adjvex > i){
				edges[index].start = i;
				edges[index].end = node->adjvex;
				edges[index].weight = node->weight;
				++index;
			}
			node = node->nextarc;
		}
	}
	//排序边集
	sort(edges,g.edge);

	//创建一个父节点和孩子节点数的数组
	int *parent = new int[g.vexnum];
	int *child = new int[g.vexnum];
	//初始化节点数据
	for(i = 0 ; i < g.vexnum ; i++){
		parent[i] = i; // 如果该节点的父节点下标等于自身则该节点为根节点
		child[i] = 0;
	}
	//生成树
	int count = 0 ;
	i = 0 ;
	while(count != g.edge){
		//找到边节点的根节点，若根节点一样则跳过此边，否则将此变加入到树中
		int root1 = findRoot(edges[i].start,parent);
		int root2 = findRoot(edges[i].end , parent);
		if(root1!=root2) //如果根节点不相同
		{
			cout << "v" << edges[i].start+1 << "---->"
                << "v" << edges[i].end+1 << "----"
                << edges[i].weight << endl;
			//按节点下标小在前生成树
			if(child[root1] >= child[root2]){
				parent[root2] = root1;
				child[root1] += child[root2]+1;
			}else{
				parent[root1] = root2;
				child[root2] += child[root1]+1;
			}
			++count;
		}	
		if(count == g.vexnum -1){
			break;//表示需要添加的边已经完成
		}
		i++;
	}
	 if (count != g.vexnum - 1) {
        cout << "此图为非连通图！无法构成最小生成树。" << endl;
    }
    delete [] edges;
    delete [] parent;
    delete [] child;
}
// 实现kahn算法 拓扑排序，AOV(活动图) 用来表示一些活动执行的先后顺序，针对无环有向图(DAG)
void kahnTopoSort(Graph g){
	stack<int> s; //保存入度为0的顶点下标
	//获取图中每个节点的入度，将入度为0的节点压入栈中，输出排序时弹出栈顶元素，并判断该节点的出度节点的更新入读
	//遍历节点的入度
	for(int i = 0  ; i< g.vexnum ; i ++){
		ArcNode *node = g.node[i].firstarc;
		while(node){
			g.indegree[node->adjvex]++;
			node = node->nextarc;
		}
	}

	//遍历入度数组，将入度大于0的节点下标加入到栈中
	for(i = 0 ; i < g.vexnum ; i++){
		if(!g.indegree[i]){
			s.push(i);
		}
	}
	int count=0; //计数输出的顶点数，如果结果不等于顶点数，这说明有环
	cout << "有向无环图的拓扑排序" <<endl;
	//数组栈中元素
	while(!s.empty()){
		int index = s.top();
		s.pop();
		g.List.push(index);  //为后续求事件的最迟发生时间做铺垫
		cout << g.node[index].data << " ";
		ArcNode *node = g.node[index].firstarc;
		while(node){
			 //输出一个无入度节点后，将他的出度节点的入度数减一
			if(!(--g.indegree[node->adjvex])){
				s.push(node->adjvex);
			}
			if((g.ve[index]+node->weight) > g.ve[node->adjvex]) g.ve[node->adjvex] = g.ve[index]+node->weight;
			node = node->nextarc;
		}
		count ++;
	}
	if(count!=g.vexnum) cout << "此图存在回环，无拓扑排序" <<endl;
	else cout << endl;
	
	//先将vl的值置为ve的最大值，方便后续判断
	for (i = 0; i < g.vexnum; i++) {
        g.vl[i] = g.ve[g.vexnum - 1];
    }
	ArcNode *temp;
	while(!g.List.empty()){
		i = g.List.top();//从逆拓扑排序开始，求vl
        g.List.pop();
        temp = g.node[i].firstarc;
        while (temp) {
            //dut<i,temp->end>，从以第k个顶点为弧尾集合中选择一个最小的值
            //来作为第i个顶点的最迟发生时间
            if (g.vl[i] > (g.vl[temp->adjvex] - temp->weight)) {
                g.vl[i] = g.vl[temp->adjvex] - temp->weight;
            }
            temp = temp->nextarc;
        }
	}
}
//dfs递归体
void DFSTopo(Graph g,stack<string> &s,int index,int *visited){
	visited[index] = 1;
	ArcNode *node = g.node[index].firstarc;
	while(node){
		if(!visited[node->adjvex])
			DFSTopo(g,s,node->adjvex,visited);
		node = node->nextarc;
	}
	s.push(g.node[index].data);
}
//使用dfs深度优先搜索的方式拓扑排序，递归一个节点的出度知道节点没有出度后，将其压入栈内，遍历完后，输出栈内元素
void DFSTopoSort(Graph g){
	stack<string> s;
	//创建一个visit数组来判断节点是否访问过
	int *visited = new int[g.vexnum];
	for(int i =0 ; i < g.vexnum ; i ++){
		visited[i] = 0;
	}
	//执行DFS算法
	for(i = 0 ; i <g.vexnum ; i++){
		if(!visited[i]) //如果未被访问
			DFSTopo(g,s,i,visited);
	}
	//遍历输出栈内元素
	cout << "DFS拓扑排序" << endl;
	while(!s.empty()){
		cout << s.top() << " "; 
		s.pop();
	}
	cout << endl;
}
//求有向网的关键路径 和关键事件
void KeyPath(Graph g){
	/*
	//求出各个事件的ve(i)事件早发生时间 和vl(i) 事件最迟发生时间
	int *ve = new int[g.vexnum];
	int *vl = new int[g.vexnum];
	//初始化第一个ve和最后一个vl
	for(int i = 0 ; i < g.vexnum ; i ++) {
		ve[i] = 0 ;
		vl[i] = 0 ;
	}
	//求每个事件的vej , vej = =Max{ve{i}+dut(<i,j>)},j= 1,2,3.... , dut(<i,j>表示已i为弧尾，j为弧头的活动的执行事件即边的权值;
	for(i = 0 ; i < g.vexnum -1 ; i ++){
		ArcNode *node = g.node[i].firstarc;
		while(node){
			if((ve[i]+node->weight) > ve[node->adjvex]) ve[node->adjvex] = ve[i]+node->weight;
			node =  node->nextarc;
		}
	}*/
	
	//先将vl的值置为ve的最大值，方便后续判断
	/*for (int i = 0; i < g.vexnum; i++) {
        g.vl[i] = g.ve[g.vexnum - 1];
    }
	ArcNode *temp;
	cout << g.List.size() << endl;
	while(!g.List.empty()){
		cout << "test" <<endl;
		i = g.List.top();//从逆拓扑排序开始，求vl
        g.List.pop();
        temp = g.node[i].firstarc;
        while (temp) {
            //dut<i,temp->end>，从以第k个顶点为弧尾集合中选择一个最小的值
            //来作为第i个顶点的最迟发生时间
            if (g.vl[i] > (g.vl[temp->adjvex] - temp->weight)) {
                g.vl[i] = g.vl[temp->adjvex] - temp->weight;
            }
            temp = temp->nextarc;
        }
	}
	cout <<endl;
	for(i = 0 ; i <g.vexnum ; i ++){
		cout << g.vl[i] << " ";
	}
	cout <<endl;
	*/
	int ee;
    int el;
	ArcNode *temp;
    for (int i = 0; i < g.vexnum; i++) {
        temp = g.node[i].firstarc;
        while (temp) {
            ee = g.ve[i];
            el = g.vl[temp->adjvex] - temp->weight;
            if (ee == el) {//这两个值相等，说明它为关键活动：
                cout << g.node[i].data
                    << "----"
                    << g.node[temp->adjvex].data
                    << "="
                    << temp->weight
                    << endl;
            }
            temp = temp->nextarc;
        }
    }
}
int main()
{
    Graph g;
	/*
    cout << "有向图的例子" << endl;
    createGraph(g,0);
    print(g);
	//DFSTraverse(g,1);
	//BFSTraverse(g,1);
	kahnTopoSort(g);
	//DFSTopoSort(g);
	KeyPath(g);
    cout << endl;
	
	/*
    cout << "无向网的例子" << endl;
    createGraph(g, 3);
    print(g);
	//prim(g,1);
	//kruskal(g,1);
	//DFSTraverse(g,1);
	//BFSTraverse(g,1);
    cout << endl;
	*/
	cout << "有向网的例子" << endl;
    createGraph(g,2);
    print(g);
	//DFSTraverse(g,1);
	//BFSTraverse(g,1);
	kahnTopoSort(g);
	//DFSTopoSort(g);
	KeyPath(g);
    cout << endl;
    return 0;
}