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
}Grammer;

/* 初始化Grammar */
void initGrammer(Grammer *G)
{
	G->length = 0;
	G->expresses = NULL;
}

