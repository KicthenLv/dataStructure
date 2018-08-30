#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 3 //定义阶数
#define MAX_CHILDS M
#define MIN_KEYS ceil(M/2)

typedef int KeyType;

typedef struct BTNode{
	KeyType keyNum; // 定义关键字数量
	KeyType *keys; // 定义关键字数组
	struct BTNode *parent;
	struct BTNode **childs; // 定义孩子数组
	bool isLeaf; 
}BTNode,*BTree;

typedef struct {
	BTNode *pt;  //指向找到的节点
	int index; //指向关键字下标
	int tag; //查找成果或失败
}Result;
/*
	创建树
*/
void createTree(BTree &T) {//初始化根节点
	if(T == NULL){
		T = (BTree)malloc(sizeof(BTNode));
	}
	T->isLeaf = true;
	T->keyNum = 0;
	T->keys = (KeyType *)malloc((MAX_CHILDS)*sizeof(KeyType));  //申请空间
	T->childs = (BTNode **)malloc(MAX_CHILDS*sizeof(BTNode));
	//初始化
	for(int i = 0 ; i < MAX_CHILDS-1 ; i ++) {
		T->keys[i] = 0 ;
		T->childs[i] = NULL;
	}
	T->childs[MAX_CHILDS-1] = NULL;
}
//查找节点点下标
int search(BTNode *p,KeyType key){
	for(int i = 1 ; i < p->keyNum ; i++){
		if(key <= p->keys[i]) return i;
	}
	return -1;
}

/*
	查找结点，与二叉树搜索树查找类似
	查找成功返回节点和关键字下标
	或者返回空
*/

Result* searchNode(BTree T,KeyType key){
	bool found = false;
	Result *result = (Result *)malloc(sizeof(Result));
	BTNode *p = T;
	BTNode *q = NULL;
	int i = -1;
	while(p!= NULL &&!found){
		i = search(p,key);
		if(i > 0 && p->keys[i] == key) found = true;
		else {q=p;p=p->childs[i];}
	}
	if(found){
		result->index = i;
		result->pt = p;
		result->tag = 1;
	} //找到了返回该节点信息
	else {
		result->index = i;
		result->pt = q;
		result->tag = 0;
	} //未找到返回前去节点
	return result;
}
/*
	添加节点
	1.若节点未满，则直接添加
	2.若节点满了，则需进行分裂操作
*/
void insertNode(BTree &T,KeyType key){
	Result *res = searchNode(T,key);
	if(res->tag == 0){
		
	}
}
int main(void){
	BTree T = NULL;
	createTree(T);
	return 0;
}