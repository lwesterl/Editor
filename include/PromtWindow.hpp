/**
  *   @file PromtWindow.hpp
  *   @author Lauri Westerholm
  *   @brief Header for PromtWindow class
  *   @remark Not used
  */

#pragma once


/*    INCLUDES    */

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

/**
  *   @class PromtWindow
  *   @brief Implements specific QDialog
  *   @remark Not used
  */

class PromtWindow: public QDialog
{
  Q_OBJECT
  public:

    /**
      *   @brief Constructor for PromtWindow
      *   @param parent The parent QWidget
      */
    PromtWindow(QWidget *parent);

    /**
      *   @brief List all images in directory
      *   @param directory Path to the directory to be listed
      */
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
