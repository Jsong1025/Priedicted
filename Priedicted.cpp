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
bool inVector(vector<char> v , char c)
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

/*
 *	消除文法G中的左递归
 */
Grammer removeLeftRecursion(Grammer G)
{
	/*
	for(int i=0;i<G.expresses.size();i++)
	{
		// 替换
		for(int j=1;j<(G.expresses.size()-1);j++)
		{
			Express e1 = G.expresses[i];
			Express e2 = G.expresses[j];
			e1.replace(e2);
			G.expresses[i] = e1;
		}
	}
	*/	

	// 消除直接左递归
	for(int i=0;i<G.expresses.size();i++)	//遍历每一条规则
	{
		Express e = G.expresses[i];
		for(int j=0;j<e.length;j++)		//遍历每一条生成式
		{
			string str = e.data[j];
			if(str[0] == e.ident)		//生成式右部的首字母和生成式左部相同，含有左递归
			{
				// 产生一个新规则
				Express f(e.ident-1);				//新规则的左部
				string *f_str = new string[2];		//新规则的生成式

				for(int k=0;k<e.length;k++)	
				{
					e.data[k] += f.ident;		//在旧规则每一条生成式后，加入新规则的左部标识符
				}

				string tmp = e.del(j);
				f_str[0] = string(tmp,1,tmp.length());	//旧规则中含有左递归的生成式，去除左递归后，放入新规则中

				char c = 0;		// 空字符 ε
				f_str[1] = c;

				f.insert(f_str,2);
				G.expresses.push_back(f);
				
				G.expresses[i] = e;
			}
		}
	}
	
	return G;
}

/*
 *	查找非终结符A的所有FRIST字符集合
 *			返回char类型的vector集合
 */
vector<char> getFirstChar(char A,Grammer G)
{
	vector<char> first;
	for(int i=0;i<G.expresses.size();i++)		//遍历每一条规则
	{
		Express e = G.expresses[i];
		if(A == e.ident)
		{
			for(int j=0;j<e.length;j++)			//遍历每一条生成式
			{
				string str = e.data[j];
				// 如果为终结符或空字符
				if(inVector(Vt,str[0]) || str[0] == 0)
					first.push_back(str[0]);
				else
				{
					//递归查询，并把查询结果压入结果集中
					vector<char> f =getFirstChar(str[0],G); 
					for(int k=0;k<f.size();k++)
						first.push_back(f[k]);
				}
			}
		}
	}
	return first;
}

/*
 *	获取语法G的FIRST集合
 */
vector<char> *getFIRST(Grammer G)
{
	vector<char> *first = new vector<char>[G.expresses.size()];
	for(int i=0;i<G.expresses.size();i++)
	{
		Express e = G.expresses[i];
		first[i].push_back(e.ident);

		for(int j=0;j<e.length;j++)
		{
			// 逐层遍历，如果生成式的首字母为终结符，或空字符。
			string str = e.data[j];
			if(inVector(Vt,str[0]) || str[0] == 0)
				first[i].push_back(str[0]);
			else
			{
				//递归查询，并把查询结果压入当前FIRST集中
				vector<char> f =getFirstChar(str[0],G); 
				for(int k=0;k<f.size();k++)
					first[i].push_back(f[k]);
			}
		}
	}

	return first;
}

/*
 *	查找标识符A对应的集合
 *			A：要查找的非终结符
 *			l：查找长度
 *			c：集合数组
 */
vector<char> findVector(char A,int l,vector<char> c[])
{
	vector<char> f;
	for(int i=0;i<=l;i++)
	{
		if(c[i][0] == A)
			f = c[i];
	}
	return f;
}

vector<char> getFollowChar(char A,int x,Grammer G,vector<char> *fs)
{
	vector<char> follow;

	for(int i=G.expresses.size()-1;i>=0;i--)
	{
		Express e2 = G.expresses[i];
		for(int j=0;j<e2.length;j++)
		{
			string str = e2.data[j];

			int n = str.find(A);		//在所有生成式右部寻找C
			if(n == -1 || A == e2.ident)
				continue;
			else if(n == (str.size()-1))		//在其他产生式中找到找到，且为右部最后
			{
				vector<char> f = findVector(e2.ident,x,fs);
				for(int k=1;k<f.size();k++)
				{
					if(f[k] != 0 && !inVector(follow,f[k]))
						follow.push_back(f[k]);
				}
			}
			else
			{
				if(inVector(Vt,str[n+1]))			//紧后的为终结符
					follow.push_back(str[n+1]);
				else			//非终结符，获取其FIRST集合
				{
					vector<char> f = getFirstChar(str[n+1],G);
					for(int k=0;k<f.size();k++)
					{
						if(f[k] != 0 && !inVector(follow,f[k]))
							follow.push_back(f[k]);
					}
					if(inVector(f,0))
					{
						vector<char> f = findVector(e2.ident,x,fs);
						for(int k=1;k<f.size();k++)
						{
							if(f[k] != 0 && !inVector(follow,f[k]))
								follow.push_back(f[k]);
						}
					}
				}
			}
		}
	}
	return follow;
}
/*
 *  获取FOLLOW集合
 */
vector<char> *getFOLLOW(Grammer G)
{
	vector<char> *follow = new vector<char>[G.expresses.size()];
	for(int i=0;i<G.expresses.size();i++)
	{
		Express e1 = G.expresses[i];
		char C = e1.ident;				//当前标识符
		follow[i].push_back(C);

		vector<char> f = getFollowChar(C,i,G,follow);
		for(int l=0;l<f.size();l++)
			follow[i].push_back(f[l]);

		if(!inVector(follow[i],'#'))
			follow[i].push_back('#');

	}
	return follow;
}

vector<char> *getSELECT(Grammer G,vector<char> *fist,vector<char> *follow)
{
	vector<char> *select = new vector<char>[G.expresses.size()];
	return select;
}

/*
 *	打印集合
 */
void printCollection(vector<char> list[],Grammer G)
{
	for(int i=0;i<G.expresses.size();i++)
	{
		Express e = G.expresses[i];
		cout<<list[i][0]<<" : ";
		for(int j=1;j<list[i].size();j++)
		{
			if(list[i][j]==0)
			{
				cout<<"ε"<<"  ";
			}
			else
			{
				cout<<list[i][j]<<"  ";
			}
		}
		cout<<endl;
	}
}

void getMTable(Grammer G)
{
 	
	//消除左递归
	G = removeLeftRecursion(G);
	cout<<"消除左递归后："<<endl;
	G.print();

	//获取FIST集合
	vector<char> *first = getFIRST(G);
	cout<<"FIRST 集合："<<endl;
	printCollection(first,G);

	//获取FOLLOW集合
	vector<char> *follow = getFOLLOW(G);
	cout<<"FOLLOW 集合："<<endl;
	printCollection(follow,G);

	//获取SELECT集合
	vector<char> *select = getSELECT(G,first,follow);

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