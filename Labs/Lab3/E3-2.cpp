#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

int main()
{
	int n = 0;

	cin >> n;

	int* Array = new int [n];

	for (int i = 0; i < n; i++)
	{
		cin >> Array[i];
	}

	int** Table = new int* [n];
	for (int i = 0; i < n; i++)
	{
		Table[i] = new int [n];
		memset(Table[i], 0, sizeof(int) * n);
	}

	for (int l = 2; l < n + 1; l++)
	{
		for (int i = 0; i < n - l + 1; i++)
		{
			int j = i + l - 1;
			int min = INT_MAX;
			int temp = i;
			for (int k = i; k < j; k++)
			{
				int q = Table[i][k] + Table[k + 1][j];
				if (q < min)
				{
					min = q;
					temp = k;
				}
			}
			for (int k = i; k <= j; k++)
			{
				min += Array[k];
			}
			Table[i][j] = min;
		}
	}
	cout << Table[0][n - 1] << endl;

	delete [] Array;
	for (int i = 0; i < n; i++)
	{
		delete [] Table[i];
	}
    delete [] Table;

	return 0;
}