#include <stdio.h>
/*
	��������
	ÿ�δ�δ�����Ԫ�����ó�һ��Ԫ���ҵ���Ԫ�����������λ�ò����ȥ
  */

void InsertSort1(int arr[],int n){
	for(int i = 1  ;i < n ; i ++){ //�ӵڶ���Ԫ�ؿ�ʼ����һ����ʾ�Ѿ�����
		int cur = arr[i];
		int j = i - 1;
		while(j>=0 && arr[j]>cur){
			arr[j+1] = arr[j]; //����������Ԫ��
			j--;
		}
		arr[j+1] = cur;
	}
}

/*
	�Ľ���������
	���ö��ַ����ҵ���Ԫ����������Ԫ���ڵ�λ��
	��Ԫ�غܶ��ʱ��Ч�ʱ�ֱ�Ӹ�
	���������������������ƫ��
  */

void InsertSort2(int arr[],int n){
	for(int i = 1 ; i < n ; i ++){ //�ӵڶ���Ԫ�ؿ�ʼ����һ����ʾ�Ѿ�����
		int cur = arr[i];
		int left = 0;
		int right = i - 1;
		while(left<=right){
			int mid = (left+right) /2; 
			if(arr[mid] > cur){
				right = mid - 1;
			}else{
				left = mid + 1;
			}
		}
		for(int j = i - 1 ; j >= left ; j--){//����Ԫ��Ϊ����Ԫ���ṩλ��
			arr[j+1] = arr[j];
		}
		arr[left] = cur;
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
	int arr[] = {2,1,5,4,6,7,3,10};
	int n = sizeof(arr)/sizeof(int);
	InsertSort2(arr,n);
	PrintResult(arr,n);
	return 0;
}