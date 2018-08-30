/**
*������������
*ʹ�ýڵ���ȡ�������ַ�������˳���������Ӻ�ɾ����ʱ�临�ӶȺܵ�
*/
#include <stdio.h>
#include <stdlib.h>

//����ڵ�ṹ��
typedef struct linkNode{
	int data;
	linkNode *next;
}linkNode,* linkedList;

//��ʼ������
void initList(linkedList &head){
	head = (linkedList)malloc(sizeof(linkedList)); //����ռ�
	head->next = NULL;
	head->data = 0;
}
//ָ���Ϸ�λ�����Ԫ��
void insertElement(linkedList &list, int index , int data){
	if(!list) exit(-1);
	if(index<1 || index > list->data+1) exit(-1);
	linkedList node = (linkedList)malloc(sizeof(linkedList)); //�����½ڵ�
	node->data = data;
	linkedList current = list ; //���һ��ͷ�ڵ������
	int i = 1;
	while(i != index){
		current = current->next;
		i++;
	}
	node->next = current->next;
	current->next = node;
	list->data ++;
}
//ɾ���Ϸ�λ��Ԫ��
void deleteElement(linkedList &list, int index){
	if(!list) exit(-1);
	if(index<1 || index > list->data) exit(-1);
	linkedList current = list ; //���һ��ͷ�ڵ������
	int i = 1;
	while(i != index){
		current = current->next;
		i++;
	}
	free(current->next);
	current->next = current->next->next;
	list->data --;
}
//��ȡָ��λ�õ�Ԫ��
int getElement(linkedList &list, int index){
	if(!list) exit(-1);
	if(index<1 || index > list->data) exit(-1);
	linkedList current = list ; //���һ��ͷ�ڵ������
	int i = 1;
	while(i != index){
		current = current->next;
		i++;
	}
	return current->next->data;
}
//�鿴����Ԫ��
void watchList(linkedList &list){
	if(!list) exit(-1);
	linkedList current = list->next ; //���һ��ͷ�ڵ������
	while(current != NULL){
		printf("%d\n",current->data);
		current = current->next;
	}
}
//�ݻ�list
void destoryList(linkedList &list){
	if(!list) exit(-1);
	list = NULL;
}
//���list
void clearList(linkedList &list){
	if(!list) exit(-1);
	destoryList(list->next);
	list->data = 0;
}
//�ϲ�list���ѵ�һ�������Ϊ�ڵ����ӵ��ڶ�������ĵ�һ���ڵ�
linkedList mergeList(linkedList &list1,linkedList &list2){
	if(!list1|| !list2) exit(-1);
	list1->data += list2->data;
	linkedList current = list1->next;
	while(current->next!=NULL){
		current = current->next;
	}
	current->next = list2->next;

	//�ݻٵڶ�������
	destoryList(list2);
	return list1;
}
int main(void){
	linkedList list1;
	initList(list1);
	linkedList list2;
	initList(list2);
	insertElement(list1,1,1);
	insertElement(list1,1,2);
	insertElement(list1,1,3);
	insertElement(list1,1,4);
	insertElement(list2,1,5);
	insertElement(list2,1,6);
	insertElement(list2,1,7);
	insertElement(list2,1,8);
	//deleteElement(list1,1);
	//int ele = getElement(list1,2);
	//printf("%d\n",ele);
	//watchList(list1);
	list1 = mergeList(list1,list2);
	watchList(list1);
	return 0;
}