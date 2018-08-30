#include<iostream>
#include<string>
using namespace std;

class Graph_DG {
private:
    int vexnum;   //ͼ�Ķ������
    int edge;     //ͼ�ı���
    int **arc;   //�ڽӾ���
    int ** dis;   //��¼�����������·������Ϣ
    int ** path;  //��¼�������·������Ϣ
public:
    //���캯��
    Graph_DG(int vexnum, int edge);
    //��������
    ~Graph_DG();
    // �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
    //�����1��ʼ���
    bool check_edge_value(int start, int end, int weight);
    //����ͼ
    void createGraph(int);
    //��ӡ�ڽӾ���
    void print();
    //�����·��
    void Floyd();
    //��ӡ���·��
    void print_path();
};
//���캯��
Graph_DG::Graph_DG(int vexnum, int edge) {
    //��ʼ���������ͱ���
    this->vexnum = vexnum;
    this->edge = edge;
    //Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
    arc = new int*[this->vexnum];
    dis = new int*[this->vexnum];
    path = new int*[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new int[this->vexnum];
        dis[i] = new int[this->vexnum];
        path[i] = new int[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //�ڽӾ����ʼ��Ϊ�����
            arc[i][k] = INT_MAX;
        }
    }
}
//��������
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

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph(int kind) {
    cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
    int start;
    int end;
    int weight;
    int count = 0;
    while (count != this->edge) {
        cin >> start >> end >> weight;
        //�����жϱߵ���Ϣ�Ƿ�Ϸ�
        while (!this->check_edge_value(start, end, weight)) {
            cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
            cin >> start >> end >> weight;
        }
        //���ڽӾ����Ӧ�ϵĵ㸳ֵ
        arc[start - 1][end - 1] = weight;
        //����ͼ��������д���
        if(kind==2)
        arc[end - 1][start - 1] = weight;
        ++count;
    }
}

void Graph_DG::print() {
    cout << "ͼ���ڽӾ���Ϊ��" << endl;
    int count_row = 0; //��ӡ�еı�ǩ
    int count_col = 0; //��ӡ�еı�ǩ
                       //��ʼ��ӡ
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout << "��" << " ";
            else
                cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::Floyd() {
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dist[i][j] = gra[i][j], pre[i][j] = j;  //��ʼ��
		for(int k = 1; k <= n; k++) {   //���Ծ��� k �����ÿ�Զ���֮��ľ�����и���
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
    cout << "��������Ե����·����" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = 0; row < this->vexnum; row++) {
        for (col = row + 1; col < this->vexnum; col++) {
            cout << "v" << row+1 << "---" << "v" << col+1 << " weight: "
                << this->dis[row][col] << " path: " << " v" << row + 1;
            temp = path[row][col];
            //ѭ�����;����ÿ��·����
            while (temp != col) {
                cout << "-->" << "v" << temp + 1;
                temp = path[temp][col];
            }
            cout << "-->" << "v" << col + 1 << endl;
        }

        cout << endl;
    }
}
//������������Ͷ�������ֵ�Ƿ���Ч�������Լ�����Ϊɶ��
//�������ͱ����Ĺ�ϵ�ǣ�((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 ||  edge > Vexnum*(Vexnum-1))
        return false;
    return true;
}
int main() {
    int vexnum; int edge;
    cout << "����ͼ�����ࣺ1��������ͼ��2��������ͼ" << endl;
    int kind;
    cin >> kind;
    //�ж������kind�Ƿ�Ϸ�
    while (1) {
        if (kind == 1 || kind == 2) {
            break;
        }
        else {
            cout << "�����ͼ�������Ų��Ϸ������������룺1��������ͼ��2��������ͼ" << endl;
            cin >> kind;
        }
    }

    cout << "����ͼ�Ķ�������ͱߵ�������" << endl;
    cin >> vexnum >> edge;
    while (!check(vexnum, edge)) {
        cout << "�������ֵ���Ϸ�������������" << endl;
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