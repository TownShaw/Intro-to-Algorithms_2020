#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_LENGTH 100000

int Free_List[MAX_LENGTH];

typedef struct
{
	int Good_1;
	int Good_2;
	int Danger;
}Danger_Rel;	//危险系数关系

Danger_Rel *initDanger_Rel(int n)
{
	Danger_Rel *Rel = (Danger_Rel *)malloc(sizeof(Danger_Rel) * n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &Rel[i].Good_1);
		scanf("%d", &Rel[i].Good_2);
		scanf("%d", &Rel[i].Danger);
	}
	return Rel;
}

int *initDanger_Goods(int n)
{
	int *Danger_Goods = (int *)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		Danger_Goods[i] = i;
	}

	return Danger_Goods;
}

int Find_Set(int *Danger_Goods, int index)
{
	if (Danger_Goods[index] != index)
	{
		Danger_Goods[index] = Find_Set(Danger_Goods, Danger_Goods[index]);
	}
	
	return Danger_Goods[index];
}

void Union_Root(int *Danger_Goods, int Root_1, int Root_2)
{
	Danger_Goods[Root_1] = Root_2;
	Danger_Goods[Root_2] = Root_2;
}

void Union(int *Danger_Goods, int i, int j)	//Danger_Goods[i]与Danger_Goods[j]所在的Set进行合并
{
	int Root_1 = Find_Set(Danger_Goods, i);
	int Root_2 = Find_Set(Danger_Goods, j);
	if (Root_1 != Root_2)
	{
		Union_Root(Danger_Goods, Root_1, Root_2);
	}
}

void Merge(Danger_Rel *Array, int low, int mid, int high)	//归并排序 Merge 操作 
{
	int length_1 = mid - low + 1;
	int length_2 = high - mid;
	Danger_Rel *Merge_1 = (Danger_Rel *)malloc(sizeof(Danger_Rel) * length_1);
	Danger_Rel *Merge_2 = (Danger_Rel *)malloc(sizeof(Danger_Rel) * length_2);
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0, k = low; i < length_1; i++, k++)	//copy
	{
		Merge_1[i] = Array[k];
	}
	for (j = 0, k = mid + 1; j < length_2; j++, k++)	//copy
	{
		Merge_2[j] = Array[k];
	}
	for (i = 0, j = 0, k = low; i < length_1 && j < length_2 && k < high + 1; k++)	//Merge
	{
		if (Merge_1[i].Danger >= Merge_2[j].Danger)
		{
			Array[k] = Merge_1[i++];
		}
		else
		{
			Array[k] = Merge_2[j++];
		}
	}
	if (i == length_1)
	{
		for ( ; j < length_2; j++, k++)
		{
			Array[k] = Merge_2[j];
		}
	}
	else if (j == length_2)
	{
		for ( ; i < length_1; i++, k++)
		{
			Array[k] = Merge_1[i];
		}
	}
	free(Merge_1);
	free(Merge_2);
}

void MergeSort(Danger_Rel *Array, int low, int high)	//归并排序
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(Array, low, mid);
		MergeSort(Array, mid + 1, high);
		Merge(Array, low, mid, high);
	}
}

int main()
{
	int n = 0;
	int m = 0;

	scanf("%d", &n);	//物品个数
	scanf("%d", &m);	//危险系数对数

	memset(Free_List, 0, MAX_LENGTH);
	int *Danger_Goods = initDanger_Goods(n + 1);
	Danger_Rel *Rel = initDanger_Rel(m);
	MergeSort(Rel, 0, m - 1);

	free(Danger_Goods);
	free(Rel);
	return 0;
}