#include "Grammer.h"
#include "Collection.h"

char Vt[] = {'A','B','C'};

int inVt(char c)
{
	return 1;
}

//������ݹ�
Grammer removeLeftRecursion(Grammer G)
{
	int i,j,k;
	GNode g1 = G.expresses;
	GNode g2 = g1->next;
	for(i=0;i<G.length;i++)
	{
		for(j=1;j<(G.length-1);j++)
		{
			g1->express = replaceENode(g1->express,g2->express);	//�滻g1�е�e1		
			g2 = g2->next;
		}
		g1 = g1->next;
	}

	// �ж��Ƿ�����ݹ�
	g1 = G.expresses;
	for(i=0;i<G.length;i++)
	{
		ENode p = g1->express.data;
		for(j=0;j<g1->express.length;j++)	//����ÿһ���ķ�
		{
			LNode l = p->phrase.head;
			if(l->data == g1->express.ident)			//������ݹ�
			{
				/* ������ݹ飬���崦����� */
				ENode q;
				Express newExpr;					//����һ�����ķ�
				LinkList list1 = copyList(l->next,p->phrase.length-1);
				LinkList list2;

				newExpr.ident = g1->express.ident+G.length;		//�±�ʶ����E'��

				insertElem(&list1 , newExpr.ident);  // S->bS'
				newExpr = enExpress(newExpr,list1); 

				insertElem(&list2,0);				//���ַ�
				newExpr = enExpress(newExpr,list1);
				G = enGrammer(G,newExpr);

				// �޸�ԭ���ʽ
				deleteNode(&(p->phrase),1);		// ɾ���ַ�	
				q = g1->express.data;
				for(k=0;k<g1->express.length;k++)  // ÿһ�����ʽ�����S'
				{
					insertElem(&(q->phrase) , newExpr.ident);
					q = q->next;
				}
				break;
			}
			p = p->next;
		}
		g1 = g1->next;
	}

	return G;
}

char getFristElem(char c,Grammer G)
{
	if(!inVt(c))		//������ս��
	{
		return c;
	}
	else
	{
		GNode g = G.expresses;
		int i;
		for(i=0;i<G.length;i++)
		{
			if(g->express.ident == c)
			getFristElem(g->express.data->phrase.head->data,G);
			g = g->next;
		}
	}
}

//��ȡFIST����
Collection getFIST(Grammer G)
{
	Collection frist;
	int i,j;
	GNode g = G.expresses;
	for(i=0;i<G.length;i++)
	{
		ENode e = g->express.data;
		LinkList list;
		for(j=0;j<g->express.length;j++)
		{
			char c = e->phrase.head->data;
			insertElem(&list,getFristElem(c,G));
		}
		frist = enCollection(frist,list);
		g= g->next;
	}
	return frist;
}

char getFollowElem(char c,Grammer G)
{
	if(!inVt(c))		//������ս��
	{
		return c;
	}
	else
	{
		GNode g = G.expresses;
		int i;
		for(i=0;i<G.length;i++)
		{
			// TODO : δ�����#����
			if(g->express.ident == c)
			getFollowElem(g->express.data->phrase.tail->data,G);
			g = g->next;
		}
	}
}
//��ȡFOLLOW����
Collection getFOLLOW(Grammer G)
{
	Collection follow;
	int i,j;
	GNode g = G.expresses;
	for(i=0;i<G.length;i++)
	{
		ENode e = g->express.data;
		LinkList list;
		for(j=0;j<g->express.length;j++)
		{
			char c = e->phrase.tail->data;
			insertElem(&list,getFristElem(c,G));
		}
		follow = enCollection(follow,list);
		g= g->next;
	}
	return follow;
}

//��ȡSELECT����
Collection getSELECT(Grammer G , Collection frist,Collection follow)
{
	Collection select;
	return select;
}

/*
 *	��ȡ�����﷨GԤ�������
 */
LinkList * getMTable (Grammer G)
{
	//������ݹ�
	Grammer G_new = removeLeftRecursion(G);
	//��ȡFIST����
	Collection first = getFIST(G_new);
	//��ȡFOLLOW����
	Collection follow = getFOLLOW(G_new);
	//��ȡSELECT����
	Collection select = getSELECT(G_new,first,follow);
	return NULL;
}