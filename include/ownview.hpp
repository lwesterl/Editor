/**
  *   @file ownview.hpp
  *   @author Lauri Westerholm
  *   @brief Contains custom QGraphicsView which Implements mouse tracking
  */

#ifndef OWN_VIEW_HEADER
#define OWN_VIEW_HEADER

/*    INCLUDES    */

#include <QGraphicsView>

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
    OwnGraphicsView(QGraphicsScene *scene,QWidget *parent): QGraphicsView(scene, parent)
    {
      setMouseTracking(false);
    }

  public slots:

  /**
    *   @brief Slot used to communicate with child scene
    *   @details The scene tells when to enable/disable mouse_tracking
    */
    void enable_mouse_tracking(bool enable)
    {
      if (enable)
      {
        setMouseTracking(true);
      }
      else
      {
        setMouseTracking(false);
      }
    }
};




#endif
