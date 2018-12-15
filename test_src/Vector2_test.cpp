/**
  *   @file Vector2_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains a test main for Vector2 class
  */

#include "../include/Vector2.hpp"


/**
  *   @brief Test main for Vector2 class
  */

int main()
{

  Vector2 vect1 = Vector2();

  std::cout << vect1;
  Vector2 vect2 = Vector2(2.656, 5.00);
  std::cout << vect2;
  float mult = 3.9;
  vect2 * mult;
  std::cout << "Multiplication test by "<< mult << std::endl;
  std::cout << vect2;

  std::cout << "Addition test " << std::endl;
  Vector2 vect3 = Vector2(2,4.5);
  std::cout << vect3 ;
  std::cout << "+" << std::endl;
  std::cout << vect2;
  std::cout <<"=="<<std::endl;
  Vector2 vect4 = vect3 + vect2;
  std::cout << vect4;

  Vector2 p0 = Vector2(100.5455,100.5531);
  double t = 0;
  double u = 1.00 - t;
  double t2 = t * t;
  double u2 = u * u;
  double u3 = u2 * u;
  double t3 = t2 * t;
  Vector2 result = u3 * p0 + (3.00 * u2 * t) * p0 + (3.00 * u * t2) * p0 +
                  t3 * p0;
  std::cout << "_______TESTING_______" << std::endl;
  std::cout << result << std::endl;
  return 0;
}
