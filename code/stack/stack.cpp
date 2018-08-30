//引入库文件
#include <stdio.h>
#include <stdlib.h>

//定义初始大小
#define INIT_STACK_SIZE 10

//定义数据结构
typedef struct {
	int *base;//存储基址
	int *top;//指向栈顶的指针
	int stacksize;
}Stack;

//初始化栈
void initStack(Stack *stack){
	stack->base = (int *)malloc(INIT_STACK_SIZE*sizeof(int)); //为栈申请空间
	if(!stack) exit(-1); 
	stack->top = stack->base;//将空栈栈顶指向栈底
	stack->stacksize = INIT_STACK_SIZE;//初始化栈大小
}
//向栈内添加元素 入栈
void push(Stack *stack,int data){
	if(stack->top - stack->base >= stack->stacksize) {
		stack->base = (int *)realloc(stack->base,(stack->stacksize + INIT_STACK_SIZE) * sizeof(int));
		if(!stack) exit(-1);
		stack->stacksize += INIT_STACK_SIZE; 
	}
	
	*stack->top++ = data;
}
//弹出栈顶元素
int pop(Stack *stack){
	if(stack->top == stack->base) exit(-1);
	return *--stack->top;
}
//获取到栈顶元素
int getTop(Stack *stack){
	if(stack->top == stack->base) exit(-1);
	return *stack->top;
}
//遍历栈
void watchStack(Stack *stack){
	if(stack->top == stack->base) exit(-1);
	for(int i = 0 ; i < stack->top - stack->base ; i ++){
		printf("%d\n",*stack->base+i);
	}
}
//摧毁栈
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