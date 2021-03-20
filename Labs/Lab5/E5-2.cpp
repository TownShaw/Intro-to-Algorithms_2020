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
	}
	void Relax(int u, int v, int weigh)		//对边 (u, v)进行松弛操作
	{
		if (Vertices[v].d > Vertices[u].d + weigh)
		{
			Vertices[v].d = Vertices[u].d + weigh;
		}
	}
	void Dijstra(int S)	//源点为 s 的 Dijstra 算法
	{
		this->Initialize(S);
		int has_Find_Min_Num = 1;	//已经找到最短路径节点的个数, 初始为 1, 因为源点 S 默认为 0
		int Min_Vertex = S;		//当前找到最短路径, 但离源点 S 最近的顶点标号
		while (has_Find_Min_Num <= Num_of_Vertices)
		{
			for (Edge *pTemp = Vertices[Min_Vertex].First_Edge; pTemp != nullptr; pTemp = pTemp->Next_Edge)
			{
				Relax(Min_Vertex, pTemp->to_Vex, pTemp->weigh);
			}
			Vertices[Min_Vertex].has_Find_Min = true;
			has_Find_Min_Num++;
			int Min_d = INFTY;
			for (int i = 1; i < Length; i++)
			{
				if (!(Vertices[i].has_Find_Min) && Vertices[i].d < Min_d)
				{
					Min_Vertex = i;
					Min_d = Vertices[i].d;
				}
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

	for (int i = 0; i < M; i++)
	{
		int u = 0;
		int v = 0;
		int weigh = 0;
		cin >> u >> v >> weigh;
		Graph->Add_Edge(u, v, weigh);
	}

	Graph->Dijstra(S);

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