
/**
  *   @file GUI_test.cpp
  *   @author Lauri Westerholm
  *   @brief Test main for Editor program
  */



#include "../include/GUI.hpp"

/**
  *   @brief Simple main for Editor program
  *   @param args The number of command line arguments
  *   @param argv Command line arguments
  */

int main(int args, char *argv[])
{
  QApplication app(args, argv);
  GUI gui;
  gui.resize(700,500);
  gui.show();

  return app.exec();
}
