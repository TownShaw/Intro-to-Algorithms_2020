#include <stdio.h>
#include <stdlib.h>

int Find_Max(int *Array, int low, int high, int *max_index)
{//在 Array[low] -- Array[high] 中寻找最大值, 同时返回最大值和最大值下标
	int max = Array[low];
	*max_index = low;

	for (int i = low + 1; i < high + 1; i++)
	{
		if (Array[i] > max)	//找到比当前最大值还大的数据
		{
			max = Array[i];
			*max_index = i;
		}
	}
	return max;
}

int main()
{
	int n = 0;	//一共有 n 天
	int k = 0;	//提前预知 k 天
	scanf("%d", &n);
	scanf("%d", &k);

	int *Array = (int *)malloc(sizeof(int) * n);	//Array 存储每天银行卡钱数目

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &Array[i]);	//输入银行卡钱数目
	}

	int max = 0;	//最大值
	int max_index = -1;	//最大值下标

	for (int i = 0; i < n - k + 1; i++)
	{
		if (i <= max_index && max_index <= i + k - 1)
		{//若前一天的最大值仍然在今天的考虑范围内, 则只要与最新可以考虑的一天进行比较即可
			if (Array[i + k - 1] > max)
			{
				max_index = i + k - 1;
				max = Array[max_index];
			}
			printf("%d ", max);
		}
		else	//否则重新查找从今天起的 k 天内的最大值
		{
			max = Find_Max(Array, i, i + k - 1, &max_index);
			printf("%d ", max);
		}
	}

	free(Array);
	return 0;
}