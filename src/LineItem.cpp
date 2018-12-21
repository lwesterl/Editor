/**
  *   @file LineItem.cpp
  *   @brief Source code for LineItem class
  */

#include "../include/LineItem.hpp"

/*  Class LineItem */

const int LineItem::CompensationValue = 10;
QColor LineItem::LineColor = Qt::black;

LineItem::LineItem(unsigned x1, unsigned y1, unsigned x2, unsigned y2): QGraphicsLineItem(x1, y1, x2, y2),
x1(x1), x2(x2), y1(y1), y2(y2)
{
  // calculate angle between world x-axis and item x-axis (use arctan)
  calculateAngle();
  // set QPen for item which has the correct color
  setPen(QPen(LineColor));
}

unsigned LineItem::getX1()
{
  return x1;
}

unsigned LineItem::getX2()
{
  return x2;
}

unsigned LineItem::getY1()
{
  return y1;
}

unsigned LineItem::getY2()
{
  return y2;
}

void LineItem::updatePosition(unsigned x_new, unsigned y_new)
{
  x2 = x_new;
  y2 = y_new;
  // update angle between world x-axis and item x-axis (use arctan)
  calculateAngle();
}

bool LineItem::isInside(unsigned x, unsigned y)
{
  if (x2 >= x1)
  {
    if ( (static_cast<int>(x1 - CompensationValue / 2) <= static_cast<int>(x)) &&
          (static_cast<int>(x) <= static_cast<int>(x2 + CompensationValue /2)) )
    {
      // x is inside the item, check y using tan function and angle
      float y_corr;
      if (y2 > y1)
      {
        // line goes downwards
        y_corr = std::tan(angle) * static_cast<float>(x - x1) + static_cast<float> (y1);
      }
      else
      {
        // line goes upwards
        y_corr = - std::tan(angle) * static_cast<float>(x - x1) + static_cast<float> (y1);
      }
      if ( (static_cast<int>(y) > static_cast<int>(y_corr - CompensationValue)) &&
          (static_cast<int>(y) < static_cast<int>(y_corr + CompensationValue)) )
          {
            // coordinate is inside item (if compensation is taken into account)
            return true;
          }
    }
  }
  else
  {
    if ( (static_cast<int>(x2 - CompensationValue / 2) <= static_cast<int>(x)) &&
          (static_cast<int>(x) <= static_cast<int>(x1 + CompensationValue /2)) )
    {
      // x is inside the item, check y using tan function and angle
      float y_corr;
      if (y2 > y1)
      {
        // line goes upwards (but starts from x2)
        y_corr = - std::tan(angle) * static_cast<float>(x - x2) + static_cast<float> (y2);
      }
      else
      {
        // line goes downwards (starts from x2). Now angle has to be changed to the adjacent angle
        y_corr = - std::tan(M_PI - angle) * static_cast<float>(x1 - x) + static_cast<float> (y1);
      }
      if ( (static_cast<int>(y) > static_cast<int>(y_corr - CompensationValue)) &&
          (static_cast<int>(y) < static_cast<int>(y_corr + CompensationValue)) )
          {
            // coordinate is inside item (if compensation is taken into account)
            return true;
          }

    }
  }

  return false;
}

void LineItem::calculateAngle()
{
  if (y2 > y1 && x2 >= x1)
  {
    angle = std::atan(static_cast<float>(y2 - y1) / static_cast<float>(x2 - x1));
  }
  else if (y2 <= y1 && x2 >= x1)
  {
    angle = std::atan(static_cast<float>(y1 - y2) / static_cast<float>(x2 - x1));
  }
  else if (y2 > y1 && x2 < x1)
  {
    angle = std::atan(static_cast<float>(y2 - y1) / static_cast<float>(x1 - x2));
  }
  else
  {
    angle = M_PI - std::atan(static_cast<float>(y1 - y2) / static_cast<float>(x1 - x2));
  }
}
