// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "stack"
using namespace std;


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
					if(tmp == "��")
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

void initVt()
{
	Vt.push_back('i');
	Vt.push_back('+');
	Vt.push_back('*');
	Vt.push_back('(');
	Vt.push_back(')');

	cout<<"Vt = { ";
	for(int i=0;i<Vt.size();i++)
	{
		cout<<Vt[i]<<" ,  ";
	}
	cout<<"}"<<endl;
	cout<<endl;
}

Grammer initGrammer()
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

int main(int argc, char* argv[])
{
	initVt();

	Grammer G = initGrammer();
	cout<<"�ķ�G��"<<endl;
	G.print();
	G.getMTable();

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			if(M[i][j].empty())
				cout<<" \t";
			else
			{
				const char *b = M[i][j].c_str();	//��ȡ���ַ�
				char c = *b;

				if(c == 0)
					cout<<"��"<<"\t";
				else
					cout<<M[i][j]<<"\t";
			}
		cout<<endl;
	}
	cout<<endl;

/*
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

	if(action (priedStack,strStack))
	{
		cout<<endl;
		printf("�﷨����ƥ�䣡\n");
	}
	else
	{
		cout<<endl;
		printf("�﷨����\n");
	}
*/

	return 0;
}