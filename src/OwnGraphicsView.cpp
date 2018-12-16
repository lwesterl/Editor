/**
  *   @file OwnGraphicsView.cpp
  *   @brief Contains source code for OwnGraphicsView
  */

#include "../include/OwnGraphicsView.hpp"


/*  Class OwnGraphicsView */

OwnGraphicsView::OwnGraphicsView(QGraphicsScene *scene,QWidget *parent): QGraphicsView(scene, parent)
{
  // set correct scene_size
  scene_size = QSize(scene->width(), scene->height());
  setMouseTracking(false);
}

/*  Enable mouse tracking */
void OwnGraphicsView::enable_mouse_tracking(bool enable)
{
  if (enable) {
    setMouseTracking(true);
  }
  else {
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
      current_scale += 0.05;
    }
    else if (((current_scale - 0.05) * scene_size.rheight() >= view_size.rheight()) &&
              ((current_scale - 0.05) * scene_size.rwidth() >= view_size.rwidth()))
    {
      current_scale -= 0.05;
    }

  }
  else if (!numDegrees.isNull())
  {
    // use these if numPixels aren't supported by os
    if (numDegrees.y() < 0) {
      current_scale += 0.05;
    }
    else if (((current_scale - 0.05) * scene_size.rheight() >= view_size.rheight()) &&
              ((current_scale - 0.05) * scene_size.rwidth() >= view_size.rwidth()))
    {
      current_scale -= 0.05;
    }
  }

  // scale the view
  resetMatrix();
  scale(current_scale, current_scale);
  event->accept();
}

/*  Update view_size */
void OwnGraphicsView::updateSize(QSize new_size)
{
  view_size = new_size;
  // reset scaling
  resetScaling();
}

/*  Update scene_size */
void OwnGraphicsView::updateSceneSize(unsigned width, unsigned height)
{
  scene_size = QSize(static_cast<int>(width), static_cast<int>(height));
  // set new scene rect
  updateSceneRect(scene()->sceneRect());
  // reset scaling
  resetScaling();
}

/*  Reset view scaling to safe state */
void OwnGraphicsView::resetScaling()
{
  // reset old scale
  resetMatrix();

  // Set view to its max size (this is needed if vindow is shrunk down)
  float width_scale = static_cast<float>(view_size.width()) / static_cast<float>(scene_size.width());
  float height_scale = static_cast<float>(view_size.height()) / static_cast<float>(scene_size.height());
  // use bigger scaling factor, crusial
  if (width_scale > height_scale) {
    current_scale = width_scale;
  }
  else {
    current_scale = height_scale;
  }
  scale(current_scale, current_scale);
}
