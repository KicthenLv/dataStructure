#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

typedef string Vertextype;
//����ṹ
struct ArcNode {
    int adjvex;   //ĳ����ָ����Ǹ������λ�ã�һ����������±꣩��
    ArcNode * nextarc; //ָ����һ������
    int weight;   //���ֻ����ͼ����Ҫʹ�á�
};

//ͷ���
struct Vnode
{
    Vertextype data;  //����Ǽ�¼ÿ���������Ϣ������һ�㶼����Ҫ��ôʹ�ã�
    ArcNode * firstarc; //ָ���һ�������ڸö���ߵ���Ϣ�����㣩
};

//
struct Graph
{
    int kind;  //ͼ������(����ͼ��0,����ͼ��1����������2����������3)
    int vexnum; //ͼ�Ķ�����
    int edge;  //ͼ�ı���
	int *indegree; //���������������
    stack<int> List; //���������и����ߵ����
    int * ve;  //��¼ÿ����������緢��ʱ��
    int * vl;  //��¼ÿ��������ٷ���ʱ��
    Vnode * node; //ͼ�ģ����㣩ͷ�������
};

void createGraph(Graph & g,int kind)
{
    cout << "�����붥��ĸ�����" << endl;
    cin >> g.vexnum;
    cout << "������ߵĸ�����" << endl;
    cin >> g.edge;
    g.kind = kind; //����ͼ������
    g.node = new Vnode[g.vexnum];
    int i;
    cout << "����ÿ���������Ϣ��" << endl;//��¼ÿ���������Ϣ
    for (i = 0; i < g.vexnum; i++)
    {
        cin >> g.node[i].data;
        g.node[i].firstarc=NULL;
    }

    cout << "������ÿ���ߵ������յ�ı�ţ�" << endl;
    for (i = 0; i < g.edge; i++)
    {
        int a;
        int b;
        cin >> a; //���
        cin >> b; //�յ�
        ArcNode * next=new ArcNode;
        next->adjvex = b - 1;
        if(kind==0 || kind==1)
			next->weight = -1;
        else {//�������ͼ������ҪȨ��
            cout << "����ñߵ�Ȩ�أ�" << endl;
            cin >> next->weight;
        }
        next->nextarc = NULL;

        //���ߴ�������
        if (g.node[a - 1].firstarc == NULL) {
            g.node[a - 1].firstarc=next;

        }
        else 
        {
            ArcNode * p;
            p = g.node[a - 1].firstarc;
            while (p->nextarc)//�ҵ�����������һ������
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

			//�����һ�������ı�Ϊ��
			if (g.node[b - 1].firstarc == NULL) {
				g.node[b - 1].firstarc = next_2;
			}
			else {
				ArcNode * temp; //��ʱ����
				temp = g.node[b - 1].firstarc;
				while (temp->nextarc) {//�ҵ�������start-1���������������һ������
					temp = temp->nextarc;
				}
				temp->nextarc = next_2;  //�ڸ������β������һ�����
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
//DFS������ȱ����ڽ�����ͼ
void DFSTraverse(Graph g, int begin){
	bool *visit = new bool[g.vexnum];
	for(int i = 0 ; i < g.vexnum ; i++){
		visit[i] = false;
	}
	cout << "ͼ��DFS���������" << endl;
	DFS_Show(g,begin-1,visit);
	cout << endl;
}
//BFS������ȱ���ͼ
void BFSTraverse(Graph g, int begin){
	bool *visit = new bool[g.vexnum];
	for(int i = 0 ; i < g.vexnum ; i++){
		visit[i] = false;
	}
	cout << "ͼ��BFS���������" << endl;
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
    cout << "ͼ���ڽӱ�Ϊ��" << endl;
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
//����һ���ṹ����ű�
typedef struct{
	int start;
	int end;
	int weight;
}edge;

//prim�㷨ʵ����С������ ,�¼����Ӷ�ΪO(n*n)
void prim(Graph g, int begin){
	//����һ�������������Ȩֵ��С����Щ��
	edge *edges = new edge[g.vexnum];
	//��ʼ���߼���
	for(int i = 0 ; i < g.vexnum ; i++){
		edges[i].weight = INT_MAX;
	}
	//��ʼ���߼��ϣ��Ƚ���ڽڵ�����й����ߵ��������뵽�����У�������ڸ���ÿ������������ıߵ�����
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
		int index = 0 ; //��ŵ�ǰ�߼�������С��Ȩֵ�ı�����
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
		edges[index].weight  = -1 ; //��ʾ�˽ڵ��Ѿ������ʣ�����������������
		//���µĽڵ��������ı�ȨֵС�ڵ�ǰ�߼��ϵ�Ȩֵ���µ��߼���
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
//��Ȩֵ����߼�
void sort(edge *edges,int edgeNum){
	//ʹ��ð������
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
//���ҽڵ�ĸ��ڵ��±�
int findRoot(int index , int *parent){
	if(index == parent[index]) //����ڵ��±���ڸ��ڵ㼯���ڵĸýڵ��±�
		return index;
	//����ݹ���Ҹ��ڵ�
	parent[index] = findRoot(parent[index],parent);
	return parent[index];
}
//ʵ��kruskal�㷨 ��������С������ �¼����Ӷ�ΪO(eloge)e��ʾͼ�ı���
void kruskal(Graph g,int begin){
	//��ͼ�ڵıߴ�ŵ��߼�������
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
	//����߼�
	sort(edges,g.edge);

	//����һ�����ڵ�ͺ��ӽڵ���������
	int *parent = new int[g.vexnum];
	int *child = new int[g.vexnum];
	//��ʼ���ڵ�����
	for(i = 0 ; i < g.vexnum ; i++){
		parent[i] = i; // ����ýڵ�ĸ��ڵ��±����������ýڵ�Ϊ���ڵ�
		child[i] = 0;
	}
	//������
	int count = 0 ;
	i = 0 ;
	while(count != g.edge){
		//�ҵ��߽ڵ�ĸ��ڵ㣬�����ڵ�һ���������˱ߣ����򽫴˱���뵽����
		int root1 = findRoot(edges[i].start,parent);
		int root2 = findRoot(edges[i].end , parent);
		if(root1!=root2) //������ڵ㲻��ͬ
		{
			cout << "v" << edges[i].start+1 << "---->"
                << "v" << edges[i].end+1 << "----"
                << edges[i].weight << endl;
			//���ڵ��±�С��ǰ������
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
			break;//��ʾ��Ҫ��ӵı��Ѿ����
		}
		i++;
	}
	 if (count != g.vexnum - 1) {
        cout << "��ͼΪ����ͨͼ���޷�������С��������" << endl;
    }
    delete [] edges;
    delete [] parent;
    delete [] child;
}
// ʵ��kahn�㷨 ��������AOV(�ͼ) ������ʾһЩ�ִ�е��Ⱥ�˳������޻�����ͼ(DAG)
void kahnTopoSort(Graph g){
	stack<int> s; //�������Ϊ0�Ķ����±�
	//��ȡͼ��ÿ���ڵ����ȣ������Ϊ0�Ľڵ�ѹ��ջ�У��������ʱ����ջ��Ԫ�أ����жϸýڵ�ĳ��Ƚڵ�ĸ������
	//�����ڵ�����
	for(int i = 0  ; i< g.vexnum ; i ++){
		ArcNode *node = g.node[i].firstarc;
		while(node){
			g.indegree[node->adjvex]++;
			node = node->nextarc;
		}
	}

	//����������飬����ȴ���0�Ľڵ��±���뵽ջ��
	for(i = 0 ; i < g.vexnum ; i++){
		if(!g.indegree[i]){
			s.push(i);
		}
	}
	int count=0; //��������Ķ������������������ڶ���������˵���л�
	cout << "�����޻�ͼ����������" <<endl;
	//����ջ��Ԫ��
	while(!s.empty()){
		int index = s.top();
		s.pop();
		g.List.push(index);  //Ϊ�������¼�����ٷ���ʱ�����̵�
		cout << g.node[index].data << " ";
		ArcNode *node = g.node[index].firstarc;
		while(node){
			 //���һ������Ƚڵ�󣬽����ĳ��Ƚڵ���������һ
			if(!(--g.indegree[node->adjvex])){
				s.push(node->adjvex);
			}
			if((g.ve[index]+node->weight) > g.ve[node->adjvex]) g.ve[node->adjvex] = g.ve[index]+node->weight;
			node = node->nextarc;
		}
		count ++;
	}
	if(count!=g.vexnum) cout << "��ͼ���ڻػ�������������" <<endl;
	else cout << endl;
	
	//�Ƚ�vl��ֵ��Ϊve�����ֵ����������ж�
	for (i = 0; i < g.vexnum; i++) {
        g.vl[i] = g.ve[g.vexnum - 1];
    }
	ArcNode *temp;
	while(!g.List.empty()){
		i = g.List.top();//������������ʼ����vl
        g.List.pop();
        temp = g.node[i].firstarc;
        while (temp) {
            //dut<i,temp->end>�����Ե�k������Ϊ��β������ѡ��һ����С��ֵ
            //����Ϊ��i���������ٷ���ʱ��
            if (g.vl[i] > (g.vl[temp->adjvex] - temp->weight)) {
                g.vl[i] = g.vl[temp->adjvex] - temp->weight;
            }
            temp = temp->nextarc;
        }
	}
}
//dfs�ݹ���
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
//ʹ��dfs������������ķ�ʽ�������򣬵ݹ�һ���ڵ�ĳ���֪���ڵ�û�г��Ⱥ󣬽���ѹ��ջ�ڣ�����������ջ��Ԫ��
void DFSTopoSort(Graph g){
	stack<string> s;
	//����һ��visit�������жϽڵ��Ƿ���ʹ�
	int *visited = new int[g.vexnum];
	for(int i =0 ; i < g.vexnum ; i ++){
		visited[i] = 0;
	}
	//ִ��DFS�㷨
	for(i = 0 ; i <g.vexnum ; i++){
		if(!visited[i]) //���δ������
			DFSTopo(g,s,i,visited);
	}
	//�������ջ��Ԫ��
	cout << "DFS��������" << endl;
	while(!s.empty()){
		cout << s.top() << " "; 
		s.pop();
	}
	cout << endl;
}
//���������Ĺؼ�·�� �͹ؼ��¼�
void KeyPath(Graph g){
	/*
	//��������¼���ve(i)�¼��緢��ʱ�� ��vl(i) �¼���ٷ���ʱ��
	int *ve = new int[g.vexnum];
	int *vl = new int[g.vexnum];
	//��ʼ����һ��ve�����һ��vl
	for(int i = 0 ; i < g.vexnum ; i ++) {
		ve[i] = 0 ;
		vl[i] = 0 ;
	}
	//��ÿ���¼���vej , vej = =Max{ve{i}+dut(<i,j>)},j= 1,2,3.... , dut(<i,j>��ʾ��iΪ��β��jΪ��ͷ�Ļ��ִ���¼����ߵ�Ȩֵ;
	for(i = 0 ; i < g.vexnum -1 ; i ++){
		ArcNode *node = g.node[i].firstarc;
		while(node){
			if((ve[i]+node->weight) > ve[node->adjvex]) ve[node->adjvex] = ve[i]+node->weight;
			node =  node->nextarc;
		}
	}*/
	
	//�Ƚ�vl��ֵ��Ϊve�����ֵ����������ж�
	/*for (int i = 0; i < g.vexnum; i++) {
        g.vl[i] = g.ve[g.vexnum - 1];
    }
	ArcNode *temp;
	cout << g.List.size() << endl;
	while(!g.List.empty()){
		cout << "test" <<endl;
		i = g.List.top();//������������ʼ����vl
        g.List.pop();
        temp = g.node[i].firstarc;
        while (temp) {
            //dut<i,temp->end>�����Ե�k������Ϊ��β������ѡ��һ����С��ֵ
            //����Ϊ��i���������ٷ���ʱ��
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
            if (ee == el) {//������ֵ��ȣ�˵����Ϊ�ؼ����
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
    cout << "����ͼ������" << endl;
    createGraph(g,0);
    print(g);
	//DFSTraverse(g,1);
	//BFSTraverse(g,1);
	kahnTopoSort(g);
	//DFSTopoSort(g);
	KeyPath(g);
    cout << endl;
	
	/*
    cout << "������������" << endl;
    createGraph(g, 3);
    print(g);
	//prim(g,1);
	//kruskal(g,1);
	//DFSTraverse(g,1);
	//BFSTraverse(g,1);
    cout << endl;
	*/
	cout << "������������" << endl;
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