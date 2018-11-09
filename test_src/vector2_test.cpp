/**
  *   @file vector2_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains a test main for Vector2 class
  */

#include "../include/vector2.hpp"


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
  return 0;
}
