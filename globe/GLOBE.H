/* Korneeva Veronika, 10-6, 06.01.2020 */
/* FILE NAME: 'globe.h'
*  PROGRAMMER VK6;
*  LAST UPDATE 06.01.2020
*  PURPOSE: WinAPI windowed application sample.
*/

#include <windows.h>
#include <commondf.h>

#include "mth.h"

#ifndef __GLOBE_H_
#define __GLOBE_H_

#ifndef __MTH_H_
typedef double dbl;

typedef struct tagVEC VEC;
struct tagVEC
{
  dbl X, Y, Z;
} ;
#endif

/* Array filling function. 
 * ARGUMENTS:
 *   - radius of sphere:
 *       dbl r;
 *   - center coordinates:
 *       int cx, cy, cz;
 * RETURNS:
 *   - NONE.
 */
void Init( dbl r, int cx, int cy, int cz );

/* Drawing function. 
 * ARGUMENTS:
 *   - HDC:
 *       HDC hdc;
 *   - width and height:
 *       int w, h;
 * RETURNS: None.
 */
void DrawGlobe( HDC hdc, int w, int h );

#if 0
/* Vector init */
VEC VecSet( dbl x, dbl y, dbl z );

/* Rotate vector around x axis function.
 * ARGUMENTS:
 *   - vertor to be rotated:
 *       VEC V;
 *   - rotate angle in degrees:
 *       dbl Angle;
 * RETURNS:
 *   (VEC) result (rotated) vector.
 */
VEC VecRotateX( VEC V, dbl Angle );

/* Rotate vector around y axis function.
 * ARGUMENTS:
 *   - vertor to be rotated:
 *       VEC V;
 *   - rotate angle in degrees:
 *       dbl Angle;
 * RETURNS:
 *   (VEC) result (rotated) vector.
 */
VEC VecRotateY( VEC V, dbl Angle );

/* Rotate vector around z axis function.
 * ARGUMENTS:
 *   - vertor to be rotated:
 *       VEC V;
 *   - rotate angle in degrees:
 *       dbl Angle;
 * RETURNS:
 *   (VEC) result (rotated) vector.
 */
VEC VecRotateZ( VEC V, dbl Angle );
#endif
#endif
/**/
