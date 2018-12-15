/**
  *   @file MainWidget.cpp
  *   @author Lauri Westerholm
  *   @brief Contains MainWidget class
  */



#include "../include/MainWidget.hpp"


// Constructor
MainWidget::MainWidget(QWidget *parent): QWidget(parent)
{
  // set layout
  layout = new QHBoxLayout();
  setLayout(layout);

  // set a scene and a view for it
  scene = new OwnGraphicsScene(this);
  view = new OwnGraphicsView(scene, this);
  // link view to the scene
  scene->addView(view);
  layout->addWidget(view);

}

// Deconstructor

MainWidget::~MainWidget()
{
  delete scene;
  delete view;
  delete layout;
}


// Inits scrollbar to horizontally left position and vertical scrollbar to center
void MainWidget::InitScrollBar()
{
  view->horizontalScrollBar()->setSliderPosition(1);
  // center the vertical scrollbar
  int max = view->verticalScrollBar()->maximum();
  int min = view->verticalScrollBar()->minimum();
  int center = (min + max) / 2;
  view->verticalScrollBar()->setValue( center );
}


/*
// Sets layout
void MainWidget::set_Layout(QHBoxLayout *layout)
{
  this->layout = layout;
  this->setLayout(layout);
}




void MainWidget::mousePressEvent(QMouseEvent *event)
{
  unsigned x_new = event->x();
  unsigned y_new = event->y();

  // Add a line from previous points if line adding mode activated
  addLine(mouse_x, mouse_y, x_new, y_new);

  // reassign mouse_x and mouse_y
  mouse_x = x_new;
  mouse_y = y_new;
  qDebug() << "Clicked\n" << "X: " << mouse_x << "Y: " << mouse_y;
}


// This adds a line to the graphics scene

void MainWidget::addLine(int x1, int y1, int x2, int y2)
{
  scene->addItem(new QGraphicsLineItem(x1, y1, x2, y2));
}
*/
