#include <stdio.h>
#include <stdlib.h>

typedef struct DataNode
{
	int Num;	//记录数字本身
	int Time;	//记录数字出现次数
	struct DataNode *pNext;
}*Data;

typedef struct Data_ListNode
{
	struct DataNode *pHead;		//头指针
	struct DataNode *pLast;		//尾指针
	int Length;				//链表长度
	int Max_Time;			//所有节点 Time 的最大值
}*Data_List;

Data_List initList()
{//初始化链表
	Data_List List = (Data_List)malloc(sizeof(struct Data_ListNode));
	List->pHead = (Data)malloc(sizeof(struct DataNode));	//初始化头指针
	List->pHead->pNext = NULL;
	List->pLast = List->pHead;
	List->pLast->pNext = NULL;
	List->Length = 0;
	List->Max_Time = 0;
	return List;
}

void Insert(Data_List List, Data pPre)
{//将位置待修改的节点调整到正确位置
	Data Key = pPre->pNext;		//Key 为位置待调整的节点
	pPre->pNext = Key->pNext;	//先将 Key抽出
	
	Data pTemp = List->pHead;
	for ( ; (pTemp->pNext != NULL) && (pTemp->pNext->Time > Key->Time); pTemp = pTemp->pNext);
	//找到与 Key->Time 有相同 Time 的子链表
	for ( ; (pTemp->pNext != NULL) && (pTemp->pNext->Time == Key->Time) && (pTemp->pNext->Num < Key->Num); pTemp = pTemp->pNext);
	//在该子链表中找到待插入位置
	Key->pNext = pTemp->pNext;	//插入 Key
	pTemp->pNext = Key;
}

void Append(Data_List List, int data)
{//在 List 中增加一个 Node, 内容为 data, 如果 data 已经存在, 则对应节点 Time+1
	List->Length++;

	Data pTemp = List->pHead->pNext;
	Data pPre = List->pHead;	//作为 pTemp 的前驱
	for ( ; pTemp != NULL; pTemp = pTemp->pNext)
	{
		if (pTemp->Num == data)
		{
			pTemp->Time++;
			if (pTemp->Time > List->Max_Time)
			{
				List->Max_Time = pTemp->Time;	//修改链表中次数最大值
			}
			Insert(List, pPre);
			return;
		}
		pPre = pTemp;
	}
	pTemp = (Data)malloc(sizeof(struct DataNode));	//新建节点, 插入到最后
	pTemp->Num = data;
	pTemp->Time = 1;
	pTemp->pNext = NULL;
	pTemp->pNext = List->pHead->pNext;
	List->pHead->pNext = pTemp;	//先插在头部, 满足 Insert() 函数格式, 再在 Insert() 中插入到合适位置
	Insert(List, List->pHead);
}

int main()
{
	Data_List List = initList();

	int length = 0;		//输入数据个数
	scanf("%d", &length);
	
	for (int i = 0; i < length; i++)
	{
		int data = 0;
		scanf("%d", &data);
		Append(List, data);
	}

	for (Data pTemp = List->pHead->pNext; pTemp != NULL; pTemp = pTemp->pNext)
	{
		printf("%d %d\n", pTemp->Num, pTemp->Time);
	}

	return 0;
}

/*

typedef struct DataNode {
	int Num;	//记录数字本身
	int Time;	//记录数字出现次数
}Data;

int main()
{
	int length = 0;
	scanf("%d", &length);
	if (length <= 0)
	{
		printf("Input Error!");
		return 0;
	}
	
	
}*/