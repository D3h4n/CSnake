#include "definitions.h"

void handlePaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hWnd, &ps);
  
  DrawFood(hdc);
  DrawSnake(hdc);
  DrawScore(hdc);
  FrameRect(hdc, &MapRect, CreateSolidBrush(0));

  EndPaint(hWnd, &ps);
}
     

void handleKeydown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(wParam){
    case 'W':
    case VK_UP:
      UpdateDir(SNAKEDIR_UP);
      break;
    
    case 'A':
    case VK_LEFT:
      UpdateDir(SNAKEDIR_LEFT);
      break;

    case 'S':
    case VK_DOWN:
      UpdateDir(SNAKEDIR_DOWN);
      break;
    
    case 'D':
    case VK_RIGHT:
      UpdateDir(SNAKEDIR_RIGHT);
      break;

    case VK_ESCAPE:
      pthread_mutex_lock(&pauseLock);

      if (MessageBox(hWnd, _T("Continue?"), _T("Pause"), MB_YESNO) == IDNO) {
        SendMessage(hWnd, WM_DESTROY, 0, 0);
      }
      
      pthread_mutex_unlock(&pauseLock);
      break;
  }
}
    
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
    case WM_PAINT:
      handlePaint(hWnd, message, wParam, lParam);
      break;

    case WM_KEYDOWN:
      handleKeydown(hWnd, message, wParam, lParam);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}
