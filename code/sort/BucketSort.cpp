#include<stdio.h>
#include<stdlib.h>
/**
	桶排序
	创建一个比需排序的数组最大元素的数组并将其置为0
	遍历需排序数组，将需排序数组内的元素出现的次数放到另一个数组内
	最后，数组另一个数组
	缺点占用空间大
	时间复杂度O(nlogn)
*/

void BucketSort(int arr[],int n){
	//1.找到最大元素
	int max = 0;
	max = arr[0];
	for(int i = 1 ; i < n ; i++){
		if(arr[i] > max) max = arr[i];
	}
	int *result = (int *)malloc(sizeof(int)*(max+1));
	for(i = 0 ; i < max+1 ; i++){
		result[i] = 0; //初始化数组	
	}
	for(i = 0 ; i < n ; i++){
		result[arr[i]]++;
	}
	for(int j = 0 ; j < max+1 ; j ++){
		if(result[j] > 0 ){
			for(int k = 0 ; k < result[j] ; k++) printf("%d ",j);
		}
	}
	printf("\n");
}

int main(void){
	int arr[] = {8,5,9,2,4,1,0,4,5};
	int n = sizeof(arr)/sizeof(int);
	BucketSort(arr,n);
	return 0;
}