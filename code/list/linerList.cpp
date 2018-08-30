//创建顺序链表
/**
*顺序表随机查询或者修改的时间复杂度很低，但是删除和添加的时间复杂度很高最好的时候为0，最差的时候为n
*针对这种随机查询或者修改很少的情况，可以使用线性链表来实现链表
*
*/
#include <stdio.h>
#include <stdlib.h>

//定义存储基址和链表大小
#define LIST_INIT_SIZE 5
#define LISTINCREMENT 3

//定义链表关系结构
typedef struct{
	int *elem; //定义存储基址，并且存的是int类型的数据
	int length; //定义链表元素长度
	int listSize; //定义链表大小  
} myList;
//初始化链表 
void initList(myList *list){
	list->elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int)); //分配存储空间 
	if(!list->elem) exit(-1);  //如果失败
	list->length = 0 ; 
	list->listSize =  LIST_INIT_SIZE;
} 
//清空链表
void clearList(myList *list){
	int i;
	for(i = 0 ; i <list->length ; i++){  
		list->elem[i] = 0;
	}
	list->length = 0;
}
//销毁链表
void destoryList(myList *list){
	list->elem = NULL;
	list->length= 0;
	list->listSize = 0;
} 
//向链表指定位置添加元素 
void insertElement(myList *list,int index,int data){
	if(index < 1 || index > list->length + 1 ) exit(-1); //位置错误退出程序 
	if(list->length == list->listSize){ //链表空间不足 重新分配空间 
		int *newBase = (int *)realloc(list->elem,(list->listSize+LISTINCREMENT)*sizeof(int));
		if(!newBase) exit(-1);
		list->elem = newBase;
		list->listSize += LISTINCREMENT;
	}
	//后移元素
	int i;
	for(i = list->length ; i >= index; i--){
		list->elem[i] = list->elem[i-1];
	}
	list->elem[index-1] = data;
	list->length++;
} 
//删除指定位置的元素
void deleteElement(myList *list, int index){
	int i;
	// 前移元素
	for(i = index-1 ; i < list->length; i++){
		list->elem[i] = list->elem[i+1];
	}
	list->length --;
} 
//判断链表是否为空
bool isEmpty(myList *list){
	if(list->length==0) return true;
	return false;
}
//定位元素位置
int locateElement(myList *list,int data){
	if(list->elem == NULL) return -1;
	for(int i = 0 ; i < list->length ; i++){
		if(list->elem[i]==data) return i+1;
	}
	return -1;
}
//合并两个链表
myList mergeList(myList *list1,myList *list2){
	myList list = *list1;
	if(list.listSize < list1->length+list2->length){
		int *newBase = (int *)realloc(list.elem,(list1->length+list2->length)*sizeof(int));
		if(!newBase) exit(-1);
		list.elem = newBase;
		list.listSize = list1->length+list2->length;
	}
	for(int i = 0 ;i < list2->length ;i++ ){
		insertElement(&list,list.length+1,list2->elem[i]);
	}
	return list;
}
int main(void){
	myList list1,list2;
	initList(&list1);
	initList(&list2);
	insertElement(&list1,1,1);
	insertElement(&list1,2,2);
	insertElement(&list1,3,1);
	insertElement(&list1,4,2);
	insertElement(&list2,1,1);
	insertElement(&list2,2,2);
	insertElement(&list2,3,10);
	//deleteElement(&list1,1);
	//clearList(&list1);
	//printf("%d\n",list1.elem[0]);
	//int index = locateElement(&list1,2);
	//printf("%d\n",index);
	myList list3 = mergeList(&list1,&list2);
	printf("%d\n",list3.length);
	printf("%d\n",list3.listSize);
	for(int i = 0 ; i < list3.length ; i++) printf("%d\n",list3.elem[i]);
	return 0;
}
