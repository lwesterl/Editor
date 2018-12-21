/**
  *   @file PixmapItem.cpp
  *   @author Lauri Westerholm
  *   @brief Contains PixmapItem class
  */




#include "../include/PixmapItem.hpp"


ConnectPoint PixmapItem::connect_point = ConnectPoint::ConnectZero;


// Constructor
// Assign correct width and heigth values based on the pixmap

PixmapItem::PixmapItem(QPixmap pixmap, QString image_name) :
 QGraphicsPixmapItem(pixmap), imagename(image_name)
{
  width = pixmap.width();
  height = pixmap.height();

  pixmap_ = pixmap;

}


// Cut the object according to painter_points content
// Cutting is done by QPainterPath and fillPath

void PixmapItem::CutItem()
{
  // Check that the vector isn't empty
  if (!painter_points.empty())
  {
    // Create a new QPainter from the pixmap
    QPainter painter(&pixmap_);
    // This make painting alpha (i.e. clears original pixels)
    painter.setCompositionMode(QPainter::CompositionMode_Clear);

    // Create a path by the vector points
    QPainterPath path;
    auto it = painter_points.begin();
    // first, move to the starting point
    path.moveTo(*it);
    it ++;
    for (; it != painter_points.end(); it++)
    {
      path.lineTo(*it);
    }
    // finally connect the last and the first point
    path.moveTo(painter_points[0]); // vector shouldn't be empty

    painter.setPen (Qt::NoPen);
    // Composition mode clear so color has no effect
    painter.fillPath (path, QBrush (QColor ("white")));
    // Swap pixmap
    this->setPixmap(pixmap_);
  }

}


// Check if x is inside the item
// return result as bool
bool PixmapItem::isXinside(unsigned x)
{
  if ((x >= x1) && (x <= (x1 + width)))
  {
    return true;
  }
  return false;
}


// Check if y is inside the item
// return result as bool
bool PixmapItem::isYinside(unsigned y)
{
  if ((y >= y1) && (y <= (y1 + height)))
  {
    return true;
  }
  return false;
}

void PixmapItem::setX(unsigned x)
{
  x1 = x;
}

void PixmapItem::setY(unsigned y)
{
  y1 = y;
}

// Adds a point to painter_points
// called when user is in the cut_image_mode

void PixmapItem::addPainterPoint(unsigned x, unsigned y)
{
  // Map points to inside the item
  int x_new = (int) x - (int) x1;
  int y_new = (int) y - (int) y1;
  x_new = check_values(x_new, 0, width);
  y_new = check_values(y_new, 0, height);

  // Add points to the vector
  painter_points.push_back(QPoint(x_new, y_new));

}

// Clears the painter_points vector
void PixmapItem::clearPointsVector()
{
  for (auto it = painter_points.begin(); it !=painter_points.end(); )
  {
    it = painter_points.erase(it);
  }
}


// Tries to remove the latest entry from the points vector
void PixmapItem::RemoveLatestPoint()
{
  // Check the vector isn't empty
  if (!painter_points.empty())
  {
    painter_points.pop_back();
  }
}

/*  Cut Pixmap based on LineItem */
void PixmapItem::LineCut()
{
  if (painter_points.size() == 2)
  {
    int x_min = painter_points[0].x();
    int x_max = painter_points[1].x();
    int y_min = painter_points[0].y();
    if (connect_point == ConnectPoint::ConnectHeight)
    {
      // connect lines from lower edges to the LineItem points
      painter_points.push_back(QPoint(x_max, height));
      painter_points.push_back(QPoint(x_min, height));
      painter_points.push_back(QPoint(x_min, y_min));
      CutItem();
    }
    else
    {
      // connect lines from upper edges to the LineItem points
      painter_points.push_back(QPoint(x_max, 0));
      painter_points.push_back(QPoint(x_min, 0));
      painter_points.push_back(QPoint(x_min, y_min));
      CutItem();
    }
  }
  clearPointsVector();
}

/*  Cut Pixmap based on a Bezier and its LineItems */
void PixmapItem::BezierCut()
{
  if (painter_points.size() > 1)
  {
    int x_start = painter_points.front().x();
    int x_end = painter_points.back().x();
    int y_start = painter_points.back().y();
    if (connect_point == ConnectPoint::ConnectHeight)
    {
      // connect lines from the points using lower edges
      painter_points.push_back(QPoint(x_end, height));
      painter_points.push_back(QPoint(x_start, height));
      painter_points.push_back(QPoint(x_start, y_start));
    }
    else
    {
      // connect lines from the points using upper edges
      painter_points.push_back(QPoint(x_end, 0));
      painter_points.push_back(QPoint(x_start, 0));
      painter_points.push_back(QPoint(x_start, y_start));
    }

    CutItem();
  }
  clearPointsVector();
}


// THIS IS NOT A PART OF THE CLASS
// Return a valid point within the coordinate boundaries
int check_values(int val, int min_val, int max_val)
{
  if (val < min_val) return 0;
  else if (val > max_val) return max_val;
  return val;
}
