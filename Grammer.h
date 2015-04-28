#include <stdio.h>
#include <malloc.h>

#include "Express.h"

typedef struct GramNode			//�ڵ�
{
	Express express;			// ���ʽ
	struct GramNode *next;

}GramNode, *GNode;

typedef struct Grammer
{
	int length;				//����
	GNode expresses;		//���ʽ����
	GNode head;
	GNode tail;
}Grammer;

/* ��ʼ��Grammar */
void initGrammer(Grammer *G)
{
	G->length = 0;
	G->expresses = NULL;
	G->head = NULL;
	G->tail = NULL;
}

/* �ж��Ƿ�Ϊ�� */
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

/* ��β������ */
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



/*	���Ͻṹ��
 *	
 *	���ڴ洢FIRST�� FOLLOW��SELECT��
 *		���ã���ʽ���ڽӱ�ʵ��
 */

typedef struct CollectionNode	   //�ڵ�
{
	LinkList data;			// �ķ�
	struct CollectionNode *next;
}CollectionNode, *CNode;


typedef struct Collection
{
	int length;			// ����
	CNode data;			// �ķ�����
	CNode head;
	CNode tail;
}Collection;

/* �ж��Ƿ�Ϊ�� */
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

/* ��β������ */
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