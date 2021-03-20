#include <stdio.h>
#include <stdlib.h>

void Swap(int *p1, int *p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int Partition(int *Array, int low, int high)
{
	if(low >= high)	//如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
	{
		return 0;
	}
	int i = low;
	int j = high;
	int pivot = Array[low];
     
	while(i < j)                               /*控制在当组内寻找一遍*/
	{
		while (i < j && pivot < Array[j])	//升序排列数组
		{
			j--;	//向前寻找
		}
		Array[i] = Array[j];         
		while (i < j && pivot > Array[i])
		{
			i++;
		}
		Array[j] = Array[i];
	}

	Array[i] = pivot;	//当在当组内找完一遍以后就把中间数 key 回归
	return i;
}

void QuickSort(int *Array, int low, int high)
{
	if(low < high)
	{	
		int mid = Partition(Array, low, high);
		QuickSort(Array, low, mid - 1);
		QuickSort(Array, mid + 1, high);
	} 
}

int main()
{
	int n = 0;
	scanf("%d", &n);	//输入数据个数

	int *Array = (int *)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &Array[i]);
	}

	QuickSort(Array, 0, n - 1);	//快速排序

	int d_max = 0;	//最大半径
	for (int i = 1; i < n; i++)
	{//计算最大差值, 即为最大直径
		if (d_max < Array[i] - Array[i - 1])
		{
			d_max = Array[i] - Array[i - 1];
		}
	}
	printf("%d", d_max);

	free(Array);
	return 0;
}