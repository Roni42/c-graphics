/* Korneeva Veronika, 10-6, 06.01.2020 */
/* FILE NAME: 'globe.c'
*  PROGRAMMER VK6;
*  LAST UPDATE 06.01.2020
*  PURPOSE: WinAPI windowed application sample.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "globe.h"
#include "timer.h"

/* PI */
#define PI 3.14159265358979323846

/**/
#define GLB_W 20
#define GLB_H 20
#define N (GLB_H * GLB_H)

#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B),C)
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr(A, B), MatrMulMatr(C, D))
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr(MatrMulMatr(A, B), MatrMulMatr3(C, D, E))
#define MatrMulMatr6(A, B, C, D, E, F) MatrMulMatr(MatrMulMatr3(A, B, C), MatrMulMatr3(D, E, F))

VEC G[GLB_H][GLB_W], GLB_Globe[GLB_H][GLB_W];
POINT GLB_Glob[GLB_H * 2][GLB_W * 2];
int GLB_CY = 0, GLB_CX = 0; 


/* Filling mas function. 
 * ARGUMENTS:
 *   - radius of sphere:
 *       dbl r;
 *   - center coordinates:
 *       int cx, cy, cz;
 * RETURNS: None.
 */
void Init( dbl r, int cx, int cy, int cz )
{
  dbl AngT, AngP, x, y, z;
  int i, j, wx = GLB_H, wy = GLB_W;

  GLB_CX = cx, GLB_CY = cy;
  for (AngT = 0, i = 0; i < GLB_H; i++, AngT += PI / (GLB_H - 1))
    for (AngP = 0, j = 0; j < GLB_W; j++, AngP += PI * 2 / (GLB_W - 1))
    {
      x = r * sin(AngT) * sin(AngP);
      y = r * cos(AngT);
      z = r * sin(AngT) * cos(AngP) + cz;
      G[i][j] = VecSet(x, y, z);
    }
} /* End of 'Init' function */

/* Filling mas function. 
 * ARGUMENTS:
 *   - HDC:
 *       HDC hdc;
 *   - width and height:
 *       int w, h;
 * RETURNS: None.
 */
void DrawGlobe( HDC hdc, int w, int h )
{
  int i, j, s = 2, r;
  dbl t;
  HPEN hPen, hOldPen;
  HBRUSH hBr, hBr1, hBr2, hOldBr;

  GLB_TimerResponse();
  t = GLB_Time;

  for (i = 0; i < GLB_H; i++)
    for (j = 0; j < GLB_W; j++)
    {
      VEC V = PointTransform(G[i][j], MatrMulMatr5(
                MatrRotateZ(t * 5),
                MatrRotateX(sin(t) * 20), 
                MatrRotateY(8 * t), 
                MatrScale(VecSet(1, 0.8, 1)), 
                MatrTranslate(VecSet(-500, -500, 0))));

      GLB_Glob[i][j].x = V.X + w / 2, 
      GLB_Glob[i][j].y = V.Y + h / 2;

    }

  hBr = CreateSolidBrush(RGB(223, 213, 123));
  hBr1 = CreateSolidBrush(RGB(250, 140, 30));
  hBr2 = GetStockObject(NULL_BRUSH);
  hOldBr = SelectObject(hdc, hBr);
  hPen = CreatePen(PS_SOLID, 0, RGB(180, 100, 230));
  hOldPen = SelectObject(hdc, hPen);

  Rectangle(hdc, 0, 0, w + 1, h + 1);

#if 0

  for (i = 0; i < GLB_H; i++)
    for (j = 0; j < GLB_W; j++)
    {
      Ellipse(hdc, GLB_Glob[i][j].x - s, GLB_Glob[i][j].y - s, 
        GLB_Glob[i][j].x + s, GLB_Glob[i][j].y + s);
    }

#endif
#if 0

    for (i = 1; i < GLB_H - 1; i++)
  {
    MoveToEx(hdc, GLB_Glob[i][0].x, GLB_Glob[i][0].y, NULL);
    for (j = 1; j < GLB_W; j++)
    {
      LineTo(hdc, GLB_Glob[i][j].x, GLB_Glob[i][j].y);
    }
  }
  for (i = 1; i < GLB_W; i++)
  {
    MoveToEx(hdc, GLB_Glob[0][0].x, GLB_Glob[0][0].y, NULL);
    for (j = 1; j < GLB_H; j++)
    {
      LineTo(hdc, GLB_Glob[j][i].x, GLB_Glob[j][i].y);
    }
  }

#endif

/*  polygon function.
 * ARGUMENTS:
 *   - d:
 *     V;
 *   - es:
 *     e;
 * RETURNS:
 *   (V.
 */

  SelectObject(hdc, hBr);
  SetDCPenColor(hdc, RGB(250, 140, 30));
  SetDCBrushColor(hdc, RGB(250, 140, 30));

  for (r = 2; r > 0; r--)
    for (i = 0; i < GLB_H - 1; i++)
      for (j = 0; j < GLB_W - 1; j++)
      {
        POINT pnt[4];

          pnt[0].x = GLB_Glob[i][j].x, 
          pnt[0].y = GLB_Glob[i][j].y, 
          pnt[1].x = GLB_Glob[i + 1][j].x, 
          pnt[1].y = GLB_Glob[i + 1][j].y, 
          pnt[2].x = GLB_Glob[i + 1][j + 1].x, 
          pnt[2].y = GLB_Glob[i + 1][j + 1].y, 
          pnt[3].x = GLB_Glob[i][j + 1].x, 
          pnt[3].y = GLB_Glob[i][j + 1].y; 

          if (r == 2 &&
            (pnt[0].x - pnt[1].x) * (pnt[0].y + pnt[1].y) / 2 +
            (pnt[1].x - pnt[2].x) * (pnt[1].y + pnt[2].y) / 2 +
            (pnt[2].x - pnt[3].x) * (pnt[2].y + pnt[3].y) / 2 +
            (pnt[3].x - pnt[0].x) * (pnt[3].y + pnt[0].y) / 2 < 0)
          {
            SelectObject(hdc, hBr1);
            Polygon(hdc, pnt, 4);
          }
          else if (r == 1 &&
            (pnt[0].x - pnt[1].x) * (pnt[0].y + pnt[1].y) / 2 +
            (pnt[1].x - pnt[2].x) * (pnt[1].y + pnt[2].y) / 2 +
            (pnt[2].x - pnt[3].x) * (pnt[2].y + pnt[3].y) / 2 +
            (pnt[3].x - pnt[0].x) * (pnt[3].y + pnt[0].y) / 2 >= 0)
          {
            SelectObject(hdc, hBr2);
            Polygon(hdc, pnt, 4);
            ;
          }

    }

  SelectObject(hdc, hOldPen);
  DeleteObject(hPen);
  SelectObject(hdc, hOldBr);
  DeleteObject(hBr);
  DeleteObject(hBr1);
  DeleteObject(hBr2);
  
  if (!GLB_IsPause)
  {
    CHAR Buf[47];

    TextOut(hdc, 5, 5, Buf, sprintf(Buf, "FPS: %5lf", GLB_FPS));
  }
  
}
