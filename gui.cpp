#include "gui.hpp"




// Implementation of GUI class
// first init base class
GUI::GUI(QWidget *parent): QMainWindow(parent)
{

  this->setWindowTitle ("Editor");
  setMouseTracking(true);



  // create a file options menu
  QMenu *file_options;
  file_options = menuBar()->addMenu("&File");

  // create a quit action
  QPixmap quit_pic(exit_img);
  QPixmap save_pic(save_img);
  QPixmap open_pic(open_img);
  QAction *save = new QAction(save_pic, "&Save", this);
  QAction *open = new QAction(open_pic, "&Open", this);
  QAction *quit_option = new QAction(quit_pic, "&Quit", this);
  file_options->addAction(save);
  file_options->addAction(open);
  file_options->addSeparator();
  file_options->addAction(quit_option);
  connect(quit_option, &QAction::triggered, qApp, &QApplication::quit);
  connect(save, &QAction::triggered, this, &GUI::saveImage);
  connect(open, &QAction::triggered, this, &GUI::openImage);

  // create a toolbar
  QToolBar *toolbar = addToolBar("Main Toolbar");

  // add a checkable line mode button
  QPixmap draw_line(draw_line_img);
  line_mode = toolbar->addAction(QIcon(draw_line),"Line mode");
  line_mode->setCheckable(true);
  line_mode->setChecked(true);
  connect(line_mode, &QAction::triggered, this, &GUI::LineMode);

  // add a checkable delete line button
  QPixmap delete_line(delete_line_img);
  delete_mode = toolbar->addAction(QIcon(delete_line),"Delete line");
  delete_mode->setCheckable(true);
  connect(delete_mode, &QAction::triggered, this, &GUI::DeleteMode);

  // add a clear previous points button
  toolbar->addSeparator();
  QPixmap clear_points(clear_points_img);
  clear_mode = toolbar->addAction(QIcon(clear_points),"Clear previous point(s)");
  connect(clear_mode, &QAction::triggered, this, &GUI::ClearMode);

  // add a clear all button
  QPixmap clear_all(clear_all_img);
  clear_all_mode = toolbar->addAction(QIcon(clear_all), "Clear all");
  connect(clear_all_mode, &QAction::triggered, this, &GUI::ClearAll);

  // add an add image button
  toolbar->addSeparator();
  QPixmap add_img(image_sketch_img);
  add_img_mode = toolbar->addAction(QIcon(add_img),"Add image");
  add_img_mode->setCheckable(true);
  add_img_mode->setChecked(false);
  connect(add_img_mode, &QAction::triggered, this, &GUI::ImgMode);

  //QPixmap quit_pic("exit.png");
  //QAction *quit = toolbar->addAction(QIcon(quit_pic),"Quit");
  //connect(quit, &QAction::triggered, qApp, &QApplication::quit);

  // MainWidget

  mainWidget = new MainWidget(this);
  this->setCentralWidget(mainWidget);
  mainWidget->InitScrollBar();
  //h_layout = new QHBoxLayout();
  //mainWidget->setLayout(h_layout);
  //mainWidget->set_Layout(new QHBoxLayout());

  // create QGraphicsScene
  //scene = new QGraphicsScene(this);
  //scene = new QGraphicsScene(mainWidget);
  //mainWidget->set_Scene(new QGraphicsScene(mainWidget));
  //mainWidget->set_Scene(new OwnGraphicsScene(mainWidget));

  // create a view for it and add the view to the layout
  //view = new QGraphicsView(scene, mainWidget);
  //mainWidget->set_View(new QGraphicsView(mainWidget->getScene(), mainWidget));
  //h_layout->addWidget(view);
  //mainWidget->getLayout()->addWidget(mainWidget->getView());

  // make the view central widget
  //this->setCentralWidget(view);



}


void GUI::LineMode()
{

  if (line_mode->isChecked())
  {
    // Set off other modes and activate line mode
    mainWidget->getScene()->LineMode(true);
    delete_mode->setChecked(false);
    add_img_mode->setChecked(false);
  }
  else
  {
    mainWidget->getScene()->LineMode(false);
  }
}

void GUI::DeleteMode()
{
  if (delete_mode->isChecked())
  {
    // Set off other modes and activate delete mode
    mainWidget->getScene()->DeleteMode(true);
    line_mode->setChecked(false);
    add_img_mode->setChecked(false);
  }
  else
  {
    mainWidget->getScene()->DeleteMode(false);
  }

}

// Trigger clear mode
void GUI::ClearMode()
{
  mainWidget->getScene()->ClearMode();
}

// Clear whole scene
void GUI::ClearAll()
{
  mainWidget->getScene()->ClearAll();
}

// Save scene to an image

void GUI::saveImage()
{
  OwnGraphicsScene *scene = mainWidget->getScene();

  //scene->clearSelection();
  //scene->setSceneRect(scene->itemsBoundingRect());
  QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::transparent);

  QPainter painter (&image);
  scene->render(&painter);

  // create a file dialog for user to save the image
  QFileDialog dialog (this);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setFileMode(QFileDialog::AnyFile);
  dialog.setNameFilter(tr("Images (*.jpeg *.png)"));
  if (dialog.exec())
  {
    QStringList names = dialog.selectedFiles();
    // try to save the image
    bool ret = image.save(names[0]);

    if (ret)
    {
      // saved
      QMessageBox::information(this, "Information", "Image saved successfully!");
    }
    else
    {
      QMessageBox::warning(this, "Warning", "Image saving failed!");
    }
  }



}

// Load an image for the scene
void GUI::openImage()
{
  // Create a QFileDialog
  QString imagename = QFileDialog::getOpenFileName(this, tr("Open image"),QDir::currentPath(), tr("*.png *.jpg "));
  bool ret = mainWidget->getScene()->setImage(imagename);
  if (ret == true)
  {
    // image opened successfully
    // inform user
    QMessageBox::information(this,"Information", "Image loaded successfully!");
  }
  else
  {
    QMessageBox::warning(this, "Warning", "Image loading failed!");
  }

}

// Check if image_add mode activated or stopped
// If activated, test if image can be added to the scene (calls scene imgMode)
// If image not possible to add, informs user
void GUI::ImgMode()
{
  if (add_img_mode->isChecked())
  {
    bool ret = mainWidget->getScene()->imgMode(true);
    if (ret == false)
    {
      // deactivate mode button
      add_img_mode->setChecked(false);
      QMessageBox::information(this, "Information", "Load an image first!");
    }
    // image mode activated
    // deactivate other modes
    line_mode->setChecked(false);
    delete_mode->setChecked(false);
  }
  else
  {
    // deactivate image mode
    mainWidget->getScene()->imgMode(false); // no need to check the return value
  }

}


/*void GUI::mouseMoveEvent(QMouseEvent *event)
{
  mouse_x = event->x();
  mouse_y = event->y();
}*/

/*
 *    This overload catches user mouse movement
 *    mouse x stored to mouse_x
 *    mouse y stored to mouse_y
 */
/*
void GUI::mousePressEvent(QMouseEvent *event)
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

void GUI::addLine(int x1, int y1, int x2, int y2)
{
  scene->addItem(new QGraphicsLineItem(x1, y1, x2, y2));
}*/
