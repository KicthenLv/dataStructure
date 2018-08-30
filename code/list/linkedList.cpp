/**
*创建线性链表
*使用节点来取代数组地址，相对于顺序表，他的添加和删除的时间复杂度很低
*/
#include <stdio.h>
#include <stdlib.h>

//定义节点结构体
typedef struct linkNode{
	int data;
	linkNode *next;
}linkNode,* linkedList;

//初始化链表
void initList(linkedList &head){
	head = (linkedList)malloc(sizeof(linkedList)); //分配空间
	head->next = NULL;
	head->data = 0;
}
//指定合法位置添加元素
void insertElement(linkedList &list, int index , int data){
	if(!list) exit(-1);
	if(index<1 || index > list->data+1) exit(-1);
	linkedList node = (linkedList)malloc(sizeof(linkedList)); //生成新节点
	node->data = data;
	linkedList current = list ; //添加一个头节点的引用
	int i = 1;
	while(i != index){
		current = current->next;
		i++;
	}
	node->next = current->next;
	current->next = node;
	list->data ++;
}
//删除合法位置元素
void deleteElement(linkedList &list, int index){
	if(!list) exit(-1);
	if(index<1 || index > list->data) exit(-1);
	linkedList current = list ; //添加一个头节点的引用
	int i = 1;
	while(i != index){
		current = current->next;
		i++;
	}
	free(current->next);
	current->next = current->next->next;
	list->data --;
}
//获取指定位置的元素
int getElement(linkedList &list, int index){
	if(!list) exit(-1);
	if(index<1 || index > list->data) exit(-1);
	linkedList current = list ; //添加一个头节点的引用
	int i = 1;
	while(i != index){
		current = current->next;
		i++;
	}
	return current->next->data;
}
//查看链表元素
void watchList(linkedList &list){
	if(!list) exit(-1);
	linkedList current = list->next ; //添加一个头节点的引用
	while(current != NULL){
		printf("%d\n",current->data);
		current = current->next;
	}
}
//摧毁list
void destoryList(linkedList &list){
	if(!list) exit(-1);
	list = NULL;
}
//清空list
void clearList(linkedList &list){
	if(!list) exit(-1);
	destoryList(list->next);
	list->data = 0;
}
//合并list，把第一个链表的为节点连接到第二个链表的第一个节点
linkedList mergeList(linkedList &list1,linkedList &list2){
	if(!list1|| !list2) exit(-1);
	list1->data += list2->data;
	linkedList current = list1->next;
	while(current->next!=NULL){
		current = current->next;
	}
	current->next = list2->next;

	//摧毁第二个链表
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