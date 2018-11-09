/**
  *   @file vector2.cpp
  *   @author Lauri Westerholm
  *   @brief Contains Vector2 class
  */



#include "../include/vector2.hpp"

/*  Multiplication overload */
Vector2& Vector2::operator * (float mult)
{
  x *= mult;
  y *= mult;
  return *this;
}


/**
  *   @brief Print overload for Vector2
  *   @param os Output stream
  *   @param vector2 Vector2 object to be printed
  *   @return Returns the updated stream
  */

std::ostream& operator <<(std::ostream &os, Vector2 &vector2)
{
  os << "X :" << vector2.getX() << std::endl << "Y :" << vector2.getY() << std::endl;
  return os;
}

/*  Addition overload  */
Vector2 operator+ (const Vector2 &vec1, const Vector2 &vec2)
{
  float x_new = vec1.getX() + vec2.getX();
  float y_new = vec1.getY() + vec2.getY();
  return Vector2(x_new, y_new);
}

/*  Another addition overload */
Vector2 operator+ (const Vector2 &vec1, float mult)
{
  float x_new = vec1.getX() * mult;
  float y_new = vec1.getY() * mult;
  return Vector2(x_new, y_new);
}

/*  Multiplication overload */
Vector2 operator* (float mult, const Vector2 &vec1)
{
  float x_new = vec1.getX() * mult;
  float y_new = vec1.getY() * mult;
  return Vector2(x_new, y_new);
}
