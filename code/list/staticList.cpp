//创建静态链表
//使用数组存储数据和备用数组存储索引
#include <stdio.h>
#include <stdlib.h>

//定义链表最大大小
#define INIT_LIST_SIZE 10

//定义链表节点
typedef struct{
	int data;
	int cur;
}Node;
//定义链表
typedef struct{
	Node *node; //定义存储数组
	int length; //定义长度
}List;

//初始化链表 将每一个节点的索引置为相对位置
void initList(List &list){
	list.node = (Node *)malloc(INIT_LIST_SIZE*sizeof(Node));
	for(int i =0 ;i<INIT_LIST_SIZE ; i++)
		list.node[i].cur = i +1 ;
	list.node[INIT_LIST_SIZE-1].cur = 0;
	list.node[0].data = 1;
	list.length = 0;
}
//模拟申请空间方法
int _malloc(List &list){
	//获取头节点的索引
	int i = list.node[0].cur;
	if(i > INIT_LIST_SIZE) exit(-1);
	if(i) list.node[0].cur = list.node[i].cur ;
	return i;
}
//模拟释放节点空间
void _free(List &list,int index){
	if(index<1 || index > INIT_LIST_SIZE) exit(-1);
	list.node[index].cur = list.node[0].cur;
	list.node[0].cur = index;
}
//添加数据
void addData(List &list,int data){
	if(list.length > INIT_LIST_SIZE - 1) {
		printf("容量不足");
		exit(-1);
	}
	int i = _malloc(list);
	list.node[i].data = data ; 
	list.length ++;
}
//定位数据
int locateData(List &list,int data){
	if(list.length < 1) exit(-1);
	int i = 1;
	while(i <= list.length) {
		if(list.node[i].data == data) return i;
		i++;
	}
	return -1;
}
//删除数据
void deleteData(List &list,int index){
	if(index<1 || index > INIT_LIST_SIZE) exit(-1);
	list.node[index].data = NULL;
	list.length --;
	_free(list,index);
}
//插入数据
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
//查看链表数据
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