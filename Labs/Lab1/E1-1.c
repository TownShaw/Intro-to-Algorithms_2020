#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INS_LENGTH 12

typedef struct BiTree
{
	int Key;
	int Value;
	struct BiTree *LChild;
	struct BiTree *RChild;
}BiTreeNode;

BiTreeNode* CreateNode(int key, int value)
{
	BiTreeNode *pNew = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	pNew->Key = key;
	pNew->Value = value;
	pNew->LChild = NULL;
	pNew->RChild = NULL;
	return pNew;
}

int Find_Value(BiTreeNode *pRoot, int value)
{
	if (pRoot == NULL)	//根节点为空, 未找到, 返回 -1
	{
		return -1;
	}
	else
	{
		if (pRoot->Value == value)	//根节点满足要求, 返回根节点关键字
		{
			return pRoot->Key;
		}
		else
		{
			if (pRoot->Value > value)	//关键字比当前根节点属性值小, 则在左子树找到属性值, 返回对应关键字
			{
				return Find_Value(pRoot->LChild, value);
			}
			else	//关键字比当前根节点属性值大, 则在右子树找到属性值, 返回对应关键字
			{
				return Find_Value(pRoot->RChild, value);
			}
		}
	}
}

void Insert(BiTreeNode *pRoot, int key, int value)	//通过 Insert() 操作维护一个二叉搜索树
{
	BiTreeNode *pTemp = pRoot;
	BiTreeNode *pPre = pRoot;	//pPre 为 pTemp 父节点
	while(pTemp != NULL)
	{	//找到待插入的位置, 总是插在叶节点处
		if (value < pTemp->Value)
		{
			pPre = pTemp;
			pTemp = pPre->LChild;
		}
		else
		{
			pPre = pTemp;
			pTemp = pPre->RChild;
		}
	}

	BiTreeNode *pNew = CreateNode(key, value);	//新建待插入节点
	if (value < pPre->Value)	//插入新建节点 pNew
	{
		pPre->LChild = pNew;
	}
	else
	{
		pPre->RChild = pNew;
	}
}

void Free_BiTree(BiTreeNode *pRoot)	//后序遍历释放整棵树
{
	if(pRoot == NULL)
	{
		return;
	}
	Free_BiTree(pRoot->LChild);
	Free_BiTree(pRoot->RChild);
	free(pRoot);
}

int main()
{
	char *Ins = (char *)malloc(sizeof(char) * MAX_INS_LENGTH);	//字符数组存储指令
	BiTreeNode *pRoot = NULL;	//初始化根节点

	while(1)	//输入指令
	{
		memset(Ins, '\0', MAX_INS_LENGTH);
		scanf("%s", Ins);
		if (strcmp(Ins, "EXIT") == 0)	//退出指令
		{
			break;
		}
		else if (strcmp(Ins, "FIND") == 0)	//查找指令
		{
			int value = 0;
			scanf("%d", &value);
			printf("%d\n", Find_Value(pRoot, value));
		}
		else if (strcmp(Ins, "INSERT") == 0)	//插入指令
		{
			int key = 0;
			int value = 0;
			scanf("%d", &key);
			scanf("%d", &value);

			if (pRoot == NULL)
			{
				pRoot = CreateNode(key, value);	//第一个节点
			}
			else
			{
				Insert(pRoot, key, value);
			}
		}
		else	//不是退出、查找、插入指令, 则为非法指令, 报错并退出程序
		{
			printf("Error: Invalid Instruction!");
			return 0;
		}
	}

	free(Ins);
	Free_BiTree(pRoot);	//释放堆空间
	return 0;
}