/**
	冒泡排序
	通过每一轮将最大或最小元素移动到头部或者尾部实现排序
	时间复杂度 最差:O(n^2), 最优:O(n)已经有序
	稳定的排序  
*/
#include<stdio.h>
/*
	传统的冒泡排序
*/
void BubbleSort1(int arr[] , int n){
	
	for(int i = 0 ; i < n - 1 ; i ++){
		bool change = true; //记录交换标识符
		for(int j = 0 ; j < n - i -1; j++){
			if(arr[j] > arr[j+1]){ //将最大的元素右yi
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				change = false; //发生交换
			}
		}
		if(change) break;
	}	
}
/*
	改进的冒泡排序
	若一轮下来进行交换则说明有序
	则跳出循环
*/
void BubbleSort2(int arr[], int n){
	int i = n - 1;
	while(i > 0){
		int pos = 0; //记录每次交换的第一个元素，若没有交换则pos = 0 
		for(int j = 0 ; j < i ; j++){
			if(arr[j] > arr[j+1]) {
				pos = j;
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp; 
			}
		}
		i = pos;
	}
}

/*
	改进的冒泡排序(鸡尾酒排序)
	每次循环进行从低到高冒泡，然后进行从高到低冒泡
*/
void BubbleSort3(int arr[], int n){
	int temp = 0 ;
	for(int i = 0 ; i < n / 2 ; i ++){
		bool change = true;
		for(int j = i ; j < n -1 ; j++){ //冒出最大的
			if(arr[j] > arr[j+1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				change = false;
			}
		}
		for(j = n-i-1 ; j > i ; j--){ //冒出最小的
			if(arr[j] < arr[j-1]) {
				temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
				change = false;
			}
		}
		if(change) break;
	}
}

/*
	打印排序结果
*/
void PrintResult(int arr[],int n){
	for(int i = 0 ; i < n ; i++) printf("%d ",arr[i]);
	printf("\n");
}

int main(void){
	int arr[] = {1,2,3,4,5,6,7};
	int n = sizeof(arr)/sizeof(int);
	BubbleSort3(arr,n);
	PrintResult(arr,n);
	return 0;
}