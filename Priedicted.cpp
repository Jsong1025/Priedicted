// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "stack"
using namespace std;


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
					if(tmp == "ε")
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

void init()
{
/*
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
	M[2][5] = "ε";
	M[2][6] = "ε";

	M[3][0] = "T";
	M[3][1] = "FS";
	M[3][2] = "";
	M[3][3] = "";
	M[3][4] = "FS";
	M[3][5] = "";
	M[3][6] = "";

	M[4][0] = "S";
	M[4][1] = "";
	M[4][2] = "ε";
	M[4][3] = "*FS";
	M[4][4] = "";
	M[4][5] = "ε";
	M[4][6] = "ε";

	M[5][0] = "F";
	M[5][1] = "i";
	M[5][2] = "";
	M[5][3] = "";
	M[5][4] = "(E)";
	M[5][5] = "";
	M[5][6] = "";

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
*/
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




void getMTable(Grammer G)
{
 	
	//消除左递归
	G.removeLeftRecursion();
	cout<<"消除左递归后："<<endl;
	G.print();

	//获取FIST集合
	vector<char> *first = G.getFIRST();
	cout<<"FIRST 集合："<<endl;
	printCollection(first,G.expresses.size());

	//获取FOLLOW集合
	vector<char> *follow = G.getFOLLOW();
	cout<<"FOLLOW 集合："<<endl;
	printCollection(follow,G.expresses.size());
/*
	//获取SELECT集合
	vector<char> *select = getSELECT(G,first,follow);
*/
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
	init();

	Grammer G = initGrammer();
	cout<<"文法G："<<endl;
	G.print();
	getMTable(G);

/*
	stack<char> priedStack;		//分析栈
	stack<char> strStack;		//剩余符号串栈

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
		printf("语法正常匹配！\n");
	}
	else
	{
		cout<<endl;
		printf("语法错误！\n");
	}
*/

	return 0;
}