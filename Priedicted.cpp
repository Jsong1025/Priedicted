// Priedicted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Grammer.h"

#include "stack"
using namespace std;

const int row = 6;
const int col = 7;
string M[row][col];
vector<char> Vt;			//�ս��

/*
 *	������v�в���c
 *			�����������true���������������false
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
 *	���ж��߼�
 */
bool action (stack<char> priedStack,stack<char> strStack)
{
	char X;
	char a;
	int step = 0;

	cout<<"-------��������-------"<<endl;
	cout<<"����\t��������"<<endl;
	a = strStack.top();
	strStack.pop();				// ʣ����Ŵ�ջ��ջ
	
	while(true)
	{
		cout<<step++<<"\t";
		
		X = priedStack.top();
		priedStack.pop();		//����ջ��ջ

		if(findVector(Vt,X))	//��Vt�б���X
		{
			if(X == a)
			{
				cout<<"\""<<a<<"\" ƥ��"<<endl;

				a = strStack.top();
				strStack.pop();				// ʣ����Ŵ�ջ��ջ
				continue;
			}
			else
				cout<<"�﷨����"<<endl;
				return false;
		}
		else
		{
			
			if(X == '#')
			{
				if(X == a)
				{
					cout<<"����"<<endl;
					return true;
				}
				else
				{
					cout<<"�﷨����"<<endl;
					return false;
				}
			}
			else
			{
				//��Ԥ��������в���X��a������з�������û�з���null
				string tmp = findInMTable(X,a);
				if(tmp.empty())
				{
					cout<<"�﷨����"<<endl;
					return false;
				}
				else
				{
					cout<<X<<" -> "<<tmp<<endl;
					if(tmp == "��")
					{
						continue;
					}
					else
					{
						for(int i=(tmp.size()-1);i>=0;i--)	//��tmp����ѹ�����ջ��
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
	M[2][5] = "��";
	M[2][6] = "��";

	M[3][0] = "T";
	M[3][1] = "FS";
	M[3][2] = "";
	M[3][3] = "";
	M[3][4] = "FS";
	M[3][5] = "";
	M[3][6] = "";

	M[4][0] = "S";
	M[4][1] = "";
	M[4][2] = "��";
	M[4][3] = "*FS";
	M[4][4] = "";
	M[4][5] = "��";
	M[4][6] = "��";

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
 *	�����ķ�G�е���ݹ�
 */
Grammer removeLeftRecursion(Grammer G)
{
	for(int i=0;i<G.length;i++)
	{
		// �滻
		for(int j=1;j<(G.length-1);j++)
		{
			Express e1 = G.expresses[i];
			Express e2 = G.expresses[j];
			e1.replace(e2);
		}
		/*
		while((i=findList(G[i],G[i][0])!=length)		// ��ai�ı��ʽ�в���������
		{
			// ������ݹ�
			
			// ��ȡiǰ����Ĳ���ʽ
			head = getHead(G[i],i);
			tail = getTail(G[i],r);
			
			// �滻
			char A = G[i][r] + G.length;
			removeRecursion(G[i],newpoint);	//�޸ĵ�ǰ���ʽ���������µı��ʽ
			Gadd(G,newpoint);				//���µı��ʽ�����ķ�G��
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
 	
	//������ݹ�
	Grammer G_new = removeLeftRecursion(G);
	//��ȡFIST����
	vector<char> first = getFIST(G_new);
	//��ȡFOLLOW����
	vector<char> follow = getFOLLOW(G_new);
	//��ȡSELECT����
	vector<char> select = getSELECT(G_new,first,follow);
/*
	// ���������ս��
	for(j=1;j<(Vt.lenth+1);j++)
	{
		M[0][j] = vt[j];
	}
	for(i=1;i<(G.length+1);i++)
	{
		M[i][0] = G[i][0];	//�������з��ս��
		for(j=1;j<(Vt.lenth+1);j++)
		{
			if(findSELECT(select,Vt[j]))	//�����SELECT�ҵ��˵�ǰ�ս��
			{
				M[i][j] = G[j];		//����ǰ�������ķ��ĺ�벿������Ԥ���������
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
	d_str[1] = "��";
	d.insert(d_str,2);
	G.expresses.push_back(d);

	Express t('T');
	string t_str = "FS";
	t.insert(t_str);
	G.expresses.push_back(t);

	Express s('S');
	string *s_str = new string[2];
	s_str[0] = "*FS";
	s_str[1] = "��";
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

	stack<char> priedStack;		//����ջ
	stack<char> strStack;		//ʣ����Ŵ�ջ

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
		printf("�﷨����ƥ�䣡\n");
	}
	else
	{
		cout<<endl;
		printf("�﷨����\n");
	}
*/
	Grammer G;
	G = initGrammer(G);
	G.print();
//	getMTable(G);

	return 0;
}