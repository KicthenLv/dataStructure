#include<stdio.h>
#include<stdlib.h>
/**
	�鲢����
	���÷ֶ���֮��˼�뽫����ֵȳ������ɷݣ�ÿһ�ݸ�������ֱ��������������
	���õݹ�ʵ�ֶַ���֮
	ƽ��ʱ�临�Ӷ� O(nlogn)
	�ռ临�Ӷ�ΪO(n)
	Java ��Arrays.sort()ʹ�ÿ������򣬲������� ���鲢���򣬸��ݲ�ͬ�ķ�ֵѡ��ͬ�㷨���㷨����Ƕ�����������㷨
  */

void Sort(int arr[],int left,int mid,int right,int *temp){ //temp Ϊ�ݴ汻���������
	//�ֱ����ߺ��ұߵ�������бȽϣ�С�ķ���result��
	int l = left;
	int r = mid+1;
	int tmp = 0;
	while(l<=mid && r<= right){ //�ҳ������С��
		if(arr[l] < arr[r])
			temp[tmp++] =  arr[l++];
		else temp[tmp++] = arr[r++];
	}
	while(l <= mid) temp[tmp++] = arr[l++]; //����δ��ѡ�е�
	while(r <= right) temp[tmp++] = arr[r++];

	//�޸�Դ����
	tmp= 0;
	while(left <= right){
		arr[left++] = temp[tmp++];
	}
}
//���õݹ���ʵ�ֶַ�����֮
void MergeSort(int arr[],int left, int right,int *temp){
	if(left < right){
		int mid = (left + right) / 2;
		MergeSort(arr,left,mid,temp); //�ֵ���С�ݿ�ʼ
		MergeSort(arr,mid+1,right,temp); 
		Sort(arr,left,mid,right,temp); //�Բ�ͬ�ݽ�����֮
	}
}

//��ӡ���
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