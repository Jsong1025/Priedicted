#include "iostream"
#include "string"
#include "vector"
using namespace std;

const int row = 6;
const int col = 7;
string M[row][col];

vector<char> Vt;			//终结符

/*
 *	在链表v中查找c
 *			如果包含返回true，如果不包含返回false
 */
static bool inVector(vector<char> v , char c)
{
	for(int i=0;i<v.size();i++)
	{
		if(c == v[i])
			return true; 
	}
	return false;
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
 *	打印预测分析表
 */
void printMTable()
{
	cout<<"预测分析表："<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			cout<<"-------\t";
		cout<<endl;
		cout<<"|";

		for(j=0;j<col;j++)
		{
			if(M[i][j].empty())
				cout<<"\t|";
			else
			{
				const char *b = M[i][j].c_str();	//提取首字符
				char c = *b;

				if(c == 0)
					cout<<"  ε"<<"\t|";
				else
					cout<<"  "<<M[i][j]<<"\t|";
			}
		}
		cout<<endl;
	}
	for(int j=0;j<col;j++)
		cout<<"-------\t";
	cout<<endl;
}
