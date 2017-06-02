#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* 创建蛇 */
snake* snake_create(void)
{
	snake* snake=malloc(sizeof(snake));
	if(!snake)
	{
		perror("malloc");
		exit(-1);
	}
	snake->head=NULL;
	snake->tail=NULL;
	snake->num=0;

	return snake;
}

/* 创建蛇结点 */
node* node_create(int row,int col)
{
	node* node=malloc(sizeof(node));
	if(!node)
	{
		perror("malloc");
		exit(-1);
	}
	node->row=row;
	node->col=col;
	node->next=NULL;
	node->prev=NULL;
}

/* 从尾部添加结点 */
void node_add(snake* ps,int row,int col)
{
	node* node=node_create(row,col);
	if(ps->head==NULL)
	{
		ps->head=node;
		ps->tail=node;
	}
	else
	{
		ps->tail->next=node;
		node->prev=ps->tail;
		ps->tail=node;
	}
	ps->num++;
}

/* 根据结点数据查找结点 */
int node_find(snake* ps,int row,int col)
{
	node* node=ps->head;

	while(node!=NULL)
	{
		if(node->row==row&&node->col==col)
		{
			return 0;
		}
		node=node->next;
	}
	
	return -1;
}

/* 蛇移动 */
void snake_move(snake* ps,int direction)
{
	node* node=ps->tail;

	while(node!=NULL)
	{
		if(node->prev!=NULL)
		{
			node->row=node->prev->row;
			node->col=node->prev->col;
		}
		node=node->prev;
	}

	switch(direction)
	{
		case UP:
			ps->head->row--;
			break;
		case DOWN:
			ps->head->row++;
			break;
		case LEFT:
			ps->head->col--;
			break;
		case RIGHT:
			ps->head->col++;
			break;
	}
}
















