#ifndef LIST_H
#define LIST_H

/* 蛇结点 */
typedef struct node
{
	int row;
	int col;
	struct node* next;
	struct node* prev;
}node;

/* 蛇 */
typedef struct
{
	node* head;
	node* tail;
	int num;
}snake;


/* 蛇移动方向 */
enum{UP=8,DOWN=5,LEFT=4,RIGHT=6};

/* 创建蛇 */
snake* snake_create(void);
/* 创建蛇结点 */
node* node_create(int row,int col);
/* 从尾部添加结点 */
void node_add(snake* ps,int row,int col);
/* 根据结点数据查找结点 */
int node_find(snake* ps,int row,int col);
/* 蛇移动 */
void snake_move(snake* ps,int direction);

#endif //LIST_H
