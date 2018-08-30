#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define N 5//带权值的叶子节点数或者是需要编码的字符数
#define M 2*N-1//n个叶子节点构造的哈夫曼树有2n-1个结点

typedef char TElemType;
//静态三叉链表存储结构
typedef struct{
	int weight;//权值只能是正数
	int parent;
	int lchild;
	int rchild;
}HTNode;//, *HuffmanTree;
typedef HTNode HuffmanTree[M+1];//0号单元不使用
 
typedef char * HuffmanCode[N+1];//存储每个字符的哈夫曼编码表，是一个字符指针数组，每个数组元素是指向字符指针的指针
//选择权值最小的两个未包含父节点的节点
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
//打印树
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
//编码过程
void enCoding(HuffmanTree &HT,HuffmanCode &HC, int *w){
	if(N<=1) return;
	int m = 2*N -1; //树的所有节点数
	//初始化树，将叶子节点初始化权重，其他节点暂时未0
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
	//设置每个子树的关系
	for(i = N+1;i<=m ; i++){
		select(HT,i-1,s1,s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].rchild = s2;
		HT[i].lchild = s1;
	}
	//从叶子节点向根节点求字符编码
	char ch[N];
	ch[N-1] = '\0';
	for(i=1 ; i<=N ; i++){
		int start = N-1;
		int cur = i;
		int par = HT[i].parent;
		while(par){//未到根节点
			if(cur == HT[par].lchild)
				ch[--start] = '0';
			else
				ch[--start] = '1';
			cur = par;
			par = HT[par].parent;
		}
		//将编码结果复制到哈弗曼编码中
		HC[i] = (char *)malloc((N-start)*sizeof(char));

		strcpy(HC[i],&ch[start]);
	}
}
//解码过程
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