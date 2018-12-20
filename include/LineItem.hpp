/**
  *   @file LineItem.hpp
  *   @author Lauri Westerholm
  *   @brief Contains header for LineItem class
  */


#pragma once

/*    INCLUDES    */

#include <QGraphicsLineItem>
#include <QDebug>
#include <cmath>


/**
  *   @class LineItem
  *   @brief Own implementation of QGraphicsLineItem
  *   @details Adds coordinate positions variables to QGraphicsLineItem
  */

class LineItem : public QGraphicsLineItem
{
  public:

    static const int CompensationValue; /**< Value used to compensate clicking the item to make it easier */

  /**
    *   @brief Constructor for LineItem
    *   @param x1 Start x coordinate
    *   @param y1 Start y coordinate
    *   @param x2 End x coordinate
    *   @param y2 End y coordinate
    */
    LineItem(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
  /**
    *   @brief Get start x coordinate
    *   @return Returns x1
    */
    unsigned getX1();

    /**
      *   @brief Get end x coordinate
      *   @return Returns x2
      */
    unsigned getX2();

    /**
      *   @brief Get start y coordinate
      *   @return Returns y1
      */
    unsigned getY1();

    /**
      *   @brief Get end y coordinate
      *   @return Returns y2
      */
    unsigned getY2();

    /**
      *   @brief Update end x and y coordinates
      *   @param x_new New end x coordinate
      *   @param y_new New end y coordinate
      */
    void updatePosition(unsigned x_new, unsigned y_new);

    /**
      *   @brief Check if coordinate is inside the item
      *   @param x x coordinate
      *   @param y y coordinate
      *   @return Returns true if the coordinate is inside the item
      */
    bool isInside(unsigned x, unsigned y);

    /**
      *   @brief Calculate angle
      *   @remark Angle is between world x-axis and item x-axis
      */
    void calculateAngle();

  private:
    unsigned x1;
    unsigned x2;
    unsigned y1;
    unsigned y2;
    float angle; /**< angle between world x-axis and item x-axis */
};
