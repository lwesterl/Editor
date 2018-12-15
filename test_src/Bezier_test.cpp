/**
  *   @file Bezier_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains a test main for Bezier class
  */


#include "Test_bezier.hpp"


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

  std::cout << "_______________Same vectors test_______________" << std::endl;
  Vector2 test_vec = Lerp(Vector2(100,100), Vector2(100,100), 0.1);
  std::cout << "Lerp result (should be 100, 100): " << test_vec.getX() << ", " << test_vec.getY() << std::endl;
  Bezier bez = Bezier(test_vec, test_vec, test_vec, test_vec);
  auto vec = bez.getVectors();
  for (auto it = vec.begin(); it != vec.end(); it++)
  {
    std::cout << *it;
  }

  return 0;
}
