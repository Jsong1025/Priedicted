#include <stdio.h>
#include <malloc.h>

#include "LinkList.h"


/*	表达式结构体
 *	
 *	采用改造型的邻接表存储，邻接表中各链表头结点采用链表串联
 */

typedef struct ExpressNode	   //节点
{
	LinkList phrase;			// 文法
	struct ExpressNode *next;
}ExpressNode, *ENode;


typedef struct Express
{
	int length;			// 长度
	char ident;			// 标识符
	ENode data;			// 文法链表
	ENode head;
	ENode tail;
}Express;

/* 判断是否为空 */
int isExpressEmpty(Express e)
{
	if(e.head == NULL && e.tail == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* 向尾部插入 */
Express enExpress(Express e , LinkList n)
{
	if(isExpressEmpty(e))
	{
		e.tail = (ENode)malloc(sizeof(ENode));
		e.tail->phrase = n;
		e.head = e.tail;
		e.tail->next = NULL;
		e.length++;
	}
	else
	{
		e.tail->next = (ENode)malloc(sizeof(ENode));
		e.tail = e.tail->next;
		e.tail->phrase = n;
		e.tail->next = NULL;
		e.length++;
	}
	return e;
}

Express replaceENode (Express e1 , Express e2)
{
	int i,j,k;

	ENode p = e1.data;
	ENode q = e2.data;

	for(i=0;i<e1.length;i++)	//遍历每一条文法
	{
		LNode l = p->phrase.head;
		for(j=0;j<p->phrase.length;j++)		//遍历每一个标示符
		{
			if(l->data == e2.ident)			//如果查找到
			{
				for(k=0; k<e2.length ;k++)
				{
					LinkList newNode = copyList(p->phrase.head,j);				// 复制开头部分
					LinkList next = copyList(l->next,(p->phrase.length-j));		// 复制结尾部分

					newNode.tail = q->phrase.head;
					q->phrase.tail->next = next.head;

					e1 = enExpress(e1,newNode);		//插入到e1中

					q = q->next;
				}
			}
			l = l->next;
		}
		p = p->next;
	}

	return e1;
}