/**
	ð������
	ͨ��ÿһ�ֽ�������СԪ���ƶ���ͷ������β��ʵ������
	ʱ�临�Ӷ� ���:O(n^2), ����:O(n)�Ѿ�����
	�ȶ�������  
*/
#include<stdio.h>
/*
	��ͳ��ð������
*/
void BubbleSort1(int arr[] , int n){
	
	for(int i = 0 ; i < n - 1 ; i ++){
		bool change = true; //��¼������ʶ��
		for(int j = 0 ; j < n - i -1; j++){
			if(arr[j] > arr[j+1]){ //������Ԫ����yi
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				change = false; //��������
			}
		}
		if(change) break;
	}	
}
/*
	�Ľ���ð������
	��һ���������н�����˵������
	������ѭ��
*/
void BubbleSort2(int arr[], int n){
	int i = n - 1;
	while(i > 0){
		int pos = 0; //��¼ÿ�ν����ĵ�һ��Ԫ�أ���û�н�����pos = 0 
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
	�Ľ���ð������(��β������)
	ÿ��ѭ�����дӵ͵���ð�ݣ�Ȼ����дӸߵ���ð��
*/
void BubbleSort3(int arr[], int n){
	int temp = 0 ;
	for(int i = 0 ; i < n / 2 ; i ++){
		bool change = true;
		for(int j = i ; j < n -1 ; j++){ //ð������
			if(arr[j] > arr[j+1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				change = false;
			}
		}
		for(j = n-i-1 ; j > i ; j--){ //ð����С��
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
	��ӡ������
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