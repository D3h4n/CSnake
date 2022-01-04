#include "definitions.h"
#include "snake.c"
#include "highscore.c"

void GenerateRandFood() {
  do{
    food->x = rand() % NUM_COLS;
    food->y = rand() % NUM_ROWS;
  }while(CheckSnakeCollision(food->x, food->y));

  GetRect(food, &foodRect);
}

BOOL CheckFoodCollision() {
  if ((head->x == food->x) && (head->y == food->y)) {
    score++;
    GenerateRandFood();
    AddNode(CreateNode());
    return TRUE;
  }

  return FALSE;
}

static inline void DrawFood(HDC hdc) {
  FillRect(hdc, &foodRect, foodBrush);
}

void DrawScore(HDC hdc) {
  char text[30];

  sprintf(text, "Highscore: %u    Score: %u", highscore, score);

  TextOut(hdc, 200, 5, text, strlen(text));
}

void ResetGame() {
  score = 0;

  DestroySnake();
  InitSnake();
  GenerateRandFood();
}

void CheckErrorBox(BOOL check, char * errorMsg, HWND hWnd){
  if (!check)
    return;

  MessageBox(hWnd, errorMsg, _T("ERROR"), MB_OK | MB_ICONSTOP | MB_TOPMOST);
}

void * GameLoop(void * arg) {
  HWND hWnd = *(HWND *) arg;
  int timeDelay = INTIALTIMEDELAY;
  char message[30];

  while(running) {
    // update snake position and screen
    MoveSnake();
    InvalidateRgn(hWnd, NULL, TRUE);
    
    // allow input
    lockInput = FALSE;

    // check if snake ate food
    // speed up snake if score is multiple of 10
    if(CheckFoodCollision() && (score % 10 == 0)){
      timeDelay *= 0.75;
    }

    // check if snake hit itself
    if(score > 1 && CheckSnakeCollision(head->x, head->y)){
      // check if  new highscore
      if (score > highscore) {
        CheckErrorBox(!writeHighscore(score), "Error Writing Highscore", hWnd);
        sprintf(message, "New Highscore: %u\n\nTRY AGAIN?", score);
        highscore = score;
      }
      else {
        sprintf(message, "Score: %u\n\nTRY AGAIN?", score);
      }

      // display gameover message
      int msgBoxID = MessageBox(hWnd, message, _T("GAMEOVER"), MB_YESNO);

      // handle try again or exit
      switch(msgBoxID) {
        case IDNO:
          SendMessage(hWnd, WM_DESTROY, 0, 0);
          break;
        
        default:
          timeDelay = INTIALTIMEDELAY;
          ResetGame();
      }
    }

    // time delay between frames
    Sleep(timeDelay);

    // stop loop if pause screen
    pthread_mutex_lock(&pauseLock);
    pthread_mutex_unlock(&pauseLock);
  }

  return NULL;
}

void InitGame(HWND * hWnd) {
  pthread_mutex_init(&pauseLock, NULL); // init mutex lock

  srand(time(0));
  highscore = getHighscore();

  InitSnake();

  // init food
  foodBrush = CreateSolidBrush(FOOD_COLOUR);
  food = CreateNode();
  GenerateRandFood();

  // init worker thread
  pthread_create(&workerThread, NULL, GameLoop, hWnd);
}

void DestroyGame() {
  // stop worker thread
  running = FALSE;
  pthread_join(workerThread, NULL);

  // de-allocate objects
  pthread_mutex_destroy(&pauseLock);

  DestroySnake();

  free(food);
  DeleteObject(foodBrush);
}
