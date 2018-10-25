#ifndef Promt_window
#define Promt_window

// THIS CLASS IS NOT USED 

#include <QStringList>
#include <QDir>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class PromtWindow: public QDialog
{
  Q_OBJECT
  public:
    PromtWindow(QWidget *parent);
    void ListImages(QDir directory);
  private slots:
    void backButton();
    void homeButton();

  private:
    QVBoxLayout *main_layout;
    QHBoxLayout *h_layout;
    QString current_dir;
    QGraphicsScene *label_scene;
    QGraphicsView *label_view;




};

#endif
