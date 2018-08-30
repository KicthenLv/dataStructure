#include <stdio.h>
/*
	��������
	�Ƕ�ð�������һ�ָĽ�
	ѡȡһ����׼Ԫ��(��һ���������һ��) 
	�����ڻ�׼��Ԫ�طŵ���׼���棬С�ķ���ǰ�棬�����ݹ�ﵽ�����Ч��
	�����ȶ��������㷨
*/

int Partition(int arr[], int left,int right){
	int pivot = arr[left]; //ȡ��һ��Ϊ��׼
	int tail = right+1;
	int temp = 0;
	for(int i = right; i > left; i --){ //���Ȼ�׼������ŵ�����ĩβ
		if(arr[i] > pivot){
			temp = arr[tail-1];
			arr[--tail] = arr[i];
			arr[i] = temp;
		}
	}
	//������׼ �����ܻ�����ȶ���
	temp = arr[left];
	arr[left] = arr[tail-1]; 
	arr[tail-1] = temp;
	//�����µĻ�׼�±�
	return tail-1;
}
/*
	��������
	���ϵİ汾�������˹���Ľ���
*/

int Partition1(int arr[], int left,int right){
	int pivot = arr[left];
	while(left<right){
		while(left<right && arr[right]>=pivot) right--; //�ҵ��������ڵ�С�ڻ�׼�ĵ�һ��Ԫ��
		arr[left] = arr[right];  //����ŵ������
		while(left<right && arr[left]<=pivot) left++;	//�ҵ��������ڵĴ��ڻ�׼�ĵ�һ��Ԫ��
		arr[right] = arr[left];  //����ŵ����ұ�
	}
	arr[left] = pivot;	//���»�׼
	return left; //�����µĻ�׼
}
void QuickSort(int arr[],int left,int right){
	if(left>=right) return;
	int partition = Partition1(arr,left,right);
	QuickSort(arr,left,partition-1);
	QuickSort(arr,partition+1,right);
}

/*
	��ӡ������
*/
void PrintResult(int arr[],int n){
	for(int i = 0 ; i < n ; i++) printf("%d ",arr[i]);
	printf("\n");
}

int main(void){ 
	int arr[] = {1,4,3,9,6,5,2,3};
	int n = sizeof(arr)/sizeof(int);
	QuickSort(arr,0,n-1);
	PrintResult(arr,n);
	return 0;
}

