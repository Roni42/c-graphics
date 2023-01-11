/*  FILE NAME: 'MTH.H'
 *  PROGRAMMER: Veronika Korneeva
 *  LAST UPDATE: 06.01.2020
 *  PURPOSE: Vector and matrix maths.
 */

#include <math.h>

#ifndef __MTH_H_
#define __MTH_H_

/***
 * Generan constants and etc.
 ***/

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(A) D2R(A)

/* DOUBLE */
typedef double DBL;

/* Vector in 3D space */
typedef struct tagVEC
{
 DBL X, Y, Z;
} VEC;

/* Matr in struct (4D max) */
typedef struct tagMATR
{
 DBL M[4][4];
} MATR;

/* Unit matrix */
static MATR UnitMatrix =
{
 {
 {1, 0, 0, 0},
 {0, 1, 0, 0},
 {0, 0, 1, 0},
 {0, 0, 0, 1}
 }
};

/*** Realise functions ***/

/***
 * Verctors (3D space) and operations with them
 ***/

/* Set vector from coordinates */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
 VEC V;
 V.X = X;
 V.Y = Y;
 V.Z = Z;
 return V;
} /* End of 'VecSet' function */

/* Vector_1 + vector_2 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Vector_1 - vector_2 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Vector * const */
__inline VEC VecMulNum( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
} /* End of 'VecSubVec' function */

/* Vector / const */
__inline VEC VecDivNum( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
} /* End of 'VecDivVec' function */

/* Negativi */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecLen2' function */

/* Dot poduct */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return (V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z);
} /* End of 'VecDotVec' function */

/* Cross product */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(
    V1.Y * V2.Z - V1.Z * V2.Y, 
    V1.Z * V2.X - V1.X * V2.Z, 
    V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Vector len ^2 */
__inline DBL VecLen2( VEC V )
{
  return (V.X * V.X + V.Y * V.Y + V.Z * V.Z);
} /* End of 'VecLen2' function */

/* Vector len  */
__inline DBL VecLen( VEC V )
{
  return sqrt(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
} /* End of 'VecLen' function */

/* Normal of vector */
__inline VEC VecNormalize( VEC V )
{
  DBL l;
  if (V.X == 0 && V.Y == 0 && V.Z == 0 || (l = VecLen2(V)) == 1)
    return V;
  l = sqrt(l);
  return VecDivNum(V, l);
} /* End of 'VecNormalize' function */

/* Sum of two vectors equolity */
__inline VEC VecAddVecEq( VEC *VRes, VEC V2 )
{
 VRes->X += V2.X;
 VRes->Y += V2.Y;
 VRes->Z += V2.Z;
 return *VRes;
}

/* Vector mul matrix */
#if 1
__inline VEC VecMulMatr( VEC V, MATR M )
{
    return VecSet(
        V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0],
        V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1],
        V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2]);
} /* End of 'VecMulMatr' function */
#endif

/***
 * Matrixes and vectors (3D space) operations
 ***/

/* Vector mul matrix */
#if 1
__inline VEC VecMulMatr(VEC V, MATR M)
{
    return VecSet(
        V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0],
        V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1],
        V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2]);
} /* End of 'VecMulMatr' function */
#endif

/* Point tansformation */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(
    V.X * M.M[0][0] + V.Y * M.M[0][1] + V.Z * M.M[0][2] + M.M[0][3],
    V.X * M.M[1][0] + V.Y * M.M[1][1] + V.Z * M.M[1][2] + M.M[1][3],
    V.X * M.M[2][0] + V.Y * M.M[2][1] + V.Z * M.M[2][2] + M.M[2][3]);
}

/* Vector transformation */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(
    V.X * M.M[0][0] + V.Y * M.M[0][1] + V.Z * M.M[0][2],
    V.X * M.M[1][0] + V.Y * M.M[1][1] + V.Z * M.M[1][2],
    V.X * M.M[2][0] + V.Y * M.M[2][1] + V.Z * M.M[2][2]);
}

/***
 * Matrixes (4D space) and operations with them
 ***/

/* Matrix mul matrix */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;
  r.M[0][0] = 
    M1.M[0][0] * M2.M[0][0] + 
    M1.M[0][1] * M2.M[1][0] + 
    M1.M[0][2] * M2.M[2][0] + 
    M1.M[0][3] * M2.M[3][0];
  r.M[0][1] = 
    M1.M[0][0] * M2.M[0][1] + 
    M1.M[0][1] * M2.M[1][1] + 
    M1.M[0][2] * M2.M[2][1] + 
    M1.M[0][3] * M2.M[3][1];
  r.M[0][2] = 
    M1.M[0][0] * M2.M[0][2] + 
    M1.M[0][1] * M2.M[1][2] + 
    M1.M[0][2] * M2.M[2][2] + 
    M1.M[0][3] * M2.M[3][2];
  r.M[0][3] = 
    M1.M[0][0] * M2.M[0][3] + 
    M1.M[0][1] * M2.M[1][3] + 
    M1.M[0][2] * M2.M[2][3] + 
    M1.M[0][3] * M2.M[3][3];
  r.M[1][0] = 
    M1.M[1][0] * M2.M[0][0] + 
    M1.M[1][1] * M2.M[1][0] + 
    M1.M[1][2] * M2.M[2][0] + 
    M1.M[1][3] * M2.M[3][0];
  r.M[1][1] = 
    M1.M[1][0] * M2.M[0][1] + 
    M1.M[1][1] * M2.M[1][1] + 
    M1.M[1][2] * M2.M[2][1] + 
    M1.M[1][3] * M2.M[3][1];
  r.M[1][2] = 
    M1.M[1][0] * M2.M[0][2] + 
    M1.M[1][1] * M2.M[1][2] + 
    M1.M[1][2] * M2.M[2][2] + 
    M1.M[1][3] * M2.M[3][2];
  r.M[1][3] = 
    M1.M[1][0] * M2.M[0][3] + 
    M1.M[1][1] * M2.M[1][3] + 
    M1.M[1][2] * M2.M[2][3] + 
    M1.M[1][3] * M2.M[3][3];
  r.M[2][0] = 
    M1.M[2][0] * M2.M[0][0] + 
    M1.M[2][1] * M2.M[1][0] + 
    M1.M[2][2] * M2.M[2][0] + 
    M1.M[2][3] * M2.M[3][0];
  r.M[2][1] = 
    M1.M[2][0] * M2.M[0][1] + 
    M1.M[2][1] * M2.M[1][1] + 
    M1.M[2][2] * M2.M[2][1] + 
    M1.M[2][3] * M2.M[3][1];
  r.M[2][2] = 
    M1.M[2][0] * M2.M[0][2] + 
    M1.M[2][1] * M2.M[1][2] + 
    M1.M[2][2] * M2.M[2][2] + 
    M1.M[2][3] * M2.M[3][2];
  r.M[2][3] = 
    M1.M[2][0] * M2.M[0][3] + 
    M1.M[2][1] * M2.M[1][3] + 
    M1.M[2][2] * M2.M[2][3] + 
    M1.M[2][3] * M2.M[3][3];
  r.M[3][0] = 
    M1.M[3][0] * M2.M[0][0] + 
    M1.M[3][1] * M2.M[1][0] + 
    M1.M[3][2] * M2.M[2][0] + 
    M1.M[3][3] * M2.M[3][0];
  r.M[3][1] = 
    M1.M[3][0] * M2.M[0][1] + 
    M1.M[3][1] * M2.M[1][1] + 
    M1.M[3][2] * M2.M[2][1] + 
    M1.M[3][3] * M2.M[3][1];
  r.M[3][2] = 
    M1.M[3][0] * M2.M[0][2] + 
    M1.M[3][1] * M2.M[1][2] + 
    M1.M[3][2] * M2.M[2][2] + 
    M1.M[3][3] * M2.M[3][2];
  r.M[3][3] = 
    M1.M[3][0] * M2.M[0][3] + 
    M1.M[3][1] * M2.M[1][3] + 
    M1.M[3][2] * M2.M[2][3] + 
    M1.M[3][3] * M2.M[3][3];
  return r;
} /* End of 'MatrMulMatr' function */

/* Creating unit matrix */
__inline MATR MatrIdentity( VOID )
{
 return UnitMatrix;
}
/* Creating Matrix to translate vector */
__inline MATR MatrTranslate( VEC T )
{
 MATR m = UnitMatrix;
 m.M[3][0] = T.X;
 m.M[3][1] = T.Y;
 m.M[3][2] = T.Z;
 return m;
}

/* Calculate matrix(3x3) determ */
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13, DBL A21, DBL A22, DBL A23, DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 +
    A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Calculate matrix(4x4) determ */
__inline DBL MatrDeterm( MATR M )
{
 return
  M.M[0][0] * MatrDeterm3x3(
    M.M[1][1], M.M[1][2], M.M[1][3],
    M.M[2][1], M.M[2][2], M.M[2][3],
    M.M[3][1], M.M[3][2], M.M[3][3]) -
  M.M[0][1] * MatrDeterm3x3(
    M.M[1][0], M.M[1][2], M.M[1][3],
    M.M[2][0], M.M[2][2], M.M[2][3],
    M.M[3][0], M.M[3][2], M.M[3][3]) +
  M.M[0][2] * MatrDeterm3x3(
    M.M[1][0], M.M[1][1], M.M[1][3],
    M.M[2][0], M.M[2][1], M.M[2][3],
    M.M[3][0], M.M[3][1], M.M[3][3]) -
  M.M[0][3] * MatrDeterm3x3(
    M.M[1][0], M.M[1][1], M.M[1][2],
    M.M[2][0], M.M[2][1], M.M[2][2],
    M.M[3][0], M.M[3][1], M.M[3][2]);
} /* End of 'MatrDeterm' function */

/* Scale matrix */
__inline MATR MatrScale( VEC V )
{
  MATR M = UnitMatrix;
  M.M[0][0] = V.X;
  M.M[1][1] = V.Y;
  M.M[2][2] = V.Z;
  return M;
} /* End of 'MatrScale' function */

/* Create matrix to rotate around X */
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M = UnitMatrix;

  M.M[1][1] = co;
  M.M[2][2] = co;
  M.M[1][2] = si;
  M.M[2][1] = -si;
  return M;
} /* End of 'MatrRotateX' function */

/* Create matrix to rotate around Y */
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M = UnitMatrix;

  M.M[0][0] = co;
  M.M[0][2] = -si;
  M.M[2][0] = si;
  M.M[2][2] = co;
  return M;
} /* End of 'MatrRotateY' function */

/* Create matrix to rotate around Z */
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M = UnitMatrix;

  M.M[0][1] = si;
  M.M[1][0] = -si;
  M.M[0][0] = co;
  M.M[1][1] = co;
  return M;
} /* End of 'MatrRotateZ' function */

/* Ortho matrix function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       DBL Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   - (MATR) result matrix.
 */
__inline MATR MatrOrtho( DBL Left, DBL Right, DBL Bottom, DBL Top, DBL Near, DBL Far )
{
  MATR M = UnitMatrix;

  M.M[0][0] = 2 / (Right - Left);
  M.M[1][1] = 2 / (Top - Bottom);
  M.M[2][2] = 2 / (Far - Near);
  M.M[3][0] = -(Right + Left) / (Right - Left);
  M.M[3][1] = -(Top + Bottom) / (Top - Bottom);
  M.M[3][2] = -(Far + Near) / (Far - Near);
  return M;
} /* End of 'MatrOrtho' function */


/* Create  matrix to rorate around vector R */
__inline MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {
        co + V.X * V.X * (1 - co),
        V.X * V.Y * (1 - co) + V.Z * si,
        V.X * V.Z * (1 - co) - V.Y * si, 0
      },
      {
        V.Y * V.X * (1 - co) - V.Z * si,
        co + V.Y * V.Y * (1 - co),
        V.Y * V.Z * (1 - co) + V.X * si, 0
      },
      {
        V.Z * V.X * (1 - co) + V.Y * si,
        V.Z * V.Y * (1 - co) - V.X * si,
        co + V.Z * V.Z * (1 - co), 0
      },
      {0, 0, 0, 1}
    }
  };
 return M;
} /* End of 'MatrRotate' function */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   - (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecCrossVec(Right, Dir);
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

#endif /* __MTH_H_ */
/* END OF 'MTH.H' FILE */