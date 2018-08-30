#include "stdio.h"
#include "stdlib.h"
/*
	线索二叉树 
	通过利用二叉树多余的节点来对二叉树线索化，避免每次都进行遍历二叉树操作，提高效率
	为节点添加左右标志域,ltag,rtag ，若为1则表示左右孩子域指向其前驱或后继节点，为0 则表示左右孩子指针指向左右孩子节点
*/

typedef enum {Link, Thread} PointerTag;

//定义数据关系
typedef struct BiNode{
	char data;
	BiNode *lchild,*rchild;
	int ltag,rtag;//定义左右孩子指针的标志量
}BiNode,*BiTree;

BiTree pre;

//创建树 存在问题
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
//使用硬编码方式创建二叉树，方便测试
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
//对节点的操作方法
void visit(BiNode *node){
	printf("%c\n",node->data);
}
//先序遍历树
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
      in_order_threading(T->lchild); 			//左孩子线索化
      if(!T->lchild) 							//如果左孩子为空，则将其指向直接前驱
	  {
         T->lchild=pre;
         T->ltag=Thread;
	  }
      if(!pre->rchild) 							//如果上一个结点的右孩子为空，则将其指向直接后继。（注意：只有访问到下一个结点时，才会知道本结点的后继是谁）
	  {
         pre->rchild=T;
         pre->rtag=Thread;
	  }
      pre=T;
      in_order_threading(T->rchild); 			//右孩子线索化
    }
	else return;
}
 
/*
加入一个头结点，使二叉线索树成一个封闭环
P：带有头结点的二叉树。头结点的左孩子指向二叉树T；右孩子指向T树中的最后一个叶子结点
T：不带有头结点的二叉树。
*/
void in_thread(BiTree P,BiTree T)
{
  P->ltag=Link;
  P->rtag=Thread;
  P->rchild=P;
  if(!T) 										//如果二叉树为空，则P的孩子指向自己。
    {
      P->lchild=P;
    }
  else
    {
      P->lchild=T;
      pre=P;
      in_order_threading(T); 					//对二叉树进行线索化
      P->rchild=pre; 						//将头结点右孩子指向最后一个叶子结点
      pre->rtag=Thread; 						//将最后一个叶子结点的右孩子指向头结点。这样，环就形成了。
      pre->rchild=P;
    }
}
//中序线索化遍历二叉树
void inOrderTraverse_Thr(BiTree Thrt){

	BiTree index = Thrt->lchild;
	while(index->lchild&&index->ltag!=Thread){index = index->lchild;}
	while(index!=Thrt){
		visit(index);
		index = index->rchild;
	}
}
//中序遍历树
void inOrderTraverse(BiTree Tree){
	if(Tree){
		inOrderTraverse(Tree->lchild);
		visit(Tree);
		inOrderTraverse(Tree->rchild);
	}
	return;
}

//后序遍历树
void postOrderTraverse(BiTree Tree){
	if(Tree){
		postOrderTraverse(Tree->lchild);
		postOrderTraverse(Tree->rchild);
		visit(Tree);
	}
	return;
}
//获取二叉树的深度
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
//获取二叉树的节点数
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
//获取二叉树的叶子节点个数
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
//使用中序返回某元素的节点
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
	BiTree Thr = (BiTree)malloc(sizeof(BiTree)); 		//构造新加入的头结点
    in_thread(Thr,Tree);
	inOrderTraverse_Thr(Thr);
	return 0;
}