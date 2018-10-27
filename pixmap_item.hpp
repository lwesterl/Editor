#ifndef Pixmap_item
#define Pixmap_item

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

unsigned chek_values(unsigned val, unsigned min_val, unsigned max_val);

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
    void addPainterPoint(unsigned x, unsigned y);
    void clearPointsVector();
    void CutItem();
    void RemoveLatestPoint();

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


#endif
