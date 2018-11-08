/**
  *   @file line_item.hpp
  *   @author Lauri Westerholm
  *   @brief Contains header for LineItem class
  */


#ifndef LINE_ITEM_HEADER
#define LINE_ITEM_HEADER

/*    INCLUDES    */

#include <QGraphicsLineItem>


/**
  *   @class LineItem
  *   @brief Own implementation of QGraphicsLineItem
  *   @details Adds coordinate positions variables to QGraphicsLineItem
  */

class LineItem : public QGraphicsLineItem
{
  public:

  /**
    *   @brief Constructor for LineItem
    *   @param x1 Start x coordinate
    *   @param y1 Start y coordinate
    *   @param x2 End x coordinate
    *   @param y2 End y coordinate
    */
    LineItem(unsigned x1, unsigned y1, unsigned x2, unsigned y2):QGraphicsLineItem(x1, y1, x2, y2),
    x1(x1), x2(x2), y1(y1), y2(y2) {}

  /**
    *   @brief Get start x coordinate
    *   @return Returns x1
    */
    unsigned getX1() {return x1;}

    /**
      *   @brief Get end x coordinate
      *   @return Returns x2
      */
    unsigned getX2() {return x2;}

    /**
      *   @brief Get start y coordinate
      *   @return Returns y1
      */
    unsigned getY1() {return y1;}

    /**
      *   @brief Get end y coordinate
      *   @return Returns y2
      */
    unsigned getY2() {return y2;}

    /**
      *   @brief Update end x and y coordinates
      *   @param x_new New end x coordinate
      *   @param y_new New end y coordinate
      */
    void updatePosition(unsigned x_new, unsigned y_new)
    {
      x2 = x_new;
      y2 = y_new;
    }
  private:
    unsigned x1;
    unsigned x2;
    unsigned y1;
    unsigned y2;
};

#endif
