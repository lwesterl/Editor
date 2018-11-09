/**
  *   @file bezier.cpp
  *   @author Lauri Westerholm
  *   @brief Contains Bezier class related functions
  */

#include "../include/bezier.hpp"


/**
  *   @brief Lerp function
  *   @details Calculates linear vector interpolation
  */
Vector2 Lerp(Vector2 a, Vector2 b, float t)
{
  return (1.0 - t) * a + t * b;
}


/**
  *   @brief Creates a bezier curve
  *   @details This function only calculates a part of the bezier curve and
  *   returns a Vector2 mathing the part of the curve
  *   @param p0 Vector2 1
  *   @param p1 Vector2 2
  *   @param p2 Vector2 3
  *   @param p3 Vector2 4
  *   @return Returns Vector2 matching a part of the curve
  */

Vector2 createBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t)
{
  float u = 1.00 - t;
  float t2 = t * t;
  float u2 = u * u;
  float u3 = u2 * u;
  float t3 = t2 * t;

  Vector2 result = u3 * p0 + (3.00 * u2 * t) + p1 + (3.00 * u * t2) * p2 +
                  t3 * p3;

  return result;
}


/*  Bezier constructor */

Bezier::Bezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
{
  for (float t = 0; t < 1; t += BECIER_INTERVAL)
  {
    Vector2 vect2 = createBezier(p0, p1, p2, p3, t);
    vectors.push_back(vect2);
  }
}
