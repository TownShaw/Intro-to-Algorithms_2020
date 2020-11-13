#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node
{
	struct Node *pNode;
}Node;

Node **initStudent(int n)
{
	Node **Student = (Node **)malloc(sizeof(Node *) * n);

	for (int i = 0; i < n; i++)
	{
		Student[i] = (Node *)malloc(sizeof(Node));
		Student[i]->pNode = Student[i];
	}

	return Student;
}

Node *Find_Set(Node *pStu)
{/*
	Node *pRoot = pStu;
	while (pRoot->pNode != pRoot)
	{
		pRoot = pRoot->pNode;
	}
	//此时 pTemp 指向根节点(或者说代表节点)

	Node *pTemp = pStu;

	while (pTemp->pNode != pTemp)
	{
		pStu->pNode = pRoot;
		pStu = pTemp;
		pTemp = pTemp->pNode;
	}

	return pRoot;
	*/

	if (pStu->pNode != pStu)
    {
    	pStu->pNode = Find_Set(pStu->pNode);
    }
  	
  	return pStu->pNode;
}

void Union_Root(Node *pRoot_1, Node *pRoot_2)
{
	pRoot_1->pNode = pRoot_2;
	pRoot_2->pNode = pRoot_2;
}

void Union(Node **Student, int i, int j)	//Student[i]与Student[j]所在的Set进行合并
{
	Node *pRoot_1 = Find_Set(Student[i]);
	Node *pRoot_2 = Find_Set(Student[j]);
	if (pRoot_1 != pRoot_2)
	{
		Union_Root(pRoot_1, pRoot_2);
	}
}

void Free_Student(Node **Student, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(Student[i]);
	}
	
	free(Student);
}

int main()
{
	int n = 0;
	int m = 0;
	int k = 0;

	scanf("%d", &n);	//学生个数
	scanf("%d", &k);	//查询次数
	scanf("%d", &m);	//关系对数

	Node **Student = initStudent(n);

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

		Node *pRoot_1 = Find_Set(Student[Stu_1]);
		Node *pRoot_2 = Find_Set(Student[Stu_2]);

		if (pRoot_1 == pRoot_2)
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}

	}

	Free_Student(Student, n);
	return 0;
}
