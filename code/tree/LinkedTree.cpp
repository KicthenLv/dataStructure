#include "stdio.h"
#include "stdlib.h"

//����ջ��ʼ��С ����������
#define INIT_STACK_SIZE 10

//�������ݹ�ϵ
typedef struct BiNode{
	char data;
	BiNode *lchild,*rchild;
}BiNode,BiTree;

//�������ݽṹ
typedef struct {
	BiNode *nodes[INIT_STACK_SIZE];//�洢��ַ
	int top;//ָ��ջ����ָ��
	int stacksize;
}Stack;

//��ʼ��ջ
void initStack(Stack *stack){
	stack->top = 0;//����ջջ��ָ��ջ��
	stack->stacksize = INIT_STACK_SIZE;//��ʼ��ջ��С
}
//��ջ�����Ԫ�� ��ջ
void push(Stack *stack,BiNode *node){
	if(stack->top >= stack->stacksize) {
		exit(-1);
	}
	stack->nodes[stack->top++] = node;
}
//����ջ��Ԫ��
BiNode *pop(Stack *stack){
	if(stack->top == 0) exit(-1);
	return stack->nodes[--stack->top];
}
//��ȡ��ջ��Ԫ��
BiNode *getTop(Stack *stack){
	if(stack->top == 0) exit(-1);
	return stack->nodes[stack->top-1];
}
//������ ��������
void createTree(BiTree *T){
	char c = getchar();
	if(c=='#'||c==' ') {
		T=NULL;
	}else{
		T = (BiNode *)malloc(sizeof(BiNode));
		T->data = c;
		createTree(T->lchild);
		createTree(T->rchild);
	}
}
//�Խڵ�Ĳ�������
void visit(BiNode *node){
	printf("%c\n",node->data);
}
//���������
void preOrderTraverse(BiTree *Tree){
	if(Tree!= NULL){
		visit(Tree);
		preOrderTraverse(Tree->lchild);
		preOrderTraverse(Tree->rchild);
	}
}
//���������
void inOrderTraverse(BiTree *Tree){
	if(Tree!= NULL){
		inOrderTraverse(Tree->lchild);
		visit(Tree);
		inOrderTraverse(Tree->rchild);
	}
}

//���������
void postOrderTraverse(BiTree *Tree){
	if(Tree!= NULL){
		postOrderTraverse(Tree->lchild);
		postOrderTraverse(Tree->rchild);
		visit(Tree);
	}
}
//��ȡ�����������
int depth(BiTree *Tree){
	int d= 0,dl= 0,dr = 0;
	if(Tree!=NULL){
		dl = depth(Tree->lchild);
		dr = depth(Tree->rchild);
		d = 1+(dl>dr?dl:dr);
	}else{
		d = 0;
	}
	return d;
}
//��ȡ�������Ľڵ���
int numNode(BiTree *Tree){
	int num = 0 , numl = 0 , numr = 0;
	if(Tree!=NULL){
		numl = numNode(Tree->lchild);
		numr = numNode(Tree->rchild);
		num = 1+numl+numr;
	}else{
		num = 0;
	}
	return num;
}
//��ȡ��������Ҷ�ӽڵ����
int leafNum(BiTree *Tree){
	if(Tree==NULL) return 0;
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
BiNode *getByData(BiTree *Tree,char data){
	BiNode *node = NULL;
	if(node!=NULL) return node;
	if(Tree== NULL){
		return NULL;
	}else{
		if(Tree->data == data) {
			node = Tree;
			return node;
		}
		if(node!=NULL) return node;
		node = getByData(Tree->lchild,data);
		if(node!=NULL) return node;
		node = getByData(Tree->rchild,data);
	}
	return node;
}
//ʹ��ջ�ķ�ʽ������� 
void preOrderTraverseByStack(Stack *stack,BiTree *Tree){
	if(Tree!=NULL){
		visit(Tree);
		preOrderTraverseByStack(stack,Tree->lchild);
		preOrderTraverseByStack(stack,Tree->rchild);
	}{
		return;
	}
}
//ʹ��ջ�ķ�ʽ������� 
void inOrderTraverseByStack(Stack *stack,BiTree *Tree){
	BiNode *node = Tree;
	push(stack,Tree);
	while(stack->top != 0){
		while(node!=NULL){
			node = node->lchild;
			push(stack,node);
		}
		node = pop(stack);
		if(node!=NULL) {
			visit(node);
			node = node->rchild;
			push(stack,node);
		}
	}
}
//ʹ��ջ�ķ�ʽ������� 
void postOrderTraverseByStack(Stack *stack,BiTree *Tree){
	BiNode *flag = NULL;
	while(Tree!=NULL || stack->top!=0){
		while(Tree!=NULL){
			push(stack,Tree);
			Tree = Tree->lchild;
		}
		Tree = pop(stack);
		if(Tree->rchild == flag || Tree->rchild ==NULL){
			visit(Tree);
			flag = Tree;
			Tree = NULL;
		}else{
			push(stack,Tree);
			Tree = Tree->rchild;
		}
	}
}
int main(void) {
	BiTree *Tree;
	int index = 0;
	//createTree(Tree);
	Tree = (BiNode *)malloc(sizeof(BiNode));
	Tree->data = 'A';
	Tree->lchild = (BiNode *)malloc(sizeof(BiNode));
	Tree->lchild->data = 'B';
	Tree->lchild->lchild = (BiNode *)malloc(sizeof(BiNode));
	Tree->lchild->lchild->data = 'D';
	Tree->lchild->lchild->lchild = NULL;
	Tree->lchild->lchild->rchild = NULL;
	Tree->lchild->rchild = NULL;
	Tree->rchild = (BiNode *)malloc(sizeof(BiNode));
	Tree->rchild->data = 'C';
	Tree->rchild->lchild = NULL;
	Tree->rchild->rchild = NULL;
/*	
	inOrderTraverse(Tree);
	printf("-------------------\n");
	postOrderTraverse(Tree);
	printf("-------------------\n");
	int dep = depth(Tree);
	printf("%d\n",dep);
	printf("-------------------\n");
	int nums = numNode(Tree);
	printf("%d\n",nums);
	printf("-------------------\n");
	int leafNums = leafNum(Tree);
	printf("%d\n",leafNums);
	printf("-------------------\n");
	BiNode *node = getByData(Tree,'B');
	printf("%c\n",node->data);
*/
	Stack *stack;
	stack = (Stack *)malloc(sizeof(Stack));
	initStack(stack);
	//��ͬ��ʽ�������
	preOrderTraverse(Tree);
	printf("-------------------\n");
	preOrderTraverseByStack(stack,Tree);
	printf("-------------------\n");
	inOrderTraverse(Tree);
	printf("-------------------\n");
	inOrderTraverseByStack(stack,Tree);
	printf("-------------------\n");
	postOrderTraverse(Tree);
	printf("-------------------\n");
	postOrderTraverseByStack(stack,Tree);
	return 0;
}