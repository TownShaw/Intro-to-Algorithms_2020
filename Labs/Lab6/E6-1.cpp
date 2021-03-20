#include <iostream>
#include <cstring>

using namespace std;

char Pattern[10001];
char Text[1000001];
int *Compute_Perfix(char *Pattern)
{
    int m = strlen(&Pattern[1]);
    int *Pi = new int [10001];
    Pi[1] = 0;
    int k = 0;
    for (int i = 2; i <= m; i++)
    {
        while (k > 0 && Pattern[k + 1] != Pattern[i])
        {
            k = Pi[k];
        }
        if (Pattern[k + 1] == Pattern[i])
        {
            k++;
        }
        Pi[i] = k;
    }
    return Pi;
}

int KMP_Matcher(char *Pattern, char *Text)
{
    int m = strlen(&Pattern[1]);
    int n = strlen(&Text[1]);
    int *Pi = Compute_Perfix(Pattern);
    int q = 0;
    int num = 0;
    for (int i = 1; i <= n; i++)
    {
        while (q > 0 && Pattern[q + 1] != Text[i])
        {
            q = Pi[q];
        }
        if (Pattern[q + 1] == Text[i])
        {
            q++;
        }
        if (q == m)
        {
            num++;
            q = Pi[q];
        }
    }
    delete [] Pi;
    return num;
}

int main()
{
    int Group_Num = 0;

    cin >> Group_Num;

    for (int i = 0; i < Group_Num; i++)
    {
        cin >> &Pattern[1];
        cin >> &Text[1];
        cout << KMP_Matcher(Pattern, Text) << endl;
    }

    return 0;
}