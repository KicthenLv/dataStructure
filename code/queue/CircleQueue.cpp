#include <stdio.h>
#include <stdlib.h>

//定义队列大小
#define INIT_QUEUE_SIZE 5

//定义循环队列的结构,循环队列与普通队列采取的不是一个结构
typedef struct CQueue{
	int *base; //定义存储基址
	int front; //定义队头的索引
	int rear; //定义队尾的索引
}CQueue;

//初始化队列
void InitQueue(CQueue *que){
	que->base = (int *)malloc(INIT_QUEUE_SIZE*sizeof(int));
	que->front = que->rear = 0;
}
//队列的长度
int queLength(CQueue *que){
	
}

//入队列
void enQueue(CQueue *que,int data){
	if((que->rear+1)%INIT_QUEUE_SIZE == que->front) exit(-1);
	que->base[que->rear] =  data;
	que->rear = (que->rear+1)%INIT_QUEUE_SIZE;
}
//出队列
int deQueue(CQueue *que){
	if(que->front == que->rear) exit(-1);
	int result = que->base[que->front];
	que->front = (que->front + 1)%INIT_QUEUE_SIZE;
	return result;
}
int main(void){
	CQueue que;
	InitQueue(&que);
	//printf("%d\n",que.front);
	return 0;
}


