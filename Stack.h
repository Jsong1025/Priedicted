include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

typedef  int ElemType;		//节点数据类型

typedef struct Node			//节点结构体
{
	ElemType data;
	struct Node *next;
}Node, *SNode;

typedef struct StackNode		//栈结构体
{
	SNode top;			//栈顶
	SNode bottom;		//栈底
	int length;			//栈深度
}Stack;

/*
 *  判断是否是空栈
 * 
 * 	参数：	Stack *  s
 *
 *	返回：伪布尔类型（int）
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
 *	数据压栈
 *	
 *	参数：	Stack *  s
 *			ElemType e	要压入的数据
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
 *	数据出栈
 *	
 *	参数：Stack	s
 *
 *	返回：ElemType  栈顶数据 
 */
ElemType pop(Stack *s)
{
	ElemType e = s->top->data;
	s->top = s->top->next;
	s->length--;
	return e;
}

/*
 *	栈遍历输出(倒序)
 *	
 *	参数：	Stack   s
 */
void printStack(Stack s)
{
	SNode p = s.top;

	printf("栈深度：");
	printf("%d\n",s.length);
	
	while(p != NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

/*
 *	获取栈顶元素
 *
 *	参数：Stack	s
 *
 *	返回：ElemType  栈顶数据 
 */
ElemType getTopElem(Stack s)
{
	return s.top->data;
}

/*
 *	栈初始化
 *	
 *	参数：	Stack *  s
 */
void initStack(Stack *s)
{
	s->length = 0;
	s->top = s->bottom = NULL;
}
