#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define N 5//��Ȩֵ��Ҷ�ӽڵ�����������Ҫ������ַ���
#define M 2*N-1//n��Ҷ�ӽڵ㹹��Ĺ���������2n-1�����

typedef char TElemType;
//��̬��������洢�ṹ
typedef struct{
	int weight;//Ȩֵֻ��������
	int parent;
	int lchild;
	int rchild;
}HTNode;//, *HuffmanTree;
typedef HTNode HuffmanTree[M+1];//0�ŵ�Ԫ��ʹ��
 
typedef char * HuffmanCode[N+1];//�洢ÿ���ַ��Ĺ������������һ���ַ�ָ�����飬ÿ������Ԫ����ָ���ַ�ָ���ָ��
//ѡ��Ȩֵ��С������δ�������ڵ�Ľڵ�
void select(HuffmanTree HT, int n, int &s1, int &s2){
	int min1 , min2 ;
	int i =1 ;
	while(HT[i].parent!=0 && i <= n)i++;
	min1 = HT[i].weight;
	s1 = i;
	i++;
	while(HT[i].parent!=0 && i <= n)i++;
	min2 = HT[i].weight;
	s2 = i;
	i++;
	if(min1>min2){
		min1 = min2+min1;
		min2 = min1-min2;
		min1 = min1-min2;
		s1 = s1+s2;
		s2 = s1-s2;
		s1 = s1-s2;
	}
	for(;i<=n;i++){
		if(HT[i].weight < min1 && HT[i].parent==0){
			min2 = min1;
			s2 = s1;
			min1 = HT[i].weight;
			s1 = i;
		}else if(HT[i].weight < min2 && HT[i].parent==0){
			min2 = HT[i].weight;
			s2 = i;
		}
	}
}
//��ӡ��
void printHuffmanTree(HuffmanTree HT,char ch[]){
	printf("\n");
	printf("data, weight, parent, lchild, rchild\n");
	for(int i = 1; i <= 2*N-1; i++){
		if(i > N){
			printf("  -, %5d, %5d, %5d, %5d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}else{
			printf("  %c, %5d, %5d, %5d, %5d\n", ch[i-1], HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}
	}
	printf("\n");
}
void printHuffmanCode(HuffmanCode HC,char ch[]){
	printf("\n");
	for(int i = 1; i <= N; i++){
		printf("%c:%s\n", ch[i-1], HC[i]);
	}
	printf("\n");
}
//�������
void enCoding(HuffmanTree &HT,HuffmanCode &HC, int *w){
	if(N<=1) return;
	int m = 2*N -1; //�������нڵ���
	//��ʼ��������Ҷ�ӽڵ��ʼ��Ȩ�أ������ڵ���ʱδ0
	int i = 1;
	for(;i<=N;i++){
		HT[i].weight = w[i-1];
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].parent = 0;
	}
	for(;i<=m;i++){
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].parent = 0; 
	}
	int s1=0,s2=0;	
	//����ÿ�������Ĺ�ϵ
	for(i = N+1;i<=m ; i++){
		select(HT,i-1,s1,s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].rchild = s2;
		HT[i].lchild = s1;
	}
	//��Ҷ�ӽڵ�����ڵ����ַ�����
	char ch[N];
	ch[N-1] = '\0';
	for(i=1 ; i<=N ; i++){
		int start = N-1;
		int cur = i;
		int par = HT[i].parent;
		while(par){//δ�����ڵ�
			if(cur == HT[par].lchild)
				ch[--start] = '0';
			else
				ch[--start] = '1';
			cur = par;
			par = HT[par].parent;
		}
		//�����������Ƶ�������������
		HC[i] = (char *)malloc((N-start)*sizeof(char));

		strcpy(HC[i],&ch[start]);
	}
}
//�������
void decoding(HuffmanTree HT, char *ch, char str[], int len, char *result){
	int cur = M;
	int i = 0;
	int j = 0;
	while(i<len){
		if('0' == str[i]){
			cur = HT[cur].lchild;
		}
		else if('1' == str[i]){
			cur = HT[cur].rchild;
		}
		if(cur<=N){
			result[j] = ch[cur-1];
			j++;
			cur = M;
		}
		i++;
	}
	result[j] = '\0';
}
void main(){
	HuffmanTree HT;
	HuffmanCode HC;
	int w[N] = {100,200,300,150,80};
	char ch[N] = {'a','b','c','d','e'};
	enCoding(HT,HC,w);
	printHuffmanTree(HT,ch);
	printHuffmanCode(HC,ch);
	char *str = "01110110001010";
	int len = 14;
	char result[14];
	decoding(HT,ch,str,len,result);
	printf("%s\n",result);
}