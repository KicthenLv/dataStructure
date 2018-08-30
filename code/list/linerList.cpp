//����˳������
/**
*˳��������ѯ�����޸ĵ�ʱ�临�ӶȺܵͣ�����ɾ������ӵ�ʱ�临�ӶȺܸ���õ�ʱ��Ϊ0������ʱ��Ϊn
*������������ѯ�����޸ĺ��ٵ����������ʹ������������ʵ������
*
*/
#include <stdio.h>
#include <stdlib.h>

//����洢��ַ�������С
#define LIST_INIT_SIZE 5
#define LISTINCREMENT 3

//���������ϵ�ṹ
typedef struct{
	int *elem; //����洢��ַ�����Ҵ����int���͵�����
	int length; //��������Ԫ�س���
	int listSize; //���������С  
} myList;
//��ʼ������ 
void initList(myList *list){
	list->elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int)); //����洢�ռ� 
	if(!list->elem) exit(-1);  //���ʧ��
	list->length = 0 ; 
	list->listSize =  LIST_INIT_SIZE;
} 
//�������
void clearList(myList *list){
	int i;
	for(i = 0 ; i <list->length ; i++){  
		list->elem[i] = 0;
	}
	list->length = 0;
}
//��������
void destoryList(myList *list){
	list->elem = NULL;
	list->length= 0;
	list->listSize = 0;
} 
//������ָ��λ�����Ԫ�� 
void insertElement(myList *list,int index,int data){
	if(index < 1 || index > list->length + 1 ) exit(-1); //λ�ô����˳����� 
	if(list->length == list->listSize){ //����ռ䲻�� ���·���ռ� 
		int *newBase = (int *)realloc(list->elem,(list->listSize+LISTINCREMENT)*sizeof(int));
		if(!newBase) exit(-1);
		list->elem = newBase;
		list->listSize += LISTINCREMENT;
	}
	//����Ԫ��
	int i;
	for(i = list->length ; i >= index; i--){
		list->elem[i] = list->elem[i-1];
	}
	list->elem[index-1] = data;
	list->length++;
} 
//ɾ��ָ��λ�õ�Ԫ��
void deleteElement(myList *list, int index){
	int i;
	// ǰ��Ԫ��
	for(i = index-1 ; i < list->length; i++){
		list->elem[i] = list->elem[i+1];
	}
	list->length --;
} 
//�ж������Ƿ�Ϊ��
bool isEmpty(myList *list){
	if(list->length==0) return true;
	return false;
}
//��λԪ��λ��
int locateElement(myList *list,int data){
	if(list->elem == NULL) return -1;
	for(int i = 0 ; i < list->length ; i++){
		if(list->elem[i]==data) return i+1;
	}
	return -1;
}
//�ϲ���������
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
