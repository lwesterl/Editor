/**
  *   @file TextItem.hpp
  *   @brief Simple reimplementation of QGraphicsTextItem
  */

#pragma once

#include <QGraphicsTextItem>
#include <QString>
#include <QColor>
#include <QPointF>
#include <QGraphicsSceneContextMenuEvent>

/**
  *   @class TextItem
  *   @brief QGraphicsTextItem inherited class
  *   @details TextItem reimplementations couple QGraphicsTextItem methods and adds wrappers
  */

class TextItem: public QGraphicsTextItem
{
  public:
    static QColor TextColor; /**< Member for Text color used */
    /**
      *   @brief Constructor
      *   @param text Default text used
      */
    TextItem(QString text);

    /**
      *   @brief Simple wrapper which calls protected and inherited keyPressEvent
      *   @details This wrapper is needed because keyPresses are transfered via OwnGraphicsScene
      *   @param keyEvent keyPressEvent
      */
    void KeyEventWrapper(QKeyEvent *keyEvent);

    /**
      *   @brief Wrapper call for QGraphicsTextItem contains
      *   @param x Scene x coordinate
      *   @param y Scene y coordinate
      *   @return Returns true if coordinate is inside the item
      */
    bool isInside(unsigned x, unsigned y);

    /**
      *   @brief Activate item
      *   @details If the item is already activated -> deactivates it
      *   @remark This method should be called from OwnGraphicsScene after the item is clicked with left mouse
      *   @return Returns activated
      */
    bool activateItem();

    /**
      *   @brief Deactivate TextItem
      */
    void deactivateItem();

  private:

    /**
      *   @brief Overload for contextMenuEvent
      *   @details TextItem doesn't want to show contextMenu
      */
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    /**
      *   @brief Overload for mousePressEvent
      *   @details TextItem mouse presses should be handled by OwnGraphicsScene not by the item itself
      */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*  Variables */
    bool activated = false;
};
