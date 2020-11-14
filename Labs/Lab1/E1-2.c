#include <stdio.h>
#include <stdlib.h>

void Merge(int *Array, int low, int mid, int high, int *Inversion)	//归并排序 Merge 操作 
{
	int length_1 = mid - low + 1;
	int length_2 = high - mid;
	int *Merge_1 = (int *)malloc(sizeof(int) * length_1);
	int *Merge_2 = (int *)malloc(sizeof(int) * length_2);
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
		if (Merge_1[i] <= Merge_2[j])
		{
			Array[k] = Merge_1[i++]; 
		}
		else
		{
			Array[k] = Merge_2[j++];
			*Inversion += length_1 - i;
			*Inversion %= 10000019;		//Inversion 可能非常大, 需要 模 10000019 保证不越界
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

void MergeSort(int *Array, int low, int high, int *Inversion)	//归并排序, Inversion 用于记录逆序对个数
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(Array, low, mid, Inversion);
		MergeSort(Array, mid + 1, high, Inversion);
		Merge(Array, low, mid, high, Inversion);
	}
}

int main()
{
	int n = 0;	//数据个数
	int Inversion = 0;	//逆序对个数
	scanf("%d", &n);

	int *Array = (int *)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{//输入数据
		scanf("%d", &Array[i]);
	}
	MergeSort(Array, 0, n - 1, &Inversion);

	printf("%d\n", Inversion % 10000019);

	for (int i = 0; i < n; i++)
	{
		printf("%d\t", Array[i]);
	}

	free(Array);
	return 0;
}