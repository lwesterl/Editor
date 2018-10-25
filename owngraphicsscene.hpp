#ifndef OWN_SCENE
#define OWN_SCENE

/*
 *    This is an Implementation for own QGraphicsScene which
 *    overloads mousePressEvent
 */

 #include <QGraphicsSceneMouseEvent>
 #include <QDebug>
 #include <QGraphicsScene>
 #include <QGraphicsItem>
 #include <QPoint>
 #include <QWidget>
 #include <QList>
 #include <list>
 #include <QPixmap>
 #include <QString>
 #include "line_item.hpp"


 class OwnGraphicsScene : public QGraphicsScene
 {
 public:
   OwnGraphicsScene(QWidget *parent):QGraphicsScene(parent) {setSceneRect(0, 0, 10000, 10000);}
   ~OwnGraphicsScene();
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void addLine(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
   unsigned getMouseX() {return mouse_x;}
   unsigned getMouseY() {return mouse_y;}
   void LineMode(bool activate);
   void DeleteMode(bool activate);
   void ClearMode();
   void remove_Item(unsigned x, unsigned y);
   void ClearAll();
   bool setImage(QString imagename);
 private:
   std::list <LineItem*> line_items;
   unsigned mouse_x;
   unsigned mouse_y;
   bool first_line = true;
   bool line_mode = true;
   bool delete_mode = false;
   QPixmap image;
 };


 #endif
