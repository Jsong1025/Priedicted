#include "Function.h"
using namespace std;

class Express	//规则
{
public:
	int length;		//当前生成式个数
	char ident;		//生成式左部
	string *data;	//生成式右部数

	Express();
	Express(char c);

	//	在规则中插入新的生成式
	void insert(string str);
	void insert(string str[],int l);

	//	删除第n条生成式
	string del(int n);

	//	将生成式中的e标识符，用e中的生成数组替换
	void replace(Express e);

	//  判断当前规则是否能含有空串
	bool haveEmptyStr();

	void print();

};

/*===================================================================================*/

Express::Express()
{
	length = 0;
	data = NULL;
}
Express::Express(char c)
{
	ident = c;
	length = 0;
	data = NULL;
}

/*
 *	在规则中插入新的生成式（多条）
 *		str :	要插入的生成式数组
 *		l   :	要插入的长度
 */
void Express::insert(string str[],int l)
{
	if(length != 0)
	{
		string *array = new string[length];
		for(int i=0;i<length;i++)
			array[i] = data[i];

		length += l;
		data = new string[length];
		for(i=0;i<(length-l);i++)
			data[i]=array[i];
		for(i=length;i<l;i++)
			data[i]=str[i];
	}
	else
	{
		length = l;
		data = new string[length];
		for(int i=0;i<l;i++)
			data[i]=str[i];
	}
}

/*
 *	在规则中插入新的生成式（单条）
 *		str :	要插入的生成式
 */
void Express::insert(string str)
{
	if(length != 0)
	{
		string *array = new string[length];
		for(int i=0;i<length;i++)
			array[i] = data[i];

		length ++;
		data = new string[length];
		for(i=0;i<(length-1);i++)
			data[i] = array[i];
		data[length-1] = str;
	}
	else
	{
		length = 1;
		data = new string[1];
		data[0] = str;
	}
}

/*
 *	删除第n条生成式
 */
string Express::del(int n)
{
	string *array = new string[length];
	for(int i=0;i<length;i++)
		array[i] = data[i];

	length -= 1;
	data = new string[length];
	for(i=0;i<n;i++)
		data[i] = array[i];
	for(i=n;i<length;i++)
		data[i] = array[i+1];
	return array[n];
}

/*
 *	将生成式中的e标识符，用e中的生成数组替换
 */
void Express::replace(Express e)
{
	for(int i=0;i<this->length;i++)
	{
		string str = this->data[i];
		int n = str.find(e.ident);
		if(n != -1)
		{
			for(int j=1;j<e.length;j++)
			{
				string newStr(str);
				newStr.replace(n,1,e.data[i]);
				this->insert(newStr);
			}
			str.replace(n,1,e.data[0]);
			this->data[i] = str;
		}
	}
}

/*
 *	判断当前规则是否能含有空串
 */
bool Express::haveEmptyStr()
{
	for(int i=0;i<this->length;i++)
	{
		if(this->data[i][0] == 0)
			return true;
	}
	return false;
}

void Express::print()
{
	for(int i=0;i<this->length;i++)
	{
		cout<<this->ident<<" -> ";
		if(data[i][0] == 0)
			cout<<"ε"<<endl;
		else
			cout<<data[i]<<endl;
	}
}

/*===================================================================================*/

class Grammer	//文法
{

public:
	vector<Express> expresses;	//规则集合

	Grammer(){}

	void print();

	// 判断某一个规则是否能够导出空串
	bool isEmptyStr(Express e);
	bool isEmptyStr(string str);

	// 根据规则标识符查找规则
	Express findExpress(char C);

	// 消除文法G中的左递归
	void removeLeftRecursion();

	// 获取语法G的FIRST集合
	vector<char> getFirstChar(char A);
	vector<char> *getFIRST();

	// 获取FOLLOW集合
	vector<char> getFollowChar(char A,int x,vector<char> *fs);
	vector<char> *getFOLLOW();

	// 获取SELECT集合
	vector<char> *getSELECT(vector<char> *follow);

	// 获取文法的预测分析表
	void getMTable();

	// 打印FIRST集合或FOLLOW集合
	void printCollection(vector<char> list[]);
	// 打印SELECT集合
	void printSELECT(vector<char> list[]);

};



/*=================================================================================*/


void Grammer::print()
{
	for(int i=0;i<expresses.size();i++)
	{
		expresses[i].print();
		cout<<endl;
	}
}

/*
 *	根据规则标识符查找规则
 */
Express Grammer::findExpress(char C)
{
	for(int i=0;i<expresses.size();i++)
	{
		if(expresses[i].ident == C)
			return expresses[i];
	}
	return Express();
}

/*
 *	 判断某一个规则是否能够导出空串
 */
bool Grammer::isEmptyStr(Express e)
{
	bool result = false;
	for(int i=0;i<e.length;i++)
	{
		if(e.haveEmptyStr())
			result = true;
		else
		{
			for(int j=0;j<e.data[i].size();j++)
			{
				Express g = findExpress(e.data[i][j]);
				result = result && isEmptyStr(g);
			}
		}
	}
	return result;
}

/*
 *	 判断某一个生成式是否能够导出空串
 */
bool Grammer::isEmptyStr(string str)
{
	bool result = false;
	if(str[0] == 0)
		result = true;
	else
	{
		for(int i=0;i<str.size();i++)
		{
			Express e = findExpress(str[i]);
			result = result && isEmptyStr(e);
		}
	}
	return result;
}
	
/*
 *	消除文法G中的左递归
 */
void Grammer::removeLeftRecursion()
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
	for(int i=0;i<expresses.size();i++)	//遍历每一条规则
	{
		Express e = expresses[i];
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
				expresses.push_back(f);
				
				expresses[i] = e;
			}
		}
	}
}

/*
 *	查找非终结符A的所有FRIST字符集合
 *			返回char类型的vector集合
 */
vector<char> Grammer::getFirstChar(char A)
{
	vector<char> first;
	for(int i=0;i<expresses.size();i++)		//遍历每一条规则
	{
		Express e = expresses[i];
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
					vector<char> f =getFirstChar(str[0]); 
					for(int k=0;k<f.size();k++)
						first.push_back(f[k]);
				}
			}
			return first;
		}
	}
	first.push_back(A);
	return first;
}

/*
 *	获取语法G的FIRST集合
 */
vector<char> *Grammer::getFIRST()
{
	vector<char> *first = new vector<char>[expresses.size()];
	for(int i=0;i<expresses.size();i++)
	{
		Express e = expresses[i];
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
				vector<char> f = getFirstChar(str[0]); 
				for(int k=0;k<f.size();k++)
					first[i].push_back(f[k]);
			}
		}
	}
	return first;
}

/*
 *	查询标识符A的FOLLOW字符集
 *			A：	要查询的标识符
 *			x：	当前的已经查出的FOLLOW集合的长度
 *			fs：已经查出的FOLLOW集合
 */
vector<char> Grammer::getFollowChar(char A,int x,vector<char> *fs)
{
	vector<char> follow;
	for(int i=expresses.size()-1;i>=0;i--)
	{
		Express e2 = expresses[i];
		for(int j=0;j<e2.length;j++)
		{
			string str = e2.data[j];

			int n = str.find(A);		//在所有生成式右部寻找C
			if(n == -1 || A == e2.ident)		//找不到，或者生成式为其自身规则
				continue;
			else if(n == (str.size()-1))		//在其他产生式中找到找到，且为右部最后
			{
				vector<char> f = findVector(e2.ident,x,fs);
				for(int k=1;k<f.size();k++)
				{
					if(f[k] != 0 && !inVector(follow,f[k]))		//去除其中的空串，以及相同内容
						follow.push_back(f[k]);
				}
			}
			else
			{
				if(inVector(Vt,str[n+1]))			//紧后的为终结符
					follow.push_back(str[n+1]);
				else			//非终结符，获取其FIRST集合
				{
					vector<char> f = getFirstChar(str[n+1]);
					for(int k=0;k<f.size();k++)
					{
						if(f[k] != 0 && !inVector(follow,f[k]))		//去除空串与相同
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
vector<char> *Grammer::getFOLLOW()
{
	vector<char> *follow = new vector<char>[expresses.size()];
	for(int i=0;i<expresses.size();i++)
	{
		Express e1 = expresses[i];
		follow[i].push_back(e1.ident);

		// 依次获取FOLLOW集合并存入follow中
		vector<char> f = getFollowChar(e1.ident,i,follow);
		for(int l=0;l<f.size();l++)
			follow[i].push_back(f[l]);

		if(!inVector(follow[i],'#'))	//添加# 号
			follow[i].push_back('#');
	}
	return follow;
}

/*
 *  获取SELECT集合
 */
vector<char> *Grammer::getSELECT(vector<char> *follow)
{
	// SELECT集合的数组长度
	int length = 0;
	for(int i=0;i<expresses.size();i++)
		length += expresses[i].length;

	vector<char> *select = new vector<char>[length];

	int n = 0;
	for(i =0;i<expresses.size();i++)
	{
		Express e = expresses[i];
		for(int j=0;j<e.length;j++)
		{
			vector<char> v = getFirstChar(e.data[j][0]);	//获取生成式右部的FIRST集合

			if(isEmptyStr(e.data[j]))	//如果生成式右部可以推导出空串
			{
				vector<char> f;
				for(int k=0;k<expresses.size();k++)
				{
					if(follow[k][0] == e.ident)
						f = follow[k];		//找到生成式左部的FOLLOW集合
				}
				for(k=0;k<v.size();k++)	//将FIRST集合压入
				{
					if(!inVector(select[n],v[k]) && v[k]!=0)
						select[n].push_back(v[k]);
				}
				for(k=1;k<f.size();k++)	//将FOLLOW集合压入
				{
					if(!inVector(select[n],f[k]) && f[k]!=0)
						select[n].push_back(f[k]);
				}
			}
			else		//生成式右部不能推导出空串，将生成式右部的FIRST集合压入
			{
				for(int k=0;k<v.size();k++)
				{
					if(v[k] != 0)
						select[n].push_back(v[k]);
				}
			}
			n++;
		}
	}
	return select;
}

void Grammer::getMTable()
{
	//消除左递归
	removeLeftRecursion();
	cout<<"消除左递归后："<<endl;
	print();

	//获取FIST集合
	vector<char> *first = getFIRST();
	cout<<"FIRST 集合："<<endl;
	printCollection(first);
	cout<<endl;

	//获取FOLLOW集合
	vector<char> *follow = getFOLLOW();
	cout<<"FOLLOW 集合："<<endl;
	printCollection(follow);
	cout<<endl;

	//获取SELECT集合
	vector<char> *select = getSELECT(follow);
	cout<<"SELECT 集合："<<endl;
	printSELECT(select);
	cout<<endl;

	// 生成预测分析表
	M[0][0] = "";

	for(int i=1;i<col;i++)
		M[0][i] = Vt[i-1];		//表头终结符
	M[0][col-1] = "#";

	for(i=1;i<row;i++)
		M[i][0] = expresses[i-1].ident; //表头非终结符

	int n = 0;
	for(i=0;i<expresses.size();i++)
	{
		Express e = expresses[i];
		for(int j=1;j<col;j++)
		{
			M[i+1][j] = "";
			const char *b = M[0][j].c_str();	//提取首字符
			char c = *b;

			int m = n;			//注：此处m作用为局部遍历select集合
			for(int k=0;k<e.length;k++)
			{
				for(int l=0;l<select[m].size();l++)
				{
					if(select[m][l] == c)		//如果当前select集中含有表头终结符
						M[i+1][j] = e.data[k];
				}
				m++;
			}
		}
		n += e.length;
	}

}

/*
 *	打印集合(FIRST或FOLLOW)
 */
void Grammer::printCollection(vector<char> list[])
{
	for(int i=0;i<expresses.size();i++)
	{
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

/*
 *	打印SELECT集合
 */
void Grammer::printSELECT(vector<char> select[])
{
	int n = 0;
	for(int i=0;i<expresses.size();i++)
	{
		Express e = expresses[i];
		for(int j=0;j<e.length;j++)
		{
			cout<<e.ident<<" -> ";

			if(e.data[j][0] == 0)
				cout<<"ε"<<" :\t ";
			else
				cout<<e.data[j]<<" :\t ";

			for(int k=0;k<select[n].size();k++)
				cout<<select[n][k]<<"  ";
			n++;
			cout<<endl;
		}
	}
	cout<<endl;
}