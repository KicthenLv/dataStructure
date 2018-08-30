// ƽ���������ʵ��
#include <queue>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

//�����б�ڵ����Ҳ����ȵĳ���
#define LH 1
#define RH -1
#define EH 0

//����AVL�Ľṹ
typedef struct AVLNode{
	int Key; //�ؼ�����
	int BF; //ƽ������
	struct AVLNode *lchild,*rchild; //���ҽڵ���
}*AVLTree;

//ʵ���������������ķ�������ƽ�������ʱ��Ҫ�õ�

//����
void R_Rotate(AVLTree &T){
	//�������ĸ��ڵ������������������������ҽڵ����ӵ�ԭ���ڵ���
	AVLNode *L = T->lchild;
	T->lchild = L->rchild;
	L->rchild = T; 
	T = L;//�����ڵ���Ϊ�µĸ��ڵ�
}

//��������������������
void L_Rotate(AVLTree &T){
	//�����ڵ�����ӽڵ���Ϊԭ���ڵ㣬���ӽڵ�����ӽڵ�Ϊԭ���ڵ㣬���ӽڵ����������Ϊԭ���ڵ�������
	AVLNode *R = T->rchild;
	T->rchild = R->lchild;
	R->lchild = T;
	T = R;//�����ڵ���Ϊ�µĸ��ڵ�
}

//ʵ����ƽ�ⷽ��
/*
  ���ڵ����������ȸ�����������Ҫƽ���ǵ��ô˷���
  ��������������������ж���ֱ������ת�����������
*/
void LeftBalance(AVLTree &L){
	//�����������
	AVLNode *lchild = L->lchild;
	//����ƽ������
	switch(lchild->BF){
		//�������߸�����������
	case EH:
		L->lchild->BF = -1;
		R_Rotate(L);
		break;
	case LH:
		L->BF = lchild->BF = EH;//����ƽ������
		R_Rotate(L); //�����˽ڵ�;
		break;
		//������ұ߸�����������Ȼ���������˽ڵ���ҽڵ㣬�������˽ڵ�
	case RH:
		AVLNode *rchild = L->rchild;
		//���ƽ������
		switch(rchild->BF){
			/* �޸�rchild�������ӵ�ƽ������ */
            case LH: 
                L->BF=RH;
                lchild->BF=EH;
                break;
            case EH: 
                L->BF = lchild->BF = EH;
                break;
            case RH: 
                L->BF = EH ;
				lchild->BF = LH;
                break;
		}
		//�����µĸ��ڵ��ƽ������
		rchild->BF = EH; 
		//������������
		L_Rotate(L->lchild);
		R_Rotate(L);
		break;
	}
}
	//ʵ����ƽ�ⷽ��
/*
  ���ڵ����������ȸ�����������Ҫƽ���ǵ��ô˷���
  ��������������������ж���ֱ������ת�������Һ���
*/
void RightBalance(AVLTree &R){
	//�����������
	AVLNode *rchild = R->rchild;
	//����ƽ������
	switch(rchild->BF){
		//�����ڵ�ƽ�⣬ֱ������
	case EH:
		rchild->BF = 1;
		L_Rotate(R);
		break;
		//�������߸�����������
	case RH:
		R->BF = rchild->BF = EH;//����ƽ������
		L_Rotate(R); //�����˽ڵ�;
		break;
		//�������߸�����������Ȼ���������˽ڵ����ڵ㣬�������˽ڵ�
	case LH:
		AVLNode *lchild = rchild->lchild;
		//���ƽ������
		switch(lchild->BF){
			/* �޸�rchild�������ӵ�ƽ������ */
            case LH: 
                R->BF=EH;
                rchild->BF=RH;
                break;
            case EH: 
                R->BF = rchild->BF = EH;
                break;
            case RH: 
                R->BF = LH ;
				rchild->BF = EH;
                break;
		}
		//�����µĸ��ڵ��ƽ������
		lchild->BF = EH; 
		//������������
		R_Rotate(R->rchild);
		L_Rotate(R);
		break;
	}
}
/*  ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */
/*  ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
/*  ʧȥƽ�⣬����ƽ����ת������������taller��ӳT������� */
//ʵ�ֲ���ڵ����
bool AVLInsert(AVLTree &T,int key, bool &taller){
	if(T == NULL){
		/*  �����½�㣬�������ߡ�����tallerΪTRUE */
        T = (AVLTree)malloc(sizeof(AVLNode));
        T->Key = key ; 
        T->lchild = T->rchild = NULL; 
        T->BF = EH;
        taller = true;
		return true;
	}
	else {
		//���������ͬ�Ľڵ�
		if(key == T->Key){
			return false;
		}
		//key���ڵ�ǰ�ڵ��key
		if(T->Key > key){
			if(!AVLInsert(T->lchild,key,taller)){
				return false;
			}
			//���ʧȥƽ��
			if(taller){
				//�жϲ���ڵ��ƽ������
				switch(T->BF){
					//������������
				case LH:
					//������ƽ����ƽ��˽ڵ�
					LeftBalance(T);
					taller = false;
					break;
					//ԭ�����
				case EH:
					taller = true;
					T->BF = LH;
					break;
					//������ƫ��,��������ӽڵ����ߵȸ�
				case RH:
					T->BF = EH;
					taller = false;
					break;
				}
			}
		}else{
			//keyС�ڵ�ǰ�ڵ��key
			if(!AVLInsert(T->rchild,key,taller)){
				return false;
			}
			
			if(taller){
				switch(T->BF)                 /*  ���T��ƽ��� */
                {
                    case LH:                        /*  ԭ�����������������ߣ������������ȸ� */
                        T->BF = EH; 
                        taller = false;  
                        break;
                    case EH:                        /*  ԭ�����������ȸߣ��������������߶�ʹ������  */
                        T->BF = RH; 
                        taller = true; 
                        break;
                    case RH:                        /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
                        RightBalance(T); 
                        taller=false; 
                        break;
                }
				
			}
		}
	}
	return true; //����ɹ�
}
//ɾ���ڵ����
bool AVLDelete(AVLTree &T,int key,bool &shorter){
	if(T == NULL) return false;
	if(key == T->Key){
		//ɾ����ؽڵ�
		if(T->lchild == NULL){
			//��������Ϊ�գ���ֱ�ӽ����������ӵ����ڵ���
			AVLNode *t = T;
			T = T->rchild;
			free(t);
			shorter = true;
		}
		else if(T->rchild == NULL){
			//��������Ϊ�գ���ֱ�ӽ����������ӵ����ڵ���
			AVLNode *t = T;
			T = T->lchild;
			free(t);
			shorter = true;
		}
		else {
			//��������������Ϊ��
			AVLNode *maxNode = T->lchild;
			//�ҵ���������ֵ����һ���ڵ�
			while(maxNode->rchild != NULL) maxNode = maxNode->rchild;
			//�����ֵ�ڵ�����ڵ�ֵ����
			T->Key = maxNode->Key;
			//ɾ��ֵ���ڵ�
			AVLDelete(T->lchild,T->Key,shorter);
		}
	}
	//���ֵ���ڸ��ڵ�key
	else if(key > T->Key){
		if(!AVLDelete(T->rchild,key,shorter)){
			return false;
		}
		//�ж�shorter
		if(shorter){
			//�ж�ƽ������
			switch(T->BF){
			case LH:
				//��ƽ��ڵ�
				LeftBalance(T);
				if(T->lchild->BF == EH)  //ע�������ͼ˼��һ�� 
                    shorter = false;
                else
                    shorter = true;
                break;
            case EH:
                T->BF = LH;
                shorter = false;
                break;
            case RH:
                T->BF = EH;
                shorter = true;
                break;
			
			}
		}
	}
	//���ֵС�ڸ��ڵ�key
	else {
		if(!AVLDelete(T->lchild, key, shorter))
        {
            return false;
        }
        if(shorter)
        {
            switch(T->BF)
            {
            case LH:
                T->BF = EH;
                shorter = true;
                break;
            case EH:
                T->BF = RH;
                shorter = false;
                break;
            case RH:
                RightBalance(T);        //��ƽ�⴦��
                if(T->rchild->BF == EH)    //ע�������ͼ˼��һ�� 
                    shorter = false;
                else
                    shorter = true;
                break;
            }
        }
	}

}
//�������
void InOrderTraverse(AVLTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%d  ", T->Key);
        InOrderTraverse(T->rchild);
    }
}
//��α���
void LevelTraverse(AVLTree T,int heith){
	heith = 0;
	if(T == NULL) return;
	//ʹ�ö��и�������
	queue<AVLNode*> que;
	que.push(T);
	while(!que.empty()){
		AVLNode *temp = que.front();
		que.pop();
		printf("%d  ",temp->Key);
		if(temp->lchild != NULL) que.push(temp->lchild);
		if(temp->rchild != NULL) que.push(temp->rchild);
	}
}
int main(void){
	int i;
    int a[10]={3,2,1,4,5,6,9};
    AVLTree T=NULL;
    bool taller;
    for(i=0;i<7;i++)
    {
        AVLInsert(T,a[i],taller);
    }
    //printf("�����������ƽ����:\n");
    //InOrderTraverse(T);
	printf("��α�������ƽ����:\n");
	LevelTraverse(T);
    printf("\n");
    printf("ɾ�����Ԫ�ز�α���:\n");
    bool shorter;
    //AVLDelete(T, 9, shorter);
	//LevelTraverse(T);
	//AVLDelete(T, 5, shorter);
	//AVLDelete(T, 6, shorter);
//printf("\n");
//	LevelTraverse(T);
    //InOrderTraverse(T);
    printf("\n");
	//printf("%d\n",T->rchild->BF);
    return 0;
}