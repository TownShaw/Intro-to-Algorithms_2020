#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *initStudent(int n)
{
	int *Student = (int *)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		Student[i] = i;
	}

	return Student;
}

int Find_Set(int *Student, int index)
{
	if (Student[index] != index)
    {
    	Student[index] = Find_Set(Student, Student[index]);
    }
  	
  	return Student[index];
}

void Union_Root(int *Student, int Root_1, int Root_2)
{
	Student[Root_1] = Root_2;
	Student[Root_2] = Root_2;
}

void Union(int *Student, int i, int j)	//Student[i]与Student[j]所在的Set进行合并
{
	int pRoot_1 = Find_Set(Student, i);
	int pRoot_2 = Find_Set(Student, j);
	if (pRoot_1 != pRoot_2)
	{
		Union_Root(Student, pRoot_1, pRoot_2);
	}
}


int main()
{
	int n = 0;
	int m = 0;
	int k = 0;

	scanf("%d", &n);	//学生个数
	scanf("%d", &k);	//查询次数
	scanf("%d", &m);	//关系对数

	int *Student = initStudent(n);

	for (int i = 0; i < m; i++)
	{
		int Stu_1, Stu_2;
		scanf("%d", &Stu_1);
		scanf("%d", &Stu_2);
		Union(Student, Stu_1, Stu_2);
	}

	for (int i = 0; i < k; i++)
	{
		int Stu_1, Stu_2;
		scanf("%d", &Stu_1);
		scanf("%d", &Stu_2);

		int pRoot_1 = Find_Set(Student, Stu_1);
		int pRoot_2 = Find_Set(Student, Stu_2);

		if (pRoot_1 == pRoot_2)
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}

	}

	free(Student);
	return 0;
}
