#ifndef Main_widget
#define Main_widget

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QScrollBar>
#include "owngraphicsscene.hpp"


/*
 *    This class is the main widget for gui
 *    contains a Graphics scene and a view for it
 *    Uses QHBoxLayout
 */

class MainWidget: public QWidget
{
public:
  MainWidget(QWidget *parent);
  ~MainWidget();

  //void addLine(int x1, int y1, int x2, int y2);

  /*void set_Scene(OwnGraphicsScene *scene) {this->scene = scene;}
  void set_View(QGraphicsView *view) {this->view = view;}
  void set_Layout(QHBoxLayout *layout);*/

  OwnGraphicsScene* getScene() {return scene;}
  QGraphicsView* getView() {return view;}
  QHBoxLayout* getLayout() {return layout;}

  // set view scrollbar to left and center of the scene
  void InitScrollBar();

private:
  OwnGraphicsScene *scene;
  QGraphicsView *view;
  QHBoxLayout *layout;

};



#endif
