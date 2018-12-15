/**
  *   @file OwnGraphicsView.cpp
  *   @brief Contains source code for OwnGraphicsView
  */

#include "../include/OwnGraphicsView.hpp"


/*  Class OwnGraphicsView */

OwnGraphicsView::OwnGraphicsView(QGraphicsScene *scene,QWidget *parent): QGraphicsView(scene, parent)
{
  setMouseTracking(false);
}

/*  Enable mouse tracking */
void OwnGraphicsView::enable_mouse_tracking(bool enable)
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

/*  Zooming in the view */
void OwnGraphicsView::wheelEvent (QWheelEvent *event)
{
  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;

  if (!numPixels.isNull())
  {
    if (numPixels.y() < 0) {
      scale_count -= 1;
    }
    else if (1.f - (scale_count + 1) * 0.05 > 0.1) scale_count += 1;

  }
  else if (!numDegrees.isNull())
  {
    // use these if numPixels aren't supported by os
    if (numDegrees.y() < 0) {
      scale_count -= 1;
    }
    else if (1.f - (scale_count +1) * 0.05 > 0.1) scale_count += 1;
  }

  // scale the view
  float new_scale = 1.0f - scale_count * 0.05;
  resetMatrix();
  scale(new_scale, new_scale);
  event->accept();
}
