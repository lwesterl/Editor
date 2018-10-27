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
 #include <QGraphicsPixmapItem>
 #include "line_item.hpp"
 #include "pixmap_item.hpp"


 struct Image_Active
 {
   //bool image_mode = false; // user has activated image mode
   bool added_scene = false; // is image added to scene
   PixmapItem *pixmap_item; // points to the current item which is moved
   unsigned char clicks = 0;
 };

 // Different modes
 #define view_mode_value 0
 #define line_mode_value 1
 #define delete_mode_value 2
 #define image_mode_value 3
 #define delete_img_mode_value 4
 #define cut_image_mode_value 5

 class OwnGraphicsScene : public QGraphicsScene
 {
 public:
   OwnGraphicsScene(QWidget *parent):QGraphicsScene(parent) {setSceneRect(0, 0, 10000, 10000);}
   ~OwnGraphicsScene();
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   void addLine(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
   unsigned getMouseX() {return mouse_x;}
   unsigned getMouseY() {return mouse_y;}
   void LineMode(bool activate);
   void DeleteMode(bool activate);
   void ClearMode();
   void remove_Item(unsigned x, unsigned y);
   void ClearAll();
   bool setImage(QString imagename);
   bool imgMode(bool activate);
   void DeleteImgMode(bool activate);
   void DeleteImg(unsigned x1, unsigned y1);
   void CutImageMode(bool active);

 private:
   std::list <LineItem*> line_items;
   std::list <PixmapItem*> pixmap_items;
   unsigned mouse_x;
   unsigned mouse_y;
   bool first_line = true;
   unsigned char mode = line_mode_value;
   //bool line_mode = true;
   //bool delete_mode = false;
   struct Image_Active image_active;
   QPixmap image = QPixmap(); // construct a Null pixmap
   //bool delete_img_mode = false;
   QString current_imagename;
   //bool cut_image_mode = false;
 };


 #endif
