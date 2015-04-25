include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

typedef  int ElemType;		//�ڵ���������

typedef struct Node			//�ڵ�ṹ��
{
	ElemType data;
	struct Node *next;
}Node, *SNode;

typedef struct StackNode		//ջ�ṹ��
{
	SNode top;			//ջ��
	SNode bottom;		//ջ��
	int length;			//ջ���
}Stack;

/*
 *  �ж��Ƿ��ǿ�ջ
 * 
 * 	������	Stack *  s
 *
 *	���أ�α�������ͣ�int��
 */
int isEmpty(Stack s)
{
	if(s.top == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 *	����ѹջ
 *	
 *	������	Stack *  s
 *			ElemType e	Ҫѹ�������
 */
void push(Stack *s , ElemType e)
{
	SNode n;
	if(isEmpty(*s))
	{
		s->top = (SNode)malloc(sizeof(SNode));
		s->bottom = s->top;
		s->top->data = e;
		s->top->next = NULL;
		s->length++;
	}
	else
	{
		n = (SNode)malloc(sizeof(SNode));
		n->data = e;
		n->next = s->top;
		s->top = n;
		s->length++;
	}
}

/*
 *	���ݳ�ջ
 *	
 *	������Stack	s
 *
 *	���أ�ElemType  ջ������ 
 */
ElemType pop(Stack *s)
{
	ElemType e = s->top->data;
	s->top = s->top->next;
	s->length--;
	return e;
}

/*
 *	ջ�������(����)
 *	
 *	������	Stack   s
 */
void printStack(Stack s)
{
	SNode p = s.top;

	printf("ջ��ȣ�");
	printf("%d\n",s.length);
	
	while(p != NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

/*
 *	��ȡջ��Ԫ��
 *
 *	������Stack	s
 *
 *	���أ�ElemType  ջ������ 
 */
ElemType getTopElem(Stack s)
{
	return s.top->data;
}

/*
 *	ջ��ʼ��
 *	
 *	������	Stack *  s
 */
void initStack(Stack *s)
{
	s->length = 0;
	s->top = s->bottom = NULL;
}
