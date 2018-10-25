#ifndef Line_Item
#define Line_Item

#include <QGraphicsLineItem>


class LineItem : public QGraphicsLineItem
{
  public:
    LineItem(unsigned x1, unsigned y1, unsigned x2, unsigned y2):QGraphicsLineItem(x1, y1, x2, y2),
    x1(x1), x2(x2), y1(y1), y2(y2) {}
    unsigned getX1() {return x1;}
    unsigned getX2() {return x2;}
    unsigned getY1() {return y1;}
    unsigned getY2() {return y2;}
  private:
    unsigned x1;
    unsigned x2;
    unsigned y1;
    unsigned y2;
};

#endif
