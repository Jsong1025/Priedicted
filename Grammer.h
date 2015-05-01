#include "iostream"
#include "string"
#include "vector"
#include "list"
using namespace std;

class Express	//规则
{

public:
	int length;		//当前生成式个数

	char ident;		//生成式左部

	string *data;	//生成式右部数

	Express()
	{
		length = 0;
		data = NULL;
	}
	Express(char c)
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
	void insert(string str[],int l)
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
	void insert(string str)
	{
		if(length != 0)
		{
			string *array = new string[length];
			for(int i=0;i<length;i++)
				array[i] = data[i];

			length ++;
			data = new string[length];
			for(i=0;i<(length-1);i++)
				data[i]=array[i];
			data[length-1]=str;
		}
		else
		{
			length = 1;
			data = new string[1];
			data[0]=str;
		}
	}

	/*
	 *	删除第n条生成式
	 */
	string del(int n)
	{
		string *array = new string[length];
		for(int i=0;i<length;i++)
			array[i] = data[i];

		length -= 1;
		data = new string[length];
		for(i=0;i<n;i++)
			data[i]=array[i];
		for(i=n;i<length;i++)
			data[i]=array[i+1];
		return array[n];
	}

	/*
	 *	将生成式中的e标识符，用e中的生成数组替换
	 */
	void replace(Express e)
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
	void print()
	{
		for(int i=0;i<this->length;i++)
		{
			cout<<this->ident<<" -> "<<data[i]<<endl;
		}
	}

};

class Grammer	//文法
{

public:
	vector<Express> expresses;	//规则集合

	Grammer()
	{
	}

	void print()
	{
		for(int i=0;i<expresses.size();i++)
		{
			expresses[i].print();
			cout<<endl;
		}
	}
};
