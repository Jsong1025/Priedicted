#include <stdio.h>
#include <malloc.h>

#include "Express.h"

typedef struct GramNode			//节点
{
	Express express;			// 表达式
	struct GramNode *next;

}GramNode, *GNode;

typedef struct Grammer
{
	int length;				//长度
	GNode expresses;		//表达式链表
	GNode head;
	GNode tail;
}Grammer;

/* 初始化Grammar */
void initGrammer(Grammer *G)
{
	G->length = 0;
	G->expresses = NULL;
	G->head = NULL;
	G->tail = NULL;
}

/* 判断是否为空 */
int isGrammerEmpty(Grammer G)
{
	if(G.head == NULL && G.tail == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* 向尾部插入 */
Grammer enGrammer(Grammer G , Express e)
{
	if(isGrammerEmpty(G))
	{
		G.tail = (GNode)malloc(sizeof(GNode));
		G.tail->express = e;
		G.head = G.tail;
		G.tail->next = NULL;
		G.length++;
	}
	else
	{
		G.tail->next = (GNode)malloc(sizeof(GNode));
		G.tail = G.tail->next;
		G.tail->express = e;
		G.tail->next = NULL;
		G.length++;
	}
	return G;
}



/*	集合结构体
 *	
 *	用于存储FIRST、 FOLLOW、SELECT集
 *		采用（链式）邻接表实现
 */

typedef struct CollectionNode	   //节点
{
	LinkList data;			// 文法
	struct CollectionNode *next;
}CollectionNode, *CNode;


typedef struct Collection
{
	int length;			// 长度
	CNode data;			// 文法链表
	CNode head;
	CNode tail;
}Collection;

/* 判断是否为空 */
int isCollectionEmpty(Collection c)
{
	if(c.head == NULL && c.tail == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* 向尾部插入 */
Collection enCollection(Collection c , LinkList l)
{
	if(isCollectionEmpty(c))
	{
		c.tail = (CNode)malloc(sizeof(CNode));
		c.tail->data = l;
		c.head = c.tail;
		c.tail->next = NULL;
		c.length++;
	}
	else
	{
		c.tail->next = (CNode)malloc(sizeof(CNode));
		c.tail = c.tail->next;
		c.tail->data = l;
		c.tail->next = NULL;
		c.length++;
	}
	return c;
}