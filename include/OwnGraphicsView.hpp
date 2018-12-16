/**
  *   @file OwnGraphicsView.hpp
  *   @author Lauri Westerholm
  *   @brief Contains custom QGraphicsView which Implements mouse tracking
  */

#pragma once

/*    INCLUDES    */

#include <QGraphicsView>
#include <QPoint>
#include <QSize>
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

  /**
    *   @brief Update view size
    *   @param new_size New view size
    *   @remark This should be called after MainWidget is resized
    */
    void updateSize(QSize new_size);

  /**
    *   @brief Updates view scene_size to match scene
    *   @remark Call this after scene size is changed
    *   @param width New scene width
    *   @param height New scene height
    */
    void updateSceneSize(unsigned width, unsigned height);

  /**
    *   @brief Reset view scaling
    *   @details Resets view scaling and set it to a safe state. Call this function
    *   when vindow or rect size is changed
    */
    void resetScaling();

  public slots:

  /**
    *   @brief Slot used to communicate with child scene
    *   @details The scene tells when to enable/disable mouse_tracking
    */
    void enable_mouse_tracking(bool enable);

  private:
    float current_scale = 1.f;
    QSize view_size;
    QSize scene_size;
};
