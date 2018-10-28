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
      line_struct.prev_x = x_new;
      line_struct.prev_y = y_new;
      first_line = false;
    }
    else if (line_struct.created)
    {
      // user has set the final position for the line
      // set previous points to the current item end coordinates
      line_struct.prev_x = line_struct.line_item->getX2();
      line_struct.prev_y = line_struct.line_item->getY2();
      line_struct.positioned = true;
      line_struct.created = false;
      if (!connect_lines)
      {
        // reset first_line to true not to connect lines
        first_line = true;
      }
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

  else if (mode == cut_image_mode_value)
  {
    if (image_cut.initialized == false)
    {
      // store the point
      image_cut.point = QPoint(x_new, y_new);
    }
    else if (image_cut.initialized && (image_cut.cut_mode == polygon_img_cut))
    {
      // Polygon cut activated
      // Add a new point
      image_cut.pixmap_item->addPainterPoint(x_new, y_new);
    }
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
  else if (mode == line_mode_value)
  {
    if (first_line == false)
    {
      // convert mouse coordinates to a scene position
      QPointF point = event->scenePos();
      unsigned x_new = point.x();
      unsigned y_new = point.y();
      if (line_struct.created)
      {
        // Don't create a new item , move previosly created
        if (connect_lines)
        {
          // connect item to the last one
          line_struct.line_item->setLine(line_struct.prev_x, line_struct.prev_y, x_new, y_new);
        }
        else
        {
          // don't connect to the prev item
          line_struct.line_item->setLine(mouse_x, mouse_y, x_new, y_new);
        }
        line_struct.line_item->updatePosition(x_new, y_new);
      }
      else
      {
        // create a new line_item
        if (connect_lines)
        {
          // connect item to the last item
          line_struct.line_item = addLine(line_struct.prev_x, line_struct.prev_y, x_new, y_new);
        }
        else
        {
          // create a complitely new element without connection to the previous one
          line_struct.line_item = addLine(mouse_x, mouse_y, x_new, y_new);
        }

        line_struct.created = true;
        line_struct.positioned = false;
      }

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

LineItem* OwnGraphicsScene::addLine(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
  //QGraphicsLineItem *line = new QGraphicsLineItem(x1, y1, x2, y2);
  LineItem *line = new LineItem(x1, y1, x2, y2);
  // Add item to the scene and line items list
  addItem(line);
  line_items.push_back(line);
  return line;
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
  else
  {
    mode = view_mode_value;
    // Clear the line_struct if item created
    if (line_struct.created)
    {
      line_struct.prev_x = line_struct.line_item->getX2();
      line_struct.prev_y = line_struct.line_item->getY2();
      line_struct.line_item = nullptr;
      line_struct.created = false;
      line_struct.positioned = true;
    }


    /*if (line_struct.created && !line_struct.positioned)
    {
      // remove the last item from the scene
      removeItem(line_struct.line_item);
      // remove the excessive LineItem from the end of the list
      line_items.pop_back();
      delete(line_struct.line_item);
    }*/
  }
}

// Swap to the delete mode
void OwnGraphicsScene::DeleteMode(bool activate)
{
  if (activate)
  {
    qDebug() << "DeleteMode actived\n";
    // enable delete mode
    mode = delete_mode_value;

    // store the (current) item if created
    if (line_struct.created)
    {
      line_struct.prev_x = line_struct.line_item->getX2();
      line_struct.prev_y = line_struct.line_item->getY2();
      line_struct.positioned = true; // now the item isn't overwritten
      line_struct.created = false;
    }

  }
  else mode = view_mode_value;
}

void OwnGraphicsScene::ClearMode()
{
  // store the (current) item
  line_struct.positioned = true; // now the item isn't overwritten
  line_struct.created = false;
  first_line = true;
}

// Remove & delete all scene objects

void OwnGraphicsScene::ClearAll()
{
  // Init first line
  first_line = true;
  // init line_struct
  line_struct.created = false;
  line_struct.line_item = nullptr;

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
  if (activate)
  {
    mode = cut_image_mode_value;
  }
  else
  {
    // clear points vector if current pixmap exists
    if (image_cut.initialized)
    {
      image_cut.pixmap_item->clearPointsVector();
      image_cut.pixmap_item = nullptr; // dont't delete original pointer
      image_cut.initialized = false;
      image_cut.cut_mode = no_img_cut;
      // clear also the point by constructing a null point
      image_cut.point = QPoint();
    }
    mode = view_mode_value;
  }
}

// Try to select the image which user pointed
// return true if image exists
// return false if it doesn't exists
// called from GUI::ContinueFromSelect

bool OwnGraphicsScene::SelectCutImg()
{
  // img_cut.point should now contain coordinates for an image
  // iterate all pixmap items and try to get the matching pixmap
  // This cannot handle multiple imaged at same position (selects the first created)

  for (auto it = pixmap_items.begin(); it != pixmap_items.end(); it++)
  {
    if ((*it)->isXinside(image_cut.point.x()) && (*it)->isYinside(image_cut.point.y()))
    {
      // The matching image found
      image_cut.pixmap_item = *it;
      image_cut.initialized = true;
      return true;
    }
  }
  // no matching image found
  return false;

}

// Assign correct cut_mode
// Called by GUI::ContinueFromMode
// (GUI checks that the cut_mode valid)
void OwnGraphicsScene::SetImgCutMode(int cut_mode)
{
  if (cut_mode == 1)
  {
    image_cut.cut_mode = polygon_img_cut;
  }
  else if (cut_mode == 2)
  {
    image_cut.cut_mode = path_img_cut;
  }
}

// This is just a wrapper call for PixmapItem::CutItem
void OwnGraphicsScene::CutPixmapItem()
{
  // Cut the item
  image_cut.pixmap_item->CutItem();
}

// Just a wrapper call for PixmapItem::RemoveLatestPoint
void OwnGraphicsScene::RemovePolyPrevious()
{
  image_cut.pixmap_item->RemoveLatestPoint();
}

// Set correct connect_lines value based on input value
void OwnGraphicsScene::setConnectLines(int value)
{
  if (value == 0)
  {
    connect_lines = true;
  }
  else connect_lines = false;

}
