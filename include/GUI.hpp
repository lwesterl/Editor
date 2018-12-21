
/**
  *   @file GUI.hpp
  *   @author Lauri Westerholm
  *   @brief Header for GUI class.
  */



#pragma once


/*    INCLUDES    */

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
#include "OwnGraphicsScene.hpp"
#include "MainWidget.hpp"
#include "ComboboxAction.hpp"
#include "SpinBoxAction.hpp"
#include "PixmapItem.hpp"


/*    MACROS    */

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
  *   @brief Bezier pic image macro
  */
#define bezier_pic_img "img_src/bezier_pic.png"

/**
  *   @brief Save button image macro
  */
#define save_button_img "img_src/save_button.png"

/**
  *   @brief Bezier remove image macro
  */
#define bezier_remove_img "img_src/bezier_remove.png"


/**
  *   @struct PolygonToolbar
  *   @brief Toolbar used in image polygon cut
  */

struct PolygonToolbar
{
  QToolBar *polygon_toolbar; /**< Pointer to the QToolBar */
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
  *   @struct BezierToolbar
  *   @brief Toolbar used during bezier mode
  */

struct BezierToolbar
{
  QToolBar *bezier_toolbar; /**< Pointer to the QToolbar */
  QComboBox *options; /**< BezierToolbar options */
  QAction *save_options; /**< Save options */
  QAction *save_bezier; /**< Button to save the Bezier */
  QAction *remove_bezier; /**< Button to remove current Bezier */
  QAction *cancel; /**< Button to cancel to main Toolbar */
};


/**
  *   @class GUI
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
  ~GUI();

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
    *   @brief Clear previous points
    *   @details Triggers clear mode in the scene
    */
  void ClearMode();

  /**
    *   @brief Clear all objects
    *   @details User triggered QAction sends a signal and clears all
    */
  void ClearAll();

  /**
    *   @brief Save scene content to an image
    *   @details User can specify where the image is saved
    */
  void saveImage();

  /**
    *   @brief Open an image
    *   @details By activating image mode user can place the image to the scene
    */
  void openImage();

  /**
    *   @brief Mode for adding images to the scene
    *   @details User can drag image and then save it to the scene
    */
  void ImgMode();

  /**
    *   @brief Delete images from the scene
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
    *   @brief Create different toolbars
    *   @details Called from GUI constructor to create all toolbars
    */
  void createToolbars();

  /**
    *   @brief Hide PolygonToolbar
    *   @param hide if true hides the toolbar
    */
  void HidePolygonToolbar(bool hide);

  /**
    *   @brief Hide ModeToolbar
    *   @param hide if true hides the toolbar
    */
  void HideModeToolbar(bool hide);

  /**
    *   @brief Hide MainToolbar
    *   @param hide if true hides the toolbar
    */
  void HideMainToolbar(bool hide);

  /**
    *   @brief Hide SelectImgToolbar
    *   @param hide if true hides the toolbar
    */
  void HideSelectToolbar(bool hide);

  /**
    *   @brief Continue to image cutting
    *   @details Called after user has selected image cutting mode
    */
  void ContinueFromMode();

  /**
    *   @brief Cancel to the main view, toolbar
    *   @details Called after user has canceled from image cutting mode
    */
  void CancelFromMode();

  /**
    *   @brief Create polygon cut to an image
    *   @details Triggered by user when user is ready to cut the image
    */
  void SetPolyFinal();

  /**
    *   @brief Remove previous cut line from an image
    *   @details Triggered by user action
    */
  void RemovePolyPrevious();

  /**
    *   @brief Return to the main view
    *   @details Called after user has canceled from polygon image cut
    */
  void CancelFromPoly();

  /**
    *   @brief Continue to image mode select
    *   @details Called after user has selected which image to cut
    */
  void ContinueFromSelect();

  /**
    *   @brief Return to the main view
    *   @details Called after user has canceled from image select
    */
  void CancelFromSelect();

  /**
    *   @brief Save options
    *   @details Called after user has modified options combobox and wants to save
    *   the options
    */
  void SaveChoices();

  /**
    *   @brief Activates/deactivates bezier_mode
    */
  void BezierMode();

  /**
    *   @brief Driggered when BezierToolbar options are saved
    *   @details Used to update OwnGraphicsScene Bezier drawing
    */
  void BezierToolbar_OptionsSaved();

  /**
    *   @brief Save the current Bezier
    *   @details Used to signal OwnGraphicsScene that the Bezier should be saved
    */
  void BezierToolbar_SaveBezier();

  /**
    *   @brief Remove the current Bezier and cancel to main toolbar
    */
  void BezierToolbar_Cancel();

  /**
    *   @brief Remove current Bezier
    */
  void BezierToolbar_Remove();


  /**
    *   @brief Hide or unhide BezierToolbar
    *   @param hide true -> hide, false -> unhide
    */
  void HideBezierToolbar(bool hide);

  void PathCut_Continue();
  void PathCut_Cancel();


private:

  /**
    *   @brief Set OwnGraphicsScene size
    *   @details calls setSceneRect for OwnGraphicsScene
    *   @param width New rect width
    *   @param height New rect height
    */
  void setSceneSize(unsigned width, unsigned height);

  /*  Variables */
  MainWidget *mainWidget;
  QAction *line_mode;
  QAction *delete_mode;
  QAction *clear_mode;
  QAction *bezier_mode;
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
  struct BezierToolbar bezierToolbar;
  QToolBar *pathcutToolbar;

  ComboboxAction *line_options_combo;
  ComboboxAction *connect_options_combo;
  SpinBoxAction *window_width;
  SpinBoxAction *window_height;


};
