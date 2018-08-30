#include "stdio.h"
#include "stdlib.h"

//定义数据关系
typedef struct {
	char *ch;
	int length;
}HString;
//将字符数组转换为字符串
void StrAssign(HString *str,char *chars,int len){
	//if(str->ch!=NULL) free(str->ch);
	int length = len;
	if(length==0) {
		str->ch = NULL;
		str->length = 0;
	}
	else{
		str->ch = (char *)malloc(length*sizeof(char));
		if(!str->ch) exit(-1);
		for(int i =0 ; i<length ;i++){
			str->ch[i] = chars[i];
		}
		str->length = length;
	}
}
//获取字符串长度
int strLength(HString *str){
	return str->length;
}
//字符串比较
int strCompare(HString *str1,HString *str2){
	for(int i = 0 ; i<str1->length&&i<str2->length;i++ ){
		if(str1->ch[i]!= str2->ch[i]) return str1->ch[i] - str2->ch[i];
	}
	return str1->length - str2->length;
}
//清空字符串
void clearStr(HString *str){
	if(str->ch==NULL) exit(-1);
	free(str->ch);
	str->length = 0;
}
//连接字符串
void concat(HString *str,HString *str1,HString *str2){
	//if(str->ch!=NULL) free(str->ch);
	str->ch = (char *)malloc((str1->length+str2->length)*sizeof(char));
	if(str->ch==NULL) exit(-1);
	for(int i = 0 ; i< str1->length ; i++){
		str->ch[i] = str1->ch[i];
	}
	for(int j = 0 ; j< str2->length ; j++){
		str->ch[j+str1->length] = str2->ch[j];
	}
	str->length = str1->length+str2->length;
}
//subString
void subString(HString *str,HString *str1,int start ,int end){
	if(start<0 || start > str1->length || end < 0 || end >str1->length || end<=start) exit(-1);
	if(str1->ch == NULL) exit(-1);
	str->ch = (char*)malloc((end-start)*sizeof(char));
	if(str->ch==NULL) exit(-1);
	for(int i = 0 ; i < end-start ; i++){
		str->ch[i] = str1->ch[i+start];
	}
	str->length = end-start;
}
//遍历打印字符串
void watch(HString *str){
	for(int i = 0 ; i < str->length ; i++)printf("%c\n",str->ch[i]);
}
int main(void){
	HString str1;
	HString str2;
	HString str3;
	HString str4;
	char chars1[] ={'A','X','W','d','e','2'};
	char chars2[] ={'A','N','c','d','e','2'};
	StrAssign(&str1,chars1,sizeof(chars1));
	StrAssign(&str2,chars2,sizeof(chars2));
	concat(&str3,&str1,&str2);
	//printf("%d\n",str3.length);
	//watch(&str1);
	//watch(&str2);
	//watch(&str3);
	subString(&str4,&str3,0,8);
	watch(&str4);
	//printf("%d\n",sizeof(chars));
	//printf("%d\n",str.length);
	//printf("%d\n",strLength(&str));
	return 0;
}