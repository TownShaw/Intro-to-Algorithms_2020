#include <iostream>

using namespace std;

/*
 * 
 *	Kruskal 算法, 找出该图的 MST 
 * 
 */

struct Edge
{
	int u;	//顶点 u
	int v;	//顶点 v
	int weigh;	//边权重
};

class Min_Heap
{
private:
	int Heap_Border = 0;	//边界
	int MAX_SIZE = 0;
	Edge* Heap = nullptr;

	inline int Min(int i, int j)	//返回剩余执行时间较小的下标
	{
		return (Heap[i].weigh < Heap[j].weigh) ? i : j;
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
		Edge temp = Heap[i];
		Heap[i] = Heap[j];
		Heap[j] = temp;
	}

public:
	Min_Heap(int N)
	{
		Heap = new Edge[N + 1];
		Heap_Border = 1;
		MAX_SIZE = N + 1;
		Heap[0] = {0, 0, 0};
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
	bool Push(const int U, const int V, const int Weigh)
	{
		if (Heap_Border == MAX_SIZE)
		{
			return false;
		}
		Heap[Heap_Border].u = U;
		Heap[Heap_Border].v = V;
		Heap[Heap_Border].weigh = Weigh;
		Heap_Border++;
		Fix_Up(Heap_Border - 1);
		return true;
	}
	const Edge & get_Min()
	{
		return Heap[1];
	}
	void Extract_Min()	//删除最小堆结点, 并返回其到达时间
	{
		Heap[1] = Heap[--Heap_Border];
		Fix_Down(1);
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
					if (Heap[Min_index].weigh < Heap[Start].weigh)	//修正堆
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
					if (Heap[Left(Start)].weigh < Heap[Start].weigh)
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
			if (Heap[Parent(Start)].weigh > Heap[Start].weigh)
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
	~Min_Heap()
	{
		delete [] Heap;
	}
};

class Disjoint_Set
{
private:
	int *Set = nullptr;
	int Length = 0;
public:
	Disjoint_Set(int N)		//初始 N 个集合
	{
		Length = N + 1;
		Set = new int [N + 1];
		for (int i = 0; i < Length; i++)
		{
			Set[i] = i;
		}
	}
	~Disjoint_Set()
	{
		delete [] Set;
	}
	int Find_Set(int i)
	{
		if (Set[i] != i)
		{
			Set[i] = Find_Set(Set[i]);
		}
		return Set[i];
	}
	void Union(int i, int j)	//i, j 所在集合合并
	{
		int Root_i = Find_Set(i);
		int Root_j = Find_Set(j);
		Set[Root_j] = Set[Root_i];
	}
};

int main()
{
	int N = 0;
	int M = 0;
	int Total_Cost = 0;

	cin >> N;
	cin >> M;

	int u = 0, v = 0, weight = 0;

	Min_Heap *M_Heap = new Min_Heap(M);
	Disjoint_Set *Dis_Set = new Disjoint_Set(N);

	for (int i = 0; i < M; i++)
	{
		cin >> u;
		cin >> v;
		cin >> weight;
		M_Heap->Push(u, v, weight);
	}

	while (!(M_Heap->isEmpty()))
	{
		Edge temp = M_Heap->get_Min();
		if (Dis_Set->Find_Set(temp.u) != Dis_Set->Find_Set(temp.v))
		{
			Dis_Set->Union(temp.u, temp.v);
			Total_Cost += temp.weigh;
		}
		M_Heap->Extract_Min();
	}

	cout << Total_Cost << endl;

	return 0;
}