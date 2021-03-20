#include <iostream>

using namespace std;

struct Page
{
	int page;
	int next_page_index;	//下一个相同页表的下标
};

bool isHit(Page* Frames, int length, int page)
{
	for (int i = 0; i < length; i++)
	{
		if (Frames[i].page == page)
		{
			Frames[i].next_page_index = 0;
			return true;
		}
	}
	return false;
}

void Replace_Page(Page* Frames, int Frames_length, int* Pages, int Pages_length, int page_index)
{//替换 page
	int max = 0;	//最远的距离
	int index = 0;	//距离最远的页帧下标
	for (int i = 0; i < Frames_length; i++)
	{//页帧中每一项都考察一遍
		if (Frames[i].next_page_index != 0)
		{
			int next_index = Frames[i].next_page_index;
			if (next_index > max)
			{
				max = next_index;
				index = i;
			}
			continue;
		}
		int j = page_index;
		for (j = page_index; j < Pages_length; j++)
		{
			if (Pages[j] == Frames[i].page)
			{
				if (j > max)
				{
					max = j;
					index = i;
				}
				Frames[i].next_page_index = j;
				break;
			}
		}
		if (j == Pages_length)
		{
			max = j;
			index = i;
			break;
		}
	}
	Frames[index].page = Pages[page_index];
	Frames[index].next_page_index = 0;
}

int main()
{
	int N = 0;	// Num of Page
	int K = 0;	// Num of Frame

	cin >> N;
	cin >> K;

	int* Pages = new int [N];
	Page* Frames = new Page [K];

	for (int i = 0; i < N; i++)
	{
		cin >> Pages[i];
	}
	for (int i = 0; i < K; i++)
	{
		Frames[i].page = -1;	//-1 代表未使用
		Frames[i].next_page_index = 0;
	}

	int Free_Frame = K;
	int Miss_Time = 0;		//Miss 次数

	int Start = 0;

	for (Start = 0; Free_Frame > 0 && Start < N; Start++)
	{
		int page = Pages[Start];
		if (!isHit(Frames, K - Free_Frame, page))
		{
			Frames[K - Free_Frame].page = page;
			Free_Frame--;
			Miss_Time++;
		}
	}

	for (int i = Start; i < N; i++)
	{
		if (!isHit(Frames, K, Pages[i]))
		{
			Miss_Time++;
			Replace_Page(Frames, K, Pages, N, i);
		}
	}

	cout << Miss_Time << endl;

	delete [] Frames;
	delete [] Pages;

	return 0;
}