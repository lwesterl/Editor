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
 #include <vector>
 #include <QPixmap>
 #include <QString>
 #include <QGraphicsPixmapItem>
 #include "line_item.hpp"
 #include "pixmap_item.hpp"

 #define no_img_cut 0
 #define polygon_img_cut 1
 #define path_img_cut 2


 struct Image_Active
 {
   //bool image_mode = false; // user has activated image mode
   bool added_scene = false; // is image added to scene
   PixmapItem *pixmap_item; // points to the current item which is moved
   unsigned char clicks = 0;
 };

 struct Image_Cut
 {
   PixmapItem *pixmap_item;
   bool initialized = false;
   unsigned char cut_mode = no_img_cut; // stores the cut mode
   QPoint point; // tells which image should be cutted
   // These are used to visualize the cutting pattern and just temporarily added to the scene
   std::vector<LineItem*> visual_items;
   LineItem *current_item;
   unsigned prev_x;
   unsigned prev_y;
   bool visual_created = false;

 };

 struct Line_Mode
 {
   LineItem *line_item; // the item which is curretly moved
   bool positioned = false;
   bool created = false; // whether element already created
   unsigned prev_x;
   unsigned prev_y;
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
   LineItem *addLine(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
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
   bool SelectCutImg();
   void SetImgCutMode(int cut_mode);
   void CutPixmapItem();
   void RemovePolyPrevious();
   void setConnectLines(int value);
   void ClearVisualItems();

 private:
   std::list <LineItem*> line_items;
   std::list <PixmapItem*> pixmap_items;
   unsigned mouse_x;
   unsigned mouse_y;
   bool first_line = true;
   bool connect_lines = true; // This controls whether first_line is reset
   struct Line_Mode line_struct;
   unsigned char mode = line_mode_value;
   //bool line_mode = true;
   //bool delete_mode = false;
   struct Image_Active image_active;
   QPixmap image = QPixmap(); // construct a Null pixmap
   //bool delete_img_mode = false;
   QString current_imagename;
   //bool cut_image_mode = false;
   struct Image_Cut image_cut;
 };


 #endif
