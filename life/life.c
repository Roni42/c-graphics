/* Veronika Korneeva, 11-6, 05.11.2020 */

#include <glut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H (800 / 4)
#define W (800 / 4)
#define ST 3

typedef unsigned char byte;

byte *F1, *F2, *Screen;
byte Fr[H][W][3];


void PutPixel( int x, int y, int a, int b, int c )
{
  if (x >= W || x < 0 || y < 0 || y >= H)

  Fr[y][x][0] = a;
  Fr[y][x][1] = b;
  Fr[y][x][2] = c;
}


void SetCell( byte *F, int x, int y, int live_pnt )
{
  x = (x + W) % W;
  y = (y + H) % H;

  F[x + y * W] = live_pnt;
}

int GetCell( byte *F, int x, int y )
{
  x = (x + W) % W;
  y = (y + H) % H;
  
  return F[x + y * W];
}
void FieldInit( void )
{
  int x, y;

  F1 = malloc(sizeof(F1) * W * H * 2);
  F2 = F1 + W * H;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
      SetCell(F1, x, y, rand() % 2 * 10 * (rand() % 2));
}

void FieldDraw( void )
{
  int x, y;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
    {
      int live_pnt = GetCell(F1, x, y);

      if (live_pnt == 0)
        PutPixel(x, y, 10, 0, 10);
      else if (live_pnt == 1)
        PutPixel(x, y, 20, 150, 20);
      else if (live_pnt == 10)
        PutPixel(x, y, 255, 255, 255);

    }
}

int GetNeighbours( byte *F, int x, int y )
{
  return 
    GetCell(F, x + 1, y + 1) + 
    GetCell(F, x + 1, y - 1) + 
    GetCell(F, x - 1, y + 1) + 
    GetCell(F, x - 1, y - 1) + 
    GetCell(F, x, y - 1) + 
    GetCell(F, x, y + 1) + 
    GetCell(F, x + 1, y) + 
    GetCell(F, x - 1, y);
}

void NewGeneation( byte *F11, byte *F22 )
{
  int x, y;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
    {
      int live_pnt = GetCell(F11, x, y);
      double n = (GetNeighbours(F11, x, y) / 10.);

      if (n >= 3 && n < 4)
        SetCell(F22, x, y, 10);
      else if (live_pnt == 10 && n >= 2 && n <= 3)
        SetCell(F22, x, y, 10);
      else if (live_pnt == 10 && (n < 2 || n > 3))
        SetCell(F22, x, y, 1);
      else if (live_pnt == 1 && (n < 2 || n > 3))
        SetCell(F22, x, y, 0);
      else
        SetCell(F22, x, y, 0);
    }
  
  //memcpy(F11, F22, W * H);
  Screen = F2, F2 = F1, F1 = Screen;  
}

double t = 0;
void Display( void )
{
  double l_t = clock();

  if (l_t - t > 0.3 / CLOCKS_PER_SEC)
  {
    NewGeneation(F1, F2);
    FieldDraw();
    t = l_t;
  }

  glPixelZoom(8, 8);
  glClearColor(0.3, 0, 0.5, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(W, H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Fr);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();

}

void Rand( int num )
{
  int i;

  for (i = 0; i < num * 47; i++)
    SetCell(F1, rand() % W, rand() % H, 10);
}
void Keyboard( byte key, int x, int y)
{
  if (key == 27)
    exit(0);
  printf("%i ", key);
  if (key >= 49 && key <= 57)
    Rand(key - 49);
}

int main( int argc, char *argv[])
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(20, 20);
  glutInitWindowSize(W * 4 + 30, H * 4 + 30);
  glutCreateWindow("Krya!");
  
  FieldInit();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
  return 0;
}