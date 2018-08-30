
#include <iostream>
using namespace std;
 
/*BST�Ľ��*/
typedef struct node
{
    int key;
    struct node *lChild, *rChild;
}Node, *BST;

//��ѯԪ��
Node *Search_BST(BST &T,int key){
	if(T==NULL) return NULL;
	Node *temp = T;
	while(temp){
		if(temp->key == key) return temp;
		if(temp->key > key) temp = temp->lChild;
		else temp = temp->rChild;
	}
	return NULL;
}

/*�ڸ�����BST�в����㣬��������Ϊelement, ʹ֮��Ϊ�µ�BST*/
bool BSTInsert(BST &p, int element)
{
    if(NULL == p) // ����
    {
        p = new Node;
        p->key = element;
        p->lChild = p->rChild = NULL;
        return true;
    }
 
    if(element == p->key) // BST�в�������ȵ�ֵ,��ע�͵������ε���ͬ����
        return false;
	
    if(element < p->key)  // �ݹ�
        return BSTInsert(p->lChild, element);
    else
        return BSTInsert(p->rChild, element);
}
//�ҵ���ɾ���ڵ��ǰ�����ߺ��
Node *findParent(BST T,int key){
	if(T==NULL) return NULL;
	Node *temp = T;
	Node *res;
	while(temp){
		if(temp->key == key) return res;
		res = temp;
		if(temp->key > key) temp = temp->lChild;
		else temp = temp->rChild;
	}
	return NULL;
}
 
//ɾ���ڵ�
bool DeleteNode(BST &T,int key){
	if(T ==NULL) return false;
	Node *del = Search_BST(T,key);
	
	if(del == NULL) return false;
	Node* temp;
	Node *parent = findParent(T,key);
	if(del->lChild==NULL && del->rChild ==NULL)
		//parent->
		del = NULL;
	else if(del->lChild ==NULL){
		if(parent == NULL) T = T->rChild;
		else{
			parent->lChild = del->rChild;
			del =NULL;
		}
		return true;
	}
	else if(del->rChild ==NULL){
		if(parent == NULL) T = T->lChild;
		else{
			parent->rChild = del->lChild;
			del =NULL;
		}
		return true;
	}
	else{
		temp= del->lChild;
		while(temp->rChild!=NULL){
			temp = temp->rChild;
		}
		del->key = temp->key;
		temp = NULL;
		return true;
	}
	return true;
}
 
/*�������*/
void preOrderTraverse(BST T)
{
    if(T)
    {
        cout << T->key << " ";
        preOrderTraverse(T->lChild);
        preOrderTraverse(T->rChild);
    }
}
 
/*�������*/
void inOrderTraverse(BST T)
{
    if(T)
    {
        inOrderTraverse(T->lChild);
        cout << T->key << " ";
        inOrderTraverse(T->rChild);
    }
}
/*�������*/
void postOrderTraverse(BST T)
{
    if(T)
    {
        inOrderTraverse(T->lChild);
        inOrderTraverse(T->rChild);
        cout << T->key << " ";
    }
}
int main()
{
    int a[13] = {4, 5, 2, 1, 0, 9, 3, 7, 6, 8,5,4,7};
    int n = 13;
    BST T;
    T = NULL;
    int i;
    for(i = 0; i < n; i++)
    {
        BSTInsert(T, a[i]);
    }
	inOrderTraverse(T);
	cout << endl;
	Node *res = Search_BST(T,9);
	printf("%d\n",res->key);
	DeleteNode(T,7);
	inOrderTraverse(T);
	cout << endl;
    return 0;
}