#include <iostream>
#include <cstring>
#define INFTY 200

using namespace std;

struct Vertex
{
	bool has_Find_Min = false;	//是否已经找到最短路径
	int d = INFTY;
	struct Edge *First_Edge = nullptr;
};

struct Edge
{
	int to_Vex;		//指向的顶点
	int weigh;
	struct Edge *Next_Edge = nullptr;
};

struct Vex_Heap
{
	int Vex;
	int d;
};

class Min_Heap
{
private:
	int Heap_Border = 0;	//边界
	int MAX_SIZE = 0;
	Vex_Heap* Heap = nullptr;

	inline int Min(int i, int j)	//返回剩余执行时间较小的下标
	{
		return (Heap[i].d < Heap[j].d) ? i : j;
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
		Vex_Heap temp = Heap[i];
		Heap[i] = Heap[j];
		Heap[j] = temp;
	}

public:
	Min_Heap(int N)
	{
		Heap = new Vex_Heap[N + 1];
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
	bool Push(const int Vex, const int d)
	{
		Heap[Heap_Border].Vex = Vex;
		Heap[Heap_Border].d = d;
		if (Heap_Border == MAX_SIZE)
		{
			Fix_Up(Heap_Border);
		}
		else
		{
			Heap_Border++;
			Fix_Up(Heap_Border - 1);
		}
		return true;
	}
	const Vex_Heap & get_Min()
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
					if (Heap[Min_index].d < Heap[Start].d)	//修正堆
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
					if (Heap[Left(Start)].d < Heap[Start].d)
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
			if (Heap[Parent(Start)].d > Heap[Start].d)
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

class Oriented_G
{
private:
	int Length = 0;
	int Num_of_Vertices = 0;	//顶点个数
public:
	Vertex *Vertices = nullptr;		//各顶点
	Oriented_G(int N)
	{
		Length = N + 1;
		Num_of_Vertices = N;
		Vertices = new Vertex [Length];
	}
	~Oriented_G()
	{
		delete [] Vertices;
	}
	void Add_Edge(int u, int v, int weigh)		//增加边 (u, v), 权重为 weigh
	{
		Edge *pTemp = Vertices[u].First_Edge;
		for ( ; pTemp != nullptr; pTemp = pTemp->Next_Edge)
		{
			if (pTemp->to_Vex == v)
			{
				pTemp->weigh = (weigh < pTemp->weigh) ? weigh : pTemp->weigh;
				return ;
			}
		}
		Edge *pNew = new Edge;
		pNew->to_Vex = v;
		pNew->weigh = weigh;

		pTemp = Vertices[u].First_Edge;		//头插法
		pNew->Next_Edge = pTemp;
		Vertices[u].First_Edge = pNew;
	}
	inline void Initialize(int S)
	{
		Vertices[S].d = 0;
		Vertices[S].has_Find_Min = false;
	}
	void Relax(int u, int v, int weigh)		//对边 (u, v)进行松弛操作
	{
		if (Vertices[v].d > Vertices[u].d + weigh)
		{
			Vertices[v].d = Vertices[u].d + weigh;
		}
	}
	void Dijkstra(Min_Heap *M_Heap, int S)	//源点为 s 的 Dijstra 算法
	{
		this->Initialize(S);
		int has_Find_Min_Num = 0;	//已经找到最短路径节点的个数, 初始为 1, 因为源点 S 默认为 0
		int Min_Vertex = S;		//当前找到最短路径, 但离源点 S 最近的顶点标号
		M_Heap->Push(S, 0);
		while (has_Find_Min_Num <= Num_of_Vertices)
		{
			if (!M_Heap->isEmpty())
			{
				Min_Vertex = M_Heap->get_Min().Vex;
				Vertices[Min_Vertex].has_Find_Min = true;
				has_Find_Min_Num++;
			}
			else
			{
				break;
			}
			for (Edge *pTemp = Vertices[Min_Vertex].First_Edge; pTemp != nullptr; pTemp = pTemp->Next_Edge)
			{
				Relax(Min_Vertex, pTemp->to_Vex, pTemp->weigh);
				if (!Vertices[pTemp->to_Vex].has_Find_Min)
				{
					M_Heap->Push(pTemp->to_Vex, Vertices[pTemp->to_Vex].d);
				}
			}
			M_Heap->Extract_Min();
			while ((!M_Heap->isEmpty()) && Vertices[M_Heap->get_Min().Vex].has_Find_Min)
			{
				M_Heap->Extract_Min();
			}
		}
	}
};

int main()
{
	int N = 0;
	int M = 0;
	int S = 0;
	int T = 0;

	cin >> N;
	cin >> M;
	cin >> S;
	cin >> T;

	Oriented_G *Graph = new Oriented_G(N);
	Min_Heap *M_Heap = new Min_Heap(N);

	for (int i = 0; i < M; i++)
	{
		int u = 0;
		int v = 0;
		int weigh = 0;
		cin >> u >> v >> weigh;
		Graph->Add_Edge(u, v, weigh);
	}

	Graph->Dijkstra(M_Heap, S);

	if (Graph->Vertices[T].d == INFTY)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << Graph->Vertices[T].d << endl;
	}

	return 0;
}