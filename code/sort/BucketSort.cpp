#include<stdio.h>
#include<stdlib.h>
/**
	Ͱ����
	����һ������������������Ԫ�ص����鲢������Ϊ0
	�������������飬�������������ڵ�Ԫ�س��ֵĴ����ŵ���һ��������
	���������һ������
	ȱ��ռ�ÿռ��
	ʱ�临�Ӷ�O(nlogn)
*/

void BucketSort(int arr[],int n){
	//1.�ҵ����Ԫ��
	int max = 0;
	max = arr[0];
	for(int i = 1 ; i < n ; i++){
		if(arr[i] > max) max = arr[i];
	}
	int *result = (int *)malloc(sizeof(int)*(max+1));
	for(i = 0 ; i < max+1 ; i++){
		result[i] = 0; //��ʼ������	
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