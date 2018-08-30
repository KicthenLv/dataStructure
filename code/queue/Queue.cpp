#include <stdio.h>
#include <stdlib.h>

//�������ݽṹ

typedef struct QNode{
	int data;
    struct QNode *next;
}QNode;

typedef struct{
	QNode *front;
	QNode *rear;
}Queue;

//��ʼ������,����ͷ�Ͷ�βָֻ��ͬһ��ָ������,ͷ�ڵ㲻�������
void InitQueue(Queue *que){
	que->front = (QNode *)malloc(sizeof(QNode));
	que->front->next = NULL;
	que->rear = que->front;
}

//��ȡ���еĳ���
int queLength(Queue *que){
	return que->rear - que->front;
}

//�ж϶����Ƿ�Ϊ��
bool isEmpty(Queue *que){
	return que->front==que->rear?true:false;
}

//���������
void enQueue(Queue *que , int data){
	QNode *qnode = (QNode *)malloc(sizeof(QNode));
	qnode->data = data ;
	que->rear->next = qnode;
	que->rear = que->rear->next;
}

//��βԪ�س�����
int deQueue(Queue *que){
	if(que->front == que->rear) exit(-1);
	int result = que->front->next->data;
	free(que->front->next);
	que->front->next = que->front->next->next;
	return result;
}

//�ݻٶ���
void destoryQue(Queue *que){
	while(que->front){
		que->rear = que->front;
		free(que->front);
		que->front = que->rear;
	}
}

//��������������Ԫ��
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