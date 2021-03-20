#include <iostream>

using namespace std;

struct Coord
{
	int x;
	int y;
};

int Compare(Coord a, Coord b)
{
	if (a.x > b.x)
	{
		return 1;
	}
	else if (a.x == b.x)
	{
		if (a.y >= b.y)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int Partition(Coord* Array, int low, int high)
{
	if(low >= high)	//如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
	{
		return 0;
	}
	int i = low;
	int j = high;
	Coord pivot = Array[low];
     
	while(i < j)                               /*控制在当组内寻找一遍*/
	{
		while (i < j && Compare(pivot, Array[j]) == 0)	//升序排列数组
		{
			j--;	//向前寻找
		}
		Array[i] = Array[j];         
		while (i < j && Compare(pivot, Array[i]) == 1)
		{
			i++;
		}
		Array[j] = Array[i];
	}

	Array[i] = pivot;	//当在当组内找完一遍以后就把中间数 key 回归
	return i;
}

void QuickSort(Coord *Array, int low, int high)
{
	if(low < high)
	{	
		int mid = Partition(Array, low, high);
		QuickSort(Array, low, mid - 1);
		QuickSort(Array, mid + 1, high);
	} 
}

int Find(Coord* Array, int* Result, int Cur_y, int index)	//在 Array 中, 找到 Array[0 - index] 内小于 Cur_y 的最大的 y 的下标
{
	int max = 0;
	int result = -1;
	for (int i = 0; i < index; i++)
	{
		if (Result[i] >= max && Array[i].y <= Cur_y)
		{
			max = Result[i];
			result = i;
		}
	}
	return result;
}

int main()
{
	int n = 0;

	cin >> n;

	Coord* Array = new Coord [n];
	for (int i = 0; i < n; i++)
	{
		cin >> Array[i].x;
		cin >> Array[i].y;
	}

	QuickSort(Array, 0, n - 1);
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << Array[i].x << ' ' << Array[i].y << endl;
	}

	int* Result = new int [n];	// Result[i] 存放 0 - i 内以 Array[i].y 为界的最大子集数

	for (int i = 1; i < n; i++)
	{
		Result[i] = 0;
	}
	Result[0] = 1;

	int Max_y = Array[0].y;	//当前最大 y
	int Max_index = 0;
	for (int i = 1; i < n; i++)
	{
		if (Array[i].y >= Max_y)
		{
			Result[i] = Result[Max_index] + 1;
			Max_y = Array[i].y;
			Max_index = i;
		}
		else	//Array[i].y < Array[i - 1].y
		{
			int index = Find(Array, Result, Array[i].y, i);
			int temp = 0;
			if (index == -1)	//没有比当前的 y 更小的
			{
				temp = 1;
			}
			else
			{
				temp = Result[index] + 1;
			}
			if (Result[Max_index] > temp)	//若当前最大的子集比 以 Result[i] 为界的子集大, 则仅保存该子集大小
			{
				Result[i] = temp;
			}
			else	//若当前最大的子集比 以 Result[i] 为界的子集小, 则更换最大子集
			{
				Result[i] = temp;
				Max_y = Array[i].y;
				Max_index = i;
			}
		}
	}

	cout << Result[Max_index] << endl;

	delete [] Array;
	delete [] Result;

	return 0;
}