#include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define END '#'		//������־

typedef  char ElemType;		//�ڵ���������

typedef struct Node			//�ڵ�ṹ��
{
	ElemType data;
	struct Node *next;
}Node, *LNode;

typedef struct LinkNode		//����ṹ��
{
	LNode head;		//ͷ���
	LNode tail;		//β�ڵ�
	int length;		//����
}LinkList;

/*
 *	�������в�������
 *	
 *	������	LinkList *  list��Ҫ��ʼ��������
 *			ElemType	Ҫ���������
 *	���أ�	α��������(int)
 */
void insertElem(LinkList *list , ElemType e)
{
	if(list->tail != NULL)
	{
		list->tail->next = (LNode)malloc(sizeof(LNode));
		list->tail=list->tail->next;
		list->tail->data = e;
		list->tail->next = NULL;
		list->length++;
	}
	else
	{
		list->tail = (LNode)malloc(sizeof(LNode));
		list->head = list->tail;
		list->tail->data = e;
		list->tail->next = NULL;
		list->length++;
	}
}
/*
 *	��������ָ��λ��
 *	
 *	������	LinkList	list
 *			ElemType	e	  Ҫ���������
 *			int			n	  �ڵ�λ�� (��0��ʼ) 
 */
void insertNode(LinkList *list ,int n , ElemType e)
{
	int i = 0;
	LNode p = list->head;
	LNode q;
	while(i < n-1)	//�ҵ�Ҫ�����ǰһ���ڵ�
	{
		p = p->next;
		i++;
	}
	q = p->next;
	p->next = (LNode)malloc(sizeof(LNode));
	p->next->data = e;
	p->next->next = q;
	list->length++;
}

/*
 *	��ȡ����ָ��λ�õ�����
 *	
 *	������	LinkList	list
 *			int			n	  �ڵ�λ��(��0��ʼ) 
 *	���أ�	ElemType	�˽ڵ������  
 */
ElemType getNodeElem(LinkList list,int n)
{
	int i = 0;
	LNode p = list.head;
	while(i < n)		//�ҵ�Ҫ����Ľڵ�
	{
		p = p->next;
		i++;
	}
	return p->data;
}

/*
 *	ɾ������ָ���ڵ�
 *	
 *	������	LinkList	list
 *			int			n	  �ڵ�λ��(��0��ʼ) 
 */
void deleteNode(LinkList *list,int n)
{
	int i = 0;
	LNode p = list->head;
	LNode q;
	while(i < n-1)	//�ҵ�Ҫ�����ǰһ���ڵ�
	{
		p = p->next;
		i++;
	}
	q = p->next;
	p->next = q->next;
	list->length--;
}

/*
 *	�������
 *	
 *	������	LinkList   list��Ҫ���������
 */
void printLinkList(LinkList list)
{
	LNode p = list.head;

	printf("�����ȣ�");
	printf("%d\n",list.length);
	
	while(p != NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}


/*
 *	�����ʼ��
 *		ѭ��ɨ���������ݣ�ֱ������ָ��������Ϊֹ
 *	
 *	������	LinkList * 	list��Ҫ��ʼ��������
 *	���أ�	α��������(int)
 */
int initLinkList(LinkList *list)
{
	char c;

	list->length = 0;
	list->head = list->tail = NULL;

	printf("�������ʼ�����ݣ�\n");
	while(1)
	{
		scanf("%s",&c);
		if(c == END)
		{
			return TRUE;
		}
		else
		{
			insertElem(list,c);
		}
	}
}

/*
 * ��lpָ����ָ��λ�ÿ�ʼ������n���ڵ�
 *
 *	TODO: δ����
 */
LinkList copyList(LNode lp,int n)
{
	int i=0;
	LinkList list;
	LNode p;
	list.length = 0;
	p = list.head;
	while(lp->next != NULL && i++ <= n)
	{
		p = (LNode)malloc(sizeof(LNode));
		p->data = lp->data;

		p = p->next;
		lp = lp->next;
		list.length++;
	}
	p->next = NULL;
	list.tail = p;
	return list;
}
