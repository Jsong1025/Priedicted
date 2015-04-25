#include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

typedef  int ElemType;		//节点数据类型

typedef struct Node			//节点结构体
{
	ElemType data;
	struct Node *next;
}Node, *QNode;

typedef struct QueueNode		//队列结构体
{
	QNode head;			//队头
	QNode tail;			//队尾
	int length;			//队列长度
}Queue;

/*
 *  判断是否是空队列
 * 
 * 	参数：	Queue *  q
 *
 *	返回：伪布尔类型（int）
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
 *	入队列
 *	
 *	参数：	Queue *  q
 *			ElemType e	要入队的数据
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
 *	数据出队列
 *	
 *	参数：Queue	q
 *
 *	返回：ElemType  队头数据 
 */
ElemType deQueue(Queue *q)
{
	ElemType e = q->head->data;
	q->head = q->head->next;
	q->length--;
	return e;
}

/*
 *	栈遍历输出
 *	
 *	参数：	Queue   q
 */
void printQueue(Queue q)
{
	QNode p = q.head;

	printf("队列长度：");
	printf("%d\n",q.length);
	
	while(p != NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

/*
 *	获取队头元素
 *
 *	参数：Queue	q
 *
 *	返回：ElemType  队头数据 
 */
ElemType getHead(Queue q)
{
	return q.head->data;
}

/*
 *	获取队尾元素
 *
 *	参数：Queue	q
 *
 *	返回：ElemType  队尾数据 
 */
ElemType getTail(Queue q)
{
	return q.tail->data;
}

/*
 *	队列初始化
 *	
 *	参数：	Queue *  q
 */
void initQueue(Queue *q)
{
	q->length = 0;
	q->head = q->tail = NULL;
}
