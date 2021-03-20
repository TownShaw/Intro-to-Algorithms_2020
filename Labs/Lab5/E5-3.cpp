#include <iostream>
#include <cstring>
#define INFTY 200

using namespace std;

class Quene
{
private:
	int Max_Size = 0;
	int Quene_Size = 0;
	int Head = 0;
	int Tail = 0;
	int *Quene_ptr = nullptr;
public:
	Quene(int N)
	{
		Max_Size = N;
		Quene_Size = 0;
		Head = 0;
		Tail = 0;
		Quene_ptr = new int [N];
	}
	~Quene()
	{
		delete [] Quene_ptr;
	}
	inline int Next(int i)
	{
		return (i + 1) % Max_Size;
	}
	void Init_Quene()
	{
		Head = Tail = 0;
		Quene_Size = 0;
	}
	bool EnQuene(int Vex)
	{
		if (Head == Tail && Quene_Size != 0)	//已满
		{
			return false;
		}
		else
		{
			Quene_ptr[Tail] = Vex;
			Tail = Next(Tail);
			Quene_Size++;
			return true;
		}
	}
	int DeQuene()
	{
		if (Quene_Size == 0)	//为空
		{
			return -1;
		}
		else
		{
			int Vex = Quene_ptr[Head];
			Head = Next(Head);
			Quene_Size--;
			return Vex;
		}
	}
	bool isEmpty()
	{
		return (Quene_Size == 0);
	}
};

class Oriented_G	//有向图
{
private:
	int **G_Matrix = nullptr;		//图矩阵
	bool *Visited = nullptr;		//用于 BFS 时确定顶点是否被访问
	int *Pi = nullptr;				//父节点数组
	int Length = 0;
	int Vex_Num = 0;
public:
	Oriented_G(int N)	// N 个顶点
	{
		Length = N + 1;
		Vex_Num = N;
		Visited = new bool [Length];
		Pi = new int [Length];
		G_Matrix = new int* [Length];
		for (int i = 0; i < Length; i++)
		{
			G_Matrix[i] = new int [Length];
			memset(G_Matrix[i], 0, Length * sizeof(int));
		}
	}
	~Oriented_G()	//析构函数
	{
		for (int i = 0; i < Length; i++)
		{
			delete [] G_Matrix[i];
		}
		delete [] G_Matrix;
		delete [] Visited;
		delete [] Pi;
	}
	inline void Add_Edge(int u, int v, int weigh)
	{
		G_Matrix[u][v] += weigh;
	}
	inline int Item(int i, int j)
	{
//		if (i >= Length || j >= Length)
//		{
//			cout << "Index out of Range!" << endl;
//			return -1;
//		}
		return G_Matrix[i][j];
	}
	bool BFS(Quene *Q, int S, int T)		//从 S 开始的 BFS
	{
		for (int i = 0; i < Length; i++)	//初始化
		{
			Visited[i] = false;
			Pi[i] = 0;
		}
		Q->Init_Quene();
		BFS_Traverse(Q, S, T);
		return (Pi[T] != 0);	//若 T 无前驱则 S 不能到 T, 返回 false, 否则返回 true
	}
	void BFS_Traverse(Quene *Q, int S, int T)	//真正的 BFS
	{
		Q->EnQuene(S);
		Visited[S] = true;
		while (!Q->isEmpty())
		{
			int Vex = Q->DeQuene();
			if (Vex == -1)
			{
				break;
			}
			for (int i = 1; i < Length; i++)
			{
				if (G_Matrix[Vex][i] != 0 && !Visited[i])
				{
					Q->EnQuene(i);
					Visited[i] = true;
					Pi[i] = Vex;
					if (i == T)
					{
						return;
					}
				}
			}
		}
	}
	int Augment_Path_Step(int S, int T)		//得到 S ~> T 的增广路径, 并减去新增流量
	{
		int Min = INFTY;
		for (int i = T; Pi[i] != 0; i = Pi[i])
		{
			Min = (G_Matrix[Pi[i]][i] < Min) ? G_Matrix[Pi[i]][i] : Min;
		}
		for (int i = T; Pi[i] != 0; i = Pi[i])
		{
			G_Matrix[Pi[i]][i] -= Min;
		}
		return Min;
	}
};

int main()
{
	int N = 0;
	int M = 0;
	int S = 0;
	int T = 0;

	cin >> N >> M >> S >> T;

	Oriented_G *G = new Oriented_G(N);
	Quene *Q = new Quene(N);

	for (int i = 0; i < M; i++)
	{
		int u = 0;
		int v = 0;
		int weigh = 0;
		cin >> u >> v >> weigh;
		G->Add_Edge(u, v, weigh);
	}
	int Max_Flow = 0;
	while (G->BFS(Q, S, T))
	{
		Max_Flow += G->Augment_Path_Step(S, T);
	}

	cout << Max_Flow << endl;

	return 0;
}