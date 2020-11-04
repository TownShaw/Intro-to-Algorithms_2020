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
	int i = low;
	int j = high;
	int pivot = Array[low];
     
	while(i < j)
	{
		while (i < j && Array[j] >= pivot)
		{
			j--;	//向前寻找
		}
		Array[i] = Array[j];         
		while (i < j && Array[i] <= pivot)
		{
			i++;
		}
		Array[j] = Array[i];
	}

	Array[i] = pivot;	//当在当组内找完一遍以后就把中间数 pivot 回归
	return i;
}

int Select_K(int *Array, int low, int high, int k)	//寻找第 k 小的数字
{
	if (low < high)
	{
		int mid = Partition(Array, low, high);
		if (mid == low + k - 1)
		{
			return Array[mid];
		}
		else if (mid > low + k - 1)
		{
			return Select_K(Array, low, mid - 1, k);
		}
		else
		{
			return Select_K(Array, mid + 1, high, k - (mid - low + 1));
		}
	}
	return Array[low];
}

int main()
{
	int n = 0;	//一共 n 个数字
	int k = 0;	//寻找第 k 小的数字
	scanf("%d", &n);
	scanf("%d", &k);

	int *Array = (int *)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &Array[i]);
	}

	printf("%d", Select_K(Array, 0, n - 1, k));

	free(Array);
	return 0;
}