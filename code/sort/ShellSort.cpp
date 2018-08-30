#include <stdio.h>
/*
	希尔排序
	直接插入排序的改进版
	通过每次排序不同区域内的元素，直到区域为整个元素集合时，完成排序
	最优的时间复杂度为 O(n)
	最差要看 gap的选择
	不稳定的排序
  */

void ShellSort(int arr[], int n){
	//定义一个区域间隔，最开始为n/2
	int gap = n/2;
	while(gap >= 1){
		for(int i = gap ; i < n ; i++){
			//利用插入排序来排序区域内的元素
			int cur = arr[i];
			int j = i - gap; //区域最开始的元素
			while(j>=0 && arr[j]>cur){
				arr[j+gap] = arr[j];//移动元素
				j -=gap;
			}
			arr[j+gap] = cur;//替换元素
		}
		gap /=2; //改变区域大小
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
	ShellSort(arr,n);
	PrintResult(arr,n);
	return 0;
}

