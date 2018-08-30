#include <stdio.h>
#include <stdlib.h>

//定义数据结构

typedef struct QNode{
	int data;
    struct QNode *next;
}QNode;

typedef struct{
	QNode *front;
	QNode *rear;
}Queue;

//初始化队列,将队头和队尾只指向同一个指针区域,头节点不存放数据
void InitQueue(Queue *que){
	que->front = (QNode *)malloc(sizeof(QNode));
	que->front->next = NULL;
	que->rear = que->front;
}

//获取队列的长度
int queLength(Queue *que){
	return que->rear - que->front;
}

//判断队列是否为空
bool isEmpty(Queue *que){
	return que->front==que->rear?true:false;
}

//数据入队列
void enQueue(Queue *que , int data){
	QNode *qnode = (QNode *)malloc(sizeof(QNode));
	qnode->data = data ;
	que->rear->next = qnode;
	que->rear = que->rear->next;
}

//队尾元素出队列
int deQueue(Queue *que){
	if(que->front == que->rear) exit(-1);
	int result = que->front->next->data;
	free(que->front->next);
	que->front->next = que->front->next->next;
	return result;
}

//摧毁队列
void destoryQue(Queue *que){
	while(que->front){
		que->rear = que->front;
		free(que->front);
		que->front = que->rear;
	}
}

//遍历队列内所有元素
void watchQueue(Queue *que){
	QNode *current = que->front->next;
	while(current){
		printf("%d\n",current->data);
		current = current->next;
	}
}

int main(){
	Queue que;
	InitQueue(&que);
	enQueue(&que,1);
	enQueue(&que,2);
	enQueue(&que,3);
	enQueue(&que,4);
	enQueue(&que,5);
	watchQueue(&que);
	//int result = deQueue(&que);
	//printf("%d\n",result);
	//destoryQue(&que);
	//int result1 = deQueue(&que);
	return 0;
}