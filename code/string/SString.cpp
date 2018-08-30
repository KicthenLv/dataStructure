#include "stdio.h"
#include "stdlib.h"

//定义串的最长size
#define MAXSIZE 10

//定义串的数据关系 第一个元素存放字符串长度
typedef  unsigned char SString[MAXSIZE+1];

//将字符集合转换为字符串
void convert(char chars[],int length,SString str){
	for(int i = 0 ; i < length ; i++){
		str[i+1] = chars[i];
	}
	str[0] = length;
}
//字符串连接算法
void concat(SString str1,SString str2,SString str3){
	if(str1[0]+str2[0]<=MAXSIZE){
		for(int i = 1 ; i <= str1[0]+str2[0];i++){
			if(i <= str1[0]) str3[i] = str1[i];
			else str3[i] = str2[i];
		}
		str3[0] = str1[0]+str2[0];
	}
	else if(str1[0] < MAXSIZE){
		for(int i = 1 ; i <= str1[0];i++){
			str3[i] = str1[i];
		}
		for(int j = str1[0]+1 ; j <= MAXSIZE-str1[0] ; j++){
			str3[j] = str2[j-str1[0]];
		}
		str3[0] = MAXSIZE;
	}
	else{
		for(int i = 1 ; i <= str1[0];i++){
			str3[i] = str1[i];
		}
		str3[0] = str1[0];
	}
}
//求字串算法
void subString (SString sub,SString s,int pos,int len){
	if(pos<1 || pos > s[0] || len<0 || len> s[0]-pos+1) exit(-1);

	for(int i = 1 ;i <=len ; i++){
		sub[i] = s[pos+i-1];
	}
	sub[0] = len;
}

int main(void){
	//创建一个字符串
	//SString str = {'a','b','c'} ;
	//printf("%c\n",str[0]);
	SString str1;
	SString str2;
	SString str3;
	SString str4;
	char chars1[11] = {'A','B','C','D','X','Y','Z','E','F','G','H'};
	char chars2[5] = {'E','F','G','H','N'};
	convert(chars1,11,str1);
	convert(chars2,5,str2);
	concat(str1,str2,str3);
	subString(str4,str3,4,5);
	printf("%c\n",str3[10]);
	printf("%c\n",str3[7]);
	printf("%c\n",str4[5]);
	//printf("%c\n",str[3]);
	return 0;
}