/**
  *   @file Bezier.cpp
  *   @author Lauri Westerholm
  *   @brief Contains Bezier class related functions
  */

#include "../include/Bezier.hpp"


/**
  *   @brief Lerp function
  *   @details Calculates linear vector interpolation
  */
Vector2 Lerp(Vector2 a, Vector2 b, float t)
{
  return (1.0 - t) * a + t * b;
}

/*  Create a part of bezier curve */

Vector2 createBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t)
{
  float u = 1.00 - t;
  float t2 = t * t;
  float u2 = u * u;
  float u3 = u2 * u;
  float t3 = t2 * t;

  Vector2 result = u3 * p0 + (3.00 * u2 * t) * p1 + (3.00 * u * t2) * p2 +
                  t3 * p3;

  return result;
}


/*  Bezier constructor */

Bezier::Bezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
{
  for (float t = 0; t < 1; t += BECIER_INTERVAL)
  {
    Vector2 vect2 = createBezier(p0, p1, p2, p3, t);
    vectors.push_back(vect2);
  }

  // Add LineItems
  int prev_x = -1;
  int prev_y = -1;

  for (auto it = vectors.begin(); it != vectors.end(); it++)
  {
    if (prev_x > 0)
    {
      // Connect the start and end points of the item
      LineItem *item = new LineItem((unsigned) prev_x, (unsigned) prev_y, it->getX(), it->getY());
      line_items.push_back(item);
    }
    // Update prev_x and prev_y
    prev_x = it->getX();
    prev_y = it->getY();
    //qDebug() << "X: " << prev_x << " Y: " << prev_y << "\n";
  }
}

/* Bezier deconstructor */
Bezier::~Bezier()
{
  // Delete all LineItems
  for (auto it = line_items.begin(); it != line_items.end(); it++)
  {
    delete(*it);
  }
  line_items.clear();
}

/*  Return the last x coordinate */
float Bezier::getEndX()
{
  if (!vectors.empty())
  {
    return vectors.back().getX();
  }
  return -1;
}

/*  Return the last y coordinate */
float Bezier::getEndY()
{
  if (!vectors.empty())
  {
    return vectors.back().getY();
  }
  return -1;
}

/*  Return the first x coordinate */
float Bezier::getStartX()
{
  if (!vectors.empty())
  {
    return vectors.front().getX();
  }
  return -1;
}

/*  Return the first y coordinate */
float Bezier::getStartY()
{
  if (!vectors.empty())
  {
    return vectors.front().getY();
  }
  return -1;
}

/*  Check if position is inside */
bool Bezier::isInside(unsigned x, unsigned y)
{
  // go through all the LineItems
  for (auto &line : line_items)
  {
    if (line->isInside(x, y)) return true;
  }
  return false;
}
