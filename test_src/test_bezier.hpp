/**
  *   @file test_bezier.hpp
  *   @author Lauri Westerholm
  *   @brief Test header for Bezier class
  *   @remark This is not intended to be directly used with Editor
  */



#ifndef TEST_BEZIER_HEADER
#define TEST_BEZIER_HEADER

/*    INCLUDES    */

#include <vector>
#include <iostream>
#include <list>
#include "../include/vector2.hpp"

/*    MACROS    */

/**
  *   @brief Macro which tells how often bezier points are calculated
  */

#define BECIER_INTERVAL 0.05

/**
  *   @class Bezier
  *   @@brief Creates bezier curves
  *   @details Used in Editor to draw bezier curves
  */

class Bezier
{
public:

  /**
    *   @brief Constructor for Bezier
    *   @param p0 Vector2 first point
    *   @param p1 Vector2 second point
    *   @param p2 Vector2 third point
    *   @param p3 Vector2 fourth point
    *   @details Calculates parts of the curve using createBezier
    *    and then adds those to the vector
    */
  Bezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3);

  /**
    *   @brief Get vector matching bezier
    *   @return Returns reference to the vector object containing Vector2 2D-vectors
    */
  std::vector<Vector2> &getVectors() {return vectors;}
private:
  std::vector <Vector2> vectors;
};

/*    EXTERNAL FUNCTIONS    */

/**
  *   @brief Creates a bezier curve
  *   @details This function only calculates a part of the bezier curve and
  *   returns a Vector2 mathing the part of the curve
  *   @param p0 Vector2 1
  *   @param p1 Vector2 2
  *   @param p2 Vector2 3
  *   @param p3 Vector2 4
  *   @param t [0 1] bezier parameter
  *   @return Returns Vector2 matching a part of the curve
  */
Vector2 createBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t);

/**
  *   @brief Lerp function
  *   @details Calculates linear vector interpolation
  */
Vector2 Lerp(Vector2 a, Vector2 b, float t);


#endif
