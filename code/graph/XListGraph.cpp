#include<iostream>
#include<string>
using namespace std;

typedef string Vertextype;
//����ṹ
struct ArcNode {
    int tailvex;   //��β���±꣬һ�㶼�ǺͶ�Ӧ��ͷ����±���ͬ
    int headvex;   //��ͷ���±�
    ArcNode * hlink; //ָ����һ����ͷͬΪheadvex�ı��� �����Ǽ�ͷ���Ǳ�
    ArcNode * tlink;  //ָ����һ����βΪtailvex�ı���,�߲��Ǽ�ͷ���Ǳ�
    int weight;  //ֻ�����Ż����������

};

//ͷ���
struct Vnode
{
    Vertextype data;  //����Ǽ�¼ÿ���������Ϣ������һ�㶼����Ҫ��ôʹ�ã�
    ArcNode *firstin; //ָ���һ������ȣ��ڸö���ı���
    ArcNode *firstout; //ָ���һ�������ȣ��ڸö���ı���
};

struct Graph
{
    int kind;  //ͼ������(����ͼ��0����������1)
    int vexnum; //ͼ�Ķ�����
    int edge;  //ͼ�ı���
    Vnode * node; //ͼ�ģ����㣩ͷ�������
};

void createGraph(Graph & g,int kind)
{
    cout << "�����붥��ĸ�����" << endl;
    cin >> g.vexnum;
    cout << "������ߵĸ���������ͼ/��Ҫ��2����" << endl;
    cin >> g.edge;
    g.kind = kind; //����ͼ������
    g.node = new Vnode[g.vexnum];
    int i;
    cout << "����ÿ���������Ϣ��" << endl;//��¼ÿ���������Ϣ
    for (i = 0; i < g.vexnum; i++)
    {
        cin >> g.node[i].data;
        g.node[i].firstin = NULL;
        g.node[i].firstout = NULL;
    }

    cout << "������ÿ���ߵ������յ�ı�ţ�" << endl;
    for (i = 0; i < g.edge; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;

        ArcNode * next = new ArcNode;
        next->tailvex = a - 1; //�����ǻ�ͷ���±�
        next-> headvex = b - 1; //��β���±�
        //ֻ����ͼ��ҪȨ����Ϣ
        if(kind==0)
        next->weight = -1;
        else
        {
            cout << "����ñߵ�Ȩ�أ�" << endl;
            cin >> next->weight;
        }
        next->tlink = NULL;
        next->hlink = NULL;
        //��λ�õĶ���ĳ��Ȼ�Ϊ��ʱ��ֱ������fisrstoutָ��ָ���µı���
        //��¼�ĳ�����Ϣ
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
        //��¼ĳ������������Ϣ
        if (g.node[b - 1].firstin == NULL)
        {
            g.node[b - 1].firstin = next;
        }
        else {
            ArcNode * now;
            now = g.node[b - 1].firstin;
            while (now->hlink)//�ҵ����һ������
            {
                now = now->hlink;
            }
            now->hlink = next;//�������һ������
        }
    }
}

void print(Graph g)
{
    int i;
    cout << "��������ĳ�����Ϣ" << endl;
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

    cout << "��������������Ϣ" << endl;

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
    cout << "����ͼ������" << endl;
    createGraph(g, 0);
    print(g);
    cout << endl;
    return 0;
}