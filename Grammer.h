#include "Function.h"
using namespace std;

class Express	//����
{
public:
	int length;		//��ǰ����ʽ����
	char ident;		//����ʽ��
	string *data;	//����ʽ�Ҳ���

	Express();
	Express(char c);

	//	�ڹ����в����µ�����ʽ
	void insert(string str);
	void insert(string str[],int l);

	//	ɾ����n������ʽ
	string del(int n);

	//	������ʽ�е�e��ʶ������e�е����������滻
	void replace(Express e);

	//  �жϵ�ǰ�����Ƿ��ܵ����մ�
	bool isEmptyStr();

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
 *	�ڹ����в����µ�����ʽ��������
 *		str :	Ҫ���������ʽ����
 *		l   :	Ҫ����ĳ���
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
 *	�ڹ����в����µ�����ʽ��������
 *		str :	Ҫ���������ʽ
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
string Express::del(int n)
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
 *	�жϵ�ǰ�����Ƿ��ܹ������մ�
 */
bool Express::isEmptyStr()
{
	return false;
}

void Express::print()
{
	for(int i=0;i<this->length;i++)
	{
		cout<<this->ident<<" -> ";
		if(data[i][0] == 0)
			cout<<"��"<<endl;
		else
			cout<<data[i]<<endl;
	}
}

/*===================================================================================*/

class Grammer	//�ķ�
{

public:
	vector<Express> expresses;	//���򼯺�

	Grammer(){}

	void print();

	// �����ķ�G�е���ݹ�
	void removeLeftRecursion();

	// ��ȡ�﷨G��FIRST����
	vector<char> getFirstChar(char A);
	vector<char> *getFIRST();

	// ��ȡFOLLOW����
	vector<char> getFollowChar(char A,int x,vector<char> *fs);
	vector<char> *getFOLLOW();

	// ��ȡSELECT����
	vector<char> getSelectChar(string str,vector<char> *follow);
	vector<char> *getSELECT(vector<char> *fist,vector<char> *follow);

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
 *	�����ķ�G�е���ݹ�
 */
void Grammer::removeLeftRecursion()
{
	/*
	for(int i=0;i<G.expresses.size();i++)
	{
		// �滻
		for(int j=1;j<(G.expresses.size()-1);j++)
		{
			Express e1 = G.expresses[i];
			Express e2 = G.expresses[j];
			e1.replace(e2);
			G.expresses[i] = e1;
		}
	}
	*/	

	// ����ֱ����ݹ�
	for(int i=0;i<expresses.size();i++)	//����ÿһ������
	{
		Express e = expresses[i];
		for(int j=0;j<e.length;j++)		//����ÿһ������ʽ
		{
			string str = e.data[j];
			if(str[0] == e.ident)		//����ʽ�Ҳ�������ĸ������ʽ����ͬ��������ݹ�
			{
				// ����һ���¹���
				Express f(e.ident-1);				//�¹������
				string *f_str = new string[2];		//�¹��������ʽ

				for(int k=0;k<e.length;k++)	
				{
					e.data[k] += f.ident;		//�ھɹ���ÿһ������ʽ�󣬼����¹�����󲿱�ʶ��
				}

				string tmp = e.del(j);
				f_str[0] = string(tmp,1,tmp.length());	//�ɹ����к�����ݹ������ʽ��ȥ����ݹ�󣬷����¹�����

				char c = 0;		// ���ַ� ��
				f_str[1] = c;

				f.insert(f_str,2);
				expresses.push_back(f);
				
				expresses[i] = e;
			}
		}
	}
}

/*
 *	���ҷ��ս��A������FRIST�ַ�����
 *			����char���͵�vector����
 */
vector<char> Grammer::getFirstChar(char A)
{
	vector<char> first;
	for(int i=0;i<expresses.size();i++)		//����ÿһ������
	{
		Express e = expresses[i];
		if(A == e.ident)
		{
			for(int j=0;j<e.length;j++)			//����ÿһ������ʽ
			{
				string str = e.data[j];
				// ���Ϊ�ս������ַ�
				if(inVector(Vt,str[0]) || str[0] == 0)
					first.push_back(str[0]);
				else
				{
					//�ݹ��ѯ�����Ѳ�ѯ���ѹ��������
					vector<char> f =getFirstChar(str[0]); 
					for(int k=0;k<f.size();k++)
						first.push_back(f[k]);
				}
			}
		}
	}
	return first;
}

/*
 *	��ȡ�﷨G��FIRST����
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
			// ���������������ʽ������ĸΪ�ս��������ַ���
			string str = e.data[j];
			if(inVector(Vt,str[0]) || str[0] == 0)
				first[i].push_back(str[0]);
			else
			{
				//�ݹ��ѯ�����Ѳ�ѯ���ѹ�뵱ǰFIRST����
				vector<char> f = getFirstChar(str[0]); 
				for(int k=0;k<f.size();k++)
					first[i].push_back(f[k]);
			}
		}
	}
	return first;
}

vector<char> Grammer::getFollowChar(char A,int x,vector<char> *fs)
{
	vector<char> follow;
	for(int i=expresses.size()-1;i>=0;i--)
	{
		Express e2 = expresses[i];
		for(int j=0;j<e2.length;j++)
		{
			string str = e2.data[j];

			int n = str.find(A);		//����������ʽ�Ҳ�Ѱ��C
			if(n == -1 || A == e2.ident)
				continue;
			else if(n == (str.size()-1))		//����������ʽ���ҵ��ҵ�����Ϊ�Ҳ����
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
				if(inVector(Vt,str[n+1]))			//�����Ϊ�ս��
					follow.push_back(str[n+1]);
				else			//���ս������ȡ��FIRST����
				{
					vector<char> f = getFirstChar(str[n+1]);
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
 *  ��ȡFOLLOW����
 */
vector<char> *Grammer::getFOLLOW()
{
	vector<char> *follow = new vector<char>[expresses.size()];
	for(int i=0;i<expresses.size();i++)
	{
		Express e1 = expresses[i];
		char C = e1.ident;				//��ǰ��ʶ��
		follow[i].push_back(C);

		vector<char> f = getFollowChar(C,i,follow);
		for(int l=0;l<f.size();l++)
			follow[i].push_back(f[l]);

		if(!inVector(follow[i],'#'))
			follow[i].push_back('#');

	}
	return follow;
}

vector<char> Grammer::getSelectChar(string str,vector<char> *follow)
{
	vector<char> select;

	return select;
}

vector<char> *Grammer::getSELECT(vector<char> *fist,vector<char> *follow)
{
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
			string str = e.data[j];
			select[n++] = getSelectChar(str,follow);
		}
	}
	return select;
}

