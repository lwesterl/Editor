/**
  *   @file OwnGraphicsView.hpp
  *   @author Lauri Westerholm
  *   @brief Contains custom QGraphicsView which Implements mouse tracking
  */

#pragma once

/*    INCLUDES    */

#include <QGraphicsView>
#include <QPoint>
#include <QWheelEvent>
#include <QDebug>

/**
  *   @class OwnGraphicsView
  *   @brief Custom QGraphicsView which Implements mouse tracking
  */

class OwnGraphicsView : public QGraphicsView
{
  Q_OBJECT
  public:

  /**
    *   @brief Constructor for OwnGraphicsView
    *   @details Starts with mouse tracking disabled
    */
    OwnGraphicsView(QGraphicsScene *scene,QWidget *parent);

/**
  *   @brief wheelEvent overload
  *   @details Used to implement zooming of the view
  */
    void wheelEvent (QWheelEvent *event);


  public slots:

  /**
    *   @brief Slot used to communicate with child scene
    *   @details The scene tells when to enable/disable mouse_tracking
    */
    void enable_mouse_tracking(bool enable);

  private:
    int scale_count = 0;
};
