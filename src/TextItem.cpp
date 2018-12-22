/**
  *   @file TextItem.cpp
  *   @brief Source code for class TextItem
  */

#include "../include/TextItem.hpp"

/*  Class TextItem */

QColor TextItem::TextColor = Qt::black;

/*  Constructor */
TextItem::TextItem(QString text): QGraphicsTextItem(text)
{
  // change text color to match the member variable
  setDefaultTextColor(TextColor);
  // set correct starting flags
  setTextInteractionFlags(Qt::NoTextInteraction);
  setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}

/*  Public wrapper call for keyEvents */
void TextItem::KeyEventWrapper(QKeyEvent *keyEvent)
{
  keyPressEvent(keyEvent);
}

/*  Is item inside */
bool TextItem::isInside(unsigned x, unsigned y)
{
  QPointF point = QPointF(static_cast<float> (x), static_cast<float> (y));
  return contains(mapFromScene(point));
}

/*  Overload for contextMenuEvent */
void TextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
  // no context menu is shown
  event->accept();
}

void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
}

/*  Activate / deactivate item */
bool TextItem::activateItem()
{
  if (!activated)
  {
    setTextInteractionFlags(Qt::TextEditable);
    setFocus();
    activated = true;
  }
  else
  {
    deactivateItem();
  }
  return activated;
}

/*  Deactivate TextItem */
void TextItem::deactivateItem()
{
  // deactivate
  setTextInteractionFlags(Qt::NoTextInteraction);
  clearFocus();
  activated = false;
}
