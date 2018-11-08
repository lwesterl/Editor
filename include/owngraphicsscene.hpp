/**
  *   @file owngraphicsscene.hpp
  *   @author Lauri Westerholm
  *   @brief Header file for OwnGraphicsScene class
  */



#ifndef OWN_SCENE_HEADER
#define OWN_SCENE_HEADER


/*    INCLUDES    */

 #include <QGraphicsSceneMouseEvent>
 #include <QDebug>
 #include <QGraphicsScene>
 #include <QGraphicsItem>
 #include <QPoint>
 #include <QWidget>
 #include <QList>
 #include <list>
 #include <vector>
 #include <QPixmap>
 #include <QString>
 #include <QGraphicsPixmapItem>
 #include "line_item.hpp"
 #include "pixmap_item.hpp"

/**
  *   @brief Macro for no image cut mode selected
  */
 #define no_img_cut 0
 /**
   *   @brief Macro for polygon cut mode selected
   */
 #define polygon_img_cut 1
 /**
   *   @brief Macro for path cut mode selected
   */
 #define path_img_cut 2

/**
  *   @struct Image_Active
  *   @brief Contains active image
  *   @details Used to when user is in image_mode
  */

 struct Image_Active
 {
   //bool image_mode = false; // user has activated image mode
   bool added_scene = false; /**< Is image added to scene */
   PixmapItem *pixmap_item; /**< Points to the current item which is moved */
   unsigned char clicks = 0; /**< Counter for mouse clicks */
 };

/**
  *   @struct Image_Cut
  *   @brief Struct for active image during image cut
  */

 struct Image_Cut
 {
   PixmapItem *pixmap_item; /**< Original image pixmap item */
   bool initialized = false;  /**< Is user selected which image to cut */
   unsigned char cut_mode = no_img_cut; /**< Stores the cut mode */
   QPoint point; /**< Tells which image should be cutted */
   std::vector<LineItem*> visual_items; /**< These are used to visualize the cutting pattern and just temporarily added to the scene */
   LineItem *current_item; /**< LineiItem which is curretly under construction */
   unsigned prev_x; /**< Previous x position */
   unsigned prev_y; /**< Previous y position */
   bool visual_created = false; /**< Whether the LineItem is added to the scene or not */

 };


/**
  *   @struct Line_Mode
  *   @brief Struct used during line_mode
  */

 struct Line_Mode
 {
   LineItem *line_item; /**< The item which is curretly moved */
   bool positioned = false; /**< Whether the item is positioned or not */
   bool created = false; /**< Whether element is already created or not */
   unsigned prev_x; /**< Previous x position */
   unsigned prev_y; /**< Previous y position */
 };


/*    MACROS    */

/**
  *   @brief Macro for view mode (drawing modes not active)
  */
 #define view_mode_value 0
 /**
   *   @brief Macro for view mode
   */
 #define line_mode_value 1
 /**
   *   @brief Macro for delete mode
   */
 #define delete_mode_value 2
 /**
   *   @brief Macro for image adding mode
   */
 #define image_mode_value 3
 /**
   *   @brief Macro for delete image mode
   */
 #define delete_img_mode_value 4
 /**
   *   @brief Macro for image cutting mode
   */
 #define cut_image_mode_value 5



 /**
   *    @class OwnGraphicsScene
   *    @brief Own QGraphicsScene implementation
   *    @details This is an implementation for own QGraphicsScene which
   *    overloads mousePressEvent to update the scene
   */


 class OwnGraphicsScene : public QGraphicsScene
 {
 public:
  /**
    *   @brief Constructor for OwnGraphicsScene
    *   @param parent The QWidget parent
    *   @details Sets standard size for the view rect
    */
   OwnGraphicsScene(QWidget *parent):QGraphicsScene(parent) {setSceneRect(0, 0, 10000, 10000);}

  /**
    *   @brief Destructor for OwnGraphicsScene
    */
   ~OwnGraphicsScene();

  /**
    *   @brief Overload for mousePressEvent
    *   @details Used to add new items to the scene, also  to remove and cut
    *   old items
    */
   void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /**
    *   @brief Overload for mouseMoveEvent
    *   @details Used to track user mouse when creating lines and cutting
    *    images
    */
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

  /**
    *   @brief Add a LineItem
    *   @param x1 Start x coordinate
    *   @param y1 Start y coordinate
    *   @param x2 End x coordinate
    *   @param y2 End y coordinate
    *   @return Returns pointer to the new item added to the scene
    */
   LineItem *addLine(unsigned x1, unsigned y1, unsigned x2, unsigned y2);

  /**
    *   @brief Get new mouse x coordinate
    *   @return Returns mouse_x value
    */
   unsigned getMouseX() {return mouse_x;}

   /**
     *   @brief Get new mouse y coordinate
     *   @return Returns mouse_y value
     */
   unsigned getMouseY() {return mouse_y;}

  /**
    *   @brief Activate or deactivate line_mode
    *   @param activate If true activates line mode
    */
   void LineMode(bool activate);

   /**
     *   @brief Activate or deactivate delete_mode
     *   @param activate If true activates delete mode
     */
   void DeleteMode(bool activate);

  /**
    *   @brief Clear previous line points
    */
   void ClearMode();

  /**
    *   @brief Remove LineItem from the scene
    *   @param x x coordinate of the item to be removed
    *   @param y y coordinate of the item to be removed
    */
   void remove_Item(unsigned x, unsigned y);

  /**
    *   @brief Remove all items from the scene
    */
   void ClearAll();

  /**
    *   @brief Construct QPixmap from an image
    */
   bool setImage(QString imagename);

  /**
    *   @brief Activate or deactivate image_mode
    *   @param activate If true activate image_mode
    */
   bool imgMode(bool activate);

   /**
     *   @brief Activate or deactivate delete_img_mode
     *   @param activate If true activate delete_img_mode
     */
   void DeleteImgMode(bool activate);

  /**
    *   @brief Delete image from the scene
    *   @param x1 x coordinate
    *   @param y1 y coordinate
    */
   void DeleteImg(unsigned x1, unsigned y1);

   /**
     *   @brief Activate or deactivate cut_image_mode
     *   @param active If true activate cut_image_mode
     */
   void CutImageMode(bool active);

  /**
    *   @brief Select image to be cut
    *   @return Returns true if image exists
    */
   bool SelectCutImg();

  /**
    *   @brief Select image cut mode
    *   @details Image cut modes are defined as macros
    */
   void SetImgCutMode(int cut_mode);

  /**
    *   @brief Wrapper for PixmapItem::CutItem
    *   @details Cuts the image by adding painter points. Removes temporary
    *   LineItems which were used to display the cut path
    */
   void CutPixmapItem();

  /**
    *   @brief Remove previous image cut point
    *   @details Removes also the LineItem matching the point
    */
   void RemovePolyPrevious();

  /**
    *   @brief Update connect_lines value
    *   @param value New connect_lines value matching combobox options
    */
   void setConnectLines(int value);

  /**
    *   @brief Removes all temporary visual_items
    *   @details Called after image cut is ready
    */
   void ClearVisualItems();

 private:
   std::list <LineItem*> line_items;
   std::list <PixmapItem*> pixmap_items;
   unsigned mouse_x;
   unsigned mouse_y;
   bool first_line = true;
   bool connect_lines = true; // This controls whether first_line is reset
   struct Line_Mode line_struct;
   unsigned char mode = line_mode_value;
   //bool line_mode = true;
   //bool delete_mode = false;
   struct Image_Active image_active;
   QPixmap image = QPixmap(); // construct a Null pixmap
   //bool delete_img_mode = false;
   QString current_imagename;
   //bool cut_image_mode = false;
   struct Image_Cut image_cut;
 };


 #endif
