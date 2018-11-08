#include "gui.cpp"

// just test main

int main(int args, char *argv[])
{
  QApplication app(args, argv);
  GUI gui;
  gui.resize(700,500);
  gui.show();

  return app.exec();
}
