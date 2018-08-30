#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 3 //�������
#define MAX_CHILDS M
#define MIN_KEYS ceil(M/2)

typedef int KeyType;

typedef struct BTNode{
	KeyType keyNum; // ����ؼ�������
	KeyType *keys; // ����ؼ�������
	struct BTNode *parent;
	struct BTNode **childs; // ���庢������
	bool isLeaf; 
}BTNode,*BTree;

typedef struct {
	BTNode *pt;  //ָ���ҵ��Ľڵ�
	int index; //ָ��ؼ����±�
	int tag; //���ҳɹ���ʧ��
}Result;
/*
	������
*/
void createTree(BTree &T) {//��ʼ�����ڵ�
	if(T == NULL){
		T = (BTree)malloc(sizeof(BTNode));
	}
	T->isLeaf = true;
	T->keyNum = 0;
	T->keys = (KeyType *)malloc((MAX_CHILDS)*sizeof(KeyType));  //����ռ�
	T->childs = (BTNode **)malloc(MAX_CHILDS*sizeof(BTNode));
	//��ʼ��
	for(int i = 0 ; i < MAX_CHILDS-1 ; i ++) {
		T->keys[i] = 0 ;
		T->childs[i] = NULL;
	}
	T->childs[MAX_CHILDS-1] = NULL;
}
//���ҽڵ���±�
int search(BTNode *p,KeyType key){
	for(int i = 1 ; i < p->keyNum ; i++){
		if(key <= p->keys[i]) return i;
	}
	return -1;
}

/*
	���ҽ�㣬���������������������
	���ҳɹ����ؽڵ�͹ؼ����±�
	���߷��ؿ�
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
	} //�ҵ��˷��ظýڵ���Ϣ
	else {
		result->index = i;
		result->pt = q;
		result->tag = 0;
	} //δ�ҵ�����ǰȥ�ڵ�
	return result;
}
/*
	��ӽڵ�
	1.���ڵ�δ������ֱ�����
	2.���ڵ����ˣ�������з��Ѳ���
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