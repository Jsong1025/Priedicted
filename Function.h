#include "iostream"
#include "string"
#include "vector"
using namespace std;

const int row = 6;
const int col = 7;
string M[row][col];
vector<char> Vt;			//�ս��

/*
 *	������v�в���c
 *			�����������true���������������false
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
 *	���ұ�ʶ��A��Ӧ�ļ���
 *			A��Ҫ���ҵķ��ս��
 *			l�����ҳ���
 *			c����������
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
 *	��Ԥ��������в���ָ���ķ�
 *			���ҳɹ�����ָ�����ķ��ַ���������ʧ�ܷ��ؿ��ַ���
 */
string findInMTable(char X,char a)
{
	for(int i=0;i<row;i++)
	{
		const char *y = M[i][0].c_str();	//��ȡ���ַ�
		char Y = *y;
		if( Y == X)
		{
			for(int j=1;j<col;j++)
			{
				const char *b = M[0][j].c_str();	//��ȡ���ַ�
				char c = *b;
				if(c == a)
					return M[i][j];
			}
		}
	}
	return "";
}

/*
 *	��ӡ����
 */
void printCollection(vector<char> list[],int length)
{
	for(int i=0;i<length;i++)
	{
		cout<<list[i][0]<<" : ";
		for(int j=1;j<list[i].size();j++)
		{
			if(list[i][j]==0)
			{
				cout<<"��"<<"  ";
			}
			else
			{
				cout<<list[i][j]<<"  ";
			}
		}
		cout<<endl;
	}
}