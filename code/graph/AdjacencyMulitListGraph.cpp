#include<iostream>
#include<string>
using namespace std;

//����
struct ArcNode
{
    int mark; //��־λ
    int ivex; //�������Ϣ���Ǹ����
    ArcNode * ilink; //�����ڶ���ivex����һ���ߵ���Ϣ
    int jvex;   //�������Ϣ���Ǹ��յ�
    ArcNode * jlink; //�����ڶ���jvex����һ���ߵ���Ϣ
    int weight;
};

//ͷ���
struct VexNode {
    string data;   //�������Ϣ���綥������
    ArcNode * firstedge; //��һ����������ı�
};

struct Graph {
    int vexnum;   //����ĸ���
    int edge;    //�ߵĸ���
    VexNode *node; //���涥����Ϣ
};

void createGraph(Graph & g)
{
    cout << "�����붥��ĸ�����" << endl;
    cin >> g.vexnum;
    cout << "������ߵĸ���������ͼ/��Ҫ��2����" << endl;
    cin >> g.edge;
    g.node = new VexNode[g.vexnum];

    int i;
    cout << "����ÿ���������Ϣ��" << endl;//��¼ÿ���������Ϣ
    for (i = 0; i < g.vexnum; i++)
    {
        cin >> g.node[i].data;
        g.node[i].firstedge = NULL;
    }

    cout << "������ÿ���ߵ������յ�ı�ţ�" << endl;
    for (i = 0; i < g.edge; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;

        ArcNode * next = new ArcNode;
        next->mark = 0;
        next->ivex = a - 1; //�����ǻ�ͷ���±�
        next->jvex = b - 1; //��β���±�
        next->weight = -1;
        next->ilink = NULL;
        next->jlink = NULL;

        //���¶����a-1����Ϣ
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
        //���¶����b-1
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