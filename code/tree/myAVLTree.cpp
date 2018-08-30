// 平衡二叉树的实现
#include <queue>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

//定义判别节点左右层次深度的常量
#define LH 1
#define RH -1
#define EH 0

//定义AVL的结构
typedef struct AVLNode{
	int Key; //关键字域
	int BF; //平衡因子
	struct AVLNode *lchild,*rchild; //左右节点域
}*AVLTree;

//实现子树左旋右旋的方法，在平衡二叉树时需要用到

//右旋
void R_Rotate(AVLTree &T){
	//将子树的根节点与左子树交换，左子树的右节点连接到原根节点上
	AVLNode *L = T->lchild;
	T->lchild = L->rchild;
	L->rchild = T; 
	T = L;//将根节点置为新的根节点
}

//左旋操作，与右旋类似
void L_Rotate(AVLTree &T){
	//将根节点的右子节点作为原根节点，右子节点的左子节点为原根节点，右子节点的左子树作为原根节点右子树
	AVLNode *R = T->rchild;
	T->rchild = R->lchild;
	R->lchild = T;
	T = R;//将根节点置为新的根节点
}

//实现左平衡方法
/*
  当节点的左子树深度高于右子树需要平衡是调用此方法
  根据左子树的情况继续判断是直接右旋转还是先左后右
*/
void LeftBalance(AVLTree &L){
	//获的其左子树
	AVLNode *lchild = L->lchild;
	//检查的平衡因子
	switch(lchild->BF){
		//如果是左边更深，则调用右旋
	case EH:
		L->lchild->BF = -1;
		R_Rotate(L);
		break;
	case LH:
		L->BF = lchild->BF = EH;//重置平衡因子
		R_Rotate(L); //右旋此节点;
		break;
		//如果是右边更深，则重置深度然后先左旋此节点的右节点，在左旋此节点
	case RH:
		AVLNode *rchild = L->rchild;
		//检查平衡因子
		switch(rchild->BF){
			/* 修改rchild及其左孩子的平衡因子 */
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
		//重置新的根节点的平衡因子
		rchild->BF = EH; 
		//先左旋再右旋
		L_Rotate(L->lchild);
		R_Rotate(L);
		break;
	}
}
	//实现右平衡方法
/*
  当节点的右子树深度高于左子树需要平衡是调用此方法
  根据右子树的情况继续判断是直接左旋转还是先右后左
*/
void RightBalance(AVLTree &R){
	//获的其右子树
	AVLNode *rchild = R->rchild;
	//检查的平衡因子
	switch(rchild->BF){
		//若果节点平衡，直接左旋
	case EH:
		rchild->BF = 1;
		L_Rotate(R);
		break;
		//如果是左边更深，则调用右旋
	case RH:
		R->BF = rchild->BF = EH;//重置平衡因子
		L_Rotate(R); //右旋此节点;
		break;
		//如果是左边更深，则重置深度然后先右旋此节点的左节点，在右旋此节点
	case LH:
		AVLNode *lchild = rchild->lchild;
		//检查平衡因子
		switch(lchild->BF){
			/* 修改rchild及其左孩子的平衡因子 */
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
		//重置新的根节点的平衡因子
		lchild->BF = EH; 
		//先右旋再左旋
		R_Rotate(R->rchild);
		L_Rotate(R);
		break;
	}
}
/*  若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
/*  数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
/*  失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。 */
//实现插入节点操作
bool AVLInsert(AVLTree &T,int key, bool &taller){
	if(T == NULL){
		/*  插入新结点，树“长高”，置taller为TRUE */
        T = (AVLTree)malloc(sizeof(AVLNode));
        T->Key = key ; 
        T->lchild = T->rchild = NULL; 
        T->BF = EH;
        taller = true;
		return true;
	}
	else {
		//如果存在相同的节点
		if(key == T->Key){
			return false;
		}
		//key大于当前节点的key
		if(T->Key > key){
			if(!AVLInsert(T->lchild,key,taller)){
				return false;
			}
			//如果失去平衡
			if(taller){
				//判断插入节点的平衡因子
				switch(T->BF){
					//如果是左边深了
				case LH:
					//调用左平衡来平衡此节点
					LeftBalance(T);
					taller = false;
					break;
					//原本相等
				case EH:
					taller = true;
					T->BF = LH;
					break;
					//右子树偏高,左子树添加节点两边等高
				case RH:
					T->BF = EH;
					taller = false;
					break;
				}
			}
		}else{
			//key小于当前节点的key
			if(!AVLInsert(T->rchild,key,taller)){
				return false;
			}
			
			if(taller){
				switch(T->BF)                 /*  检查T的平衡度 */
                {
                    case LH:                        /*  原本左子树比右子树高，现左、右子树等高 */
                        T->BF = EH; 
                        taller = false;  
                        break;
                    case EH:                        /*  原本左、右子树等高，现因右子树增高而使树增高  */
                        T->BF = RH; 
                        taller = true; 
                        break;
                    case RH:                        /*  原本右子树比左子树高，需要作右平衡处理 */
                        RightBalance(T); 
                        taller=false; 
                        break;
                }
				
			}
		}
	}
	return true; //插入成功
}
//删除节点操作
bool AVLDelete(AVLTree &T,int key,bool &shorter){
	if(T == NULL) return false;
	if(key == T->Key){
		//删除相关节点
		if(T->lchild == NULL){
			//若左子树为空，则直接将右子树连接到父节点上
			AVLNode *t = T;
			T = T->rchild;
			free(t);
			shorter = true;
		}
		else if(T->rchild == NULL){
			//若右子树为空，则直接将左子树连接到父节点上
			AVLNode *t = T;
			T = T->lchild;
			free(t);
			shorter = true;
		}
		else {
			//若左右子树都不为空
			AVLNode *maxNode = T->lchild;
			//找到左子树中值最大的一个节点
			while(maxNode->rchild != NULL) maxNode = maxNode->rchild;
			//将最大值节点与根节点值互换
			T->Key = maxNode->Key;
			//删除值最大节点
			AVLDelete(T->lchild,T->Key,shorter);
		}
	}
	//如果值大于根节点key
	else if(key > T->Key){
		if(!AVLDelete(T->rchild,key,shorter)){
			return false;
		}
		//判断shorter
		if(shorter){
			//判断平衡因子
			switch(T->BF){
			case LH:
				//左平衡节点
				LeftBalance(T);
				if(T->lchild->BF == EH)  //注意这里，画图思考一下 
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
	//如果值小于根节点key
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
                RightBalance(T);        //右平衡处理
                if(T->rchild->BF == EH)    //注意这里，画图思考一下 
                    shorter = false;
                else
                    shorter = true;
                break;
            }
        }
	}

}
//中序遍历
void InOrderTraverse(AVLTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%d  ", T->Key);
        InOrderTraverse(T->rchild);
    }
}
//层次遍历
void LevelTraverse(AVLTree T,int heith){
	heith = 0;
	if(T == NULL) return;
	//使用队列辅助遍历
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
    //printf("中序遍历二叉平衡树:\n");
    //InOrderTraverse(T);
	printf("层次遍历二叉平衡树:\n");
	LevelTraverse(T);
    printf("\n");
    printf("删除结点元素层次遍历:\n");
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