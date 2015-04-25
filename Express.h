#include <stdio.h>
#include <malloc.h>

#include "LinkList.h"


/*	���ʽ�ṹ��
 *	
 *	���ø����͵��ڽӱ�洢���ڽӱ��и�����ͷ������������
 */

typedef struct ExpressNode	   //�ڵ�
{
	LinkList phrase;			// �ķ�
	struct ExpressNode *next;
}ExpressNode, *ENode;


typedef struct Express
{
	int length;			// ����
	char ident;			// ��ʶ��
	ENode data;			// �ķ�����
}Express;

Express replaceENode (Express e1 , Express e2)
{
	int i,j,k;

	ENode p = e1.data;
	ENode q = e2.data;

	for(i=0;i<e1.length;i++)	//����ÿһ���ķ�
	{
		LNode l = p->phrase.head;
		for(j=0;j<p->phrase.length;j++)		//����ÿһ����ʾ��
		{
			if(l->data == e2.ident)			//������ҵ�
			{
				for(k=0; k<e2.length ;k++)
				{
					LinkList newNode = copyList(p->phrase.head,j);				// ���ƿ�ͷ����
					LinkList next = copyList(l->next,(p->phrase.length-j));		// ���ƽ�β����

					newNode.tail = q->phrase.head;
					q->phrase.tail->next = next.head;

					enLinkList(e1,newNode);		//���뵽e1��

					q = q->next;
				}
			}
			l = l->next;
		}
		p = p->next;
	}

	return e1;
}