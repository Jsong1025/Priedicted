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
vector<char> Vt;			//终结符

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
		const char *y = M[i][0].c_str();	//提取首字符
		char Y = *y;
		if( Y == X)
		{
			for(int j=0;j<col;j++)
			{
				const char *b = M[0][i].c_str();	//提取首字符
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

	stack<char> priedStack;		//分析栈
	stack<char> strStack;		//剩余符号串栈

	while(true)
	{
		
		X = priedStack.top();
		priedStack.pop();		//分析栈出栈

		a = strStack.top();
		strStack.pop();			// 剩余符号串栈出栈

		if(findVector(Vt,X))	//在Vt中遍历X
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
				//在预测分析表中查找X和a，如果有返回链表，没有返回null
				string tmp = findInMTable(X,a);
				if(tmp.empty())
				{
					return false;
				}
				else
				{
					const char *c = tmp.c_str();	//提取tmp的首字符
					char first_char = *c;
					priedStack.push(first_char);	//压入分析栈中
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{

	if(action ())
	{
		printf("语法正常匹配！\n");
	}
	else
	{
		printf("语法错误！\n");
	}
	return 0;
}

/*
LinkList getMTable(G)
{
	//消除左递归
	Gram G_new = removeLeftRecursion(G);
	//获取FIST集合
	Collection fist = getFIST(G_new);
	//获取FOLLOW集合
	Collection follow = getFOLLOW(G_new);
	//获取SELECT集合
	Collection select = getSELECT(G_new,first,follow);

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

}

Gram removeLeftRecursion(Gram G)
{
	for(i=0;i<G.lenth;i++)
	{
		// 替换
		for(j=1;j<(G.lenth-1);j++)
		{
			adjTable ai = G[j];		//表达式ai，用邻接表
			addList(G[i],G[j][0],ai);	//在Ai中查找Aj，如果有，用Aj的表达式list代替

		}

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
	}
}

Collection getFIST(G_new)
{

}

  */