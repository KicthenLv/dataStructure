/*
实现二叉搜索树
使用递归和迭代的方式插入删除查找节点
二叉搜索树的长度不超过二叉树的深度
最坏的情况的平均查找长度为单支树(n+1)/2
最好的情况为log2(n)成正比 ，即折半查找的判定树相同
*/
#include <stdio.h>
#include <stdlib.h>

//定义二叉搜索树的结构
typedef struct BSTNode{
	int key;
	BSTNode *lchild;
	BSTNode *rchild;
	BSTNode(){
		lchild = NULL;
		rchild = NULL;
	}
}*BSTree;
//查找节点
bool BST_Search(BSTree T, int key){
	if(T == NULL) return false;
	BSTNode *temp = T;
	while(temp != NULL){
		if(temp->key == key) return true;
		else if(temp->key >key) temp = temp->lchild;
		else temp = temp->rchild;
	}
	return false;
}
//插入节点
bool BST_InsertNode(BSTree &T,int key){
	if(T == NULL){
		BSTNode *node = new BSTNode;
		node->key = key;
		node->lchild = node->rchild = NULL;
		T = node;
		return true;
	}
	BSTNode *temp = T;
	BSTNode *node = new BSTNode;
	node->key = key;
	node->lchild = node->rchild = NULL;
	while(temp!= NULL){
		if(temp->key == key) return false;
		else if(temp->key > key && temp->lchild != NULL) temp = temp->lchild;
		else if(temp->key < key && temp->rchild != NULL) temp = temp->rchild;
		else break;
	}
	if(temp->key > key) temp->lchild = node;
	else temp->rchild = node;
	return true;
}
//构建二叉搜索树
bool BST_CreateTree(BSTree &T,int* keys,int len){
	for(int i = 0 ; i < len ; i++){
		BST_InsertNode(T,keys[i]);
	}
	return true;
}
bool DeleteNode(BSTree &T){
	//如果左子树为空,就直接将左子树替换为该节点
	if(T->lchild == NULL){
		BSTNode *r = T; 
		T = T->rchild;
		free(r);
		return true;
	}
	//若果右子树为空 则直接替换为左子树
	if(T->rchild == NULL){
		BSTNode *l = T; 
		T = T->lchild;
		free(l);
		return true;
	}
	//如果左右子树都不为空，则找到左子树中节点值最大的节点替换该节点
	BSTNode *maxNode = T->lchild; //最大值节点
	BSTNode *parent = T; //最大值节点的父节点
	while(maxNode->rchild != NULL) {
		parent = maxNode;
		maxNode = maxNode->rchild;
	}
	//替换值
	T->key = maxNode->key;
	//重新连接父节点
	if(parent != T) parent->rchild = maxNode->lchild;
	else parent->lchild = maxNode->lchild;
	//释放掉最大值节点
	free(maxNode);
	return true;
}
//删除节点迭代方式
bool BST_DeleteNode_Recurrence(BSTree &T , int key){
	if(T == NULL) return false;
	if(T->key == key) return DeleteNode(T);
	if(T->key > key) return BST_DeleteNode_Recurrence(T->lchild,key);
	if(T->key < key) return BST_DeleteNode_Recurrence(T->rchild,key);
}
//删除节点操作
bool BST_DeleteNode(BSTree &T , int key){
	//查找是否存在此节点
	if(!BST_Search(T,key)) return false;
	
	//分情况开始删除节点
	//找到该节点极其此节点的前驱或者后继
	BSTNode *cur = T;
	BSTNode *parent = NULL;
	while(cur->lchild != NULL || cur->rchild != NULL){
		if(cur->key == key) break;
		else if(cur->key > key && cur->lchild != NULL) {
			parent = cur;
			cur = cur->lchild;
		}
		else if(cur->key < key && cur->rchild != NULL){
			parent = cur;
			cur = cur->rchild;
		}
	}
	//1.被删除节点有左子树无右子树
	if(cur->lchild == NULL){
		//1.如果parent为空，即删除根节点的情况
		if(parent == NULL){
			//将根节点置为右子树
			T = cur->rchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//2.如果被删除节点是父节点的左子树节点
		if(parent->key > cur->key){
			//将父节点的左子树连接到被删除节点的右子树上
			parent->lchild = cur->rchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//3.如果被删除节点是父节点的右子树节点
		if(parent->key < cur->key){
			//将父节点的右子树连接到被删除节点的右子树上
			parent->rchild = cur->rchild;
			//delete cur;
			cur = NULL;
			return true;
		}
	}
	//2.被删除节点有右子树无左子树
	if(cur->rchild == NULL){
		//1.如果parent为空，即删除根节点的情况
		if(parent == NULL){
			//将根节点置为右子树
			T = cur->lchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//2.如果被删除节点是父节点的左子树节点
		if(parent->key > cur->key){
			//将父节点的左子树连接到被删除节点的左子树上
			parent->lchild = cur->lchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//3.如果被删除节点是父节点的右子树节点
		if(parent->key < cur->key){
			//将父节点的右子树连接到被删除节点的右子树上
			parent->rchild = cur->lchild;
			//delete cur;
			cur = NULL;
			return true;
		}	
	}
	//3.被删除节点既有左子树也有右子树
	else{
		//选出左子树中值最大的节点替换根节点或者右子树值最小的节点
		BSTNode *maxLeftNode = cur->lchild;
		parent = cur;
		//找出左子树中值最大的哪一个点
		while(maxLeftNode->rchild != NULL){
			parent = maxLeftNode;
			maxLeftNode = maxLeftNode->rchild;
		}
		//将其值付给被删除节点
		cur->key = maxLeftNode->key;
		//如果最大值节点的左子树不为空，就讲最大节点的父节点的右子树连接到到最大值节点的左子树
		if(maxLeftNode->lchild == NULL && maxLeftNode->rchild == NULL){
			if(parent->lchild->key == maxLeftNode->key) parent->lchild = NULL;
			else parent->rchild = NULL;
		}
		if(maxLeftNode->lchild != NULL){
			if(parent->rchild->key == maxLeftNode->key)
				parent->rchild = maxLeftNode->lchild;
			else 
				parent->lchild = maxLeftNode->lchild;
			maxLeftNode = NULL;
		}
		//删除最大值节点
		//delete maxLeftNode;
		return true;
	}
}
//中序遍历二叉搜索树，结果是一个有序的序列
void InOrderTraversal(BSTree T){
	if(T == NULL) return;
	if(T->lchild!= NULL) InOrderTraversal(T->lchild);
	printf("%d ",T->key);
	if(T->rchild!= NULL) InOrderTraversal(T->rchild);

}
int main(void){
	BSTree Tree = NULL;
	//BST_InsertNode(Tree,1);
	int keys[] = {6,3,1,0,2,5,4,8,7,9,20};
	BST_CreateTree(Tree,keys,10);
	InOrderTraversal(Tree);
	printf("\n");
	//if(BST_Search(Tree,20)) printf("hah\n");
	BST_InsertNode(Tree,20);
//	BST_DeleteNode(Tree,6);
	BST_DeleteNode_Recurrence(Tree,9);
	BST_Search(Tree,8);
	InOrderTraversal(Tree);
	printf("\n");
	return 0;
}
