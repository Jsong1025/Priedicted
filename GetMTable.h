#include "Grammer.h"

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
LinkList getFIST(Grammer G)
{
	LinkList frist;
	return frist;
}

//��ȡFOLLOW����
LinkList getFOLLOW(Grammer G)
{
	LinkList follow;
	return follow;
}

//��ȡSELECT����
LinkList getSELECT(Grammer G , LinkList frist,LinkList follow)
{
	LinkList select;
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
	LinkList first = getFIST(G_new);
	//��ȡFOLLOW����
	LinkList follow = getFOLLOW(G_new);
	//��ȡSELECT����
	LinkList select = getSELECT(G_new,first,follow);
	return NULL;
}