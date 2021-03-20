#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/********************************************************************
 * 题目见文件E2-EX
 * ******************************************************************/
/******************************
 * 此题可以由贪心算法来写，先求出最大的危险系数，将其断开，如果可以断开，那就继续迭代
 * 如果无法断开则当前危险系数则为最大危险系数
 * 用并查集来表示是否位于同一个仓库，每个并查集有一个相斥集
 * 且并查集个数定为偶数个
 * 再考虑求最大的危险系数，这个可以用max heap，tree等结构
 * 以下用的就是max heap
 * ***************************/
#define NIL -1

typedef struct e_product
{
    int first;
    int next;
    int size;
    int last;
    int oppose;
}product;

typedef struct e_danger
{
    int pam1;
    int pam2;
    int value;
}danger;

int find_set(product * products, int x)
{
    return products[x].first;
}

void make_set(product * products, int x, int y)
{
    products[x].first = x;
    products[x].next = NIL;
    products[x].size = 1;
    products[x].last = x;
    products[x].oppose = y;
}

void append(product * products, int x, int y)
{
    int z;
    products[products[x].last].next = y;
    products[x].last = products[y].last;
    products[x].size += products[y].size;
    products[products[y].oppose].oppose = x;
    z = y;
    while(z != NIL)
    {
        products[z].first = x;
        z = products[z].next;
    }
}

void set_union(product * products, int x, int y)
{
    int first1,first2;
    first1 = products[x].first;
    first2 = products[y].first;
    if(products[first1].size > products[first2].size)
        append(products,first1, first2);
    else
        append(products,first2, first1);
}

void set_insert(product * products,int x,int y)
{
    products[y].first = x;
    products[y].next = NIL;
    products[products[x].last].next = y;
    products[x].size += 1;
    products[x].last = y;
}

int left(int i)
{
    return 2 * i;
}

int right(int i)
{
    return 2 * i + 1;
}

void max_heapfy(danger * dangers, int i, int size)
{
    int l,r,largest;
    danger temp;
    l = left(i);
    r = right(i);
    if(l <= size && dangers[l].value > dangers[i].value)
    {
        largest = l;
    }  
    else
    {
        largest = i;
    }
    if(r <= size && dangers[r].value > dangers[largest].value)
    {
        largest = r;
    }
    if( largest != i)
    {
        temp.pam1 = dangers[largest].pam1;
        temp.pam2 = dangers[largest].pam2;
        temp.value = dangers[largest].value;
        dangers[largest].pam1 = dangers[i].pam1;
        dangers[largest].pam2 = dangers[i].pam2;
        dangers[largest].value = dangers[i].value;
        dangers[i].pam1 = temp.pam1;
        dangers[i].pam2 = temp.pam2;
        dangers[i].value = temp.value;
        max_heapfy(dangers,largest,size);
    }
}

void build_max_heap(danger * dangers, int size)
{
    int i;
    for(i = size / 2; i > 0; i --)
    {
        max_heapfy(dangers,i,size);
    }
}

int pop_max_heap(danger * dangers, int size, danger* pop)
{
    pop->pam1 = dangers[1].pam1;
    pop->pam2 = dangers[1].pam2;
    pop->value = dangers[1].value;
    dangers[1].pam1 = dangers[size].pam1;
    dangers[1].pam2 = dangers[size].pam2;
    dangers[1].value = dangers[size].value;
    max_heapfy(dangers,1,size - 1);
    return size - 1;
}

int find_max(product * products, danger * dangers, int m_danger)
{
    int size;
    danger max_pop;
    int pam_first1,pam_first2;
    int oppose1,oppose2;
    size = m_danger;
    build_max_heap(dangers,size);
    while(size >= 0)
    {
        if(size == 0)
        {
            return 0;
        }
        size = pop_max_heap(dangers,size,&max_pop);
        pam_first1 = products[max_pop.pam1].first;
        pam_first2 = products[max_pop.pam2].first;
        if(pam_first1 == NIL && pam_first2 == NIL)
        {
            if(max_pop.pam1 == max_pop.pam2)
                break;
            make_set(products,max_pop.pam1,max_pop.pam2);
            make_set(products,max_pop.pam2,max_pop.pam1);
        }
        else if(pam_first1 == NIL)
        {
            set_insert(products,products[pam_first2].oppose,max_pop.pam1);
        }
        else if(pam_first2 == NIL)
        {
            set_insert(products,products[pam_first1].oppose,max_pop.pam2);
        }
        else
        {
            oppose1 = products[pam_first1].oppose;
            oppose2 = products[pam_first2].oppose;
            if(oppose1 == pam_first2)
            {
                continue;
            }
            else if(pam_first1 == pam_first2)
            {
                break;
            }
            else
            {
                set_union(products,pam_first1,oppose2);
                set_union(products,pam_first2,oppose1);
            }
            
        }
        
    }
    return max_pop.value;
}

int main()
{
    int n_nums,m_lines;
    int i;
    int pam1,pam2;
    int max;
    product * products;
    danger * dangers;
    scanf("%d%d",&n_nums,&m_lines);
    products = (product *)malloc(sizeof(product) * (n_nums + 1));
    dangers = (danger *)malloc(sizeof(danger) * (m_lines + 1));
    for(i = 0; i <= n_nums; i++)
    {
        products[i].first = NIL;
    }
    for(i = 1; i <= m_lines; i++)
    {
        scanf("%d%d%d",&dangers[i].pam1,&dangers[i].pam2,&dangers[i].value);
    }
    max = find_max(products,dangers,m_lines);
    printf("%d",max);
    //system("pause");
    return 0;
}