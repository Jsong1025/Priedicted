// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "iostream"
#include "string"
#include "stack"
#include "vector"
using namespace std;

const int row = 5;
const int col = 5;
string M[row][col];
vector<char> Vt;			//�ս��

bool findVector(vector<char> v , char c)
{
	return true;
}

string findInMTable(char X,char a)
{
	return "";
}

bool action ()
{
	char X;
	char a;

	stack<char> priedStack;		//����ջ
	stack<char> strStack;		//ʣ����Ŵ�ջ

	while(true)
	{
		
		X = priedStack.top();
		priedStack.pop();
		a = strStack.top();
		strStack.pop();

		if(findVector(Vt,X))	//��Vt�б���X
		{
			if(X == a)
				continue;
			else
				return false;
		}
		else
		{
			
			if(X == '#')
			{
				if(X == a)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				//��Ԥ��������в���X��a������з�������û�з���null
				string tmp = findInMTable(X,a);
				 if(tmp.empty())
				 {
					 return false;
				 }
				 else
				 {
					const char *c = tmp.c_str();
					char first_char = *c;
					priedStack.push(first_char);
				 }
			}
		}
	}
}

int main(int argc, char* argv[])
{
	action ();
	return 0;
}

/*
LinkList getMTable(G)
{
	//������ݹ�
	Gram G_new = removeLeftRecursion(G);
	//��ȡFIST����
	Collection fist = getFIST(G_new);
	//��ȡFOLLOW����
	Collection follow = getFOLLOW(G_new);
	//��ȡSELECT����
	Collection select = getSELECT(G_new,first,follow);

	// ���������ս��
	for(j=1;j<(Vt.lenth+1);j++)
	{
		M[0][j] = vt[j];
	}
	for(i=1;i<(G.length+1);i++)
	{
		M[i][0] = G[i][0];	//�������з��ս��
		for(j=1;j<(Vt.lenth+1);j++)
		{
			if(findSELECT(select,Vt[j]))	//�����SELECT�ҵ��˵�ǰ�ս��
			{
				M[i][j] = G[j];		//����ǰ�������ķ��ĺ�벿������Ԥ���������
			}
			else
			{
				M[i][j] = NULL;
			}
		}
	}

}

Gram removeLeftRecursion(Gram G)
{
	for(i=0;i<G.lenth;i++)
	{
		// �滻
		for(j=1;j<(G.lenth-1);j++)
		{
			adjTable ai = G[j];		//���ʽai�����ڽӱ�
			addList(G[i],G[j][0],ai);	//��Ai�в���Aj������У���Aj�ı��ʽlist����

		}

		while((i=findList(G[i],G[i][0])!=length)		// ��ai�ı��ʽ�в���������
		{
			// ������ݹ�
			
			// ��ȡiǰ����Ĳ���ʽ
			head = getHead(G[i],i);
			tail = getTail(G[i],r);
			
			// �滻
			char A = G[i][r] + G.length;
			removeRecursion(G[i],newpoint);	//�޸ĵ�ǰ���ʽ���������µı��ʽ
			Gadd(G,newpoint);				//���µı��ʽ�����ķ�G��
		}
	}
}

Collection getFIST(G_new)
{

}

  */