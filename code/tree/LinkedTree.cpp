#include "stdio.h"
#include "stdlib.h"

//定义栈初始大小 用来遍历树
#define INIT_STACK_SIZE 10

//定义数据关系
typedef struct BiNode{
	char data;
	BiNode *lchild,*rchild;
}BiNode,BiTree;

//定义数据结构
typedef struct {
	BiNode *nodes[INIT_STACK_SIZE];//存储基址
	int top;//指向栈顶的指针
	int stacksize;
}Stack;

//初始化栈
void initStack(Stack *stack){
	stack->top = 0;//将空栈栈顶指向栈底
	stack->stacksize = INIT_STACK_SIZE;//初始化栈大小
}
//向栈内添加元素 入栈
void push(Stack *stack,BiNode *node){
	if(stack->top >= stack->stacksize) {
		exit(-1);
	}
	stack->nodes[stack->top++] = node;
}
//弹出栈顶元素
BiNode *pop(Stack *stack){
	if(stack->top == 0) exit(-1);
	return stack->nodes[--stack->top];
}
//获取到栈顶元素
BiNode *getTop(Stack *stack){
	if(stack->top == 0) exit(-1);
	return stack->nodes[stack->top-1];
}
//创建树 存在问题
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
//对节点的操作方法
void visit(BiNode *node){
	printf("%c\n",node->data);
}
//先序遍历树
void preOrderTraverse(BiTree *Tree){
	if(Tree!= NULL){
		visit(Tree);
		preOrderTraverse(Tree->lchild);
		preOrderTraverse(Tree->rchild);
	}
}
//中序遍历树
void inOrderTraverse(BiTree *Tree){
	if(Tree!= NULL){
		inOrderTraverse(Tree->lchild);
		visit(Tree);
		inOrderTraverse(Tree->rchild);
	}
}

//后序遍历树
void postOrderTraverse(BiTree *Tree){
	if(Tree!= NULL){
		postOrderTraverse(Tree->lchild);
		postOrderTraverse(Tree->rchild);
		visit(Tree);
	}
}
//获取二叉树的深度
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
//获取二叉树的节点数
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
//获取二叉树的叶子节点个数
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
//使用中序返回某元素的节点
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
//使用栈的方式先序遍历 
void preOrderTraverseByStack(Stack *stack,BiTree *Tree){
	if(Tree!=NULL){
		visit(Tree);
		preOrderTraverseByStack(stack,Tree->lchild);
		preOrderTraverseByStack(stack,Tree->rchild);
	}{
		return;
	}
}
//使用栈的方式中序遍历 
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
//使用栈的方式后序遍历 
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
	//不同方式先序遍历
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