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

/*  Overload for resizeEvent */
void MainWidget::resizeEvent(QResizeEvent *event)
{
  //  update view size
  view->updateSize(event->size());
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

/*  Set new backgroundcolor */
void MainWidget::changeBackgroundColor(const QColor &color)
{
  QPalette palette = QPalette();
  palette.setColor(QPalette::Background, color);
  setAutoFillBackground(true);
  setPalette(palette);
}
