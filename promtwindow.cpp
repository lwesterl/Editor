#include "promtwindow.hpp"



// Constructor

PromtWindow::PromtWindow(QWidget *parent): QDialog(parent)
{

  // Set layout
  main_layout = new QVBoxLayout();
  setLayout(main_layout);
  h_layout = new QHBoxLayout();
  main_layout -> addLayout(h_layout);

  QPushButton *back_button = new QPushButton();
  back_button->setIcon(QIcon("back_arrows.png"));
  back_button->setIconSize(QSize(15,15));
  back_button->setFixedSize(QSize(15,15));

  QPushButton *home_button = new QPushButton();
  home_button->setIcon(QIcon("home.png"));
  home_button->setIconSize(QSize(15,15));
  home_button->setFixedSize(QSize(15,15));

  // Connect the buttons
  connect(back_button, SIGNAL (released()), this, SLOT (backButton()));
  connect(home_button, SIGNAL (released()), this, SLOT (homeButton()));



  // Add buttons to the h_layout
  h_layout->addWidget(back_button);
  h_layout->addWidget(home_button);

  // create QGraphicsScene and a view
  label_scene = new QGraphicsScene(this);
  label_view = new QGraphicsView(label_scene, this);
  main_layout->addWidget(label_view);


  // List image files
  ListImages(QDir::currentPath());

}

// List all images in the directory

void PromtWindow::ListImages(QDir directory)
{
  QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.png" << "*.PNG",QDir::Files);
  QString info = "Pictures in directory: " + directory.absolutePath();
  QGraphicsTextItem *info_text = new QGraphicsTextItem(info);

  label_scene->addItem(info_text);

  int count = 1;
  foreach(QString filename, images)
  {
    QGraphicsTextItem *new_item = new QGraphicsTextItem(filename);
    new_item->setPos(0,count * 20); // add objects below each other
    label_scene->addItem(new_item);
    count ++;

  }
}


void PromtWindow::backButton()
{
  // go one step back in directory
  QDir curr = QDir::currentPath();
}


void PromtWindow::homeButton()
{
  // Go to Home dir and list its content
  QDir home = QDir::home();
  // First clear TextItems
  label_scene->clear();
  ListImages(home);
}
