#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 6
#define HASH_LENGTH 14348907

typedef struct HashNode
{
	int Name;
	int Num;
	struct HashNode *pNext;
}HashNode, *HashTab;

typedef struct NameNode
{
	int Name;
	int Num;
	struct NameNode *LChild;
	struct NameNode *RChild;
}NameNode;

typedef struct
{
	NameNode *pRoot;
}NameTree;

typedef struct
{
	int Name;	//该学生的名字
	HashNode *pNode;	//指向代表该名字的节点
}Student;

int Convert(char *str)
{
	int sum = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		sum = sum * 26 + (str[i] - 'a');
	}
	return sum;
}

HashNode *CreateHashNode(int Name)
{
	HashNode *pNew = (HashNode *)malloc(sizeof(HashNode));
	pNew->Name = Name;
	pNew->Num = 0;
	pNew->pNext = NULL;
	return pNew;
}

HashTab *initHashTab()
{
	HashTab *Table = (HashTab *)malloc(sizeof(HashNode *) * HASH_LENGTH);
	for (int i = 0; i < HASH_LENGTH; i++)
	{
		Table[i] = NULL;
	}
	return Table;
}

HashNode *Insert_HashTab(HashTab *Table, int Name)
{
	int index = Name % HASH_LENGTH;
	HashNode *pTemp = Table[index];
	for ( ; pTemp != NULL; pTemp = pTemp->pNext)
	{
		if (pTemp->Name == Name)
		{
			return pTemp;
		}
	}
	HashNode *pNew = CreateHashNode(Name);
	pNew->pNext = Table[index];
	Table[index] = pNew;
	return pNew;
}

NameNode *CreateNode(int Name)
{
	NameNode *pName = (NameNode *)malloc(sizeof(NameNode));
	pName->Num = 0;
	pName->Name = Name;
	pName->LChild = NULL;
	pName->RChild = NULL;
	return pName;
}

NameTree *init_NameTree()
{
	NameTree *Tree = (NameTree *)malloc(sizeof(NameTree));
	Tree->pRoot = NULL;
	return Tree;
}

NameNode *Insert(NameTree *Tree, int Name)	//通过 Insert() 操作维护一个二叉搜索树
{
	if (Tree->pRoot == NULL)
	{
		Tree->pRoot = CreateNode(Name);
		return Tree->pRoot;
	}
	NameNode *pTemp = Tree->pRoot;
	NameNode *pPre = Tree->pRoot;	//pPre 为 pTemp 父节点
	while(pTemp != NULL)
	{	//找到待插入的位置, 总是插在叶节点处
		if (Name == pTemp->Name)
		{
			return pTemp;
		}
		else if (Name < pTemp->Name)
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

	NameNode *pNew = CreateNode(Name);	//新建待插入节点
	if (Name < pPre->Name)	//插入新建节点 pNew
	{
		pPre->LChild = pNew;
	}
	else
	{
		pPre->RChild = pNew;
	}
	return pNew;
}

void Free_Tree(NameNode *pRoot)
{
	if (pRoot != NULL)
	{
		Free_Tree(pRoot->LChild);
		Free_Tree(pRoot->RChild);
		free(pRoot);
	}
}

void goBack(Student *Array, int Right, int NewRight, int *Name_Kind)
{//右端从 Right 回退到 NewRight, 同时更新新窗口的名字种类
	for (int i = Right; i > NewRight; i--)
	{
		if (--(Array[i].pNode->Num) == 0)
		{
			(*Name_Kind)--;
		}
	}
}

int main()
{
	int num = 0;	// n 个子队
	int length = 0;	// 队列长度
	int k = 0;	// k 个不重复的名字, 窗口大小
	int Name_Kind = 0;	//当前窗口中不同名字的个数

	scanf("%d", &length);
	scanf("%d", &k);

//	NameTree *Tree = init_NameTree();
	HashTab *Table = initHashTab();
	int Left = 0;				//滑动窗口的左端
	int Right = 0;				//滑动窗口的右端


	char Input_str[MAX_LENGTH];
	Student *Array = (Student *)malloc(sizeof(Student) * length);
	for (int i = 0; i < length; i++)
	{
		scanf("%s", Input_str);
		Array[i].Name = Convert(Input_str);
		Array[i].pNode = Insert_HashTab(Table, Array[i].Name);
	}

	for (Right = 0; Right < Left + k; Right++)
	{//初始化窗口
		if (Array[Right].pNode->Num == 0)
		{
			Name_Kind++;
		}
		Array[Right].pNode->Num++;
	}

	for (Left = 0; Left < length - k + 1; Left++)
	{
		Right = Left + k - 1;	//Right - Left = k
		while (Right < length)
		{
			if (Name_Kind == k)
			{
				num++;
			}
			if (++Right == length)
			{
				Right--;
				break;
			}
			if (Array[Right].pNode->Num != 0)
			{//说明与窗口内的某人同名
				Array[Right].pNode->Num++;
/*				if (Name_Kind == k)
				{
					num++;
				}*/
				continue;
			}
			else
			{//新名字
				Array[Right].pNode->Num++;
				Name_Kind++;
				if (Name_Kind > k)
				{//右端回退, 退出 while 循环, Left++
					break;
				}
			}
		}
		goBack(Array, Right, Left + k, &Name_Kind);
		if (--(Array[Left].pNode->Num) == 0)
		{
			Name_Kind--;
		}
	}
	printf("%d", num);

//	Free_Tree(Tree->pRoot);
	free(Table);
	free(Array);
	return 0;
}