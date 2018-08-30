#include "stdio.h"
#include "stdlib.h"
/*
	���������� 
	ͨ�����ö���������Ľڵ����Զ�����������������ÿ�ζ����б������������������Ч��
	Ϊ�ڵ�������ұ�־��,ltag,rtag ����Ϊ1���ʾ���Һ�����ָ����ǰ�����̽ڵ㣬Ϊ0 ���ʾ���Һ���ָ��ָ�����Һ��ӽڵ�
*/

typedef enum {Link, Thread} PointerTag;

//�������ݹ�ϵ
typedef struct BiNode{
	char data;
	BiNode *lchild,*rchild;
	int ltag,rtag;//�������Һ���ָ��ı�־��
}BiNode,*BiTree;

BiTree pre;

//������ ��������
void createTree(BiTree T){
	char c = getchar();
	if(c=='#'||c==' ') {
		T=NULL;
	}else{
		T = (BiTree)malloc(sizeof(BiTree));
		T->data = c;
		T->ltag = Link;
		T->rtag = Link;
		createTree(T->lchild);
		createTree(T->rchild);
	}
}
//ʹ��Ӳ���뷽ʽ�������������������
void createTree1(BiTree Tree){
	Tree->data = 'A';
	Tree->ltag = Link;
	Tree->rtag = Link;
	Tree->lchild = (BiNode *)malloc(sizeof(BiNode));
	Tree->lchild->data = 'B';
	Tree->lchild->ltag = Link;
	Tree->lchild->rtag = Link;
	Tree->lchild->lchild = (BiNode *)malloc(sizeof(BiNode));
	Tree->lchild->lchild->data = 'D';
	Tree->lchild->lchild->ltag = Link;
	Tree->lchild->lchild->rtag = Link;
	Tree->lchild->lchild->lchild = NULL;
	Tree->lchild->lchild->rchild = NULL;
	Tree->lchild->rchild = NULL;
	Tree->rchild = (BiNode *)malloc(sizeof(BiNode));
	Tree->rchild->data = 'C';
	Tree->rchild->ltag = Link;
	Tree->rchild->rtag = Link;
	Tree->rchild->lchild = NULL;
	Tree->rchild->rchild = NULL;
}
//�Խڵ�Ĳ�������
void visit(BiNode *node){
	printf("%c\n",node->data);
}
//���������
void preOrderTraverse(BiTree Tree){
	if(Tree){
		visit(Tree);
		preOrderTraverse(Tree->lchild);
		preOrderTraverse(Tree->rchild);
	}
    return;
}

void in_order_threading(BiTree T)
{
    if(T)
    {
      in_order_threading(T->lchild); 			//����������
      if(!T->lchild) 							//�������Ϊ�գ�����ָ��ֱ��ǰ��
	  {
         T->lchild=pre;
         T->ltag=Thread;
	  }
      if(!pre->rchild) 							//�����һ�������Һ���Ϊ�գ�����ָ��ֱ�Ӻ�̡���ע�⣺ֻ�з��ʵ���һ�����ʱ���Ż�֪�������ĺ����˭��
	  {
         pre->rchild=T;
         pre->rtag=Thread;
	  }
      pre=T;
      in_order_threading(T->rchild); 			//�Һ���������
    }
	else return;
}
 
/*
����һ��ͷ��㣬ʹ������������һ����ջ�
P������ͷ���Ķ�������ͷ��������ָ�������T���Һ���ָ��T���е����һ��Ҷ�ӽ��
T��������ͷ���Ķ�������
*/
void in_thread(BiTree P,BiTree T)
{
  P->ltag=Link;
  P->rtag=Thread;
  P->rchild=P;
  if(!T) 										//���������Ϊ�գ���P�ĺ���ָ���Լ���
    {
      P->lchild=P;
    }
  else
    {
      P->lchild=T;
      pre=P;
      in_order_threading(T); 					//�Զ���������������
      P->rchild=pre; 						//��ͷ����Һ���ָ�����һ��Ҷ�ӽ��
      pre->rtag=Thread; 						//�����һ��Ҷ�ӽ����Һ���ָ��ͷ��㡣�����������γ��ˡ�
      pre->rchild=P;
    }
}
//��������������������
void inOrderTraverse_Thr(BiTree Thrt){

	BiTree index = Thrt->lchild;
	while(index->lchild&&index->ltag!=Thread){index = index->lchild;}
	while(index!=Thrt){
		visit(index);
		index = index->rchild;
	}
}
//���������
void inOrderTraverse(BiTree Tree){
	if(Tree){
		inOrderTraverse(Tree->lchild);
		visit(Tree);
		inOrderTraverse(Tree->rchild);
	}
	return;
}

//���������
void postOrderTraverse(BiTree Tree){
	if(Tree){
		postOrderTraverse(Tree->lchild);
		postOrderTraverse(Tree->rchild);
		visit(Tree);
	}
	return;
}
//��ȡ�����������
int depth(BiTree Tree){
	int d= 0,dl= 0,dr = 0;
	if(Tree){
		dl = depth(Tree->lchild);
		dr = depth(Tree->rchild);
		d = 1+(dl>dr?dl:dr);
	}else{
		d = 0;
	}
	return d;
}
//��ȡ�������Ľڵ���
int numNode(BiTree Tree){
	int num = 0 , numl = 0 , numr = 0;
	if(Tree){
		numl = numNode(Tree->lchild);
		numr = numNode(Tree->rchild);
		num = 1+numl+numr;
	}else{
		num = 0;
	}
	return num;
}
//��ȡ��������Ҷ�ӽڵ����
int leafNum(BiTree Tree){
	if(!Tree) return 0;
	int lleafNumr = 0 , rleafNum = 0,leafnum = 0;
	if(Tree->lchild==NULL && Tree->rchild==NULL){
		return 1;
	}else{
		lleafNumr = leafNum(Tree->lchild);
		rleafNum = leafNum(Tree->rchild);
		leafnum = lleafNumr+rleafNum;
	}
	return leafnum;
}
//ʹ�����򷵻�ĳԪ�صĽڵ�
BiNode *getByData(BiTree Tree,char data){
	BiTree node = NULL;
	if(node) return node;
	if(!Tree){
		return NULL;
	}else{
		if(Tree->data == data) {
			node = Tree;
			return node;
		}
		if(node) return node;
		node = getByData(Tree->lchild,data);
		if(node) return node;
		node = getByData(Tree->rchild,data);
	}
	return node;
}

int main(void) {
    printf("------------------------\n");
	BiTree Tree;
	Tree = (BiTree)malloc(sizeof(BiTree));
	createTree1(Tree); 
	postOrderTraverse(Tree);
	printf("------------------------\n");
	BiTree Thr = (BiTree)malloc(sizeof(BiTree)); 		//�����¼����ͷ���
    in_thread(Thr,Tree);
	inOrderTraverse_Thr(Thr);
	return 0;
}