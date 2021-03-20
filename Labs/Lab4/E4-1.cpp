#include <iostream>

using namespace std;

int Partition(int* Array, int low, int high)
{
	if(low >= high)	//如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
	{
		return 0;
	}
	int i = low;
	int j = high;
	int pivot = Array[low];
	
	while(i < j)
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

int Set_Station(int* Village, int length, int Radius, int i)
{
	int Left_Edge = Village[i];		//左边界
	while (i + 1 < length && (Left_Edge + Radius) >= Village[i + 1])
	{
		i++;
	}
	int Center = Village[i];
	while (i < length && (Center + Radius) >= Village[i])
	{
		i++;
	}
	return i;
}

int main()
{
	int N = 0;
	int Radius = 0;

	cin >> N;		//村子个数
	cin >> Radius;	//半径

	int* Village = new int [N];

	for (int i = 0; i < N; i++)
	{
		cin >> Village[i];
	}

	QuickSort(Village, 0, N - 1);	//排序

	cout << endl;
	for (int i = 0; i < N; i++)
	{
		cout << Village[i] <<endl;
	}

	int Num = 0;	//基站个数
	int i = 0;
	while (i < N)
	{
		i = Set_Station(Village, N, Radius, i);
		Num++;
	}

	cout << Num << endl;

	delete [] Village;

	return 0;
}