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
 *	主判断逻辑
 */
bool action (stack<char> priedStack,stack<char> strStack)
{
	char X;
	char a;
	int step = 0;

	cout<<"-------分析过程-------"<<endl;
	cout<<"步骤\t分析过程"<<endl;
	a = strStack.top();
	strStack.pop();				// 剩余符号串栈出栈
	
	while(true)
	{
		cout<<step++<<"\t";
		
		X = priedStack.top();
		priedStack.pop();		//分析栈出栈

		if(inVector(Vt,X))	//在Vt中遍历X
		{
			if(X == a)
			{
				cout<<"\""<<a<<"\" 匹配"<<endl;

				a = strStack.top();
				strStack.pop();				// 剩余符号串栈出栈
				continue;
			}
			else
				cout<<"语法错误"<<endl;
				return false;
		}
		else
		{
			
			if(X == '#')
			{
				if(X == a)
				{
					cout<<"接受"<<endl;
					return true;
				}
				else
				{
					cout<<"语法错误"<<endl;
					return false;
				}
			}
			else
			{
				//在预测分析表中查找X和a，如果有返回链表，没有返回null
				string tmp = findInMTable(X,a);
				if(tmp.empty())
				{
					cout<<"语法错误"<<endl;
					return false;
				}
				else
				{
					cout<<X<<" -> "<<tmp<<endl;
					if(tmp[0] == 0)		//空串
					{
						continue;
					}
					else
					{
						for(int i=(tmp.size()-1);i>=0;i--)	//将tmp逆序压入分析栈中
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
	stack<char> priedStack;		//分析栈
	stack<char> strStack;		//剩余符号串栈

	char c[5] = {'i','+','*','(',')'};	//终结符集合Vt
	string str = "i+i*i#";		//要分析的句子

	const int x = 2;
	const int y = 2;
	string a[x][y] = {{"1","2"},{"1","2"}};

	string **g = new string*[2];
	for(int i=0;i<x;i++)
		g[i] = a[i];

	initVt(c,5);		//初始化终结符集合

	for(i=(str.size()-1);i>=0;i--)
		strStack.push(str.at(i));		//将要分析的句子逆序压入符号栈中

	Grammer G = initGrammer(g,x,y);	//初始化文法
	cout<<"文法G："<<endl;
	G.print();

	G.getMTable();		//获取预测分析表
	printMTable();

	//将#和文法G的第一个非终结符压入分析栈
	priedStack.push('#');
	priedStack.push(G.expresses[0].ident);

	//START
	if(action(priedStack,strStack))
	{
		cout<<endl;
		printf("语法正常匹配！\n");
	}
	else
	{
		cout<<endl;
		printf("语法错误！\n");
	}

	return 0;
}