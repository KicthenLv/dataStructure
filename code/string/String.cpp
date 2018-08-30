#include <stdio.h>
#include <stdlib.h>

//定义串的最大长度
#define MAXSIZE 255

//定义串的结构
typedef unsigned char String[MAXSIZE+1]; //第0位置存放长度

//串的连接
void concat(String &R,String s1,String s2){
	if(s1[0]+s1[0]<=MAXSIZE){
		R[1..s1[0]] = s1[1..s1[0]];
		R[s1[0]+1..s1[0]+s2[0]] = s2[1..s2[0]];
		R[0] = s1[0]+s2[0];
	}
	else if(s1[0]<MAXSIZE){
		R[1..s1[0]] = s1[1..s1[0]];	
		R[s1[0]+1..MAXSIZE] = s2[1..MAXSIZE-[s1[0]]];
		R[0] = MAXSIZE;
	}
	else{
		T[0..MAXSIZE] = s1[0..MAXSIZE];
	}
}

int main(void){
	String str = {'a','b','c','d'};
	return 0;
}
