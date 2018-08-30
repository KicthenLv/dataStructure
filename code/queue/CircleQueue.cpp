#include <stdio.h>
#include <stdlib.h>

//������д�С
#define INIT_QUEUE_SIZE 5

//����ѭ�����еĽṹ,ѭ����������ͨ���в�ȡ�Ĳ���һ���ṹ
typedef struct CQueue{
	int *base; //����洢��ַ
	int front; //�����ͷ������
	int rear; //�����β������
}CQueue;

//��ʼ������
void InitQueue(CQueue *que){
	que->base = (int *)malloc(INIT_QUEUE_SIZE*sizeof(int));
	que->front = que->rear = 0;
}
//���еĳ���
int queLength(CQueue *que){
	
}

//�����
void enQueue(CQueue *que,int data){
	if((que->rear+1)%INIT_QUEUE_SIZE == que->front) exit(-1);
	que->base[que->rear] =  data;
	que->rear = (que->rear+1)%INIT_QUEUE_SIZE;
}
//������
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


