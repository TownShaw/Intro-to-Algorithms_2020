#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 2

typedef struct BiTree
{
	int Time;
	int Bigger_Than;	//在该子树中小于该节点 Time 的节点个数
	struct BiTree *Parent;
	struct BiTree *LChild;
	struct BiTree *RChild;
}BiTreeNode;

BiTreeNode* CreateNode(int Time)
{
	BiTreeNode *pNew = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	pNew->Time = Time;
	pNew->Bigger_Than = 0;
	pNew->Parent = NULL;
	pNew->LChild = NULL;
	pNew->RChild = NULL;
	return pNew;
}

int getMin_k(BiTreeNode *pRoot, int k)
{//得到第 k 小的 Time
	if (pRoot == NULL)	//根节点为空, 未找到, 返回 -1
	{
		return 0;
	}
	else if (pRoot->Bigger_Than + 1 == k)
	{
		return pRoot->Time;
	}
	else if (pRoot->Bigger_Than + 1 > k)
	{
		return getMin_k(pRoot->LChild, k);
	}
	else
	{
		return getMin_k(pRoot->RChild, k - (pRoot->Bigger_Than + 1));
	}
}

void Transplant(BiTreeNode **pRoot, BiTreeNode *pNew, BiTreeNode *pOld)
{//在 pRoot 为根的树中将以 pOld 为根的子树替换为以 pNew 为根的子树

}

void Insert(BiTreeNode *pRoot, int Time)	//通过 Insert() 操作维护一个二叉搜索树
{
	BiTreeNode *pTemp = pRoot;
	BiTreeNode *pPre = pRoot;	//pPre 为 pTemp 父节点
	while(pTemp != NULL)
	{	//找到待插入的位置, 总是插在叶节点处
		if (Time <= pTemp->Time)
		{
			pPre = pTemp;
			pTemp->Bigger_Than++;
			pTemp = pPre->LChild;
		}
		else
		{
			pPre = pTemp;
			pTemp = pPre->RChild;
		}
	}

	BiTreeNode *pNew = CreateNode(Time);	//新建待插入节点
	if (Time <= pPre->Time)	//插入新建节点 pNew
	{
		pPre->LChild = pNew;
		pNew->Parent = pPre;
	}
	else
	{
		pPre->RChild = pNew;
		pNew->Parent = pPre;
	}
}

BiTreeNode *__Find_Min(BiTreeNode *pRoot)
{//!!! 仅可用于 Delete() 函数内部 !!!
	BiTreeNode *pTemp = pRoot;
	while (pTemp->LChild != NULL)
	{
		pTemp->Bigger_Than--;
		pTemp = pTemp->LChild;
	}
	return pTemp;
}

void Delete(BiTreeNode **pRoot, int Time)
{
	BiTreeNode *pTemp = *pRoot;
	while (pTemp->Time != Time)
	{
		if (pTemp->Time > Time)
		{
			pTemp->Bigger_Than--;
			pTemp = pTemp->LChild;
		}
		else
		{
			pTemp = pTemp->RChild;
		}
	}
	if (pTemp->LChild == NULL && pTemp->RChild == NULL)
	{//pTemp 为叶节点
		if (pTemp == *pRoot)
		{//根节点直接 free
			free(pTemp);
			*pRoot = NULL;
		}
		else if (pTemp == pTemp->Parent->LChild)
		{
			pTemp->Parent->LChild = NULL;
			free(pTemp);
		}
		else
		{
			pTemp->Parent->RChild = NULL;
			free(pTemp);
		}
	}
	else if (pTemp->LChild != NULL && pTemp->RChild != NULL)
	{
		BiTreeNode *pMin = __Find_Min(pTemp->RChild);
		pTemp->Time = pMin->Time;
		if (pMin->RChild == NULL)
		{//pMin->LChild 必为 NULL
			if (pMin == pMin->Parent->LChild)
			{
				pMin->Parent->LChild = NULL;
				free(pMin);
			}
			else
			{
				pMin->Parent->RChild = NULL;
				free(pMin);
			}
		}
		else
		{
			if (pMin == pMin->Parent->LChild)
			{
				pMin->Parent->LChild = pMin->RChild;
				pMin->RChild->Parent = pMin->Parent;
				free(pMin);
			}
			else
			{
				pMin->Parent->RChild = pMin->RChild;
				pMin->RChild->Parent = pMin->Parent;
				free(pMin);
			}
		}
	}
	else if (pTemp->LChild != NULL)
	{
		if (pTemp == *pRoot)
		{
			(*pRoot) = (*pRoot)->LChild;
			(*pRoot)->Parent = NULL;
			free(pTemp);
		}
		else if (pTemp == pTemp->Parent->LChild)
		{
			pTemp->Parent->LChild = pTemp->LChild;
			pTemp->LChild->Parent = pTemp->Parent;
			free(pTemp);
		}
		else
		{
			pTemp->Parent->RChild = pTemp->LChild;
			pTemp->LChild->Parent = pTemp->Parent;
			free(pTemp);
		}
	}
	else
	{//pTemp->RChild != NULL
		if (pTemp == *pRoot)
		{
			(*pRoot) = (*pRoot)->RChild;
			(*pRoot)->Parent = NULL;
			free(pTemp);
		}
		else if (pTemp == pTemp->Parent->LChild)
		{
			pTemp->Parent->LChild = pTemp->RChild;
			pTemp->RChild->Parent = pTemp->Parent;
			free(pTemp);
		}
		else
		{
			pTemp->Parent->RChild = pTemp->RChild;
			pTemp->RChild->Parent = pTemp->Parent;
			free(pTemp);
		}
	}
}

void Free_BiTree(BiTreeNode *pRoot)	//后序遍历释放整棵树
{
	if (pRoot == NULL)
	{
		return;
	}
	Free_BiTree(pRoot->LChild);
	Free_BiTree(pRoot->RChild);
	free(pRoot);
}

void Pre_Order_Traverse(BiTreeNode *pRoot)
{
	if (pRoot != NULL)
	{
		printf("%d: %d\t", pRoot->Time, pRoot->Bigger_Than);
		Pre_Order_Traverse(pRoot->LChild);
		Pre_Order_Traverse(pRoot->RChild);
	}
}

void In_Order_Traverse(BiTreeNode *pRoot)
{
	if (pRoot != NULL)
	{
		In_Order_Traverse(pRoot->LChild);
		printf("%d: %d\t", pRoot->Time, pRoot->Bigger_Than);
		In_Order_Traverse(pRoot->RChild);
	}
}

int main()
{
	int n = 0;	//n条指令
	char Ins[MAX_LENGTH];	//指令符
	BiTreeNode *pRoot = NULL;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		memset(Ins, '\0', MAX_LENGTH);
		scanf("%s", &Ins);
		int Time = 0;
		int k = 0;
		int num = 0;	//用于 getMin_k() 计数
		switch (Ins[0])
		{
		case 'I':
			scanf("%d", &Time);
			if (pRoot == NULL)
			{
				pRoot = CreateNode(Time);
			}
			else
			{
				Insert(pRoot, Time);
			}
			break;
		
		case 'D':
			scanf("%d", &Time);
			Delete(&pRoot, Time);
			break;

		case 'K':
			scanf("%d", &k);
			printf("%d\n", getMin_k(pRoot, k));
			break;

		default:
			printf("Error! No such Ins!");
			break;
		}
	}
	Pre_Order_Traverse(pRoot);
	printf("\n");
	In_Order_Traverse(pRoot);

	Free_BiTree(pRoot);
	return 0;
}