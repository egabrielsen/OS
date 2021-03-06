#include <assert.h>
#include <stdio.h>
#include "point.h"
#include <math.h>

/*
 * Update *p by increasing p->x by x and 
 * p->y by y
 */
void point_translate(Point *p, double x, double y)
{
  p->x += x;
  p->y += y;
}

/*
 * Return the distance from p1 to p2
 */
double point_distance(const Point *p1, const Point *p2)
{
  int x = p2->x - p1->x;
  int y = p2->y - p1->y;
  return sqrt(x*x + y*y);
}
