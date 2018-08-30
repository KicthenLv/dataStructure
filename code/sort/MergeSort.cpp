#include<stdio.h>
#include<stdlib.h>
/**
	归并排序
	运用分而治之的思想将数组分等长的若干份，每一份各自排序，直到完整数组排序
	利用递归实现分而治之
	平均时间复杂度 O(nlogn)
	空间复杂度为O(n)
	Java 中Arrays.sort()使用快速排序，插入排序 ，归并排序，根据不同的阀值选择不同算法，算法中内嵌了其他排序算法
  */

void Sort(int arr[],int left,int mid,int right,int *temp){ //temp 为暂存被排序的数组
	//分别对左边和右边的数组进行比较，小的放入result中
	int l = left;
	int r = mid+1;
	int tmp = 0;
	while(l<=mid && r<= right){ //找出区间较小的
		if(arr[l] < arr[r])
			temp[tmp++] =  arr[l++];
		else temp[tmp++] = arr[r++];
	}
	while(l <= mid) temp[tmp++] = arr[l++]; //放入未被选中的
	while(r <= right) temp[tmp++] = arr[r++];

	//修改源数组
	tmp= 0;
	while(left <= right){
		arr[left++] = temp[tmp++];
	}
}
//利用递归来实现分而和治之
void MergeSort(int arr[],int left, int right,int *temp){
	if(left < right){
		int mid = (left + right) / 2;
		MergeSort(arr,left,mid,temp); //分到最小份开始
		MergeSort(arr,mid+1,right,temp); 
		Sort(arr,left,mid,right,temp); //对不同份进行治之
	}
}

//打印结果
void PrintResult(int arr[], int n){
	for(int i = 0; i < n ; i ++) printf("%d ",arr[i]);
	printf("\n");
}
int main(void){
	int arr[] = {9,8,7,6,5,4,3,2,1};
	int n = sizeof(arr)/sizeof(int);
	int *temp = (int*)malloc(sizeof(int)*n);
	for(int i = 0 ; i < n ; i ++) temp[i] = 0;
	MergeSort(arr,0,n-1,temp);
	PrintResult(arr,n);
	free(temp);
	return 0;
}