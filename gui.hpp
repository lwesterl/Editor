#ifndef Gui_header
#define Gui_header



#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBoxLayout>
#include <QPoint>
#include <QPushButton>
#include <QImage>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QStringList>
#include "owngraphicsscene.hpp"
#include "mainwidget.hpp"

// Source images
#define exit_img "img_src/exit.png"
#define open_img "img_src/open.png"
#define save_img "img_src/save.png"
#define draw_line_img "img_src/draw_line.png"
#define delete_line_img "img_src/delete_line.png"
#define clear_points_img "img_src/clear_points.png"
#define clear_all_img "img_src/clear_all.png"
#define image_sketch_img "img_src/image_sketch.png"




// Graphical user interface
// inherits GMainWindow

class GUI: public QMainWindow
{
public:
  GUI(QWidget *parent = 0);
  ~GUI() {delete mainWidget;}
  void LineMode();
  void DeleteMode();
  void ClearMode();
  void ClearAll();
  void saveImage();
  void openImage();
  void ImgMode();

  //void mouseMoveEvent(QMouseEvent *event);
  //void mousePressEvent(QMouseEvent *event);
  //int getMouseX(){return mouse_x;}
  //int getMouseY(){return mouse_y;}
  //void addLine(int x1, int y1, int x2, int y2);

private:
  //unsigned mouse_x = 0;
  //unsigned mouse_y = 200;
  //QGraphicsScene *scene;
  //QGraphicsView *view;
  //QHBoxLayout *h_layout;
  MainWidget *mainWidget;
  QAction *line_mode;
  QAction *delete_mode;
  QAction *clear_mode;
  QAction *clear_all_mode;
  QAction *add_img_mode;


};


#endif
