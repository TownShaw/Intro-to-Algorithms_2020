#include <iostream>
#include <cstring>

using namespace std;

enum ColorType {WHITE, GRAY, BLACK};

struct Vertex
{
	enum ColorType Color;
	int d;		//发现时间
	int f;		//结束时间
	int Pi;		//前驱
};

bool **G_Matrix = nullptr;		//图矩阵
bool **G_Matrix_T = nullptr;	//转置图矩阵, 用于实现 Tanjan 算法
Vertex *Vertices = nullptr;
int Length = 0;
int Vex_Num = 0;
int Time_Count = 0;		//DFS 时使用的计时器

void Add_Edge(int u, int v)
{
	G_Matrix[u][v] = true;
}

void Trans_G()
{
	G_Matrix_T = new bool* [Length];
	for (int i = 0; i < Length; i++)
	{
		G_Matrix_T[i] = new bool [Length];
		for (int j = 0; j < Length; j++)
		{
			G_Matrix_T[j][i] = false;
		}
	}
	for (int i = 0; i < Length; i++)
	{
		for (int j = 0; j < Length; j++)
		{
			G_Matrix_T[j][i] = G_Matrix[i][j] ? true : false;
		}
	}
}

bool DFS(bool **Graph_Matrix)		//从 1 开始的 DFS, 若 Transpose == true, 则对转置图进行 DFS, 否则对原图 DFS
{
	for (int i = 0; i < Length; i++)
	{
		Vertices[i].Color = ColorType::WHITE;
		Vertices[i].d = Vertices[i].f = 0;
		Vertices[i].Pi = 0;
	}
	Time_Count = 0;
	for (int i = 1; i < Length; i++)
	{
		DFS_Traverse(i, Graph_Matrix);
	}
	return true;
}

void DFS_Traverse(int S, bool **Graph_Matrix)	//对 Graph_Matrix 指向的矩阵进行 DFS
{
	Vertices[S].Color = ColorType::GRAY;
	Vertices[S].d = ++Time_Count;
	for (int i = 1; i < Length; i++)
	{
		if (Graph_Matrix[S][i] && Vertices[i].Color == ColorType::WHITE)
		{
			Vertices[i].Color = ColorType::GRAY;
			Vertices[i].Pi = S;
			DFS_Traverse(i, Graph_Matrix);
		}
	}
	Vertices[S].Color = ColorType::BLACK;
	Vertices[S].f = ++Time_Count;
}

void Tanjan()
{
	DFS(G_Matrix);
}

int main()
{
	int N = 0;
	int M = 0;

	cin >> N >> M;

	Length = N + 1;
	Vex_Num = N;
	G_Matrix = new bool* [Length];
	Vertices = new Vertex [Length];
	for (int i = 0; i < Length; i++)
	{
		G_Matrix[i] = new bool [Length];
		memset(G_Matrix[i], false, Length);
	}

	for (int i = 0; i < M; i++)
	{
		int u = 0;
		int v = 0;
		cin >> u >> v;
		Add_Edge(u, v);
	}
	Trans_G();



	for (int i = 0; i < Length; i++)
	{
		delete [] G_Matrix[i];
	}
	delete [] G_Matrix;
	for (int i = 0; i < Length; i++)
	{
		delete [] G_Matrix_T[i];
	}
	delete [] G_Matrix_T;
	delete [] Vertices;

	return 0;
}