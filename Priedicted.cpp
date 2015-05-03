// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "stack"
using namespace std;

Grammer initGrammer(string **g,int x,int y)
{
	Grammer G;

	Express e('E');
	string *e_str = new string[2];
	e_str[0] = "E+T";
	e_str[1] = "T";
	e.insert(e_str,2);
	G.expresses.push_back(e);

	Express t('T');
	string *t_str = new string[2];
	t_str[0] = "T*F";
	t_str[1] = "F";
	t.insert(t_str,2);
	G.expresses.push_back(t);

	Express f('F');
	string *f_str = new string[2];
	f_str[0] = "i";
	f_str[1] = "(E)";
	f.insert(f_str,2);
	G.expresses.push_back(f);

	return G;
}

/*
 *	���ж��߼�
 */
bool action (stack<char> priedStack,stack<char> strStack)
{
	char X;
	char a;
	int step = 0;

	cout<<"-------��������-------"<<endl;
	cout<<"����\t��������"<<endl;
	a = strStack.top();
	strStack.pop();				// ʣ����Ŵ�ջ��ջ
	
	while(true)
	{
		cout<<step++<<"\t";
		
		X = priedStack.top();
		priedStack.pop();		//����ջ��ջ

		if(inVector(Vt,X))	//��Vt�б���X
		{
			if(X == a)
			{
				cout<<"\""<<a<<"\" ƥ��"<<endl;

				a = strStack.top();
				strStack.pop();				// ʣ����Ŵ�ջ��ջ
				continue;
			}
			else
				cout<<"�﷨����"<<endl;
				return false;
		}
		else
		{
			
			if(X == '#')
			{
				if(X == a)
				{
					cout<<"����"<<endl;
					return true;
				}
				else
				{
					cout<<"�﷨����"<<endl;
					return false;
				}
			}
			else
			{
				//��Ԥ��������в���X��a������з�������û�з���null
				string tmp = findInMTable(X,a);
				if(tmp.empty())
				{
					cout<<"�﷨����"<<endl;
					return false;
				}
				else
				{
					cout<<X<<" -> "<<tmp<<endl;
					if(tmp[0] == 0)		//�մ�
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
}

int main(int argc, char* argv[])
{
	stack<char> priedStack;		//����ջ
	stack<char> strStack;		//ʣ����Ŵ�ջ

	char c[5] = {'i','+','*','(',')'};	//�ս������Vt
	string str = "i+i*i#";		//Ҫ�����ľ���

	const int x = 2;
	const int y = 2;
	string a[x][y] = {{"1","2"},{"1","2"}};

	string **g = new string*[2];
	for(int i=0;i<x;i++)
		g[i] = a[i];

	initVt(c,5);		//��ʼ���ս������

	for(i=(str.size()-1);i>=0;i--)
		strStack.push(str.at(i));		//��Ҫ�����ľ�������ѹ�����ջ��

	Grammer G = initGrammer(g,x,y);	//��ʼ���ķ�
	cout<<"�ķ�G��"<<endl;
	G.print();

	G.getMTable();		//��ȡԤ�������
	printMTable();

	//��#���ķ�G�ĵ�һ�����ս��ѹ�����ջ
	priedStack.push('#');
	priedStack.push(G.expresses[0].ident);

	//START
	if(action(priedStack,strStack))
	{
		cout<<endl;
		printf("�﷨����ƥ�䣡\n");
	}
	else
	{
		cout<<endl;
		printf("�﷨����\n");
	}

	return 0;
}