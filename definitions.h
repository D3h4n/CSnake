#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <wingdi.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

// snake
#define SNAKE_HEAD_COLOUR RGB(69, 111, 56)
#define SNAKE_BODY_COLOUR RGB(79, 121, 66)

#define FOOD_COLOUR RGB(222, 82, 70)

// dimensions
#define WIN_LENGTH 572
#define WIN_HEIGHT 600
#define GRID_PADDING 25

#define NODE_SIZE 20

#define NUM_ROWS 25
#define NUM_COLS 25

#define INTIALTIMEDELAY 100

// files
#define HIGHSCORE_FILENAME "highscore.bin"

// macros
#define __coord(x) (x * NODE_SIZE)


// types
typedef enum SNAKEDIR_ENUM {
  SNAKEDIR_UP,
  SNAKEDIR_DOWN, 
  SNAKEDIR_LEFT,
  SNAKEDIR_RIGHT
} E_SnakeDir;

typedef struct Node_struct {
  INT16 x, y;
  struct Node_struct * next;
} Node, *P_SnakeNode, *P_FoodNode;

// global constants
const RECT MapRect = {
  .top = GRID_PADDING,
  .bottom = __coord(NUM_ROWS) + GRID_PADDING,
  .left = GRID_PADDING,
  .right = __coord(NUM_COLS) + GRID_PADDING
};


// global variables
pthread_t workerThread;

pthread_mutex_t pauseLock;
BOOL lockInput = FALSE;
BOOL running = TRUE;

UINT score = 0;
UINT highscore = 0;

RECT foodRect;
HBRUSH foodBrush;
HBRUSH snakeHeadBrush;
HBRUSH snakeBodyBrush;

P_FoodNode food = NULL;
P_SnakeNode head = NULL;
P_SnakeNode tail = NULL;
E_SnakeDir snakeDir = SNAKEDIR_UP;
#endif
