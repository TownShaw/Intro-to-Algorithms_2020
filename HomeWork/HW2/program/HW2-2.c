#include <stdio.h>
#include <stdlib.h>
#define TOTAL 1
#define MATH 2
#define IDENTITY 3

typedef struct student
{
	int ID;
	int Math;
	int English;
	int Total;
}stud_Node;

void Swap(stud_Node *Node_1, stud_Node *Node_2)
{
	stud_Node temp = *Node_1;
	*Node_1 = *Node_2;
	*Node_2 = temp;
}
/*
int Partition(stud_Node *stud_Array, int low, int high)
{//根据 Kind 决定根据什么数据进行排序
	int i = low;
	int j = high;
	stud_Node pivot = stud_Array[low];
	
	while(1)
	{
		if (i >= j)
		{//切分结束, 跳出
			break;
		}
		while ((i < high) && 
			  ((pivot.Total < stud_Array[i].Total) || 	//i 总成绩大于 pivot, 不用交换
			  (pivot.Total == stud_Array[i].Total && pivot.Math < stud_Array[i].Math) || 	// i 总成绩与 pivot 相等, 数学高于 pivot
			  (pivot.Total == stud_Array[i].Total && pivot.Math == stud_Array[i].Math && pivot.ID < stud_Array[i].ID)))	//i 总成绩、数学均与 pivot 相等, 学号大于 pivot
		{//找到综合大于 pivot 的学生
			i++;
		}
		while ((j > low) && 
			  ((pivot.Total > stud_Array[j].Total) || 	//j 总成绩小于 pivot, 不用交换
			  (pivot.Total == stud_Array[j].Total && pivot.Math > stud_Array[j].Math) || 	// j 总成绩与 pivot 相等, 数学低于 pivot
			  (pivot.Total == stud_Array[j].Total && pivot.Math == stud_Array[j].Math && pivot.ID > stud_Array[j].ID)))	//j 总成绩、数学均与 pivot 相等, 学号小于 pivot
		{//找到综合小于 pivot 的学生
			j--;
		}
		if(i < j)
		{
			Swap(&stud_Array[i], &stud_Array[j]);
		}
	}
	Swap(&stud_Array[i], &stud_Array[high]);
	
	return i;
}
*/

int Partition(stud_Node *stud_Array, int low, int high)
{
	if(low >= high)	//如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
	{
		return 0;
	}
	int i = low;
	int j = high;
	stud_Node pivot = stud_Array[low];
     
	while(i < j)                               /*控制在当组内寻找一遍*/
	{
	while (i < j && 
			  ((pivot.Total > stud_Array[j].Total) || 	//j 总成绩小于 pivot, 不用交换
			  (pivot.Total == stud_Array[j].Total && pivot.Math > stud_Array[j].Math) || 	// j 总成绩与 pivot 相等, 数学低于 pivot
			  (pivot.Total == stud_Array[j].Total && pivot.Math == stud_Array[j].Math && pivot.ID > stud_Array[j].ID)))	//i 总成绩、数学均与 pivot 相等, 学号大于 pivot
		{
			j--;	//向前寻找
		}
		stud_Array[i] = stud_Array[j];         
		while (i < j && 
			  ((pivot.Total < stud_Array[i].Total) || 	//i 总成绩大于 pivot, 不用交换
			  (pivot.Total == stud_Array[i].Total && pivot.Math < stud_Array[i].Math) || 	// i 总成绩与 pivot 相等, 数学高于 pivot
			  (pivot.Total == stud_Array[i].Total && pivot.Math == stud_Array[i].Math && pivot.ID < stud_Array[i].ID)))	//j 总成绩、数学均与 pivot 相等, 学号小于 pivot
		{
			i++;
		}
		stud_Array[j] = stud_Array[i];
	}
     
	stud_Array[i] = pivot;	//当在当组内找完一遍以后就把中间数key回归
	return i;
}

void QuickSort(stud_Node *stud_Array, int low, int high)
{
	if(low < high)
	{
		int mid = Partition(stud_Array, low, high);
		QuickSort(stud_Array, low, mid - 1);
		QuickSort(stud_Array, mid + 1, high);
	} 
}

int main()
{
	int length = 0;
	scanf("%d", &length);	//输入学生个数

	stud_Node *stud_Array = (stud_Node *)malloc(sizeof(stud_Node) * length);
	for (int i = 0; i < length; i++)
	{
		scanf("%d", &stud_Array[i].ID);
		scanf("%d", &stud_Array[i].Math);
		scanf("%d", &stud_Array[i].English);
		stud_Array[i].Total = stud_Array[i].Math + stud_Array[i].English;	//计算总成绩
	}

	QuickSort(stud_Array, 0, length - 1);	//排序

	for (int i = 0; i < length; i++)
	{
		printf("%d ", stud_Array[i].ID);
	}

	free(stud_Array);
}
