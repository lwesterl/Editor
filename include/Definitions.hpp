/**
  *   @file Definitions.hpp
  *   @brief Header data handling related enums and maps
  */

#pragma once

#include <map>
#include <QString>

/**
  *   @namespace Editor
  *   @brief NameSpace for enums GUI uses
  */
namespace Editor
{

  /**
    *   @enum ColorSetting
    *   @brief Tells which color colorDialog changes
    */
  enum ColorSetting
  {
    SceneColor,
    HighlightColor,
    LineColor,
    SpecialColor,
    TextColor
  };

  /**
    *   @enum ConnectPoint
    *   @brief Tells where PixmapItem path cut connects (which edge of the item)
    */
  enum ConnectPoint
  {
    ConnectHeight,
    ConnectZero,
    ConnectCenter
  };
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


/**
  *   @namespace Path
  *   @brief Namespace for all paths
  */
namespace Path
{
  /**
    *   @enum ImageName
    *   @brief Enum for all image names used in GUI
    */
  enum ImageName
  {
    exit_img,
    open_img,
    save_img,
    draw_line_img,
    delete_line_img,
    text_item_img,
    clear_all_img,
    image_sketch_img,
    image_delete_img,
    image_cut_img,
    continue_img,
    cancel_img,
    finish_img,
    remove_point_img,
    bezier_pic_img,
    save_button_img,
    bezier_remove_img
  };

  extern std::map<ImageName, QString> Images; /**< Map from enum value to correct image path */
  extern std::map<Editor::ColorSetting, QString> ColorFiles; /**< Map from enum value to correct file path */
}
