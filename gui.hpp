#ifndef Gui_header
#define Gui_header



#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBoxLayout>
#include <QPoint>
#include <QPushButton>
#include <QImage>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>
#include "owngraphicsscene.hpp"
#include "mainwidget.hpp"
#include "combobox_action.hpp"

// Source images
#define exit_img "img_src/exit.png"
#define open_img "img_src/open.png"
#define save_img "img_src/save.png"
#define draw_line_img "img_src/draw_line.png"
#define delete_line_img "img_src/delete_line.png"
#define clear_points_img "img_src/clear_points.png"
#define clear_all_img "img_src/clear_all.png"
#define image_sketch_img "img_src/image_sketch.png"
#define image_delete_img "img_src/image_delete.png"
#define image_cut_img "img_src/image_cut.png"

struct PolygonToolbar
{
  QToolBar *polygon_toolbar;
  QAction *endpoints;
  QLabel *endpoints_text;
  QAction *final_point;
  QLabel *final_point_text;
  QAction *remove;
  QLabel *remove_text;
  QAction *cancel;
};

struct ModeToolbar
{
  QToolBar *mode_toolbar;
  QComboBox *combobox;
  QAction *continue_button;
  QAction *cancel;
};

struct SelectImgToolbar
{
  QToolBar *select_img_toolbar;
  QLabel *info;
  QAction *continue_button;
  QAction *cancel;
};


// Graphical user interface
// inherits GMainWindow

class GUI: public QMainWindow
{
public:
  GUI(QWidget *parent = 0);
  ~GUI() {delete mainWidget;}
  void LineMode();
  void DeleteMode();
  void ClearMode();
  void ClearAll();
  void saveImage();
  void openImage();
  void ImgMode();
  void DeleteImgMode();
  void CutImageMode();
  void createToolbars();
  void HidePolygonToolbar(bool hide);
  void HideModeToolbar(bool hide);
  void HideMainToolbar(bool hide);
  void HideSelectToolbar(bool hide);
  void ContinueFromMode();
  void CancelFromMode();
  void SetPolyFinal();
  void RemovePolyPrevious();
  void CancelFromPoly();
  void ContinueFromSelect();
  void CancelFromSelect();
  void SaveChoices();

  //void mouseMoveEvent(QMouseEvent *event);
  //void mousePressEvent(QMouseEvent *event);
  //int getMouseX(){return mouse_x;}
  //int getMouseY(){return mouse_y;}
  //void addLine(int x1, int y1, int x2, int y2);

private:
  MainWidget *mainWidget;
  QAction *line_mode;
  QAction *delete_mode;
  QAction *clear_mode;
  QAction *clear_all_mode;
  QAction *add_img_mode;
  QAction *delete_img_mode;
  QAction *cut_image_mode;
  QAction *continue_img_cut;
  QAction *cancel_img_cut;
  QToolBar *main_toolbar;

  struct PolygonToolbar polyToolbar;
  struct ModeToolbar modeToolbar;
  struct SelectImgToolbar selectToolbar;

  ComboboxAction *line_options_combo;


};


#endif
