#include<iostream>
#include<string>
#include<stack>
using namespace std;
//����
struct ArcNode {
    ArcNode * next; //��һ�������ı�
    int adjvex;   //���满β�����ڶ�����е��±�
};
struct Vnode {
    string data; //��������
    ArcNode * firstarc; //��һ�������ڸö����
};

class Graph_DG {
private:
    int vexnum; //ͼ�Ķ�����
    int edge;   //ͼ�ı���
    int * indegree; //ÿ���ߵ�������
    Vnode * arc; //�ڽӱ�
public:
    Graph_DG(int, int);
    ~Graph_DG();
    //�������ߵĶ����Ƿ�Ϸ�
    bool check_edge_value(int,int);
    //����һ��ͼ
    void createGraph();
    //��ӡ�ڽӱ�
    void print();
    //������������,Kahn�㷨
    bool topological_sort();
    //������������DFS�㷨
    bool topological_sort_by_dfs();
    void dfs(int n,bool * & visit, stack<string> & result);
};
Graph_DG::Graph_DG(int vexnum, int edge) {
    this->vexnum = vexnum;
    this->edge = edge;
    this->arc = new Vnode[this->vexnum];
    this->indegree = new int[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        this->indegree[i] = 0;
        this->arc[i].firstarc = NULL;
		cout << "�����붨����" <<endl;
		string name="";
		cin >> name ;
        this->arc[i].data = name;
    }
}
//�ͷ��ڴ�ռ�
Graph_DG::~Graph_DG() {
    ArcNode * p, *q;
    for (int i = 0; i < this->vexnum; i++) {
        if (this->arc[i].firstarc) {
            p = this->arc[i].firstarc;
            while (p) {
                q = p->next;
                delete p;
                p = q;
            }
        }
    }
    delete [] this->arc;
    delete [] this->indegree;
}
//�ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end) {
    if (start<1 || end<1 || start>vexnum || end>vexnum) {
        return false;
    }
    return true;
}
void Graph_DG::createGraph() {
    int count = 0;
    int start, end;
    cout << "����ÿ�������յ�Ķ����ţ���1��ʼ��ţ�" << endl;
    while (count != this->edge) {
        cin >> start;
        cin >> end;
        //�����Ƿ�Ϸ�
        while (!this->check_edge_value(start, end)) {
            cout << "����Ķ��㲻�Ϸ�������������" << endl;
            cin >> start;
            cin >> end;
        }
        //����һ���µı���
        ArcNode * temp = new ArcNode;
        temp->adjvex = end - 1;
        temp->next = NULL;
        //�����ǰ����Ļ�û�б�����ʱ��
        if (this->arc[start - 1].firstarc == NULL) {
            this->arc[start - 1].firstarc = temp;
        }
        else {
            ArcNode * now = this->arc[start - 1].firstarc;
            while(now->next) {
                now = now->next;
            }//�ҵ�����������һ�����
            now->next = temp;
        }
        ++count;
    }
}
void Graph_DG::print() {
    int count = 0;
    cout << "ͼ���ڽӾ���Ϊ��" << endl;
    //��������������������
    while (count != this->vexnum) {
        //�������Ľ��
        cout << this->arc[count].data<<" ";
        ArcNode * temp = this->arc[count].firstarc;
        while (temp) {
            cout<<"<"<< this->arc[count].data<<","<< this->arc[temp->adjvex].data<<"> ";
            temp = temp->next;
        }
        cout << "^" << endl;
        ++count;
    }
}

bool Graph_DG::topological_sort() {
    cout << "ͼ����������Ϊ��" << endl;
    //ջs���ڱ���ջΪ�յĶ����±�
    stack<int> s;
    int i;
    ArcNode * temp;
    //����ÿ���������ȣ�������indgree������
    for (i = 0; i != this->vexnum; i++) {
        temp = this->arc[i].firstarc;
        while (temp) {
            ++this->indegree[temp->adjvex];
            temp = temp->next;
        }

    }

    //�����Ϊ0�Ķ�����ջ
    for (i = 0; i != this->vexnum; i++) {
        if (!indegree[i]) {
            s.push(i); 
        }
    }
    //count���ڼ�������Ķ������
    int count=0;
    while (!s.empty()) {//���ջΪ�գ������ѭ��
        i = s.top();
        s.pop();//����ջ��Ԫ�أ�����ջ��Ԫ�س�ջ
        cout << this->arc[i].data<<" ";//�����������
        temp = this->arc[i].firstarc;
        while (temp) {
            if (!(--this->indegree[temp->adjvex])) {//�����ȼ��ٵ�Ϊ0������ջ
                s.push(temp->adjvex);
            }
            temp = temp->next;
        }
        ++count;
    }
    if (count == this->vexnum) {
        cout << endl;
        return true;
    } 
    cout << "��ͼ�л�������������" << endl;
    return false;//˵�����ͼ�л�
}
bool Graph_DG::topological_sort_by_dfs() {
    stack<string> result;
    int i;
    bool * visit = new bool[this->vexnum];
    //��ʼ�����ǵ�visit����
    memset(visit, 0, this->vexnum);
    cout << "����DFS����������Ϊ��" << endl;
    //��ʼִ��DFS�㷨
    for (i = 0; i < this->vexnum; i++) {
        if (!visit[i]) {
            dfs(i, visit, result);
        }
    }
    //����������У���Ϊ����ÿ�ζ����ҵ��˳���Ϊ0�Ķ������ջ�У�
    //�������ʱ��ʵ��Ҫ�����������������ÿ�ζ���������Ϊ0�Ķ���
    for (i = 0; i < this->vexnum; i++) {
        cout << result.top() << " ";
        result.pop();
    }
    cout << endl;
    return true;
}
void Graph_DG::dfs(int n, bool * & visit, stack<string> & result) {

        visit[n] = true;
        ArcNode * temp = this->arc[n].firstarc;
        while (temp) {
            if (!visit[temp->adjvex]) {
                dfs(temp->adjvex, visit,result);
            }
            temp = temp->next;
        }
        //���ڼ��붥�㵽�����е�ʱ������dfs���������˳�֮ʱ��
        //��dfs���������Ǹ��ݹ鷽����
        //����Ҫ��ǰ���㻹���ڱ�ָ����������ʲô���㣬
        //���ͻ�ݹ����dfs�������������˳���
        //��ˣ��˳�dfs��������ζ�ŵ�ǰ����û��ָ����������ı���
        //������ǰ������һ��·���ϵ����һ�����㡣
        //���仰˵��ʵ���Ǵ�ʱ�ö������Ϊ0��
        result.push(this->arc[n].data);

}
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}
int main() {
    int vexnum; int edge;


    cout << "����ͼ�Ķ�������ͱߵ�������" << endl;
    cin >> vexnum >> edge;
    while (!check(vexnum, edge)) {
        cout << "�������ֵ���Ϸ�������������" << endl;
        cin >> vexnum >> edge;
    }
    Graph_DG graph(vexnum, edge);
    graph.createGraph();
    graph.print();
    graph.topological_sort();
    graph.topological_sort_by_dfs();
    system("pause");
    return 0;

}