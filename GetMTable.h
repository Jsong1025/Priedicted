#include "Grammer.h"

//消除左递归
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
			Express e2 = replaceENode(g1->express,e1);		//替换g1中的e1

			g2 = g2->next;
		}
		g1 = g1->next;
	}

	// 判断是否含有左递归
	g1 = G.expresses;
	for(i=0;i<G.length;i++)
	{
		ENode p = g1->express.data;
		for(j=0;j<e1.length;j++)	//遍历每一条文法
		{
			LNode l = p->phrase.head;
			for(k=0;k<p->phrase.length;k++)		//遍历每一个标示符
			{
				if(l->data == e1.ident)			//含有左递归
				{
					/* 消除左递归，具体处理过程 */
					//  TODO:
					Express newExpr;					//增加一条新文法
					newExpr.ident = e1.ident+G.length;		//新标识符（E'）
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

//获取FIST集合
LinkList getFIST(Grammer G)
{
	LinkList frist;
	return frist;
}

//获取FOLLOW集合
LinkList getFOLLOW(Grammer G)
{
	LinkList follow;
	return follow;
}

//获取SELECT集合
LinkList getSELECT(Grammer G , LinkList frist,LinkList follow)
{
	LinkList select;
	return select;
}

/*
 *	获取根据语法G预测分析表
 */
LinkList * getMTable (Grammer G)
{
	//消除左递归
	Grammer G_new = removeLeftRecursion(G);
	//获取FIST集合
	LinkList first = getFIST(G_new);
	//获取FOLLOW集合
	LinkList follow = getFOLLOW(G_new);
	//获取SELECT集合
	LinkList select = getSELECT(G_new,first,follow);
	return NULL;
}