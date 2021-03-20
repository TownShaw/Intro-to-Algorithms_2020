#include <iostream>

using namespace std;

int Partition(int *Array, int low, int high)
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

bool judge(int *Clothes, int length, int Distance, int M)
{
	int Remove_Num = 0;
	int base = 0;
	for (int i = 1; i < length; i++)
	{
		if (Clothes[i] - Clothes[base] < Distance)
		{
			Remove_Num++;
		}
		else
		{//从 i 开始找子区间
			base = i;
		}
	}
	if (Remove_Num > M)
	{//移除超过 M 个, 并非可行解
		return false;
	}
	else
	{//可行解
		return true;
	}
}

int main()
{
	int N = 0;
	int M = 0;

	cin >> N;
	cin >> M;

	int *Clothes = new int [N];

	for (int i = 0; i < N; i++)
	{
		cin >> Clothes[i];
	}

	QuickSort(Clothes, 0, N - 1);
	cout << endl;

	for (int i = 0; i < N; i++)
	{
		cout << Clothes[i] << endl;
	}
	
	int low = Clothes[0];
	int high = Clothes[N - 1];
	int Min_Dis = 0;

	while (low <= high)
	{
		int mid = (low + high) / 2;		//二分查找可行距离
		int Dis = mid - Clothes[0];
		if (judge(Clothes, N, Dis, M))
		{
			Min_Dis = Dis;
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	cout << Min_Dis << endl;

	delete [] Clothes;

	return 0;
}