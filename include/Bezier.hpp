/**
  *   @file Bezier.hpp
  *   @author Lauri Westerholm
  *   @brief Header for Bezier class
  */



#pragma once

/*    INCLUDES    */

#include <vector>
#include <iostream>
#include <list>
#include <QDebug>
#include "LineItem.hpp"
#include "Vector2.hpp"

/*    MACROS    */

/**
  *   @brief Macro which tells how often bezier points are calculated
  */

#define BECIER_INTERVAL 0.01

/**
  *   @class Bezier
  *   @brief Creates bezier curves
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
    *   @brief Deconstructor
    *   @details deletes line_items
    */
  ~Bezier();

  /**
    *   @brief Get vector matching bezier
    *   @return Returns reference to the vector object containing Vector2 2D-vectors
    */
  std::vector<Vector2> &getVectors() {return vectors;}

  /**
    *   @brief Get LineItem vector matching the object
    */
  std::vector <LineItem*> getLineItems() {return line_items;}

  /**
    *   @brief Get Bezier end x coordinate
    *   @return Returns the last x coordinate from vectors
    */
  float getEndX();

  /**
    *   @brief Get Bezier end y coordinate
    *   @return Returns the last y coordinate from vectors
    */
  float getEndY();

  /**
    *   @brief Get Bezier start x coordinate
    *   @return Returns the first x coordinate from vectors
    */
  float getStartX();

  /**
    *   @brief Get Bezier start y coordinate
    *   @return Returns the first y coordinate from vectors
    */
  float getStartY();

  /**
    *   @brief Check whether position is inside bezier or not
    *   @param x x coordinate
    *   @param y y coordinate
    *   @return Returns true if position is inside
    *   @remark This is relatively heavy method
    */
  bool isInside(unsigned x, unsigned y);

private:
  std::vector <Vector2> vectors;
  std::vector <LineItem*> line_items;
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
