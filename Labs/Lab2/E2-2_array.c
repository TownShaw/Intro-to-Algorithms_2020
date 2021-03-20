#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 6
#define HASH_LENGTH 14348907
int Hash_Name[HASH_LENGTH];

int Convert(char *str)
{
	int sum = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		sum = sum * 26 + (str[i] - 'a');
	}
	return sum;
}
void goBack(int *Array, int Right, int NewRight, int *Name_Kind)
{//右端从 Right 回退到 NewRight, 同时更新新窗口的名字种类
	for (int i = Right; i > NewRight; i--)
	{
		if (--Hash_Name[Array[i]] == 0)
		{
			(*Name_Kind)--;
		}
	}
}

int main()
{
	int num = 0;	// n 个子队
	int length = 0;	// 队列长度
	int k = 0;	// k 个不重复的名字, 窗口大小
	int Name_Kind = 0;	//当前窗口中不同名字的个数

	scanf("%d", &length);
	scanf("%d", &k);

//	NameTree *Tree = init_NameTree();
	int Left = 0;				//滑动窗口的左端
	int Right = -1;				//滑动窗口的右端


	char Input_str[MAX_LENGTH];
	int *Array = (int *)malloc(sizeof(int) * length);
	memset(Hash_Name, 0, HASH_LENGTH);
	for (int i = 0; i < length; i++)
	{
		scanf("%s", Input_str);
		Array[i] = Convert(Input_str);
	}

	while (Left < length - k + 1)
	{
		if (Name_Kind < k)
		{
			if (Right + 1 >= length)
			{
				break;
			}
			Hash_Name[Array[++Right]]++;
			if (Hash_Name[Array[Right]] == 1)
			{
				Name_Kind++;
			}
		}
		else if (Name_Kind == k)
		{
			num++;
			Right++;
			if (Right == length)
			{
				if (--Hash_Name[Array[Left++]] == 0)
				{
					Name_Kind--;
				}
				for (Right = length - 1; Right > Left + k - 1; Right--)
				{
					if (--Hash_Name[Array[Right]] == 0)
					{
						Name_Kind--;
					}
				}
				continue;
			}
			else
			{
				Hash_Name[Array[Right]]++;
			}
			if (Hash_Name[Array[Right]] == 1)
			{
				Name_Kind++;
			}
		}
		else
		{
			if (--Hash_Name[Array[Left++]] == 0)
			{
				Name_Kind--;
			}
			if (Name_Kind == k)
			{
				num++;
				Right++;
				if (Right == length)
				{
					if (--Hash_Name[Array[Left++]] == 0)
					{
						Name_Kind--;
					}
					for (Right = length - 1; Right > Left + k - 1; Right--)
					{
						if (--Hash_Name[Array[Right]] == 0)
						{
							Name_Kind--;
						}
					}
					continue;
				}
				else
				{
					Hash_Name[Array[Right]]++;
					if (Hash_Name[Array[Right]] == 1)
					{
						Name_Kind++;
					}
					continue;
				}
			}
			while (Name_Kind >= k && Right >= Left)
			{
				if (Name_Kind == k)
				{
					num++;
				}
				if (--Hash_Name[Array[Right--]] == 0)
				{
					Name_Kind--;
				}
			}
			if (--Hash_Name[Array[Left++]] == 0)
			{
				Name_Kind--;
			}
		}
	}

	printf("%d", num);

	free(Array);
	return 0;
}