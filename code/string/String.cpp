#include <stdio.h>
#include <stdlib.h>

//���崮����󳤶�
#define MAXSIZE 255

//���崮�Ľṹ
typedef unsigned char String[MAXSIZE+1]; //��0λ�ô�ų���

//��������
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
