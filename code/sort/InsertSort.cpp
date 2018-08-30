#include <stdio.h>
/*
	插入排序
	每次从未排序的元素内拿出一个元素找到该元素在已排序的位置插入进去
  */

void InsertSort1(int arr[],int n){
	for(int i = 1  ;i < n ; i ++){ //从第二个元素开始，第一个表示已经有序
		int cur = arr[i];
		int j = i - 1;
		while(j>=0 && arr[j]>cur){
			arr[j+1] = arr[j]; //左移已排序元素
			j--;
		}
		arr[j+1] = cur;
	}
}

/*
	改进插入排序
	利用二分法，找到该元素在已排序元素内的位置
	在元素很多的时候效率比直接高
	但是如果本来就有序的语就偏低
  */

void InsertSort2(int arr[],int n){
	for(int i = 1 ; i < n ; i ++){ //从第二个元素开始，第一个表示已经有序
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
		for(int j = i - 1 ; j >= left ; j--){//右移元素为插入元素提供位置
			arr[j+1] = arr[j];
		}
		arr[left] = cur;
	}
}


/*
	打印排序结果
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