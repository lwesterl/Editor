/**
  *   @file PixmapItem.cpp
  *   @author Lauri Westerholm
  *   @brief Contains PixmapItem class
  */




#include "../include/PixmapItem.hpp"


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


// THIS IS NOT A PART OF THE CLASS
// Return a valid point within the coordinate boundaries
int check_values(int val, int min_val, int max_val)
{
  if (val < min_val) return 0;
  else if (val > max_val) return max_val;
  return val;
}
