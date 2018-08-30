#include <stdio.h>
/*
	ϣ������
	ֱ�Ӳ�������ĸĽ���
	ͨ��ÿ������ͬ�����ڵ�Ԫ�أ�ֱ������Ϊ����Ԫ�ؼ���ʱ���������
	���ŵ�ʱ�临�Ӷ�Ϊ O(n)
	���Ҫ�� gap��ѡ��
	���ȶ�������
  */

void ShellSort(int arr[], int n){
	//����һ�����������ʼΪn/2
	int gap = n/2;
	while(gap >= 1){
		for(int i = gap ; i < n ; i++){
			//���ò������������������ڵ�Ԫ��
			int cur = arr[i];
			int j = i - gap; //�����ʼ��Ԫ��
			while(j>=0 && arr[j]>cur){
				arr[j+gap] = arr[j];//�ƶ�Ԫ��
				j -=gap;
			}
			arr[j+gap] = cur;//�滻Ԫ��
		}
		gap /=2; //�ı������С
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
	ShellSort(arr,n);
	PrintResult(arr,n);
	return 0;
}

