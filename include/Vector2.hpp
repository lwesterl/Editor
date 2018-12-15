/**
  *   @file Vector2.hpp
  *   @author Lauri Westerholm
  *   @brief Header for Vector2 class
  */


#pragma once


/*    INCLUDES    */

#include <iostream>



/**
  *   @class Vector2
  *   @brief Class for a basic 2D vector
  *   @details Used to create Bezier objects
  */

class Vector2
{

public:

  /**
    *   @brief Constructor for Vector2
    *   @param x x coordinate
    *   @param y y coordinate
    */
  Vector2(float x, float y): x(x), y(y) {}

  /**
    *   @brief Empty constructor for Vector
    */
  Vector2(): x(0), y(0) {}

  /**
    *   @brief Multiplication overload
    *   @param mult Multiplier for vector
    *   @return Returns multiplied vector as reference
    */
  Vector2& operator * (float mult);

  /**
    *   @brief Friend addition definition
    *   @param vec1 Base vector
    *   @param mult Value to be added
    *   @return Returns new Vector2 which is multiplication of inputs
    *   @remark Notice the parameters
    */
  friend Vector2 operator+ (const Vector2 &vec1, float mult);

  /**
    *   @brief Friend multiplication definition
    *   @param vec1 Base vector
    *   @param mult Multiplier
    *   @return Returns new Vector2 which is multiplication of inputs
    */
  friend Vector2 operator* (float mult, const Vector2 &vec1);

  /**
    *   @brief Friend addition definition
    *   @param vec1 Base vector 1
    *   @param vec2 Base vector 2
    *   @remark Notice the parameters
    *   @return Returns a new Vector2 which is addition of the two vectors
    */
  friend Vector2 operator+ (const Vector2 &vec1, const Vector2 &vec2);


  /**
    *   @brief Get x coordinate
    *   @return Returns Vector2 x
    */
  float getX () const {return x;}

  /**
    *   @brief Get y coordinate
    *   @return Returns Vector2 y
    */
  float getY () const {return y;}

private:
  float x;
  float y;

};


/**
  *   @brief Print overload for Vector2
  *   @param os Output stream
  *   @param vector2 Vector2 object to be printed
  *   @return Returns the updated stream
  */

std::ostream& operator <<(std::ostream &os, Vector2 &vector2);
