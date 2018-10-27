#include "pixmap_item.hpp"


// Constructor
// Assign correct width and heigth values based on the pixmap

PixmapItem::PixmapItem(QPixmap pixmap, QString image_name) :
 QGraphicsPixmapItem(pixmap), imagename(image_name)
{
  width = pixmap.width();
  height = pixmap.height();

  pixmap_ = pixmap;


  QPainter painter(&pixmap_);
  painter.setCompositionMode(QPainter::CompositionMode_Clear);

  // just for testing
  static const QPointF points[4] = {
    QPointF(0, 0),
    QPointF(50, 50),
    QPointF(70, 30.0),
    QPointF(80.0, 0.0)
  };


  QPainterPath path;

  path.moveTo (points[0]);

  path.lineTo (points[1]);

  path.lineTo (points[2]);
  path.lineTo (points[3]);

  painter.setPen (Qt::NoPen);
  // Composition mode clear so color has no effect
  painter.fillPath (path, QBrush (QColor ("white")));
  // just for testing
  this->setPixmap(pixmap_);
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
  // Map points to inside item
  unsigned x_new = x - x1;
  unsigned y_new = y - y1;

  x_new = chek_values(x_new, 0, width);
  y_new = chek_values(y_new, 0, height);

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

unsigned chek_values(unsigned val, unsigned min_val, unsigned max_val)
{
  if (val < min_val) return 0;
  else if (val > max_val) return max_val;
  return val;
}
