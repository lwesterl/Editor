
/**
  *   @file gui.hpp
  *   @author Lauri Westerholm
  *   @brief Header for gui class.
  */



#ifndef GUI_HEADER
#define GUI_HEADER



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


/**
  *   @brief Exit image macro
  */
#define exit_img "img_src/exit.png"
/**
  *   @brief Open image macro
  */
#define open_img "img_src/open.png"
/**
  *   @brief Save image macro
  */
#define save_img "img_src/save.png"
/**
  *   @brief Draw line image macro
  */
#define draw_line_img "img_src/draw_line.png"
/**
  *   @brief Delete line image macro
  */
#define delete_line_img "img_src/delete_line.png"
/**
  *   @brief Clear points image macro
  */
#define clear_points_img "img_src/clear_points.png"
/**
  *   @brief Clear all image macro
  */
#define clear_all_img "img_src/clear_all.png"
/**
  *   @brief Image sketch macro
  */
#define image_sketch_img "img_src/image_sketch.png"
/**
  *   @brief Image delete image macro
  */
#define image_delete_img "img_src/image_delete.png"
/**
  *   @brief Image cut image macro
  */
#define image_cut_img "img_src/image_cut.png"
/**
  *   @brief Continue image macro
  */
#define continue_img "img_src/continue.png"
/**
  *   @brief Cancel image macro
  */
#define cancel_img "img_src/cancel.png"
/**
  *   @brief Finish image macro
  */
#define finish_img "img_src/finish.png"
/**
  *   @brief Remove point image macro
  */
#define remove_point_img "img_src/remove_point.png"



/**
  *   @struct PolygonToolbar
  *   @brief Toolbar used in image polygon cut
  */

struct PolygonToolbar
{
  QToolBar *polygon_toolbar; /**< Pointer to the QToolBar */
  QAction *endpoints; /**< Not used */
  QLabel *endpoints_text; /**< Not used */
  QAction *final_point; /**< Connects to SetPolyFinal */
  QLabel *final_point_text; /**< Info text for user about cutting */
  QAction *remove; /**< Connects to RemovePolyPrevious */
  QLabel *remove_text; /**< Info text for user */
  QAction *cancel; /**< Connects to CancelFromPoly */
};

/**
  *   @struct ModeToolbar
  *   @brief Toolbar for changing image cut mode
  */

struct ModeToolbar
{
  QToolBar *mode_toolbar; /**< Pointer to the QToolbar */
  QComboBox *combobox;  /**< Pointer to the QComboBox */
  QAction *continue_button; /**< Pointer to a QAction which connects to ContinueFromMode */
  QAction *cancel; /**< Pointer to a QAction which connects to CancelFromMode */
};

/**
  *   @struct SelectImgToolbar
  *   @brief Toolbar used to select image to be cut
  */

struct SelectImgToolbar
{
  QToolBar *select_img_toolbar; /**< Pointer to the QToolBar */
  QLabel *info; /**< Label used to inform user */
  QAction *continue_button; /**< Pointer to a QAction which connects to ContinueFromSelect */
  QAction *cancel; /**< Pointer to a QAction which connects to CancelFromSelect */
};


/**
  *   @class GUI gui.hpp
  *   @brief Graphical user interface
  *   @details Inherits QMainWindow. Implements inteface to mainwidget
  */



class GUI: public QMainWindow
{
public:

  /**
    *   @brief GUI constructor
    *   @param parent the parent widget
    */
  GUI(QWidget *parent = 0);
  /**
    *   @brief GUI deconstructor
    *   @details Deletes mainwidget
    */
  ~GUI() {delete mainWidget;}
  /**
    *   @brief Line drawing mode
    *   @details QAction sends a signal and activates or deactivates line mode
    */
  void LineMode();
  /**
    *   @brief Delete lines mode
    *   @details QAction sends a signal and activates or deactivates delete mode
    */
  void DeleteMode();
  /**
    *   @brief Clears previous points
    *   @details Triggers clear mode in the scene
    */
  void ClearMode();
  /**
    *   @brief Clears all objects
    *   @details User triggered QAction sends a signal and clears all
    */
  void ClearAll();
  /**
    *   @brief Saves scene content to an image
    *   @details User can specify where the image is saved
    */
  void saveImage();
  /**
    *   @brief Opens an image
    *   @details By activating image mode user can place the image to the scene
    */
  void openImage();
  /**
    *   @brief Mode for adding images to the scene
    *   @details User can drag image and then save it to the scene
    */
  void ImgMode();
  /**
    *   @brief Deletes images from the scene
    *   @details User holds cursor over an image and clicks to delete the image
    */
  void DeleteImgMode();
  /**
    *   @brief Mode for cutting images
    *   @details Images can be cut to multiple shapes. Starts a toolbar which
    *   promts user to choose which image is being cut. Then user chooses cut style
    *   and finally cuts the image
    */
  void CutImageMode();
  /**
    *   @brief Creates different toolbars
    *   @details Called from GUI constructor to create all toolbars
    */
  void createToolbars();
  /**
    *   @brief Hides PolygonToolbar
    *   @param hide if true hides the toolbar
    */
  void HidePolygonToolbar(bool hide);
  /**
    *   @brief Hides ModeToolbar
    *   @param hide if true hides the toolbar
    */
  void HideModeToolbar(bool hide);
  /**
    *   @brief Hides MainToolbar
    *   @param hide if true hides the toolbar
    */
  void HideMainToolbar(bool hide);
  /**
    *   @brief Hides SelectImgToolbar
    *   @param hide if true hides the toolbar
    */
  void HideSelectToolbar(bool hide);
  /**
    *   @brief Continues to image cutting
    *   @details Called after user has selected image cutting mode
    */
  void ContinueFromMode();
  /**
    *   @brief Cancels to the main view, toolbar
    *   @details Called after user has canceled from image cutting mode
    */
  void CancelFromMode();
  /**
    *   @brief Creates polygon cut to an image
    *   @details Triggered by user when user is ready to cut the image
    */
  void SetPolyFinal();
  /**
    *   @brief Removes previous cut line from an image
    *   @details Triggered by user action
    */
  void RemovePolyPrevious();
  /**
    *   @brief Returns to the main view
    *   @details Called after user has canceled from polygon image cut
    */
  void CancelFromPoly();
  /**
    *   @brief Continues to image mode select
    *   @details Called after user has selected which image to cut
    */
  void ContinueFromSelect();
  /**
    *   @brief Returns to the main view
    *   @details Called after user has canceled from image select
    */
  void CancelFromSelect();
  /**
    *   @brief Saves options
    *   @details Called after user has modified options combobox and wants to save
    *   the options
    */
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
