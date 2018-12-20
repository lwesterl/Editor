/**
  *   @file PixmapItem.hpp
  *   @author Lauri Westerholm
  *   @brief Header for PixmapItem class
  */


#pragma once

/*    INCLUDES    */

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <QRegion>
#include <QPolygon>
#include <QString>
#include <QImage>
#include <QColor>
#include <QPainterPath>
#include <QBrush>
#include <vector>
#include <QDebug>



/**
  *   @brief Map value to limits
  *   @param val Value to be mapped
  *   @param min_val Minimum value, the lower limit
  *   @param max_val Maximum value, the upper limit
  *   @return Mapped value
  *   @details If val within the limits, return val. If val < min_val, return
  *   min_val. If val > max_val, return max_val
  *   @remark Function is not a part of the class but it's called from the class
  */

int check_values(int val, int min_val, int max_val);




/**
  *   @class PixmapItem
  *   @brief Own QGraphicsPixmapItem implementation
  *   @details This class inherits QGraphicsPixmapItem
  *   Adds a position specifiers to the base class
  */

class PixmapItem: public QGraphicsPixmapItem
{
  public:

    /**
      *   @brief Constructor for PixmapItem
      *   @param pixmap Pixmap which the item is created from
      *   @param image_name Name(path) of the image used in Pixmap
      */
    PixmapItem(QPixmap pixmap, QString image_name);

    /**
      *   @brief Is x coordinate inside the item
      *   @param x x coordinate
      *   @return Returns true if x is inside the item
      */
    bool isXinside(unsigned x);

    /**
      *   @brief Is y coordinate inside the item
      *   @param y y coordinate
      *   @return Returns true if y is inside the item
      */
    bool isYinside(unsigned y);

    /**
      *   @brief Set new x coordinate
      *   @param x New x coordinate
      */
    void setX(unsigned x);

    /**
      *   @brief Set new y coordinate
      *   @param y New y coordinate
      */
    void setY(unsigned y);

    /**
      *   @brief Add QPoint to painter_points
      *   @param x x coordinate of the point
      *   @param y y coordinate of the point
      *   @details The painter point is used in cut image mode to create a
      *   polygon cut
      */
    void addPainterPoint(unsigned x, unsigned y);

    /**
      *   @brief Clear all QPoints of the item
      *   @details Points are cleared from painter_points vector
      */
    void clearPointsVector();

    /**
      *   @brief Cut the item
      *   @details Cut path is defined by QPainterPath which is created from
      *   QPoints in painter_points
      */
    void CutItem();

    /**
      *   @brief Remove the latest point added
      *   @details Removes the latest entry from painter_points vector
      */
    void RemoveLatestPoint();

    /**
      *   @brief Cut item based on a LineItem
      *   @details Connects lines from lower edges of the pixmap to the LineItem points
      */
    void LineCut();

    /**
      *   @brief Cut item based on a Bezier (its LineItems)
      *   @details Connects lines from the last painter_point to the first using
      *   lower edge as a connection point
      */
    void BezierCut();

  private:
    QPixmap pixmap_;
    std::vector<QPoint> painter_points;

    // Item width and height
    unsigned width;
    unsigned height;
    // upper left corner coordinates
    unsigned x1;
    unsigned y1;
    QString imagename; // not used at the moment

};
