/*二叉树的顺序表示
	使用数组来存储结点
	按完全二叉树的方式来存储结点
	使用完全二叉树的性质来获取结点
*/
#include "stdio.h"
#include "stdlib.h"

#define MAXSIZE 7

typedef struct {
	int nodes[MAXSIZE];
	int size;
}BT;
bool checkIndex(BT *bt,int index){
	if(index < 0 || index>bt->size) return false;
}
//初始化二叉树
void InitTree(BT *bt){
	bt->size = 0 ;
}
//按完全二叉树的顺序向二叉树内添加元素
void Add(BT *bt,int data){
	if(bt->size>=MAXSIZE) return;
	bt->nodes[bt->size] = data;
	bt->size ++;
}
//判断树是否为空
bool isEmpty(BT *bt){
	return bt->size==0;
}
//获取根节点
int getRoot(BT *bt){
	return bt->nodes[0] ==0?0:bt->nodes[0];
}
//获取父节点
int getParent(BT *bt,int index){
	if(!checkIndex(bt,index)) return 0;
	return bt->nodes[index/2];
}
//获取左子节点
int getLchild(BT *bt,int index){
	if(!checkIndex(bt,index)) return 0;
	if(2*index > bt->size ) return 0;
	return bt->nodes[2*index];
}
//获取右子节点
int getRchild(BT *bt, int index){
	if(!checkIndex(bt,index)) return 0;
	if(2*index +1> bt->size ) return 0;
	return bt->nodes[2*index+1];
}
//返回指定元素的位置
int indexOf(BT *bt,int data){
	if(data==0) return -1;
	for(int i=0;i<bt->size;i++) {  
		if(data==(bt->nodes[i])) {  
		   return i;  
		}  
	}  
	return -1;
}
//指定位置添加结点
void insert(BT *bt,int parent,bool isLeft,int data){
	if(bt->nodes[parent] == 0 || data ==0) return;
	if(isLeft){
		if(parent*2>MAXSIZE)return ;
		if(bt->nodes[parent*2] == 0) bt->size ++;
		bt->nodes[parent*2] = data;
	}else{
		if(parent*2+1>MAXSIZE)return ;
		if(bt->nodes[parent*2] == 0) bt->size ++;
		bt->nodes[parent*2+1] = data;
	}
}
//访问结点
void visit(BT *bt,int index){
	if(!checkIndex(bt,index)) return ;
	if(bt->nodes[index]==0) return;
	printf("%d\n",bt->nodes[index]);
}
//按完全二叉树的顺序遍历二叉树
void Traverse(BT *bt){
	for(int i=0;i<bt->size;i++) {  
		printf("%d\n",bt->nodes[i]);
	}  
}
//先序遍历二叉树
void PreOrderTraverse(BT *bt,int index){
	if(bt->size <= 0 ) return;
	if(index > bt->size) return;
	//printf("%d\n",index);
	visit(bt,index-1);
	PreOrderTraverse(bt,2*index);
	PreOrderTraverse(bt,2*index+1);
}
//中序遍历二叉树
void InOrderTraverse(BT *bt,int index){
	if(bt->size <= 0 ) return;
	if(index > bt->size) return;
	//printf("%d\n",index);
	InOrderTraverse(bt,2*index);
	visit(bt,index-1);
	InOrderTraverse(bt,2*index+1);
}
//后序遍历二叉树
void PostOrderTraverse(BT *bt,int index){
	if(bt->size <= 0 ) return;
	if(index > bt->size) return;
	//printf("%d\n",index);
	PostOrderTraverse(bt,2*index);
	PostOrderTraverse(bt,2*index+1);
	visit(bt,index-1);
}

int main(void){
	BT bt;
	InitTree(&bt);
	Add(&bt,1);
	Add(&bt,2);
	Add(&bt,3);
	Add(&bt,4);
	//visit(&bt,3);
	//Traverse(&bt);
	PreOrderTraverse(&bt,1);
	InOrderTraverse(&bt,1);
	PostOrderTraverse(&bt,1);
	return 0 ;
}
