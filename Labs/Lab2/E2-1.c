#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INS_LENGTH 12
#define BLACK 0
#define RED 1
//红黑树实现

typedef struct RBTreeNode
{
	int Key;
	char Color;
	struct RBTreeNode *Parent;
	struct RBTreeNode *LChild;
	struct RBTreeNode *RChild;
}RBTreeNode;

typedef struct RBTree
{
	RBTreeNode *pRoot;	//根节点
	RBTreeNode *NIL;	//哨兵节点
}RBTree;

RBTree *initRBTree()
{
	RBTree *Tree = (RBTree *)malloc(sizeof(RBTree));
	Tree->pRoot = NULL;
	Tree->NIL = (RBTreeNode *)malloc(sizeof(RBTreeNode));
	Tree->NIL->Key = 0;
	Tree->NIL->Color = BLACK;
	Tree->NIL->Parent = NULL;
	Tree->NIL->LChild = NULL;
	Tree->NIL->RChild = NULL;
	return Tree;
}

RBTreeNode *CreateNode(int Key, int Color)
{
	RBTreeNode *pNew = (RBTreeNode *)malloc(sizeof(RBTreeNode));
	pNew->Key = Key;
	pNew->Color = Color;
	pNew->Parent = NULL;
	pNew->LChild = NULL;
	pNew->RChild = NULL;
	return pNew;
}

void Left_Rotate(RBTree *Tree, RBTreeNode *p)
{//以 p 为根节点的子树进行左旋
	RBTreeNode *pTemp = p->RChild;	//右孩子
	p->RChild = pTemp->LChild;	//连接 p 和 pTemp 的左孩子
	if(pTemp->LChild != Tree->NIL)
	{
		pTemp->LChild->Parent = p;
	}
	pTemp->Parent = p->Parent;	//连接 pTemp 和 原来的 p 的父节点
	if(pTemp->Parent == Tree->NIL)	//pTemp 为根, 则将根指针指向新根 pTemp
	{
		Tree->pRoot = pTemp;
	}
	else if(p == p->Parent->LChild)
	{
		p->Parent->LChild = pTemp;
	}
	else
	{
		p->Parent->RChild = pTemp;
	}
	pTemp->LChild = p;	//连接 pTemp 和 p
	p->Parent = pTemp;
}

void Right_Rotate(RBTree *Tree, RBTreeNode *p)
{//以 p 为根节点的子树进行左旋
	RBTreeNode *pTemp = p->LChild;	//pTemp 为 p 的左孩子
	p->LChild = pTemp->RChild;	//连接 p 和 pTemp 的右孩子
	if(pTemp->RChild != Tree->NIL)
	{
		pTemp->RChild->Parent = p;
	}
	pTemp->Parent = p->Parent;	//连接 pTemp 和 原来的 p 的父节点
	if(pTemp->Parent == Tree->NIL)	//pTemp 为根, 则将根指针指向新根 pTemp
	{
		Tree->pRoot = pTemp;
	}
	else if(p == p->Parent->LChild)
	{
		p->Parent->LChild = pTemp;
	}
	else
	{
		p->Parent->RChild = pTemp;
	}
	pTemp->RChild = p;	//连接 pTemp 和 p
	p->Parent = pTemp;
}

void RB_Insert_Fixup(RBTree *Tree, RBTreeNode *pNew)
{//对 Tree 进行修正, 其中 pNew 为新插入的红色节点
	while (pNew->Parent->Color == RED)
	{//只要 pNew->Parent->Color == RED, 则冲突仍然存在, 还需要进行调整, 且 pNew 祖父节点必为黑
		if (pNew->Parent == pNew->Parent->Parent->LChild)
		{//pNew 父节点是 pNew 祖先节点的左孩子
			RBTreeNode *pUncle = pNew->Parent->Parent->RChild;
			if (pUncle->Color == RED)
			{//case 1
				pUncle->Parent->Color = RED;	//pNew 祖先节点染红
				pUncle->Color = BLACK;
				pNew->Parent->Color = BLACK;
				pNew = pNew->Parent->Parent;	//准备下一次迭代
			}
			else
			{
				if (pNew == pNew->Parent->RChild)
				{//case 2
					pNew = pNew->Parent;	//左旋之前令 pNew 指向其父节点
					Left_Rotate(Tree, pNew);
				}
				pNew->Parent->Color = BLACK;	//case 3
				pNew->Parent->Parent->Color = RED;
				Right_Rotate(Tree, pNew->Parent->Parent);
			}
		}
		else	//镜面反射, 此时 pNew 父节点是 pNew 祖先节点的右孩子
		{//pNew 父节点是 pNew 祖先节点的左孩子
			RBTreeNode *pUncle = pNew->Parent->Parent->LChild;
			if (pUncle->Color == RED)
			{//case 1
				pUncle->Parent->Color = RED;	//pNew 祖先节点染红
				pUncle->Color = BLACK;
				pNew->Parent->Color = BLACK;
				pNew = pNew->Parent->Parent;	//准备下一次迭代
			}
			else
			{
				if (pNew == pNew->Parent->LChild)
				{//case 2
					pNew = pNew->Parent;	//右旋之前令 pNew 指向其父节点
					Right_Rotate(Tree, pNew);
				}
				pNew->Parent->Color = BLACK;	//case 3
				pNew->Parent->Parent->Color = RED;
				Left_Rotate(Tree, pNew->Parent->Parent);
			}
		}
	}
	Tree->pRoot->Color = BLACK;
}

void RB_Insert(RBTree *Tree, int Key)
{
	RBTreeNode *pTemp = Tree->pRoot;
	RBTreeNode *pPre = Tree->NIL;
	if (pTemp == NULL)	//说明 Tree->pRoot 原来是空的
	{
		Tree->pRoot = CreateNode(Key, BLACK);	//根节点为黑色
		Tree->pRoot->Parent = Tree->NIL;	//将根节点的父指针指向哨兵
		Tree->pRoot->LChild = Tree->NIL;
		Tree->pRoot->RChild = Tree->NIL;
		return;
	}
	while (pTemp != Tree->NIL)	//找到待插入位置
	{
		pPre = pTemp;
		if (Key < pTemp->Key)
		{
			pTemp = pTemp->LChild;
		}
		else
		{
			pTemp = pTemp->RChild;
		}
	}
	RBTreeNode *pNew = CreateNode(Key, RED);	//新插入节点默认为红色
	if (Key < pPre->Key)
	{
		pPre->LChild = pNew;
		pNew->Parent = pPre;
		pNew->LChild = Tree->NIL;
		pNew->RChild = Tree->NIL;
	}
	else
	{
		pPre->RChild = pNew;
		pNew->Parent = pPre;
		pNew->LChild = Tree->NIL;
		pNew->RChild = Tree->NIL;
	}
	RB_Insert_Fixup(Tree, pNew);
}

int Find_Value(RBTree *Tree, int Key)
{
	if (Tree->pRoot == NULL)	//根节点为空, 未找到, 返回 -1
	{
		return -1;
	}
	RBTreeNode *pPre = Tree->NIL;
	RBTreeNode *pTemp = Tree->pRoot;
	while (pTemp != Tree->NIL)
	{
		pPre = pTemp;
		if (pTemp->Key == Key)
		{
			return Key;
		}
		else if (Key < pTemp->Key)
		{
			pTemp = pTemp->LChild;
		}
		else
		{
			pTemp = pTemp->RChild;
		}
	}
	//能走到这一步说明没找到

	if (Key < pPre->Key)
	{
		while (pPre == pPre->Parent->LChild)
		{//这条路上的节点都比 Key 大
			pPre = pPre->Parent;
		}
		pPre = pPre->Parent;
	}
	if (pPre == Tree->NIL)
	{//说明没有比 Key 还小的关键字
		return -1;
	}
	else
	{
		return pPre->Key;
	}
}

void Free_RBTree(RBTreeNode *pRoot, RBTreeNode *NIL)	//后序遍历释放整棵树
{
	if(pRoot == NIL)
	{
		return;
	}
	Free_RBTree(pRoot->LChild, NIL);
	Free_RBTree(pRoot->RChild, NIL);
	free(pRoot);
}

int main()
{
	char *Ins = (char *)malloc(sizeof(char) * MAX_INS_LENGTH);	//字符数组存储指令
	RBTree *Tree = initRBTree();

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
			int key = 0;
			scanf("%d", &key);
			printf("%d\n", Find_Value(Tree, key));
		}
		else if (strcmp(Ins, "INSERT") == 0)	//插入指令
		{
			int key = 0;
			scanf("%d", &key);

			RB_Insert(Tree, key);
		}
		else	//不是退出、查找、插入指令, 则为非法指令, 报错并退出程序
		{
			printf("Error: Invalid Instruction!");
			return 0;
		}
	}

	free(Ins);
	Free_RBTree(Tree->pRoot, Tree->NIL);	//释放堆空间
	free(Tree);
	return 0;
}