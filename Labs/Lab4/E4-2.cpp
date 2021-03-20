#include <iostream>

using namespace std;

struct Task
{
	int r;	//到达时间
	int p;	//剩余执行时间
};

class Task_Heap
{
private:
	int Heap_Border = 0;	//边界
	int MAX_SIZE = 0;

	inline int Min(int i, int j)	//返回剩余执行时间较小的下标
	{
		return (Heap[i].p < Heap[j].p) ? i : j;
	}
	inline int Parent(int i)
	{
		return i / 2;
	}
	inline int Left(int i)
	{
		return 2 * i;
	}
	inline int Right(int i)
	{
		return 2 * i + 1;
	}
	void Swap(int i, int j)
	{
		Task temp = Heap[i];
		Heap[i] = Heap[j];
		Heap[j] = temp;
	}

public:
	Task* Heap = nullptr;
	Task_Heap(int N)
	{
		Heap = new Task[N];
		Heap_Border = 1;
		MAX_SIZE = N + 1;
		Heap[0] = {0, 0};
	}
	bool isEmpty()
	{
		if (Heap_Border == 1)
		{
			return true;
		}
		return false;
	}
	int get_Size()
	{
		return Heap_Border - 1;
	}
	bool Push(const Task &T)
	{
		if (Heap_Border == MAX_SIZE)
		{
			return false;
		}
		Heap[Heap_Border].p = T.p;
		Heap[Heap_Border].r = T.r;
		Heap_Border++;
		return true;
	}
	int Extract_Min()	//删除最小堆结点, 并返回其到达时间
	{
		int Arri = Heap[1].r;
		Heap[1] = Heap[--Heap_Border];
		Fix_Down(1);
		return Arri;
	}
	bool Fix_Down(int Start)	//从 Start 开始向下修正堆
	{
		if (Start >= Heap_Border)
		{
			return false;
		}
		while (Start < Heap_Border)
		{
			if (Left(Start) < Heap_Border)
			{
				if (Right(Start) < Heap_Border)
				{
					int Min_index = Min(Left(Start), Right(Start));	//两者剩余执行时间较小的下标
					if (Heap[Min_index].p < Heap[Start].p)	//修正堆
					{
						Swap(Start, Min_index);
						Start = Min_index;
					}
					else
					{
						break;
					}
				}
				else
				{
					if (Heap[Left(Start)].p < Heap[Start].p)
					{
						Swap(Start, Left(Start));
						Start = Left(Start);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		return true;
	}
	bool Fix_Up(int Start)	//从 Start 开始向上修正堆
	{
		if (Start >= Heap_Border)
		{
			return false;
		}
		while (Start > 1)
		{
			if (Heap[Parent(Start)].p > Heap[Start].p)
			{
				Swap(Parent(Start), Start);
				Start /= 2;
			}
			else
			{
				break;
			}
		}
		return true;
	}
	int Add_Tasks(Task *Total_Task, int i, int Current_Time)
	{	//将 Current_Time 到达的任务加入堆中, 此时任务表中的下标为 i
		if (i >= MAX_SIZE - 1)	//表示 Total_Task 中的任务都已经加入堆中
		{
			return i;
		}
		for ( ; Total_Task[i].r == Current_Time; i++)
		{
			Push(Total_Task[i]);
			Fix_Up(Heap_Border - 1);
		}
		return i;
	}
	~Task_Heap()
	{
		delete [] Heap;
	}
};


int Compare(const Task &a, const Task &b)
{
	if (a.r < b.r)
	{
		return 1;
	}
	else if (a.r == b.r)
	{
		if (a.p <= b.p)
		{
			return 1;
		}
	}
	return 0;
}

int Partition(Task* Array, int low, int high)
{
	if(low >= high)	//如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
	{
		return 0;
	}
	int i = low;
	int j = high;
	Task pivot = Array[low];
	
	while(i < j)
	{
		while (i < j && (Compare(pivot, Array[j]) == 1))	//升序排列数组
		{
			j--;	//向前寻找
		}
		Array[i] = Array[j];
		while (i < j && (Compare(pivot, Array[i]) == 0))
		{
			i++;
		}
		Array[j] = Array[i];
	}

	Array[i] = pivot;	//当在当组内找完一遍以后就把中间数 key 回归
	return i;
}

void QuickSort(Task* Array, int low, int high)
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
	int N = 0;

	cin >> N;

	Task* Total_Task = new Task[N];
	Task_Heap* T_Heap = new Task_Heap(N);

	for (int i = 0; i < N; i++)
	{
		cin >> Total_Task[i].r;
		cin >> Total_Task[i].p;
	}

	QuickSort(Total_Task, 0, N - 1);
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		cout << Total_Task[i].r << ' ' << Total_Task[i].p << endl;
	}

	int Current_Time = 0;
	int Total_Wait_Time = 0;

	for (int i = 0; i < N || !(T_Heap->isEmpty()); Current_Time++)
	{	//当所有任务都已经加入堆中同时堆为空时代表全部处理完成, 退出循环
		i = T_Heap->Add_Tasks(Total_Task, i, Current_Time);
		if (!(T_Heap->isEmpty()) && (--T_Heap->Heap[1].p == 0))
		{
			int Arr_Time = T_Heap->Extract_Min();
			Total_Wait_Time += Current_Time - Arr_Time + 1;
		}
	}

	cout << Total_Wait_Time << endl;

	delete [] Total_Task;

	return 0;
}