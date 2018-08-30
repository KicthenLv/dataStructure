//������ļ�
#include <stdio.h>
#include <stdlib.h>

//�����ʼ��С
#define INIT_STACK_SIZE 10

//�������ݽṹ
typedef struct {
	int *base;//�洢��ַ
	int *top;//ָ��ջ����ָ��
	int stacksize;
}Stack;

//��ʼ��ջ
void initStack(Stack *stack){
	stack->base = (int *)malloc(INIT_STACK_SIZE*sizeof(int)); //Ϊջ����ռ�
	if(!stack) exit(-1); 
	stack->top = stack->base;//����ջջ��ָ��ջ��
	stack->stacksize = INIT_STACK_SIZE;//��ʼ��ջ��С
}
//��ջ�����Ԫ�� ��ջ
void push(Stack *stack,int data){
	if(stack->top - stack->base >= stack->stacksize) {
		stack->base = (int *)realloc(stack->base,(stack->stacksize + INIT_STACK_SIZE) * sizeof(int));
		if(!stack) exit(-1);
		stack->stacksize += INIT_STACK_SIZE; 
	}
	
	*stack->top++ = data;
}
//����ջ��Ԫ��
int pop(Stack *stack){
	if(stack->top == stack->base) exit(-1);
	return *--stack->top;
}
//��ȡ��ջ��Ԫ��
int getTop(Stack *stack){
	if(stack->top == stack->base) exit(-1);
	return *stack->top;
}
//����ջ
void watchStack(Stack *stack){
	if(stack->top == stack->base) exit(-1);
	for(int i = 0 ; i < stack->top - stack->base ; i ++){
		printf("%d\n",*stack->base+i);
	}
}
//�ݻ�ջ
void destoryStack(Stack *stack){
	free(stack->base);
}
int main(void){
	Stack stack;
	initStack(&stack);
	push(&stack,1);
	push(&stack,2);
	push(&stack,3);
	push(&stack,4);
	watchStack(&stack);
	int data = pop(&stack);
	printf("%d\n",data);
	//destoryStack(&stack);
	return 0;
}