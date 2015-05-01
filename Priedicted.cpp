// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "iostream"
#include "string"
#include "stack"
#include "vector"
using namespace std;

const int row = 6;
const int col = 7;
string M[row][col];
vector<char> Vt;			//�ս��

bool findVector(vector<char> v , char c)
{
	for(int i=0;i<v.size();i++)
	{
		if(c == v[i])
			return true; 
	}
	return false;
}

string findInMTable(char X,char a)
{
	for(int i=0;i<row;i++)
	{
		const char *y = M[i][0].c_str();	//��ȡ���ַ�
		char Y = *y;
		if( Y == X)
		{
			for(int j=1;j<col;j++)
			{
				const char *b = M[0][j].c_str();	//��ȡ���ַ�
				char c = *b;
				if(c == a)
					return M[i][j];
			}
		}
	}
	return "";
}

bool action ()
{
	char X;
	char a;

	stack<char> priedStack;		//����ջ
	stack<char> strStack;		//ʣ����Ŵ�ջ

	strStack.push('#');
	strStack.push('i');
	strStack.push('*');
	strStack.push('i');
	strStack.push('+');
	strStack.push('i');

	priedStack.push('#');
	priedStack.push('E');

	a = strStack.top();
	strStack.pop();				// ʣ����Ŵ�ջ��ջ
	while(true)
	{
		
		X = priedStack.top();
		priedStack.pop();		//����ջ��ջ

		if(findVector(Vt,X))	//��Vt�б���X
		{
			if(X == a)
			{
				a = strStack.top();
				strStack.pop();				// ʣ����Ŵ�ջ��ջ
				continue;
			}
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
				else if(tmp == "��")
				{
					continue;
				}
				else
				{
					for(int i=(tmp.size()-1);i>=0;i--)	//��tmp����ѹ�����ջ��
					{
						char c = tmp[i];
						priedStack.push(c);	
					}
				}
			}
		}
	}
}

void init()
{
	M[0][0] = "";
	M[0][1] = "i";
	M[0][2] = "+";
	M[0][3] = "*";
	M[0][4] = "(";
	M[0][5] = ")";
	M[0][6] = "#";

	M[1][0] = "E";
	M[1][1] = "TD";
	M[1][2] = "";
	M[1][3] = "";
	M[1][4] = "TD";
	M[1][5] = "";
	M[1][6] = "";

	M[2][0] = "D";
	M[2][1] = "";
	M[2][2] = "+TD";
	M[2][3] = "";
	M[2][4] = "";
	M[2][5] = "��";
	M[2][6] = "��";

	M[3][0] = "T";
	M[3][1] = "FS";
	M[3][2] = "";
	M[3][3] = "";
	M[3][4] = "FS";
	M[3][5] = "";
	M[3][6] = "";

	M[4][0] = "S";
	M[4][1] = "";
	M[4][2] = "��";
	M[4][3] = "*FS";
	M[4][4] = "";
	M[4][5] = "��";
	M[4][6] = "��";

	M[5][0] = "F";
	M[5][1] = "i";
	M[5][2] = "";
	M[5][3] = "";
	M[5][4] = "(E)";
	M[5][5] = "";
	M[5][6] = "";

	Vt.push_back('i');
	Vt.push_back('+');
	Vt.push_back('*');
	Vt.push_back('(');
	Vt.push_back(')');

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			if(M[i][j].empty())
				cout<<" \t";
			else
				cout<<M[i][j]<<"\t";
		cout<<endl;
	}
	cout<<endl;

	cout<<"Vt = { ";
	for(i=0;i<Vt.size();i++)
	{
		cout<<Vt[i]<<" ,  ";
	}
	cout<<"}"<<endl;
}

int main(int argc, char* argv[])
{
	init();

	if(action ())
	{
		printf("�﷨����ƥ�䣡\n");
	}
	else
	{
		printf("�﷨����\n");
	}

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