/* Korneeva Veronika, 10-6, 06.01.2020 */
/* FILE NAME: 'main.C'
 *  PROGRAMMER: VK6
 *  LAST UPDATE: 06.01.2020
 *  PURPOSE: WinAPI windowed application sample.
 */
#include <stdlib.h>

#include "globe.h"
#include "timer.h"

#define VK6_MY_NAME "Prograaam"         

/* Main startup program function
 *  ARGUMENTS:
 *  - application instance handle
 *    HINSTANCE
 *  -
 *
 *  -
 *
 *  -
 *  RETURNS:
 *  -LRESULT CALLBACK
 */

/* Win handle function */
LRESULT CALLBACK VK6_WINFUNC(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hDC = 0;
  static int w = 800, h = 800;
  static HDC hMemDC;
  static HBITMAP hBm;
  static int R = 200;
  

  switch (Msg)
  {
  case WM_CREATE:
    Init(R, w / 2, h / 2, 0);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 13, 10, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    /* Create bitmap */
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);

    /* Attach bitmap */
    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 0, 0);

    return 0;
  case WM_TIMER:
    hDC = GetDC(hWnd);

    DrawGlobe(hMemDC, w, h);

    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    InvalidateRect(hWnd, NULL, FALSE);

    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_PAINT:     
    hDC = BeginPaint(hWnd, &ps); 
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBoxA(NULL, "Close the window?", "?", 
          MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 13);
  case WM_KEYDOWN:
    if (wParam == 'W')
    {
      R += 10;
      SendMessage(hWnd, WM_CREATE, 0, 0);
    }	
    if (wParam == 'S')
    {
      R -= 10;
      SendMessage(hWnd, WM_CREATE, 0, 0);
    }	
    if (wParam == 'P')
      GLB_IsPause = !GLB_IsPause;

    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'VK6_WINFUNC' function*/

int WINAPI WinMain( HINSTANCE hInstance, 
                   HINSTANCE hPrevlnstance, 
                   CHAR *lpCmdLine, 
                   int nShowCmd)
{
  HBRUSH hFirstBr;
  WNDCLASS wc;
  HWND hWnd; 
  MSG msg;


  hFirstBr = CreateSolidBrush(RGB(20, 25, 30));

  wc.style = 0;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = /*(HBRUSH)*/hFirstBr;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hInstance = hInstance;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = VK6_MY_NAME;
  wc.lpfnWndProc = VK6_WINFUNC;

  DeleteObject(hFirstBr);

  /* Checking class creation */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "ERROR", "", MB_OK | MB_ICONERROR);
    return 0;
  }
  /* Window creation */
  hWnd = CreateWindowA(VK6_MY_NAME, "Computer graphics globe", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 800,
    800, NULL, NULL, hInstance, NULL) ;

  
  /* Main massage loop */
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 0, 0);
  }

  return msg.wParam;
} /* End of 'WinMain' function */

/* END OF 'T41EYES.C' FILE */
