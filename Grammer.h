#include "iostream"
#include "string"
#include "vector"
#include "list"
using namespace std;

class Express	//����
{

public:
	int length;		//��ǰ����ʽ����

	char ident;		//����ʽ��

	string *data;	//����ʽ�Ҳ���

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
	 *	�ڹ����в����µ�����ʽ��������
	 *		str :	Ҫ���������ʽ����
	 *		l   :	Ҫ����ĳ���
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
	 *	�ڹ����в����µ�����ʽ��������
	 *		str :	Ҫ���������ʽ
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
	 *	ɾ����n������ʽ
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
	 *	������ʽ�е�e��ʶ������e�е����������滻
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

class Grammer	//�ķ�
{

public:
	vector<Express> expresses;	//���򼯺�

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
