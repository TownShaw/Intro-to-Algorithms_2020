#include <iostream>

using namespace std;

class Matrix_Sol
{
private:
public:
	char** Matrix;
	int row;	//矩阵行
	int col;	//矩阵列

	Matrix_Sol()
	{
		Matrix = nullptr;
	}
	Matrix_Sol(int n, int m)
	{
		row = n;
		col = m;
		Matrix = new char* [n];
		for (int i = 0; i < n; i++)
		{
			Matrix[i] = new char [m];
		}
	}
	~ Matrix_Sol();
};

int Find_Square(Matrix_Sol* Sol, int x, int y)
{	//搜查 Matrix 中以 (x, y) 为左上顶点的正方形个数
	int Square_Num = 0;
	
	int row_edge = x;
	int col_edge = y;
	
	while (row_edge < Sol->row && col_edge < Sol->col)
	{
		for (int i = row_edge, j = y; j <= col_edge; j++)	//行判断
		{
			if (Sol->Matrix[i][j] == 1)
			{
				return Square_Num;
			}
		}

		for (int i = x, j = col_edge; i <= row_edge; i++)	//列判断
		{
			if (Sol->Matrix[i][j] == 1)
			{
				return Square_Num;
			}
		}

		Square_Num++;
		row_edge++;
		col_edge++;
	}
	return Square_Num;
}

int main()
{
	int n = 0;	//n 列
	int m = 0;	//m 行

	cin >> n;
	cin >> m;

	Matrix_Sol* Sol = new Matrix_Sol(n, m);

	for (int i = 0; i < Sol->row; i++)
	{
		for (int j = 0; j < Sol->col; j++)
		{
			cin >> Sol->Matrix[i][j];
			Sol->Matrix[i][j] -= '0';
		}
	}

	int Num = 0;
	for (int i = 0; i < Sol->row; i++)
	{
		for (int j = 0; j < Sol->col; j++)
		{
			Num += Find_Square(Sol, i, j);
		}
	}

	cout << Num;

	return 0;
}