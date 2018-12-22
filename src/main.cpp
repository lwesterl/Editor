
/**
  *   @file main.cpp
  *   @author Lauri Westerholm
  *   @brief Main for Editor program
  */



#include "../include/GUI.hpp"
#include <QIcon>

/**
  *   @brief Simple main for Editor program
  *   @param args The number of command line arguments
  *   @param argv Command line arguments
  */

int main(int args, char *argv[])
{
  QApplication app(args, argv);
  QIcon app_icon;
  app_icon.addFile(Path::Images[Path::ImageName::app_icon]);
  app.setWindowIcon(app_icon);
  GUI gui;
  gui.resize(700,500);
  gui.show();

  return app.exec();
}
