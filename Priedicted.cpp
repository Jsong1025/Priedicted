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

		if(inVector(Vt,X))	//��Vt�б���X
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
 *	�����ķ�G�е���ݹ�
 */
Grammer removeLeftRecursion(Grammer G)
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
	for(int i=0;i<G.expresses.size();i++)	//����ÿһ������
	{
		Express e = G.expresses[i];
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
				G.expresses.push_back(f);
				
				G.expresses[i] = e;
			}
		}
	}
	
	return G;
}

/*
 *	���ҷ��ս��A������FRIST�ַ�����
 *			����char���͵�vector����
 */
vector<char> getFirstChar(char A,Grammer G)
{
	vector<char> first;
	for(int i=0;i<G.expresses.size();i++)		//����ÿһ������
	{
		Express e = G.expresses[i];
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
 *	��ȡ�﷨G��FIRST����
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
			// ���������������ʽ������ĸΪ�ս��������ַ���
			string str = e.data[j];
			if(inVector(Vt,str[0]) || str[0] == 0)
				first[i].push_back(str[0]);
			else
			{
				//�ݹ��ѯ�����Ѳ�ѯ���ѹ�뵱ǰFIRST����
				vector<char> f =getFirstChar(str[0],G); 
				for(int k=0;k<f.size();k++)
					first[i].push_back(f[k]);
			}
		}
	}

	return first;
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

vector<char> getFollowChar(char A,int x,Grammer G,vector<char> *fs)
{
	vector<char> follow;

	for(int i=G.expresses.size()-1;i>=0;i--)
	{
		Express e2 = G.expresses[i];
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
 *  ��ȡFOLLOW����
 */
vector<char> *getFOLLOW(Grammer G)
{
	vector<char> *follow = new vector<char>[G.expresses.size()];
	for(int i=0;i<G.expresses.size();i++)
	{
		Express e1 = G.expresses[i];
		char C = e1.ident;				//��ǰ��ʶ��
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
 *	��ӡ����
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

void getMTable(Grammer G)
{
 	
	//������ݹ�
	G = removeLeftRecursion(G);
	cout<<"������ݹ��"<<endl;
	G.print();

	//��ȡFIST����
	vector<char> *first = getFIRST(G);
	cout<<"FIRST ���ϣ�"<<endl;
	printCollection(first,G);

	//��ȡFOLLOW����
	vector<char> *follow = getFOLLOW(G);
	cout<<"FOLLOW ���ϣ�"<<endl;
	printCollection(follow,G);

	//��ȡSELECT����
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
	cout<<"�ķ�G��"<<endl;
	G.print();
	getMTable(G);

/*
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

	return 0;
}