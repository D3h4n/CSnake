#include "definitions.h"

P_SnakeNode CreateNode() {
  P_SnakeNode temp;
  
  if ((temp = malloc(sizeof(Node))) == NULL) {
    return NULL;
  }

  temp->x = 0;
  temp->y = 0;
  temp->next = NULL;

  return temp;
}

void GetRect(Node * node, RECT * rect) {
  rect->top = __coord(node->y) + GRID_PADDING;
  rect->bottom = rect->top + NODE_SIZE;
  rect->left = __coord(node->x) + GRID_PADDING;
  rect->right = rect->left + NODE_SIZE;
}

void AddNode(P_SnakeNode newNode) {
  newNode->x = tail->x;
  newNode->y = tail->y;

  tail->next = newNode;
  tail = newNode;
}

void DrawSnake(HDC hdc) {
  RECT rect;
  P_SnakeNode curr = head->next;

  GetRect(head, &rect);
  FillRect(hdc, &rect, snakeHeadBrush);

  while(curr) {
    GetRect(curr, &rect);
    FillRect(hdc, &rect, snakeBodyBrush);
    curr = curr->next;
  }
}

void UpdateDir(E_SnakeDir newSnakeDir) {
  if(lockInput) return; // prevent input before snake moves

  lockInput = TRUE;

  // prevent snake turning back into itself
  if (newSnakeDir == SNAKEDIR_UP && snakeDir == SNAKEDIR_DOWN) {
    return;
  } 
  
  if (newSnakeDir == SNAKEDIR_DOWN && snakeDir == SNAKEDIR_UP) {
    return;
  }

  if (newSnakeDir == SNAKEDIR_LEFT && snakeDir == SNAKEDIR_RIGHT){
    return;
  }

  if (newSnakeDir == SNAKEDIR_RIGHT && snakeDir == SNAKEDIR_LEFT){
    return;
  }

  snakeDir = newSnakeDir;
}

void MoveSnake() {
  UINT16 prevX, prevY, temp;
  P_SnakeNode curr = head->next;

  // store last head coords
  prevX = head->x;
  prevY = head->y;

  // move snake head
  switch(snakeDir){
    case SNAKEDIR_UP:
      head->y--;

      if (head->y < 0) {
        head->y = NUM_ROWS - 1;
      }
      break;

    case SNAKEDIR_DOWN:
      head->y++;

      if (head->y >= NUM_ROWS) {
        head->y = 0;
      }
      break;

    case SNAKEDIR_LEFT:
      head->x--;

      if (head->x < 0) {
        head->x = NUM_COLS - 1;
      }
      break;

    case SNAKEDIR_RIGHT:
      head->x++;

      if (head->x >= NUM_COLS) {
        head->x = 0;
      }
      break; 
  }


  // move snake body
  while(curr) {
    temp = curr->x;
    curr->x = prevX;
    prevX = temp;

    temp = curr->y;
    curr->y = prevY;
    prevY = temp;

    curr = curr->next;
  }
}

BOOL CheckSnakeCollision(INT16 x, INT16 y) {
  P_SnakeNode curr = head->next;

  // iterate through each node and check if coords match  
  while(curr) {
    if(curr->x == x && curr->y == y) {
      return TRUE;
    }

    curr = curr->next;
  }

  return FALSE;
}

void InitSnake() {
  // create head node
  if((head = CreateNode()) == NULL) {
    MessageBox(NULL, _T("Error initializing snake"), "caption", 0);
    exit(1);
  }

  // init head in the middle of the grid
  head->x = (NUM_COLS / 2) - 1;
  head->y = (NUM_ROWS / 2) - 1;
  tail = head;

  // create brushes for head and body of snake
  snakeHeadBrush = CreateSolidBrush(SNAKE_HEAD_COLOUR);
  snakeBodyBrush = CreateSolidBrush(SNAKE_BODY_COLOUR);
}

void DestroySnake() {
  P_SnakeNode next;

  // de-allocate nodes
  while(head) {
    next = head->next;
    free(head);
    head = next;
  }

  // destroy objects
  DeleteObject(snakeBodyBrush);
  DeleteObject(snakeHeadBrush);
}
