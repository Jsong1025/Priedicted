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
}Grammer;

/* ��ʼ��Grammar */
void initGrammer(Grammer *G)
{
	G->length = 0;
	G->expresses = NULL;
}

