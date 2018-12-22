/**
  *   @file Definitions.hpp
  *   @brief Header data handling related enums and maps
  */

#pragma once

#include <map>

namespace Editor
{

};

/**
  *   @namespace Scene
  *   @brief NameSpace for enums used in OwnGraphicsScene
  */
namespace Scene
{

  extern const int Control_point_circle_diameter; /**< Tells Bezier control point circle diameter */


  /**
    *   @enum ImageCutMode
    *   @brief Enum for different image cut modes, used in OwnGraphicsScene
    */
  enum ImageCutMode
  {
    no_img_cut,
    polygon_img_cut,
    path_img_cut
  };

  /**
    *   @enum Mode
    *   @brief Enum for different OwnGraphicsScene operating modes
    *   @details Every operation (adding lines, removing items etc.) has its own mode
    */
  enum Mode
  {
    view_mode_value,
    line_mode_value,
    delete_mode_value,
    image_mode_value,
    delete_img_mode_value,
    cut_image_mode_value,
    bezier_mode_value,
    text_mode_value
  };

  /**
    *   @enum BezierLockMode
    *   @brief Tells when Bezier start point should be locked
    */
  enum BezierLockMode
  {
    partially_locked,
    locked,
    unlocked
  };
};
