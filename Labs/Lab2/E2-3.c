#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct AllocNode
{
	int Left;	//记录左端点 
	int Right;	//记录右端点
	struct AllocNode *pNext;
}AllocNode;

typedef struct AllocList
{
	AllocNode *pHead;
	int Length;
}AllocList;

AllocList *initList()
{
	AllocList *List = (AllocList *)malloc(sizeof(AllocList));
	List->pHead = (AllocNode *)malloc(sizeof(AllocNode));
	List->pHead->Left = -1;
	List->pHead->Right = -1;
	List->pHead->pNext = NULL;	//初始化头节点
	List->Length = 0;
	return List;
}

AllocNode *CreateNode(int Left, int Right)
{
	AllocNode *pNew = (AllocNode *)malloc(sizeof(AllocNode));
	pNew->Left = Left;
	pNew->Right = Right;
	pNew->pNext = NULL;
	return pNew;
}

int AllocMem(AllocList *List, int Left, int Right)
{//在 Array 中 找到 Point 待插入的位置, 若找到的位置不能分配则返回 NIL
	AllocNode *pTemp = List->pHead;
	while (pTemp->pNext != NULL)
	{
		if (Right < pTemp->pNext->Left)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	if (pTemp == List->pHead || Left > pTemp->Right)
	{
		AllocNode *pNew = CreateNode(Left, Right);	//插入分配区域
		pNew->pNext = pTemp->pNext;
		pTemp->pNext = pNew;
		List->Length++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void Free_List(AllocList *List)
{
	AllocNode *pTemp = List->pHead;
	while (pTemp != NULL)
	{
		pTemp = pTemp->pNext;
		free(List->pHead);
		List->pHead = pTemp;
	}
	free(List);
}

int main()
{
	int n = 0;	//分配 n 次
	scanf("%d", &n);

	AllocList *List = initList();

	for (int i = 0; i < n; i++)
	{
		int Left = 0;
		int Right = 0;
		scanf("%d", &Left);
		scanf("%d", &Right);

		int stus = AllocMem(List, Left, Right);

		if (stus == FALSE)	//分配失败
		{
			printf("-1\n");
		}
		else
		{
			printf("0\n");
		}
	}

	Free_List(List);
	return 0;
}