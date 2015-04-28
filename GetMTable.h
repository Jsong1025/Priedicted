#include "Grammer.h"
#include "Collection.h"

char Vt[] = {'A','B','C'};

int inVt(char c)
{
	return 1;
}

//消除左递归
Grammer removeLeftRecursion(Grammer G)
{
	int i,j,k;
	GNode g1 = G.expresses;
	GNode g2 = g1->next;
	for(i=0;i<G.length;i++)
	{
		for(j=1;j<(G.length-1);j++)
		{
			g1->express = replaceENode(g1->express,g2->express);	//替换g1中的e1		
			g2 = g2->next;
		}
		g1 = g1->next;
	}

	// 判断是否含有左递归
	g1 = G.expresses;
	for(i=0;i<G.length;i++)
	{
		ENode p = g1->express.data;
		for(j=0;j<g1->express.length;j++)	//遍历每一条文法
		{
			LNode l = p->phrase.head;
			if(l->data == g1->express.ident)			//含有左递归
			{
				/* 消除左递归，具体处理过程 */
				ENode q;
				Express newExpr;					//增加一条新文法
				LinkList list1 = copyList(l->next,p->phrase.length-1);
				LinkList list2;

				newExpr.ident = g1->express.ident+G.length;		//新标识符（E'）

				insertElem(&list1 , newExpr.ident);  // S->bS'
				newExpr = enExpress(newExpr,list1); 

				insertElem(&list2,0);				//空字符
				newExpr = enExpress(newExpr,list1);
				G = enGrammer(G,newExpr);

				// 修改原表达式
				deleteNode(&(p->phrase),1);		// 删除字符	
				q = g1->express.data;
				for(k=0;k<g1->express.length;k++)  // 每一条表达式后加入S'
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
	if(!inVt(c))		//如果是终结符
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

//获取FIST集合
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
	if(!inVt(c))		//如果是终结符
	{
		return c;
	}
	else
	{
		GNode g = G.expresses;
		int i;
		for(i=0;i<G.length;i++)
		{
			// TODO : 未加添加#处理
			if(g->express.ident == c)
			getFollowElem(g->express.data->phrase.tail->data,G);
			g = g->next;
		}
	}
}
//获取FOLLOW集合
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

//获取SELECT集合
Collection getSELECT(Grammer G , Collection frist,Collection follow)
{
	Collection select;
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
	Collection first = getFIST(G_new);
	//获取FOLLOW集合
	Collection follow = getFOLLOW(G_new);
	//获取SELECT集合
	Collection select = getSELECT(G_new,first,follow);
	return NULL;
}