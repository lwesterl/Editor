#include "owngraphicsscene.hpp"



OwnGraphicsScene::~OwnGraphicsScene()
{
  // remove list objects
  for (auto it = line_items.begin(); it !=line_items.end();)
  {
    it = line_items.erase(it);
  }
  for (auto it = pixmap_items.begin(); it != pixmap_items.end();)
  {
    it = pixmap_items.erase(it);
  }
  clear();
}

void OwnGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent  *event)
{
  // Convert point to scene coordinates
  QPointF point = event->scenePos();
  unsigned x_new = point.x();
  unsigned y_new = point.y();

  // Add a line from previous points if line adding mode activated
  if (mode == line_mode_value)
  {
    if (first_line)
    {
      // no previous points
      first_line = false;
    }
    else
    {
      addLine(mouse_x, mouse_y, x_new, y_new);
    }

    // reassign mouse_x and mouse_y
    mouse_x = x_new;
    mouse_y = y_new;
    qDebug() << "Clicked\n" << "X: " << mouse_x << "Y: " << mouse_y;
  }
  else if (mode == delete_mode_value)
  {
    // Remove the elent user clicked
    remove_Item(x_new, y_new);
  }

  else if (mode == image_mode_value)
  {
    if (image_active.clicks == 0)
    {
      // add a new image to the scene
      image_active.pixmap_item = new PixmapItem(image, current_imagename);
      addItem(image_active.pixmap_item);
      // add item also to the pixmap_items list
      pixmap_items.push_back(image_active.pixmap_item);
      image_active.added_scene = true;
      image_active.clicks = 1;
    }
    else if (image_active.clicks == 1)
    {
      // user wants to place the image
      // init values for a new image ready to be placed
      image_active.added_scene = false;
      image_active.clicks = 0;

    }

  }
  else if (mode == delete_img_mode_value)
  {
    // try to delete the PixmapItem user clicked
    DeleteImg(x_new, y_new);
  }
}

// Move image according to user mouse movements
void OwnGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (mode == image_mode_value)
  {
    // user is moving the image
    if (image_active.added_scene)
    {
      // convert mouse coordinates to scene position
      QPointF point = event->scenePos();
      unsigned x_new = point.x();
      unsigned y_new = point.y();

      // move the image accordinly
      // mouse tells x1 and y1 positions so upper left corner
      image_active.pixmap_item->setPos(x_new, y_new);
      // add position also to the item itself
      image_active.pixmap_item->setX(x_new);
      image_active.pixmap_item->setY(y_new);
    }

  }
}

// This method goes throw OwnGraphicsScene items and tries to remove item
// at location x , y
void OwnGraphicsScene::remove_Item(unsigned x, unsigned y)
{
  for (std::list<LineItem*>::iterator it = line_items.begin(); it != line_items.end(); it++)
  {
    // remove list item if coordinates match
    if ( ( ((*it)->getX1() <= x ) && ((*it)->getX2() >= x) ) ||
      ( ((*it)->getX1() >= x ) && ((*it)->getX2() <= x) ) )

    {
      if ( ( ((*it)->getY1() >= y) && ((*it)->getY2() <= y) ) ||
      ( ((*it)->getY1() <= y) && ((*it)->getY2() >= y) ) )

      {
        // Item found, remove it
        removeItem(*it); // remove from the scene
        line_items.remove(*it);
        delete(*it);
        break;
      }
    }

  }
}


// This adds a line to the graphics scene

void OwnGraphicsScene::addLine(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
  //QGraphicsLineItem *line = new QGraphicsLineItem(x1, y1, x2, y2);
  LineItem *line = new LineItem(x1, y1, x2, y2);
  // Add item to the scene and line items list
  addItem(line);
  line_items.push_back(line);
}


// Swap to the line mode
void OwnGraphicsScene::LineMode(bool activate)
{

  if (activate)
  {
    qDebug() << "LineMode actived\n";
    /*line_mode = true;
    delete_mode = false;
    image_active.image_mode = false;
    delete_img_mode = false;
    cut_image_mode = false;*/
    mode = line_mode_value;
  }
  else mode = view_mode_value;
}

// Swap to the delete mode
void OwnGraphicsScene::DeleteMode(bool activate)
{
  if (activate)
  {
    qDebug() << "DeleteMode actived\n";
    /*delete_mode = true;
    line_mode = false;
    image_active.image_mode = false;
    delete_img_mode = false;
    cut_image_mode = false;*/
    mode = delete_mode_value;
  }
  else mode = view_mode_value;
}

void OwnGraphicsScene::ClearMode()
{
  first_line = true;
}

// Remove & delete all scene objects

void OwnGraphicsScene::ClearAll()
{
  // Init first line
  first_line = true;

  // remove list objects
  for (auto it = line_items.begin(); it !=line_items.end();)
  {
    it = line_items.erase(it);
  }

  // clear all pixmap_items
  for (auto it = pixmap_items.begin(); it != pixmap_items.end();)
  {
    it = pixmap_items.erase(it);
  }

  clear(); // removes all objects and deletes them


}


//Construct a QPixmap from an image
bool OwnGraphicsScene::setImage(QString imagename)
{
  image = QPixmap(imagename);
  if (image.isNull())
  {
    // pixmap NUll so failed to open image
    return false;
  }
  current_imagename = imagename;
  return true;
}


// Enable or disaple imgMode based on activate
// Also don't activate img mode if the image can't be added (inform gui)
bool OwnGraphicsScene::imgMode(bool activate)
{
  if (activate == false)
  {
    //image_active.image_mode = false;
    mode = view_mode_value;
    return false;
  }

  /*line_mode = false;
  delete_mode = false;
  delete_img_mode = false;
  cut_image_mode = false;*/

  // test if image can be added
  if (image.isNull())
  {
    // can't add the image
    mode = view_mode_value;
    return false;
  }

  // update mode status
  mode = image_mode_value;

  return true;
}

void OwnGraphicsScene::DeleteImgMode(bool activate)
{
  if (activate)
  {
    // enable delete_img_mode and disaple other modes
    /*delete_img_mode = true;
    line_mode = false;
    delete_mode = false;
    image_active.image_mode = false;
    cut_image_mode = false;*/
    mode = delete_img_mode_value;
  }
  else
  {
    mode = view_mode_value;
  }

}


// try to delete image at x1, y1

void OwnGraphicsScene::DeleteImg(unsigned x1, unsigned y1)
{
  for (std::list <PixmapItem*>::iterator it = pixmap_items.begin(); it != pixmap_items.end(); it++)
  {
    if ((*it)->isXinside(x1) && (*it)->isYinside(y1))
    {
      // item found at clicked position
      // remove item from the scene
      removeItem(*it);
      // remove item from the list and delete it
      pixmap_items.remove(*it);
      delete(*it);
      break;
    }
  }
}

// Activate cut_image_mode
void OwnGraphicsScene::CutImageMode(bool activate)
{
  image_active.clicks = 0;
  if (activate)
  {
    mode = cut_image_mode_value;
    image_active.pixmap_item = nullptr;
  }
  else
  {
    // clear points vector if current pixmap exists
    if (image_active.pixmap_item != nullptr)
    {
      image_active.pixmap_item->clearPointsVector();
    }
    mode = view_mode_value;
  }
}
