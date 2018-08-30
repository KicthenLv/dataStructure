//������̬����
//ʹ������洢���ݺͱ�������洢����
#include <stdio.h>
#include <stdlib.h>

//������������С
#define INIT_LIST_SIZE 10

//��������ڵ�
typedef struct{
	int data;
	int cur;
}Node;
//��������
typedef struct{
	Node *node; //����洢����
	int length; //���峤��
}List;

//��ʼ������ ��ÿһ���ڵ��������Ϊ���λ��
void initList(List &list){
	list.node = (Node *)malloc(INIT_LIST_SIZE*sizeof(Node));
	for(int i =0 ;i<INIT_LIST_SIZE ; i++)
		list.node[i].cur = i +1 ;
	list.node[INIT_LIST_SIZE-1].cur = 0;
	list.node[0].data = 1;
	list.length = 0;
}
//ģ������ռ䷽��
int _malloc(List &list){
	//��ȡͷ�ڵ������
	int i = list.node[0].cur;
	if(i > INIT_LIST_SIZE) exit(-1);
	if(i) list.node[0].cur = list.node[i].cur ;
	return i;
}
//ģ���ͷŽڵ�ռ�
void _free(List &list,int index){
	if(index<1 || index > INIT_LIST_SIZE) exit(-1);
	list.node[index].cur = list.node[0].cur;
	list.node[0].cur = index;
}
//�������
void addData(List &list,int data){
	if(list.length > INIT_LIST_SIZE - 1) {
		printf("��������");
		exit(-1);
	}
	int i = _malloc(list);
	list.node[i].data = data ; 
	list.length ++;
}
//��λ����
int locateData(List &list,int data){
	if(list.length < 1) exit(-1);
	int i = 1;
	while(i <= list.length) {
		if(list.node[i].data == data) return i;
		i++;
	}
	return -1;
}
//ɾ������
void deleteData(List &list,int index){
	if(index<1 || index > INIT_LIST_SIZE) exit(-1);
	list.node[index].data = NULL;
	list.length --;
	_free(list,index);
}
//��������
void insertData(List &list,int index, int data){
	if(index<1||index>list.length) exit(-1);
	int i = _malloc(list);
	list.node[i].data = data;
	if(index ==1 ){
		list.node[i].cur = list.node[index-1].data ;
		list.node[index-1].data = i;
	}else{
		list.node[i].cur = list.node[index-1].cur ;
		list.node[index-1].cur = i ; 
	}
	list.length++;
	if(list.node[i-1].cur == i && list.node[i].cur != i+1){
		list.node[i-1].cur = list.node[0].cur;
	}
}
//�鿴��������
void watchData(List &list){
	int i = 1;
	while(i<=list.length){
		printf("%d",list.node[i].data);
		printf("-->");
		printf("%d\n",list.node[i].cur);
		i++;
	}
}
int main(void){
	List list;
	initList(list);
	addData(list,1);
	//deleteData(list,1);
	addData(list,2);
	addData(list,3);
	addData(list,4);
	insertData(list,1,10);
	insertData(list,1,11);
	//insertData(list,2,11);
	addData(list,7);
	addData(list,8);
	watchData(list);
	//printf("%d\n",list.node[0].cur);
	//printf("%d\n",list.length);
	//printf("%d\n",locateData(list,4));
	return 0;
}