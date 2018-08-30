#include <stdio.h>    
#include <stdlib.h>   
 
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100                     /* �洢�ռ��ʼ������ */
 
typedef int Status;                     /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
 
 
/* �������Ķ���������ṹ���� */
typedef  struct BitNode                 /* ���ṹ */
{
    int data;                           /* ������� */
    int bf;                             /*  ����ƽ������ */
    struct BitNode *lchild, *rchild;    /* ���Һ���ָ�� */
} BitNode, *BiTree;
 
 
/* ����pΪ���Ķ������������������� */
/* ����֮��pָ���µ�������㣬����ת����֮ǰ���������ĸ���� */
//����-˳ʱ����ת(��LL�;͵öԸ����������ת)
void R_Rotate(BiTree *P)
{ 
    BiTree L;
    L=(*P)->lchild;                      /*  Lָ��P������������� */
    (*P)->lchild=L->rchild;               /*  L���������ҽ�ΪP�������� */
    L->rchild=(*P);
    *P=L;                               /*  Pָ���µĸ���� */
}
 
/* ����PΪ���Ķ������������������� */
/* ����֮��Pָ���µ�������㣬����ת����֮ǰ���������ĸ����0  */
//����-��ʱ����ת(��RR�;͵öԸ����������ת)
void L_Rotate(BiTree *P)
{ 
    BiTree R;
    R = (*P)->rchild;                    /* Rָ��P������������� */
    (*P)->rchild = R->lchild;         /* R���������ҽ�ΪP�������� */
    R->lchild = (*P);
    *P = R;                             /* Pָ���µĸ���� */
}
 
#define LH +1                           /*  ��� */ 
#define EH 0                            /*  �ȸ� */ 
#define RH -1                           /*  �Ҹ� */ 
 
/*  ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���� */
/*  ���㷨����ʱ��ָ��Tָ���µĸ���� */
void LeftBalance(BiTree *T)
{ 
    BiTree L,Lr;
    L = (*T)->lchild;                    /*  Lָ��T������������� */
    switch(L->bf)
    { 
        /* ���T����������ƽ��ȣ�������Ӧƽ�⴦�� */
        case LH:                        /* �½�������T�����ӵ��������ϣ�Ҫ������������ */
            (*T)->bf=L->bf=EH;
            R_Rotate(T);
            break;
        case RH:                        /* �½�������T�����ӵ��������ϣ�Ҫ��˫������ */ //
            Lr=L->rchild;                /* Lrָ��T�����ӵ��������� */
            switch(Lr->bf)
            {   
                /* �޸�T�������ӵ�ƽ������ */
                case LH: 
                    (*T)->bf=RH;
                    L->bf=EH;
                    break;
                case EH: 
                    (*T)->bf=L->bf=EH;
                    break;
                case RH: 
                    (*T)->bf=EH;
                    L->bf=LH;
                    break;
            }
            Lr->bf=EH;
            L_Rotate(&(*T)->lchild); /* ��T��������������ƽ�⴦�� */
            R_Rotate(T);                /* ��T������ƽ�⴦�� */
    }
}
 
/*  ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���� */
/*  ���㷨����ʱ��ָ��Tָ���µĸ���� */
void RightBalance(BiTree *T)
{ 
    BiTree R,Rl;
    R=(*T)->rchild;                      /*  Rָ��T������������� */
    switch(R->bf)
    { 
        /*  ���T����������ƽ��ȣ�������Ӧƽ�⴦�� */
        case RH:                        /*  �½�������T���Һ��ӵ��������ϣ�Ҫ������������ */
            (*T)->bf=R->bf=EH;
            L_Rotate(T);
            break;
        case LH:                        /*  �½�������T���Һ��ӵ��������ϣ�Ҫ��˫������ */ //��С��ƽ�����ĸ����Ϊ�������Һ���Ϊ��
            Rl=R->lchild;                /*  Rlָ��T���Һ��ӵ��������� */
            switch(Rl->bf)
            { 
                /*  �޸�T�����Һ��ӵ�ƽ������ */
                case RH: 
                    (*T)->bf=LH;
                    R->bf=EH;
                    break;
                case EH: 
                    (*T)->bf=R->bf=EH;
                    break;
                case LH: 
                    (*T)->bf=EH;
                    R->bf=RH;
                    break;
            }
            Rl->bf=EH;
            R_Rotate(&(*T)->rchild); /*  ��T��������������ƽ�⴦�� */
            L_Rotate(T);                /*  ��T������ƽ�⴦�� */
    }
}
 
/*  ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */
/*  ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
/*  ʧȥƽ�⣬����ƽ����ת������������taller��ӳT������� */
Status InsertAVL(BiTree *T,int e,Status *taller)
{  
    if(!*T)
    { 
        /*  �����½�㣬�������ߡ�����tallerΪTRUE */
        *T=(BiTree)malloc(sizeof(BitNode));
        (*T)->data=e; 
        (*T)->lchild=(*T)->rchild=NULL; 
        (*T)->bf=EH;
        *taller=TRUE;
    }
    else
    {
        if (e==(*T)->data)
        { 
            /*  �����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
            *taller=FALSE; 
            return FALSE;
        }
        if (e<(*T)->data)
        { 
            /*  Ӧ������T���������н������� */
            if(!InsertAVL(&(*T)->lchild, e, taller)) /*  δ���� */
                return FALSE;
            if(*taller)                             /*   �Ѳ��뵽T�����������������������ߡ� */
                switch((*T)->bf)                 /*  ���T��ƽ��� */
                {
                    case LH:                        /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
                        LeftBalance(T); 
                        *taller=FALSE; 
                        break;
                    case EH:                        /*  ԭ�����������ȸߣ��������������߶�ʹ������ */
                        (*T)->bf=LH; 
                        *taller=TRUE; 
                        break;
                    case RH:                        /*  ԭ�����������������ߣ������������ȸ� */ 
                        (*T)->bf=EH; 
                        *taller=FALSE; 
                        break;
                }
        }
        else
        { 
            /*  Ӧ������T���������н������� */
            if(!InsertAVL(&(*T)->rchild,e, taller)) /*  δ���� */
            {
                return FALSE;
            }
            if(*taller)                             /*  �Ѳ��뵽T���������������������ߡ� */
            {
                switch((*T)->bf)                 /*  ���T��ƽ��� */
                {
                    case LH:                        /*  ԭ�����������������ߣ������������ȸ� */
                        (*T)->bf=EH; 
                        *taller=FALSE;  
                        break;
                    case EH:                        /*  ԭ�����������ȸߣ��������������߶�ʹ������  */
                        (*T)->bf=RH; 
                        *taller=TRUE; 
                        break;
                    case RH:                        /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
                        RightBalance(T); 
                        *taller=FALSE; 
                        break;
                }
            }
        }
    }
    return TRUE;
}
 
 
/* 
����ƽ��Ķ���������t�д��ں�e����ͬ�ؼ��ֵĽ�㣬��ɾ��֮ 
������TRUE�����򷵻�FALSE������ɾ����ʹ���������� 
ʧȥƽ�⣬����ƽ����ת������������shorter��ӳt�䰫���
*/
int deleteAVL(BiTree *t, int key, int *shorter)
{
    if(*t == NULL)                                      //�����ڸ�Ԫ�� 
    {
        return FALSE;                                   //ɾ��ʧ�� 
    }
    else if(key == (*t)->data)                           //�ҵ�Ԫ�ؽ��
    {
        BitNode *q = NULL;
        if((*t)->lchild == NULL)                     //������Ϊ�� 
        {
            q = (*t);
            (*t) = (*t)->rchild;
            free(q);
            *shorter = TRUE;
        }
        else if((*t)->rchild == NULL)                    //������Ϊ�� 
        {
            q = (*t);
            (*t) = (*t)->lchild;
            free(q);
            *shorter = TRUE;
        }
        else                                            //��������������,
        {
            q = (*t)->lchild;
            while(q->rchild)
            {
                q = q->rchild;
            }
            (*t)->data = q->data;
            deleteAVL(&(*t)->lchild, q->data, shorter);   //���������еݹ�ɾ��ǰ����� 
        }
    }
    else if(key < (*t)->data)                         //�������м������� 
    {
        if(!deleteAVL(&(*t)->lchild, key, shorter))
        {
            return FALSE;
        }
        if(*shorter)
        {
            switch((*t)->bf)
            {
            case LH:
                (*t)->bf = EH;
                *shorter = TRUE;
                break;
            case EH:
                (*t)->bf = RH;
                *shorter = FALSE;
                break;
            case RH:
                RightBalance(&(*t));        //��ƽ�⴦��
                if((*t)->rchild->bf == EH)    //ע�������ͼ˼��һ�� 
                    *shorter = FALSE;
                else
                    *shorter = TRUE;
                break;
            }
        }
    }
    else                                //�������м������� 
    {
        if(!deleteAVL(&(*t)->rchild, key, shorter))
        {
            return FALSE;
        }
        if(shorter)
        {
            switch((*t)->bf)
            {
            case LH:
                LeftBalance(&(*t));         //��ƽ�⴦�� 
                if((*t)->lchild->bf == EH)  //ע�������ͼ˼��һ�� 
                    *shorter = FALSE;
                else
                    *shorter = TRUE;
                break;
            case EH:
                (*t)->bf = LH;
                *shorter = FALSE;
                break;
            case RH:
                (*t)->bf = EH;
                *shorter = TRUE;
                break;
            }
        }
    }
    return TRUE;
}
 
void InOrderTraverse(BiTree t)
{
    if(t)
    {
        InOrderTraverse(t->lchild);
        printf("%d  ", t->data);
        InOrderTraverse(t->rchild);
    }
}
 
 
int main(void)
{    
    int i;
    int a[10]={3,2,1,4,5,6,7,10,9,8};
    BiTree T=NULL;
    Status taller;
    for(i=0;i<10;i++)
    {
        InsertAVL(&T,a[i],&taller);
    }
    printf("�����������ƽ����:\n");
    InOrderTraverse(T);
    printf("\n");
    printf("ɾ�����Ԫ��5���������:\n");
    int shorter;
    deleteAVL(&T, 5, &shorter);
    InOrderTraverse(T);
    printf("\n");
    return 0;
}