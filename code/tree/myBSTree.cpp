/*
ʵ�ֶ���������
ʹ�õݹ�͵����ķ�ʽ����ɾ�����ҽڵ�
�����������ĳ��Ȳ����������������
��������ƽ�����ҳ���Ϊ��֧��(n+1)/2
��õ����Ϊlog2(n)������ �����۰���ҵ��ж�����ͬ
*/
#include <stdio.h>
#include <stdlib.h>

//��������������Ľṹ
typedef struct BSTNode{
	int key;
	BSTNode *lchild;
	BSTNode *rchild;
	BSTNode(){
		lchild = NULL;
		rchild = NULL;
	}
}*BSTree;
//���ҽڵ�
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
//����ڵ�
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
//��������������
bool BST_CreateTree(BSTree &T,int* keys,int len){
	for(int i = 0 ; i < len ; i++){
		BST_InsertNode(T,keys[i]);
	}
	return true;
}
bool DeleteNode(BSTree &T){
	//���������Ϊ��,��ֱ�ӽ��������滻Ϊ�ýڵ�
	if(T->lchild == NULL){
		BSTNode *r = T; 
		T = T->rchild;
		free(r);
		return true;
	}
	//����������Ϊ�� ��ֱ���滻Ϊ������
	if(T->rchild == NULL){
		BSTNode *l = T; 
		T = T->lchild;
		free(l);
		return true;
	}
	//���������������Ϊ�գ����ҵ��������нڵ�ֵ���Ľڵ��滻�ýڵ�
	BSTNode *maxNode = T->lchild; //���ֵ�ڵ�
	BSTNode *parent = T; //���ֵ�ڵ�ĸ��ڵ�
	while(maxNode->rchild != NULL) {
		parent = maxNode;
		maxNode = maxNode->rchild;
	}
	//�滻ֵ
	T->key = maxNode->key;
	//�������Ӹ��ڵ�
	if(parent != T) parent->rchild = maxNode->lchild;
	else parent->lchild = maxNode->lchild;
	//�ͷŵ����ֵ�ڵ�
	free(maxNode);
	return true;
}
//ɾ���ڵ������ʽ
bool BST_DeleteNode_Recurrence(BSTree &T , int key){
	if(T == NULL) return false;
	if(T->key == key) return DeleteNode(T);
	if(T->key > key) return BST_DeleteNode_Recurrence(T->lchild,key);
	if(T->key < key) return BST_DeleteNode_Recurrence(T->rchild,key);
}
//ɾ���ڵ����
bool BST_DeleteNode(BSTree &T , int key){
	//�����Ƿ���ڴ˽ڵ�
	if(!BST_Search(T,key)) return false;
	
	//�������ʼɾ���ڵ�
	//�ҵ��ýڵ㼫��˽ڵ��ǰ�����ߺ��
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
	//1.��ɾ���ڵ�����������������
	if(cur->lchild == NULL){
		//1.���parentΪ�գ���ɾ�����ڵ�����
		if(parent == NULL){
			//�����ڵ���Ϊ������
			T = cur->rchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//2.�����ɾ���ڵ��Ǹ��ڵ���������ڵ�
		if(parent->key > cur->key){
			//�����ڵ�����������ӵ���ɾ���ڵ����������
			parent->lchild = cur->rchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//3.�����ɾ���ڵ��Ǹ��ڵ���������ڵ�
		if(parent->key < cur->key){
			//�����ڵ�����������ӵ���ɾ���ڵ����������
			parent->rchild = cur->rchild;
			//delete cur;
			cur = NULL;
			return true;
		}
	}
	//2.��ɾ���ڵ�����������������
	if(cur->rchild == NULL){
		//1.���parentΪ�գ���ɾ�����ڵ�����
		if(parent == NULL){
			//�����ڵ���Ϊ������
			T = cur->lchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//2.�����ɾ���ڵ��Ǹ��ڵ���������ڵ�
		if(parent->key > cur->key){
			//�����ڵ�����������ӵ���ɾ���ڵ����������
			parent->lchild = cur->lchild;
			//delete cur;
			cur = NULL;
			return true;
		}
		//3.�����ɾ���ڵ��Ǹ��ڵ���������ڵ�
		if(parent->key < cur->key){
			//�����ڵ�����������ӵ���ɾ���ڵ����������
			parent->rchild = cur->lchild;
			//delete cur;
			cur = NULL;
			return true;
		}	
	}
	//3.��ɾ���ڵ����������Ҳ��������
	else{
		//ѡ����������ֵ���Ľڵ��滻���ڵ����������ֵ��С�Ľڵ�
		BSTNode *maxLeftNode = cur->lchild;
		parent = cur;
		//�ҳ���������ֵ������һ����
		while(maxLeftNode->rchild != NULL){
			parent = maxLeftNode;
			maxLeftNode = maxLeftNode->rchild;
		}
		//����ֵ������ɾ���ڵ�
		cur->key = maxLeftNode->key;
		//������ֵ�ڵ����������Ϊ�գ��ͽ����ڵ�ĸ��ڵ�����������ӵ������ֵ�ڵ��������
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
		//ɾ�����ֵ�ڵ�
		//delete maxLeftNode;
		return true;
	}
}
//������������������������һ�����������
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
