/***
	ѡ������
	ÿһ�ִ�δ��ѡ���Ԫ����ѡ�����������С��Ԫ�طŵ�ͷ������β��
	ʱ�临�Ӷ� O(n^2)  
	�ռ临�Ӷ� O(1)
	�ȶ������򣬲���ı������Ԫ�ص����λ��
*/
#include <stdio.h>

/**
	arr[] ����������飬nΪ����ĳ���
	��������
*/
void SelectSort(int arr[],int n){
	int min = 0; //��¼��С�±�
	int temp = 0;
	for(int i = 0 ; i < n ; i ++){
		min = i ;
		temp = arr[i]; //����������������ֱ�����Ի�ӷ��ȷ�ʽ����
		for(int j = i + 1 ; j < n ; j++){
			if(arr[j] < arr[min]) min = j; //��δ��ѡ���Ԫ�����ҳ���СԪ���±�
		}
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
/**
	arr[] ����������飬nΪ����ĳ���
	�Ľ���ÿ��ѭ���ҳ�������С��ֵ���±�
	����ѭ���Ĵ���
	��������
*/
void SelectSort2(int arr[],int n){
	int min = 0; //��¼��С�±�
	int max = 0; 
	int temp1 = 0;
	int temp2 = 0;
	for(int i = 0 ; i < n/2; i ++){
		min = i ;
		max = i ; 
		temp1 = arr[i]; //����������������ֱ�����Ի�ӷ��ȷ�ʽ����
		temp2 = arr[i];
 		for(int j = i + 1 ; j < n - i; j++){
			if(arr[j] < arr[min]) min = j; //��δ��ѡ���Ԫ�����ҳ���СԪ���±�
			if(arr[j] > arr[max]) max = j; //ѡ�������Ԫ���±�
		}
		arr[i] = arr[min];
		arr[min] = temp1;
		arr[n-i-1] = arr[max];
		arr[max] = temp2;
	}
}
/*
	��ӡ������
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
