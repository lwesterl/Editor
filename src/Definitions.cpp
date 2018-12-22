/**
  *   @file Definitions.cpp
  *   @brief Contains data handling related enums and maps
  */

#include "../include/Definitions.hpp"


namespace Scene
{
  const int Control_point_circle_diameter = 30;
};


namespace Path
{
  std::map<ImageName, QString> Images
  {
    { ImageName::exit_img, "data/img/exit.png" },
    { ImageName::open_img, "data/img/open.png" },
    { ImageName::save_img, "data/img/save.png" },
    { ImageName::draw_line_img, "data/img/draw_line.png" },
    { ImageName::delete_line_img, "data/img/delete_line.png" },
    { ImageName::text_item_img, "data/img/text_item.png" },
    { ImageName::clear_all_img, "data/img/clear_all.png" },
    { ImageName::image_sketch_img, "data/img/image_sketch.png" },
    { ImageName::image_delete_img, "data/img/image_delete.png" },
    { ImageName::image_cut_img, "data/img/image_cut.png" },
    { ImageName::continue_img, "data/img/continue.png" },
    { ImageName::cancel_img, "data/img/cancel.png" },
    { ImageName::finish_img, "data/img/finish.png" },
    { ImageName::remove_point_img, "data/img/remove_point.png" },
    { ImageName::bezier_pic_img, "data/img/bezier_pic.png" },
    { ImageName::save_button_img, "data/img/save_button.png" },
    { ImageName::bezier_remove_img, "data/img/bezier_remove.png" }
  };

  std::map<Editor::ColorSetting, QString> ColorFiles
  {
    { Editor::ColorSetting::SceneColor, "data/config/SceneColor.dat" },
    { Editor::ColorSetting::HighlightColor, "data/config/HighlightColor.dat" },
    { Editor::ColorSetting::LineColor, "data/config/LineColor.dat" },
    { Editor::ColorSetting::SpecialColor, "data/config/SpecialColor.dat" },
    { Editor::ColorSetting::TextColor, "data/config/TextColor.dat" }
  };
};
