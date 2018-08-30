/***
	选择排序：
	每一轮从未被选择的元素内选择出最大或者最小的元素放到头部或者尾部
	时间复杂度 O(n^2)  
	空间复杂度 O(1)
	稳定的排序，不会改变相等于元素的相对位置
*/
#include <stdio.h>

/**
	arr[] 被排序的数组，n为数组的长度
	增序排序
*/
void SelectSort(int arr[],int n){
	int min = 0; //记录最小下标
	int temp = 0;
	for(int i = 0 ; i < n ; i ++){
		min = i ;
		temp = arr[i]; //交换第三方，或者直接用以或加法等方式交换
		for(int j = i + 1 ; j < n ; j++){
			if(arr[j] < arr[min]) min = j; //从未被选择的元素内找出最小元素下标
		}
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
/**
	arr[] 被排序的数组，n为数组的长度
	改进，每次循环找出最大和最小的值的下标
	减少循环的次数
	增序排序
*/
void SelectSort2(int arr[],int n){
	int min = 0; //记录最小下标
	int max = 0; 
	int temp1 = 0;
	int temp2 = 0;
	for(int i = 0 ; i < n/2; i ++){
		min = i ;
		max = i ; 
		temp1 = arr[i]; //交换第三方，或者直接用以或加法等方式交换
		temp2 = arr[i];
 		for(int j = i + 1 ; j < n - i; j++){
			if(arr[j] < arr[min]) min = j; //从未被选择的元素内找出最小元素下标
			if(arr[j] > arr[max]) max = j; //选择出最大的元素下标
		}
		arr[i] = arr[min];
		arr[min] = temp1;
		arr[n-i-1] = arr[max];
		arr[max] = temp2;
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
	int arr[] = {2,1,5,4,6,7,3};
	int n = sizeof(arr)/sizeof(int);
	SelectSort2(arr,n);
	PrintResult(arr,n);
	return 0;
}
