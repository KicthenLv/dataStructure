#include<iostream>
#include<stack>
#include<string>
using namespace std;
//����
struct ArcNode {
    int start;    //��β�Ķ�����±�
    int end;    //��ͷ�Ķ�����±� ���м�ͷ��һ��
    int weight; //����Ȩ��
    ArcNode * next; //��һ����
};
//ͷ���
struct Vnode {
    ArcNode * firstarc;  //��һ�������ڸøö���Ļ�
    string data;
};

class Graph_DG {
private:
    int vexnum; //�������
    int edge;   //�ߵ�����
    Vnode * arc; //�ڽӱ�
    int *indegree; //���������������
    stack<int> List; //���������и����ߵ����
    int * ve;  //��¼ÿ����������緢��ʱ��
    int * vl;  //��¼ÿ��������ٷ���ʱ��

public:
    Graph_DG(int vexnum, int edge); 
    ~Graph_DG();//��������
    bool check_edge_value(int, int, int); //���ߵ���Ϣ�Ƿ�Ϸ�
    void createGraph();//����һ���µ�ͼ
    void print();//��ӡͼ���ڽӱ�
    bool topological_sort();
    bool CriticalPath();
};
Graph_DG::Graph_DG(int vexnum, int edge) {  
        /*
        ��ʼ��һЩ��������Ϣ��
        �����ߺͶ����������������������飬�ڽӱ�ĵ�
        */
        this->vexnum = vexnum;
        this->edge = edge;
        this->arc = new Vnode[this->vexnum];
        this->indegree = new int[this->vexnum];
        this->ve = new int[this->vexnum];
        this->vl = new int[this->vexnum];
        for (int i = 0; i < this->vexnum; i++) {
            this->indegree[i] = 0;
            this->ve[i] = 0;
            this->arc[i].firstarc = NULL;
			cout << "����ڵ������" <<endl;
			string name= "";
			cin >> name;
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
    delete[] this->arc;
    delete[] this->indegree;
}
//�ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end,int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph() {
    cout << "������ÿ���ߵ������յ�ı�ţ������1��ʼ��ţ��Լ�ÿ���ߵ�Ȩ��" << endl;
    int count = 0; //��¼��ʼ���ߵ�����
    int start, end, weight;
    while (count != this->edge) {
        cin >> start >> end >> weight;
        while (!check_edge_value(start, end, weight)) {
            cout << "�������Ϣ���Ϸ������������룺" << endl;
            cin >> start >> end >> weight;
        }
        ArcNode * temp = new ArcNode;
        temp->start = start-1;
        temp->end = end-1;
        temp->weight = weight;
        temp->next = NULL;
        //�����ǰ����Ļ�û�б�����ʱ��
        ++indegree[temp->end];   //��Ӧ�Ļ�ͷ�Ķ������ȼ�1
        if (this->arc[start - 1].firstarc == NULL) {
            this->arc[start - 1].firstarc = temp;
        }
        else {
            ArcNode * now = this->arc[start - 1].firstarc;
            while (now->next) {
                now = now->next;
            }//�ҵ�����������һ�����
            now->next = temp;
        }
        ++count;
    }
}
void Graph_DG::print() {
    cout << "ͼ���ڽӱ�Ϊ��" << endl;
    int  count = 0;
    while (count != this->vexnum) {
        cout << this->arc[count].data << " ";
        ArcNode * temp = this->arc[count].firstarc;
        while (temp) {
            cout << "<"
                << this->arc[temp->start].data
                << ","
                << this->arc[temp->end].data
                << ">="
                << temp->weight
                << " ";
            temp = temp->next;
        }
        cout << "^" << endl;
        ++count;
    }
}

bool Graph_DG::topological_sort() {
    cout << "ͼ����������Ϊ��" << endl;
    stack<int> s; //�������Ϊ0�Ķ����±�
    ArcNode * temp;
    int i;
    for (i = 0; i < this->vexnum; i++) {
        if (!indegree[i]) s.push(i); //���Ϊ0 ������ջ
    }
    //count���ڼ�������Ķ������
    int count = 0;
    while (!s.empty()) {//���ջΪ�գ��˳�ѭ��
        i = s.top(); //i����ջ����Ԫ��
        s.pop();
        cout << this->arc[i].data << " ";//�����������
        temp = this->arc[i].firstarc;
        this->List.push(i);
        while (temp) {
            if (!(--indegree[temp->end])) {//�����ȼ��ٵ�Ϊ0������ջ
                s.push(temp->end);
            }
            //ͬʱ����ve��ֵ
            if ((ve[i] + temp->weight) > ve[temp->end]) {
                ve[temp->end] = ve[i] + temp->weight;
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

bool Graph_DG::CriticalPath() {

    if (!this->topological_sort()) {
        cout << "��ͼ�л����޹ؼ�·��" << endl;
        return false;
    }
    cout << "ͼ�Ĺؼ�·��Ϊ��" << endl;
    //��ʼ��vl��ֵ��Ϊve[this->vexnum-1]
    int k;

    for (k = 0; k < this->vexnum; k++) {
        vl[k] = ve[this->vexnum - 1];

    }

    ArcNode * temp;
    while (!this->List.empty()) {
        k = List.top();//������������ʼ����vl
        List.pop();
        temp = this->arc[k].firstarc;
        while (temp) {
            //dut<k,temp->end>�����Ե�k������Ϊ��β������ѡ��һ����С��ֵ
            //����Ϊ��i���������ٷ���ʱ��
            if (vl[k] > (vl[temp->end] - temp->weight)) {
                vl[k] = vl[temp->end] - temp->weight;
            }
            temp = temp->next;
        }
    }
    int ee;
    int el;
    for (k = 0; k < this->vexnum; k++) {
        temp= temp = this->arc[k].firstarc;
        while (temp) {
            ee = ve[k];
            el = vl[temp->end] - temp->weight;
            if (ee == el) {//������ֵ��ȣ�˵����Ϊ�ؼ����
                cout << this->arc[k].data
                    << "----"
                    << this->arc[temp->end].data
                    << "="
                    << temp->weight
                    << endl;
            }
            temp = temp->next;
        }
    }
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
    graph.CriticalPath();
    system("pause");
    return 0;

}