
/**
  *   @file mainwidget.hpp
  *   @author Lauri Westerholm
  *   @brief Header file for MainWidget class
  */



#ifndef MAIN_WIDGET_HEADER
#define MAIN_WIDGET_HEADER


/*    INCLUDES    */

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QScrollBar>
#include "owngraphicsscene.hpp"


/**
  *   @class MainWidget
  *   @brief Mainwidget for GUI
  *   @details This class is the main widget for gui
  *    contains a Graphics scene and a view for it
  *    Uses QHBoxLayout
  */

class MainWidget: public QWidget
{
public:
  /**
    *   @brief Constructor for MainWidget
    *   @param parent the parent QWidget
    */
  MainWidget(QWidget *parent);
  /**
    *   @brief Deconstructor
    */
  ~MainWidget();

  //void addLine(int x1, int y1, int x2, int y2);

  /*void set_Scene(OwnGraphicsScene *scene) {this->scene = scene;}
  void set_View(QGraphicsView *view) {this->view = view;}
  void set_Layout(QHBoxLayout *layout);*/

  /**
    *   @brief Get the scene
    *   @return Returns the graphics scene
    */
  OwnGraphicsScene* getScene() {return scene;}
  /**
    *   @brief Get the view
    *   @return Returns the graphics view
    */
  QGraphicsView* getView() {return view;}
  /**
    *   @brief Get the layout
    *   @return Returns the graphics layout
    */
  QHBoxLayout* getLayout() {return layout;}

  /**
    *   @brief Init the scrollbar
    *   @details Set view scrollbar to left and center of the scene
    */
  void InitScrollBar();

private:
  OwnGraphicsScene *scene;
  QGraphicsView *view;
  QHBoxLayout *layout;

};



#endif
