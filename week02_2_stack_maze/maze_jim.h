#ifndef _MAZE_STACK_
#define _MAZE_STACK_
#define	HEIGHT 100
#define WIDTH 100
#include "../week02_1_stack/linkedstack_jim.h"
#include <stdbool.h>

void findPath(int mazeArray[WIDTH][HEIGHT], MapPosition startPos, \
				MapPosition endPos, \
				LinkedStack *pStack);
int pushLSMapPosition(LinkedStack* pStack, MapPosition data);
void showPath(LinkedStack *pStack);
void printMaze(int mazeArray[WIDTH][HEIGHT]);
bool movable(MapPosition curPos, int dir, int mazeArray[WIDTH][HEIGHT]);
MapPosition moveTo(MapPosition curPos, int dir, int  mazeArray[WIDTH][HEIGHT]);


#endif

#ifndef _MAZE_STACK_DEF_
#define _MAZE_STACK_DEF_

#define PATH		0		/* 갈 수 있는 곳 */
#define WALL		1		/* 벽 */
#define VISITED		2		/* 방문한 곳 */
#define BACLTRACLED	3		/* 되돌아갈 때 */
#endif