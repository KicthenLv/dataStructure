#include<iostream>
#include<string.h>
#include<queue>
using namespace std;


enum Graphkind{ DG, DN, UDG, UDN }; //{����ͼ������ͼ����������������}

typedef struct  Node
{
    int * vex;  //��������
    int vexnum; //�������
    int edge;   //ͼ�ı���
    int ** adjMatrix; //ͼ���ڽӾ���
	int **dis; //Floyd�㷨ʹ�õ��ľ�������
	int **path;//floyd�㷨ʹ�õ������·��
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
    cout << "���붥��ĸ���" << endl;
    cin >> G.vexnum;
    cout << "����ߵĸ���" << endl;
    cin >> G.edge;
    //��������

    //cout << "����ͼ�����ࣺDG:����ͼ DN������ͼ��UDG��������,UDN:������" << endl;
    G.kind = kind;
    //Ϊ�������鿪�ٿռ�
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



    /*//����ÿ��Ԫ�ص���Ϣ,�����Ϣ�����ڻ�����Ҫʹ��
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vex[i];
    }*/
    cout << "�����������й�ϵ�Ķ������ţ����磺����ͼ��1 2 ����1�Ŷ���ָ��2�Ŷ��㣬����ͼ�����ʾ1 �� 2֮���б�" << endl;
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
            cout << "����ñߵ�Ȩ�أ�" << endl;
            cin >> weight;
            G.adjMatrix[a - 1][b - 1] = weight;
        }
        else {
            int weight;
            cout << "����ñߵ�Ȩ�أ�" << endl;
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
                cout << "��" << " ";
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
    for (int i = 0; i < g.vexnum; i++) {//�ҳ���һ��λ�����ʵĶ���
        if (g.adjMatrix[v][i] == 0 || g.adjMatrix[v][i] == INT_MAX) { //����������㲻���ڱ�
            continue;
        }
        else if (!visit[i]) {//���û�б����ʣ����ʸý��
            DFS_store_array(g, i, visit);
        }
    }
}
//DFS ������ȱ����ڽӾ���ͼ
void DFSTraverse(MGraph g,int begin){
	bool * visit;
    visit = new bool[g.vexnum];
    int i;
    for (i = 0; i < g.vexnum; i++) {
        visit[i] = false;
    }
    cout << "ͼ��DFS���������" << endl;
    DFS_store_array(g,begin - 1,visit);
    //���ͼ�Ƿ���ͨͬ����ô�������ﻹ��Ҫ��ÿ���������һ�Σ���֤
    //ȫ�����㶼��������
    for (i = 0; i < g.vexnum; i++) {
        if (!visit[i])
            DFS_store_array(g, i,visit);
    }	
	cout << endl;
}
//BFS ������ȱ���
void BFSTraverse(MGraph g,int begin){
	bool * visit;
    visit = new bool[g.vexnum];
    int i;
    for (i = 0; i < g.vexnum; i++) {
        visit[i] = false;
    }
    cout << "ͼ��BFS���������" << endl;
    //ͨ������֮ǰ˵���㷨˼·�����ǿ���֪��
    //������Ҫʹ���Ƚ��ȳ������ݴ洢�ṹʵ�����ǵ�BFS����ʵ�Ǿ��Ƕ���
    queue<int>  q;
    for (int v = 0; v < g.vexnum; v++) {//����ѭ����Ϊ�˱�֤����ͨͬ������£�ÿ�����㶼���Ա�����
        if (!visit[(begin-1 + v) % g.vexnum])//ע����㲻һ����v1
        {
            cout << (begin - 1 + v) % g.vexnum << " ";
            visit[(begin - 1 + v) % g.vexnum] = true;
            q.push((begin - 1 + v) % g.vexnum);//��ʼ�����ǵĶ���
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int j = 0; j < g.vexnum; j++) {
                    if (g.adjMatrix[u][j] == 0 || g.adjMatrix[u][j] == INT_MAX) { //����������㲻���ڱ�
                        continue;
                    }
                    else if (!visit[j] ) {//�ȷ������к�u�����Ķ��㣬���Ұ����Ǽ������
                        cout << j <<" ";
                        visit[j] = true;
                        q.push(j);
                    }
                }
            }
        }

    }
    cout << "���" << endl;
}
struct Assis_array {
    int start; //�ߵ��յ�
    int end;  //�ߵ����
    int weight;  //�ߵ�Ȩ��
};
//����prim�㷨ʵ���ڽӾ�������С������
//�¼����Ӷ�ΪO(n*n)
void Prim(MGraph g,int begin) {
	//ʹ��һ�����������ÿ��������������Ȩֵ��С�ı�
	//��ʼ������
	Assis_array *edges = new Assis_array[g.vexnum];
	for(int i = 0 ; i < g.vexnum ; i ++){
		edges[i].weight =  g.adjMatrix[begin-1][i];
		edges[i].start = begin -1 ;
		edges[i].end = i;
	}
	//����ڽڵ�����Ϊ-1��ʾ�ѱ�����
	edges[begin-1].weight = -1;
	//�������нڵ�������Ȩֵ��С�ı�
	int j = 0;
	for(i = i ; i < g.vexnum ; i++ ){
		int min = INT_MAX;
		int index = 0 ; //����һ������������͸��±߼���
		//ÿ�ִӱߵļ�������ҳ�Ȩֵ��С�ı����
		for(j = 0 ; j < g.vexnum ; j++){
			if(edges[j].weight != -1){
				if(edges[j].weight < min){
					min = edges[j].weight;
					index = j;
				}
			}
		}
		edges[index].weight = -1;
		//����������Ľڵ���Ϣ
		cout << "v" << (edges[index].start+1) << "---->"
			<< "v" << (edges[index].end+1) << "----"
			<< edges[index].weight <<endl;
		
		//���±߼�����Ϣ �����ѱ����Ľڵ�����С��Ȩֵ�߸��µ��߼���
		for(j = 0 ; j < g.vexnum ; j++){
			if(g.adjMatrix[edges[index].end][j] < edges[j].weight){
				edges[j].weight = g.adjMatrix[edges[index].end][j];
				edges[j].start = edges[index].end;
				edges[j].end = j;	
			}
		}
	}
 
}
//ʹ�õڽ�˹�����㷨ʵ������С·��
void Dijkstra(MGraph g,int begin){
	//�½�·������
	Dis *dis = new Dis[g.vexnum];
	//������ڳ�ʼֵ
	for(int i = 0 ; i < g.vexnum ;i++){
		dis[i].value = g.adjMatrix[begin-1][i]; 
		dis[i].path = begin-1 + "-->" + (i+1);
	}
	dis[begin-1].value = 0;
	dis[begin-1].visit = true;
	//ѭ�����ҳ���ÿ���ڵ����С·��
	int count = 0 ;
	while(count!=g.vexnum){
		//�ҵ���㵽�����ڵ����С����Υ�����ʵĽڵ��±�
		int min = INT_MAX;
		int index = 0;
		for(int j = 0 ; j < g.vexnum ; j ++){
			if(!dis[j].visit&&dis[j].value < min){
				min = dis[j].value;
				index = j;
			}
		}
		//�Ѵ˽ڵ�ķ��ʡ���ֵΪtrue
		dis[index].visit = true;
		++count;
		//������ǰ·����С��ͷ����������·������ͷ����뱻����ͷ����ͷ��������·��С��ԭ·����·��ֵ
		for(i = 0 ; i <g.vexnum ; i ++){
			if(!dis[i].visit&& g.adjMatrix[index][i]!=INT_MAX && (dis[i].value>g.adjMatrix[index][i]+dis[index].value)){
				dis[i].value = g.adjMatrix[index][i]+dis[index].value;
			}
		}
	}
	//���dis�ڵ�����
	for(i = 0 ; i < g.vexnum ; i++){
		if(dis[i].value == INT_MAX){
			cout << "v" << begin << "---->" << "v" << i+1 << ": ��" <<endl;
		}else{
			cout << "v" << begin << "---->" << "v" << i+1 << ": " << dis[i].value <<endl;
		}
	}
}
//����Floyd�㷨���û��������֮������·��

void floyd(MGraph G) {
	int row = 0;
    int col = 0;
    for (row = 0; row < G.vexnum; row++) {
        for (col = 0; col < G.vexnum; col++) {
            //�Ѿ���D��ʼ��Ϊ�ڽӾ����ֵ
            G.dis[row][col] = G.adjMatrix[row][col];
            //����P�ĳ�ֵ��Ϊ�����ߵ��յ㶥����±�
            G.path[row][col] = col;
        }
    }

    //����ѭ�������ڼ���ÿ����Ե����·��
    int temp = 0;
    int select = 0;
    for (temp = 0; temp < G.vexnum; temp++) {
        for (row = 0; row < G.vexnum; row++) {
            for (col = 0; col < G.vexnum; col++) {
                //Ϊ�˷�ֹ�����������Ҫ����һ��selectֵ
                select = (G.dis[row][temp] == INT_MAX || G.dis[temp][col] == INT_MAX) ? INT_MAX : (G.dis[row][temp] + G.dis[temp][col]);
                if (G.dis[row][col] > select) {
                    //�������ǵ�D����
                    G.dis[row][col] = select;
                    //�������ǵ�P����
                    G.path[row][col] = G.path[row][temp];
                }
            }
        }
    }
}
void print_path(MGraph G) {
    cout << "��������Ե����·����" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = 0; row < G.vexnum; row++) {
        for (col = 0; col < G.vexnum; col++) {
			if(row == col) continue;
            cout << "v" << row + 1 << "---" << "v" << col+1 << " weight: "
                << G.dis[row][col] << " path: " << " v" << row + 1;
            temp = G.path[row][col];
            //ѭ�����;����ÿ��·����
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
		cout << "������ͼ�����ͣ�����ͼ:1 , ����ͼ:2 , ������:3 , ������:4" <<endl;
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