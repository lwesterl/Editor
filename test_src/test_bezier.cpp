/**
  *   @file test_bezier.cpp
  *   @author Lauri Westerholm
  *   @brief Contains Bezier class related functions
  *   @remark Not intended to be used directly with Editor
  */

#include "test_bezier.hpp"


/**
  *   @brief Lerp function
  *   @details Calculates linear vector interpolation
  */
Vector2 Lerp(Vector2 a, Vector2 b, double t)
{
  return (1.0 - t) * a + t * b;
}

/*  Create a part of bezier curve */

Vector2 createBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, double t)
{
  double u = 1.00 - t;
  double t2 = t * t;
  double u2 = u * u;
  double u3 = u2 * u;
  double t3 = t2 * t;
  //std::cout << "u3 : " << u3 << std::endl;

  Vector2 result = u3 * p0 + (3.00 * u2 * t) * p1 + (3.00 * u * t2) * p2 +
                  t3 * p3;

  return result;
}


/*  Bezier constructor */

Bezier::Bezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
{
  for (double t = 0; t <= 1; t += BECIER_INTERVAL)
  {
    Vector2 vect2 = createBezier(p0, p1, p2, p3, t);
    vectors.push_back(vect2);
  }
}
