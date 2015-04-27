#include "Grammer.h"

typedef Express Collection;		//���ϣ��ڽӱ�

char Vt = {};

//������ݹ�
Grammer removeLeftRecursion(Grammer G)
{
	int i,j;
	GNode g1 = G.expresses;
	GNode g2 = g1->next;
	for(i=0;i<G.length;i++)
	{

		for(j=1;j<(G.length-1);j++)
		{
			Express e1 = g2->express;
			Express e2 = replaceENode(g1->express,e1);		//�滻g1�е�e1

			g2 = g2->next;
		}
		g1 = g1->next;
	}

	// �ж��Ƿ�����ݹ�
	g1 = G.expresses;
	for(i=0;i<G.length;i++)
	{
		ENode p = g1->express.data;
		for(j=0;j<e1.length;j++)	//����ÿһ���ķ�
		{
			LNode l = p->phrase.head;
			for(k=0;k<p->phrase.length;k++)		//����ÿһ����ʾ��
			{
				if(l->data == e1.ident)			//������ݹ�
				{
					/* ������ݹ飬���崦����� */
					//  TODO:
					Express newExpr;					//����һ�����ķ�
					newExpr.ident = e1.ident+G.length;		//�±�ʶ����E'��
					LinkList head = copyList(p->phrase.head,k);

				}
				l = l->next;
			}
			p = p->next;
		}
		g1 = g1->next;
	}

	return G;
}

//��ȡFIST����
Collection getFIST(Grammer G)
{
	Collection frist;
	int i,j,k;
	for(i=0;i<G.length;i++)
	{
		Express e = G.expresses->express;
		ENode = e.data;
		frist.ident = e.ident;
		for(j=0;j<e.length;j++)
		{
			LNode n = e.data->phrase.head;
			if(inVt(n->data))	//�����ǰ�ڵ������ս��
			{
				addElemCollection(frist.data->phrase,n->data);	//����ǰ�ս�����뵽������
			}
			else
			{
				addElemCollection(frist.data->phrase,findFrist(n->data,G));	//findFrist()���ҷ��ս�����׸��ս��
			}
		}
	}
	return frist;
}

char findFrist(char c,Grammer G)
{

}

//��ȡFOLLOW����
Collection getFOLLOW(Grammer G)
{
	Collection follow;
	int i,j,k;
	for(i=0;i<G.length;i++)
	{
		Express e = G.expresses->express;
		ENode = e.data;
		frist.ident = e.ident;
		for(j=0;j<e.length;j++)
		{
			LNode n = e.data->phrase.tail;
			if(inVt(n->data))	//�����ǰ�ڵ������ս��
			{
				addElemCollection(follow.data->phrase,n->data);	//����ǰ�ս�����뵽������
			}
			else
			{
				addElemCollection(follow.data->phrase,findFollow(n->data));	//findFrist()���ҷ��ս�����׸��ս��
			}
		}
	}

	return follow;
}

//��ȡSELECT����
Collection getSELECT(Grammer G , LinkList frist,LinkList follow)
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