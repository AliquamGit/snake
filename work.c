#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <curses.h>

#include "list.h"

/* 地图宽度 */
#define WE 30
/* 地图高度 */
#define HI 30
/* 地图 */
int map[WE][HI];

/* 得分 */
int scores=0;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

/* 苹果 */
typedef struct
{
	int row;
	int col;
}apple_t;
apple_t apple;

/* 蛇 */
snake* ps=NULL;

/* 蛇运动方向 */
int direction;

/* 创建苹果 */
void apple_create(void)
{
	int row=0;
	int col=0;

	while(1)
	{
		row=rand()%28+1;
		col=rand()%28+1;
		if(node_find(ps,row,col))
		{
			apple.row=row;
			apple.col=col;
			break;
		}
	}
}

/* 初始化蛇 */
void snake_init(void)
{
	int row=0;
	int col=0;

	ps=snake_create();

	while(1)
	{
		row=rand()%28+1;
		col=rand()%28+1;
		if(apple.row!=row||apple.col!=col)
		{
			switch(rand()%4)
			{
				case 0:
					direction=UP;
					break;
				case 1:
					direction=DOWN;
					break;
				case 2:
					direction=LEFT;
					break;
				case 3:
					direction=RIGHT;
					break;
			}
			break;
		}
	}
	node_add(ps,row,col);
}

/* 显示画面 */
void show()
{
	int i=0;
	int j=0;

	system("clear");
	for(i=0;i<WE;i++)
	{
		for(j=0;j<HI;j++)
		{
			if(i==0||i==WE-1||j==0||j==HI-1)
			{
				printf("#");
			}
			else if(i==apple.row&&j==apple.col)
			{
				printf("\033[0;32m@\033[0m");
			}
			else if(i==ps->head->row&&j==ps->head->col)
			{
				printf("\033[0;31m$\033[0m");
			}
			else if(node_find(ps,i,j)==0)
			{
				printf("\033[0;33m+\033[0m");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\r\n");
	}
	printf("\r\n");
	printf("scores:%d\r\n",scores);
	fflush(stdout);
}

/* 移动 */
void _move(void)
{
	pthread_mutex_lock(&mutex);
	snake_move(ps,direction);
	pthread_mutex_unlock(&mutex);
}

/* 控制方向线程 */
void* direction_thread(void* arg)
{
	int _direction=0;
	initscr();

	while(1)
	{
		/*
		scanf("%*[^\n]");
		scanf("%*c");
		scanf("%d",&_direction);
		*/
		_direction=getch();
		//printf("\033[0;31m%c\033[0m",_direction);
		//fflush(stdout);
		if(_direction!=UP&&_direction!=DOWN&&_direction!=LEFT&&_direction!=RIGHT)
		{
			if(_direction==LEFT+1)
			{
				break;
			}
			continue;
		}
		if((_direction==UP&&direction==DOWN)||(_direction==DOWN&&direction==UP)||(_direction==LEFT&&direction==RIGHT)||(_direction==RIGHT&&direction==LEFT))
		{
			if(ps->num>1)
			{
				continue;
			}
		}
		pthread_mutex_lock(&mutex);
		direction=_direction;
		pthread_mutex_unlock(&mutex);
	}
	endwin();
	exit(0);
}

/* 碰撞类型 */
enum{CWALL,CAPPLE,CAIR,CSELF};

/* 碰撞检测 */
int collfunc(void)
{
	if(ps->head->row==0||ps->head->row==WE-1||ps->head->col==0||ps->head->col==HI-1)
	{
		return CWALL;
	}
	else if(ps->head->row==apple.row&&ps->head->col==apple.col)
	{
		node_add(ps,ps->tail->row,ps->tail->col);
		return CAPPLE;
	}
	/*
	else if(node_find(ps,ps->head->row,ps->head->col)==0&&ps->num>1)
	{
		return CSELF;
	}
	*/

	return CAIR;
}

int main(int argc,char* argv[])
{
	int i=0;
	int j=0;
	int coll=0;
	int cmd;
	pthread_t tid;

	srand(time(NULL));
	pthread_create(&tid,NULL,direction_thread,NULL);

	snake_init();
	apple_create();
	show();

	do
	{
		_move();
		coll=collfunc();
		if(coll==CWALL||coll==CSELF)
		{
			printf("\033[0;31mGame Over\033[0m\n");
			endwin();
			exit(0);
		}
		else if(coll==CAPPLE)
		{
			scores+=10;
			apple_create();
		}
		show();
		usleep(300000);
		//sleep(10);
	}while(1);

	return 0;
}











