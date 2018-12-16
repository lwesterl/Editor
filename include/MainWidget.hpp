
/**
  *   @file MainWidget.hpp
  *   @author Lauri Westerholm
  *   @brief Header file for MainWidget class
  */



#pragma once


/*    INCLUDES    */

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QScrollBar>
#include "OwnGraphicsScene.hpp"
#include "OwnGraphicsView.hpp"


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

  /**
    *   @brief Overload for resizeEvent
    *   @param event resizeEvent
    */
  virtual void resizeEvent(QResizeEvent *event);

  /**
    *   @brief Get the scene
    *   @return Returns the graphics scene
    */
  OwnGraphicsScene* getScene() {return scene;}
  /**
    *   @brief Get the view
    *   @return Returns the graphics view
    */
  OwnGraphicsView* getView() {return view;}
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
  OwnGraphicsView *view;
  QHBoxLayout *layout;

};
