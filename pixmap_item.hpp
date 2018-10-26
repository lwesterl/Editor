#ifndef Pixmap_item
#define Pixmap_item

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <QRegion>
#include <QPolygon>
#include <QVector>
#include <QString>
#include <QImage>
#include <QBitmap>
#include <QColor>
#include <QPainterPath>
#include <QBrush>


// This class inherits QGraphicsPixmapItem
// Adds a position specifiers to the upper class

class PixmapItem: public QGraphicsPixmapItem
{
  public:

    PixmapItem(QPixmap pixmap, QString image_name);
    bool isXinside(unsigned x);
    bool isYinside(unsigned y);
    void setX(unsigned x);
    void setY(unsigned y);

  private:
    QPixmap pixmap_;
    //QPainter painter;

    // Item width and height
    unsigned width;
    unsigned height;
    // upper left corner coordinates
    unsigned x1;
    unsigned y1;
    QString imagename;




};


#endif
