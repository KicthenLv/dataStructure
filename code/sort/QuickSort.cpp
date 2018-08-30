#include <stdio.h>
/*
	快速排序
	是对冒泡排序的一种改进
	选取一个基准元素(第一个或者最后一个) 
	将大于基准的元素放到基准后面，小的放在前面，经过递归达到排序的效果
	不是稳定的排序算法
*/

int Partition(int arr[], int left,int right){
	int pivot = arr[left]; //取第一个为基准
	int tail = right+1;
	int temp = 0;
	for(int i = right; i > left; i --){ //将比基准大的数放到数组末尾
		if(arr[i] > pivot){
			temp = arr[tail-1];
			arr[--tail] = arr[i];
			arr[i] = temp;
		}
	}
	//调换基准 ，可能会打乱稳定性
	temp = arr[left];
	arr[left] = arr[tail-1]; 
	arr[tail-1] = temp;
	//返回新的基准下标
	return tail-1;
}
/*
	快速排序
	书上的版本，减少了过多的交换
*/

int Partition1(int arr[], int left,int right){
	int pivot = arr[left];
	while(left<right){
		while(left<right && arr[right]>=pivot) right--; //找到该区域内的小于基准的第一个元素
		arr[left] = arr[right];  //将其放到最左边
		while(left<right && arr[left]<=pivot) left++;	//找到该区域内的大于基准的第一个元素
		arr[right] = arr[left];  //将其放到最右边
	}
	arr[left] = pivot;	//更新基准
	return left; //返回新的基准
}
void QuickSort(int arr[],int left,int right){
	if(left>=right) return;
	int partition = Partition1(arr,left,right);
	QuickSort(arr,left,partition-1);
	QuickSort(arr,partition+1,right);
}

/*
	打印排序结果
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

