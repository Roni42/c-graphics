/* Korneeva Veronika, 10-6, 06.01.2020 */
/* FILE NAME: 'help.c'
*  PROGRAMMER VK6;
*  LAST UPDATE 06.01.2020
*  PURPOSE: WinAPI windowed application sample.
*/
#include <math.h>
#include <time.h>

#include "globe.h"
 
#define PI 3.14159265358979323846

#if 0
/* Rotate vector around z axis function.
 * ARGUMENTS:
 *   - vertor to be rotated:
 *       VEC V;
 *   - rotate angle in degrees:
 *       dbl Angle;
 * RETURNS:
 *   (VEC) result (rotated) vector.
 */

VEC VecRotateZ( VEC V, dbl Angle )
{
  dbl A, a; 
  A = a, a = D2R(A), si = sin(a), co = cos(a);


  return VecSet(V.X * co - V.Y * si, V.X * si + V.Y * co, V.Z);
} /* End of 'VecRotateZ' function */

/* Rotate vector around y axis function.
 * ARGUMENTS:
 *   - vertor to be rotated:
 *       VEC V;
 *   - rotate angle in degrees:
 *       dbl Angle;
 * RETURNS:
 *   (VEC) result (rotated) vector.
 */
VEC VecRotateY( VEC V, dbl Angle )
{
  dbl a = D2R(Angle), si = sin(a), co = cos(a);

  return VecSet(V.Z * si + V.X * co, V.Y, V.Z * co - V.X * si);
} /* End of 'VecRotateY' function */

/* Rotate vector around x axis function.
 * ARGUMENTS:
 *   - vertor to be rotated:
 *       VEC V;
 *   - rotate angle in degrees:
 *       dbl Angle;
 * RETURNS:
 *   (VEC) result (rotated) vector.
 */
VEC VecRotateX( VEC V, dbl Angle )
{
  dbl a = D2R(Angle), si = sin(a), co = cos(a);

  return VecSet(V.X, V.Y * co - V.Z * si, V.Y * si + V.Z * co);
} /* End of 'VecRotateX' function */
#endif
/* END OF 'HELP.C' FILE */