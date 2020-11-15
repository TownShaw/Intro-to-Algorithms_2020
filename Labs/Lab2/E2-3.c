#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct AllocNode
{
	int Left;	//记录左端点 
	int Right;	//记录右端点
	struct AllocNode *LChild;
	struct AllocNode *RChild;
}AllocNode;

typedef struct AllocTree
{
	AllocNode *pRoot;
}AllocTree;

AllocTree *initTree()
{
	AllocTree *Tree = (AllocTree *)malloc(sizeof(AllocTree));
	Tree->pRoot = NULL;
	return Tree;
}

AllocNode *CreateNode(int Left, int Right)
{
	AllocNode *pNew = (AllocNode *)malloc(sizeof(AllocNode));
	pNew->Left = Left;
	pNew->Right = Right;
	pNew->LChild = NULL;
	pNew->RChild = NULL;
	return pNew;
}

int AllocMem(AllocTree *Tree, int Left, int Right)
{//在 Array 中 找到 Point 待插入的位置, 若找到的位置不能分配则返回 NIL
	AllocNode *pTemp = Tree->pRoot;
	AllocNode *pPre = NULL;
	while (pTemp != NULL)
	{
		pPre = pTemp;
		if (Right < pTemp->Left)
		{//待插入区间在 pTemp 左边
			pTemp = pTemp->LChild;
		}
		else if (Left > pTemp->Right)
		{//待插入区间在 pTemp 右边
			pTemp = pTemp->RChild;
		}
		else
		{//发生重叠
			return FALSE;
		}
	}
	AllocNode *pNew = CreateNode(Left, Right);
	if (Tree->pRoot == NULL)
	{
		Tree->pRoot = pNew;
	}
	else if (Right < pPre->Left)
	{
		pPre->LChild = pNew;
	}
	else
	{
		pPre->RChild = pNew;
	}
	
	return TRUE;
}

void Free_AllocArea(AllocNode *pRoot)
{
	if (pRoot != NULL)
	{
		Free_AllocArea(pRoot->LChild);
		Free_AllocArea(pRoot->RChild);
		free(pRoot);
	}
}

int main()
{
	int n = 0;	//分配 n 次
	scanf("%d", &n);

	AllocTree *Tree = initTree();

	for (int i = 0; i < n; i++)
	{
		int Left = 0;
		int Right = 0;
		scanf("%d", &Left);
		scanf("%d", &Right);

		int stus = AllocMem(Tree, Left, Right);

		if (stus == FALSE)	//分配失败
		{
			printf("-1\n");
		}
		else
		{
			printf("0\n");
		}
	}

	Free_AllocArea(Tree->pRoot);
	return 0;
}