/**
  *   @file OwnGraphicsScene.hpp
  *   @author Lauri Westerholm
  *   @brief Header file for OwnGraphicsScene class
  */



#pragma once


/*    INCLUDES    */

 #include <QGraphicsSceneMouseEvent>
 #include <QDebug>
 #include <QGraphicsScene>
 #include <QGraphicsItem>
 #include <QPoint>
 #include <QWidget>
 #include <QList>
 #include <list>
 #include <deque>
 #include <vector>
 #include <map>
 #include <QPixmap>
 #include <QString>
 #include <QGraphicsPixmapItem>
 #include <QGraphicsEllipseItem>
 #include <QBrush>
 #include <QPen>
 #include "LineItem.hpp"
 #include "PixmapItem.hpp"
 #include "OwnGraphicsView.hpp"
 #include "Bezier.hpp"
 #include "Vector2.hpp"
 #include "TextItem.hpp"

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
   LineItem *current_item; /**< LineItem which is curretly under construction */
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

/**
  *   @struct Bezier_Mode
  *   @brief Struct used during bezier_mode
  */

 struct Bezier_Mode
 {
   Vector2 p1; /**< The first bezier point */
   Vector2 p2; /**< The second bezier point */
   Vector2 p3; /**< The third bezier point */
   Vector2 p4; /**< The fourth bezier point */
   bool created = false; /**< Whether the Bezier is created or not */
   int lock_mode = 1; /**< Whether the start point is locked or not */
   Bezier *active_bezier = nullptr; /**< Pointer to the Bezier being constructed */
   QGraphicsEllipseItem *circle1 = nullptr; /**< Circle which center is the first control point */
   QGraphicsEllipseItem *circle2 = nullptr; /**< Circle which center is the second control point */
   QGraphicsEllipseItem *circle3 = nullptr; /**< Circle which center is the third control point */
   QGraphicsEllipseItem *circle4 = nullptr; /**< Circle which center is the fourth control point */
 };

/**
  *   @struct End_Points
  *   @brief Used to look up end points
  *   @details End points are used as starting points for new objects
  */
 struct End_Points
 {
   bool found = false; /**< Tells whether end points are found or not */
   unsigned distance = 10; /**< Tells how far points are tried to find */
   unsigned end_x; /**< x coordinate of the end point */
   unsigned end_y; /**< y coordinate of the end point */
   QGraphicsEllipseItem *end_circle = nullptr; /**< Circle drawn to the end points */

 };

/**
  *   @struct X_Y_Coordinates
  *   @brief Struct that contains x and y coordinates
  *   @details Used with LookEndPoints
  */
 struct X_Y_Coordinates
 {
   int x = -1; /**< x coordinate */
   int y = -1; /**< y coordinate */
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
   *   @brief Macro for bezier mode
   */
 #define bezier_mode_value 6

/**
  *   @brief Macro for text mode
  */
 #define text_mode_value 7

/**
  *   @brief Macro for Bezier control point circle diameter
  */
#define Control_point_circle_diameter 30

/**
  *   @brief Macro for BezierMode lock_mode
  *   @details During this mode moving control points which are joined to an end
  *   point isn't allowed
  */
#define Bezier_option_partially_locked 1

/**
  *   @brief Macro for BezierMode lock_mode
  *   @details During this mode the first control point cannot be moved
  */
#define Bezier_option_locked 2

/**
  *   @brief Macro for BezierMode lock_mode
  *   @details During this mode the first control point can be always moved
  */
#define Bezier_option_unlocked 3




 /**
   *    @class OwnGraphicsScene
   *    @brief Own QGraphicsScene implementation
   *    @details This is an implementation for own QGraphicsScene which
   *    overloads mousePressEvent to update the scene
   */


 class OwnGraphicsScene : public QGraphicsScene
 {
  Q_OBJECT
  public:
    static bool END_POINTS_ACTIVE; /**< Whether items end points are shown */
    static QColor SpecialColor; /**< Color used with special items (End points circles) */

  /**
    *   @brief Constructor for OwnGraphicsScene
    *   @param parent The QWidget parent
    *   @details Sets standard size for the view rect
    */
   OwnGraphicsScene(QWidget *parent);

  /**
    *   @brief Destructor for OwnGraphicsScene
    */
   ~OwnGraphicsScene();

  /**
    *   @brief Overload for mousePressEvent
    *   @details Used to add new items to the scene, also  to remove and cut
    *   old items
    */
   virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /**
    *   @brief Overload for mouseMoveEvent
    *   @details Used to track user mouse when creating lines and cutting
    *    images
    */
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

   /**
     *   @brief Overload for keyPressEvents
     *   @param keyEvent Key event
     */
   virtual void keyPressEvent(QKeyEvent *keyEvent);

  /**
    *   @brief Overload for mouseReleaseEvent
    *   @param event mouseReleaseEvent
    */
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

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
    *   @brief Activate text_mode
    *   @param activate Activate / deactivate TextMode
    */
   void TextMode(bool activate);

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
    *   @brief Update END_POINTS_ACTIVE value
    *   @param value New END_POINTS_ACTIVE value matching combobox options
    */
   void setEndPointsActive(int value);

  /**
    *   @brief Removes all temporary visual_items
    *   @details Called after image cut is ready
    */
   void ClearVisualItems();

  /**
    *   @brief Activates/deactivates bezier mode
    */
   void BezierMode(bool active);

  /**
    *   @brief Constructs a Bezer object
    *   @param x Mouse x coordinate
    *   @param y Mouse y coordinate
    *   @param point_added Which point user moved, 0 means construct new Bezier
    */
   void CreateBezier(unsigned x, unsigned y, int point_added);

  /**
    *   @brief Add Bezier to the scene
    *   @details To be more precise adds the LineItems matching the Bezier (line_items)
    *   to the scene
    *   @param bezier Pointer to Bezier which is added to the scene
    */
   void AddBezier(Bezier *bezier);

  /**
    *   @brief Remove Bezier from the scene
    *   @details Removes the LineItems matching the Bezier and then deletes the object itself
    *   @param bezier Pointer to the Bezier to be removed
    */
   void RemoveBezier(Bezier *bezier);

/**
  *   @brief Create circles matching the bezier control points
  *   @param point Which circle needs to be created
  *   @remark point 0 -> create all circles, point 1 -> create circle 1 etc.
  */
  void CreateControlPointCircles(int point);

  /**
    *   @brief Remove circles matching the bezier control points
    *   @param point Which circle needs to be removed
    *   @remark point 0 -> remove all circles, point 1 -> remove circle 1 etc.
    */
  void RemoveControlPointCircles(int point);

/**
  *   @brief Convert control point coordinates to circle left top corner point
  *   @param point Vector2 containing control point
  *   @return Returns circle point as a Vector2 object
  */
  Vector2 ControlPoint2Circle(Vector2 point);

/**
  *   @brief Check whether mouse is inside control points or not
  *   @param x Mouse x coordinate
  *   @param y Mouse y coordinate
  *   @return Returns 0 if not inside, else returns point number which is inside
  *   @remark Goes through control points in reverse order so that point 0
  *   remains starting point and point 4 end point
  */
  int isInsideControlPoint(unsigned x, unsigned y);

/**
  *   @brief Try to find end points that match mouse position
  *   @param x Mouse x coordinate
  *   @param y Mouse y coordinate
  *   @return Returns X_Y_Coordinates which contain end point
  *   @details If no end point matches, returns negative coordinates
  */
  struct X_Y_Coordinates LookEndPoints(unsigned x, unsigned y);

/**
  *   @brief Remove an end point
  *   @details End point is removed from end_points_dict. This method should
  *   be called when LineItem or Bezier is removed from the scene. Removes only
  *   one end point matching x and y
  *   @param x Item x coordinate
  *   @param y Item y coordinate
  */
  void RemoveEndPoint(unsigned x, unsigned y);


/**
  *   @brief Add an end point
  *   @details End point is added to end_points_dict. This method should
  *   be called when LineItem or Bezier is created and added to the scene
  *   @param x Item x coordinate
  *   @param y Item y coordinate
  */
  void AddEndPoint(unsigned x, unsigned y);

/**
  *   @brief Update End_Points
  *   @details Checks if mouse is over an end point and possibly draws a
  *   circle representing the end point. Updates also end_y and end_x values
  *   @param x Current mouse x coordinate
  *   @param y Current mouse y coordinate
  *   @remark Depends heavily on LookEndPoints
  *   @bug Cannot find end points which x or y coordinate is 0
  */
  void UpdateEndPoints(unsigned x, unsigned y);

/**
  *   @brief Remove old end_circle from End_Points struct
  *   @remark Does nothing if the circle is nullptr
  */
  void RemoveEndPointCircle(void);

/**
  *   @brief Add parent OwnGraphicsView
  *   @details After this it's possible to send signals to the view. The view
  *   must be added right after creating it
  *   @param view OwnGraphicsView parent view
  */
  void addView(OwnGraphicsView *view);

/**
  *   @brief Set mouse tracking on or off
  *   @details Sends signal to parent_view to enable or disable mouse tracking
  *   @param enable true -> enable, false -> disable
  */
  void mouse_tracking(bool enable);


/**
  *   @brief Update Bezier_Mode lock_mode
  *   @details Called from GUI when when user has changed BezierToolbar options
  *   @param option New value for lock_mode
  *   @remark Works only if option is a valid lock_mode
  */
  void modifyBezierOptions(int option);

/**
  *   @brief Remove current Bezier
  *   @details Called from GUI, BezierToolbar_Remove
  */
  void EraseBezier();

/**
  *   @brief Stop editing bezier and save it
  *   @details Called from GUI, BezierToolbar_SaveBezier
  */
  void BezierReady();

/**
  *   @brief Cut image according to selected path
  *   @remark Called from GUI when pathcutToolbar continue button is pressed
  */
  void pathImageCut();

/**
  *   @brief Change scene backgroundcolor
  *   @param color New backgroundcolor
  */
  void changeBackgroundColor(const QColor &color);

signals:

/**
  *   @brief Used to enable/disable mouse tracking from parent_view
  */
  void switch_mouse_tracking(bool enable);


private:

/**
  *   @brief Add QGraphicsTextItem
  *   @param x x coordinate
  *   @param y y coordinate
  */
  void addTextItem(unsigned x, unsigned y);

/**
  *   @brief Move current_text
  *   @param x New x coordinate
  *   @param y New y coordinate
  */
  void moveTextItem(unsigned x, unsigned y);

/**
  *   @brief Enable text item editing
  *   @details Goes through all text_items and enables item editing if there is an
  *   item at (x,y). Sets item to current_text
  *   @param x x coordinate
  *   @param y y coordinate
  */
  void enableTextEditing(unsigned x, unsigned y);

/**
  *   @brief Deactivate all text_items
  *   @remark This should be used when user moves out of text_mode
  */
  void deactivateTextItems();

  /*  Variables */
   OwnGraphicsView *parent_view;
   std::list <LineItem*> line_items;
   std::deque <PixmapItem*> pixmap_items;
   std::list <Bezier*> beziers;
   std::deque <TextItem*> text_items;
   TextItem *current_text = nullptr;
   unsigned mouse_x;
   unsigned mouse_y;
   bool first_line = true;
   struct Line_Mode line_struct;
   unsigned char mode = line_mode_value;
   struct Image_Active image_active;
   QPixmap image = QPixmap(); // construct a Null pixmap
   QString current_imagename;
   struct Image_Cut image_cut;
   struct Bezier_Mode bezier_struct;
   struct End_Points end_points_struct;
   std::map<unsigned, std::list<unsigned> > end_points_dict; /**< Dictionary
   where end points are stored with x coordinate as key and then list of y coordinates */

 };
