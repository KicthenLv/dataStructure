#include<stdio.h>
#include<stdlib.h>
#define		key				number
#define 	N 				5
typedef 	long			KeyType;

//˳���Ĳ���
struct ElemType
{
	long 	number;
	int 	Chinese;
	int		English;
	int 	math;
	int		total;
};
 
struct SSTable
{
	ElemType	*elem;
	int			length;
};
 
void Creat_Seq(SSTable &ST, ElemType r[], int n)
{
	int i;
	ST.elem = (ElemType*)malloc(sizeof(ElemType)*(n+1));
	if (!ST.elem)	exit(-1);
	
	for (i = 1; i <= n; ++i)
	{
		ST.elem[i] = r[i-1];
	}
	ST.length = n;
}
 
void Destroy(SSTable &ST)
{
	if (ST.elem)
		free(ST.elem);
	ST.elem = NULL;
	ST.length = 0;
}
 
int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	//��iλ��������key��Ƚ�����ͬ�򷵻�i�����򷵻�0;
	ST.elem[0].key = key;//��ֹÿ�ζ��ж��Ƿ���ҽ�����0�ŵ�Ԫ�������洢����
	for (i = ST.length; !(key==ST.elem[i].key); --i);
	return i;
}
void visit(ElemType e){
	printf("%d\n",e.number);
}
void Traverse(SSTable ST)
{ 
	int i;
	ElemType *p;
	p = ++ST.elem;
	for (i = 1; i <= ST.length; ++i)
		visit(*p++);
}
//�۰����ʵ��
//�ŵ㣬���ұ�˳�����Ч�ʸ�
//ȱ�㣬��Ҫ����������������
//�¼����Ӷȣ�O(log2n)
int binary_search(int *binary,int key,int len){
	//��������ָ��ֱ�ָ������������С����
	int low = 0;
	int high = len - 1;
	int mid = 0;
	while(low <= high){
		mid = (low+high)/2;
		if(binary[mid] == key){
			return mid;
		}
		else if(binary[mid] > key){
			high--;
		}else {
			low++;
		}
	}
	return -1;
}

int main(void){
	//��������
	int data[] = {1,2,3,4,5,6,7};
	//�����۰����
	int index = binary_search(data,7,7);
	printf("%d\n", index+1);


	//��������������
	ElemType *r;
	r = (ElemType*)malloc(sizeof(ElemType)*N);
	r[0].number = 1;
	r[0].Chinese = 90;
	r[0].math = 100;
	r[0].English = 20;
	r[0].total = r[0].Chinese + r[0].math +r[0].English;
	r[1].number = 2;
	r[1].Chinese = 90;
	r[1].math = 100;
	r[1].English = 20;
	r[1].total = r[0].Chinese + r[0].math +r[0].English;
	r[2].number = 3;
	r[2].Chinese = 90;
	r[2].math = 100;
	r[2].English = 20;
	r[2].total = r[0].Chinese + r[0].math +r[0].English;
	//�������ұ�
	SSTable table;
	Creat_Seq(table,r,3);
	int result = Search_Seq(table,1);
	Traverse(table);
	return 0;
}
