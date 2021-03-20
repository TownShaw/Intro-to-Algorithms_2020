#include <iostream>
#include <cstring>

using namespace std;

struct Object
{
	int Weigh;	//物品重量
	int Value;	//物品价值
	int Num;	//物品个数
};

int Max_Value(int** Result, Object* obj, int kind, int volume)		//给定背包容量 Volume, 在 1 ~ kind 种物品中, 选取最大价值数
{
	if (kind == 0 || volume <= 0)
	{
		return 0;
	}
	else if (Result[kind][volume] != 0)
	{
		return Result[kind][volume];
	}
	else
	{
		int max = 0;
		for (int i = 0; i <= obj[kind].Num && i * obj[kind].Weigh <= volume; i++)
		{
			int temp = Max_Value(Result, obj, kind - 1, volume - obj[kind].Weigh * i) + obj[kind].Value * i;
			max = (max < temp) ? temp : max;
		}
		Result[kind][volume] = max;
		return max;
	}

}

int main()
{
	int n = 0;	//物品种类
	int Volume = 0;	//背包空间

	cin >> n;
	cin >> Volume;

	Object* obj = new Object [n + 1];

	for (int i = 1; i < n + 1; i++)
	{
		cin >> obj[i].Weigh;
		cin >> obj[i].Value;
		cin >> obj[i].Num;
	}
	
	int** Result = new int* [n + 1];	//结果表
	for (int i = 0; i < n + 1; i++)
	{
		Result[i] = new int [Volume + 1];
		memset(Result[i], 0, sizeof(int) * (Volume + 1));
	}

	cout << Max_Value(Result, obj, n, Volume) << endl;

	for (int i = 0; i < n + 1; i++)
	{
		delete [] Result[i];
	}
	delete [] Result;

	return 0;
}