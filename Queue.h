#include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

typedef  int ElemType;		//�ڵ���������

typedef struct Node			//�ڵ�ṹ��
{
	ElemType data;
	struct Node *next;
}Node, *QNode;

typedef struct QueueNode		//���нṹ��
{
	QNode head;			//��ͷ
	QNode tail;			//��β
	int length;			//���г���
}Queue;

/*
 *  �ж��Ƿ��ǿն���
 * 
 * 	������	Queue *  q
 *
 *	���أ�α�������ͣ�int��
 */
int isEmpty(Queue q)
{
	if(q.head == NULL && q.tail == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 *	�����
 *	
 *	������	Queue *  q
 *			ElemType e	Ҫ��ӵ�����
 */
void enQueue(Queue *q , ElemType e)
{
	if(isEmpty(*q))
	{
		q->tail = (QNode)malloc(sizeof(QNode));
		q->tail->data = e;
		q->head = q->tail;
		q->tail->next = NULL;
		q->length++;
	}
	else
	{
		q->tail->next = (QNode)malloc(sizeof(QNode));
		q->tail = q->tail->next;
		q->tail->data = e;
		q->tail->next = NULL;
		q->length++;
	}
}

/*
 *	���ݳ�����
 *	
 *	������Queue	q
 *
 *	���أ�ElemType  ��ͷ���� 
 */
ElemType deQueue(Queue *q)
{
	ElemType e = q->head->data;
	q->head = q->head->next;
	q->length--;
	return e;
}

/*
 *	ջ�������
 *	
 *	������	Queue   q
 */
void printQueue(Queue q)
{
	QNode p = q.head;

	printf("���г��ȣ�");
	printf("%d\n",q.length);
	
	while(p != NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

/*
 *	��ȡ��ͷԪ��
 *
 *	������Queue	q
 *
 *	���أ�ElemType  ��ͷ���� 
 */
ElemType getHead(Queue q)
{
	return q.head->data;
}

/*
 *	��ȡ��βԪ��
 *
 *	������Queue	q
 *
 *	���أ�ElemType  ��β���� 
 */
ElemType getTail(Queue q)
{
	return q.tail->data;
}

/*
 *	���г�ʼ��
 *	
 *	������	Queue *  q
 */
void initQueue(Queue *q)
{
	q->length = 0;
	q->head = q->tail = NULL;
}
