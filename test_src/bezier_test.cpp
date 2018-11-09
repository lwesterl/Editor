/**
  *   @file bezier_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains a test main for Bezier class
  */


#include "../include/bezier.hpp"


/**
  *   @brief Test main for Bezier class
  */

int main ()
{
  Vector2 vect1 = Vector2(3.455,889.9);
  Vector2 vect2 = Vector2(324, 4.9);
  Vector2 vect3 = Lerp(vect1,vect2,0.5);
  std::cout << vect3;

  Vector2 vect_zero = Vector2();
  std::list <Vector2> vectors;
  for (float t = 0; t < 1; t+=0.05)
  {
    Vector2 result = createBezier(vect_zero, vect1, vect2, vect3, t);
    vectors.push_back(result);
  }
  std::cout << "Vectors :" << std::endl;
  for (std::list<Vector2>::iterator it = vectors.begin(); it != vectors.end(); it++)
  {
    std::cout << *it;
  }
  std::cout << "_______________Bezier object test__________ " << std::endl;
  Bezier bezier = Bezier(vect_zero, vect1, vect2, vect3);
  auto vects = bezier.getVectors();
  for (auto it = vects.begin(); it != vects.end(); it++)
  {
    std::cout << *it;
  }

  return 0;
}
