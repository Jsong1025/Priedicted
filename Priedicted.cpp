// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "stack"
using namespace std;

const int row = 6;
const int col = 7;
string M[row][col];
vector<char> Vt;			//终结符

/*
 *	在链表v中查找c
 *			如果包含返回true，如果不包含返回false
 */
bool findVector(vector<char> v , char c)
{
	for(int i=0;i<v.size();i++)
	{
		if(c == v[i])
			return true; 
	}
	return false;
}

/*
 *	在预测分析表中查找指定文法
 *			查找成功返回指定的文法字符串，查找失败返回空字符串
 */
string findInMTable(char X,char a)
{
	for(int i=0;i<row;i++)
	{
		const char *y = M[i][0].c_str();	//提取首字符
		char Y = *y;
		if( Y == X)
		{
			for(int j=1;j<col;j++)
			{
				const char *b = M[0][j].c_str();	//提取首字符
				char c = *b;
				if(c == a)
					return M[i][j];
			}
		}
	}
	return "";
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

		if(findVector(Vt,X))	//在Vt中遍历X
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
	cout<<endl;
}

/*
 *	消除文法G中的左递归
 */
Grammer removeLeftRecursion(Grammer G)
{
	for(int i=0;i<G.length;i++)
	{
		// 替换
		for(int j=1;j<(G.length-1);j++)
		{
			Express e1 = G.expresses[i];
			Express e2 = G.expresses[j];
			e1.replace(e2);
		}
		/*
		while((i=findList(G[i],G[i][0])!=length)		// 在ai的表达式中查找其自身
		{
			// 消除左递归
			
			// 获取i前后面的产生式
			head = getHead(G[i],i);
			tail = getTail(G[i],r);
			
			// 替换
			char A = G[i][r] + G.length;
			removeRecursion(G[i],newpoint);	//修改当前表达式，并返回新的表达式
			Gadd(G,newpoint);				//将新的表达式加入文法G中
		}
		*/
	}
	return G;
}

vector<char> getFIST(Grammer G)
{
	vector<char> first;
	return first;
}

vector<char> getFOLLOW(Grammer G)
{
	vector<char> follow;
	return follow;
}

vector<char> getSELECT(Grammer G,vector<char> fist,vector<char> follow)
{
	vector<char> select;
	return select;
}

void getMTable(Grammer G)
{
 	
	//消除左递归
	Grammer G_new = removeLeftRecursion(G);
	//获取FIST集合
	vector<char> first = getFIST(G_new);
	//获取FOLLOW集合
	vector<char> follow = getFOLLOW(G_new);
	//获取SELECT集合
	vector<char> select = getSELECT(G_new,first,follow);
/*
	// 横排首行终结符
	for(j=1;j<(Vt.lenth+1);j++)
	{
		M[0][j] = vt[j];
	}
	for(i=1;i<(G.length+1);i++)
	{
		M[i][0] = G[i][0];	//竖列首行非终结符
		for(j=1;j<(Vt.lenth+1);j++)
		{
			if(findSELECT(select,Vt[j]))	//如果在SELECT找到了当前终结符
			{
				M[i][j] = G[j];		//将当前行所在文法的后半部分填入预测分析表中
			}
			else
			{
				M[i][j] = NULL;
			}
		}
	}

  */
}

Grammer initGrammer(Grammer G)
{
	Express e('E');
	string e_str = "TD";
	e.insert(e_str);
	G.expresses.push_back(e);

	Express d('D');
	string *d_str = new string[2];
	d_str[0] = "+TD";
	d_str[1] = "ε";
	d.insert(d_str,2);
	G.expresses.push_back(d);

	Express t('T');
	string t_str = "FS";
	t.insert(t_str);
	G.expresses.push_back(t);

	Express s('S');
	string *s_str = new string[2];
	s_str[0] = "*FS";
	s_str[1] = "ε";
	s.insert(s_str,2);
	G.expresses.push_back(s);

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
/*
	init();

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
	Grammer G;
	G = initGrammer(G);
	G.print();
//	getMTable(G);

	return 0;
}