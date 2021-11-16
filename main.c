#include "definitions.h"
#include "game.c"
#include "handles.c"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  // Hide console window
  ShowWindow(GetConsoleWindow(), SW_HIDE); 

  static TCHAR szWindowClass[] = _T("DesktopApp");
  static TCHAR szTitle[] = _T("Snake");
  MSG msg;

  // setup window
  WNDCLASSEX wcex = {
    .cbSize = sizeof(WNDCLASSEX),
    .style = CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc = WndProc,
    .cbClsExtra = 0,
    .cbWndExtra = 0,
    .hInstance = hInstance,
    .hIcon = LoadIcon(hInstance, IDI_APPLICATION),
    .hCursor = LoadIcon(hInstance, IDC_HAND),
    .hbrBackground = (HBRUSH) (COLOR_WINDOW + 1),
    .lpszMenuName = NULL,
    .lpszClassName = szWindowClass,
    .hIconSm = LoadIcon(hInstance, IDI_APPLICATION),
  };

  // register window
  if(!RegisterClassEx(&wcex)) {
    MessageBox(NULL, 
      _T("Call to RegisterClassEx failed!"), 
      _T("Snake"),
      0
    );

    return 1;
  }
  
  int xPos = (GetSystemMetrics(SM_CXSCREEN) - WIN_LENGTH) / 2;
  int yPos = (GetSystemMetrics(SM_CYSCREEN) - WIN_HEIGHT) / 2;

  // create window
  HWND hWnd = CreateWindow(
    szWindowClass, 
    szTitle, 
    WS_OVERLAPPEDWINDOW, 
    xPos, yPos, 
    WIN_LENGTH, WIN_HEIGHT, 
    NULL, 
    NULL, 
    hInstance, 
    NULL
  );

  if(!hWnd) {
    MessageBox(NULL, 
      _T("Call to CreateWindowEx Failed!"), 
      _T("Snake"), 
      0
    );

    return 1;
  }
  
  //initialise the game
  InitGame(&hWnd); 

  // show window
  ShowWindow(hWnd, nCmdShow);
  // UpdateWindow(hWnd);

  // message loop
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // Destroy Game and Cleanup
  DestroyGame();
  
  // Show console window
  ShowWindow(GetConsoleWindow(), SW_SHOW); 
  return (int) msg.wParam;
}
