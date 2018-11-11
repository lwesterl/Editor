/**
  *   @file gui.cpp
  *   @author Lauri Westerholm
  *   @brief Contains GUI class
  */



#include "../include/gui.hpp"





// Implementation of GUI class
// first init base class
GUI::GUI(QWidget *parent): QMainWindow(parent)
{

  this->setWindowTitle ("Editor");
  setContextMenuPolicy(Qt::NoContextMenu); // don't allow clicking toolboxes


  // create a file options menu
  QMenu *file_options;
  file_options = menuBar()->addMenu("&File");

  // create a quit action
  QPixmap quit_pic(exit_img);
  QPixmap save_pic(save_img);
  QPixmap open_pic(open_img);
  QAction *save = new QAction(save_pic, "&Save", this);
  QAction *open = new QAction(open_pic, "&Open", this);
  QAction *quit_option = new QAction(quit_pic, "&Quit", this);
  file_options->addAction(save);
  file_options->addAction(open);
  file_options->addSeparator();
  file_options->addAction(quit_option);
  connect(quit_option, &QAction::triggered, qApp, &QApplication::quit);
  connect(save, &QAction::triggered, this, &GUI::saveImage);
  connect(open, &QAction::triggered, this, &GUI::openImage);

  // create options menu
  QMenu *options;
  options = menuBar()->addMenu("&Options");
  // Add a ComboboxAction
  line_options_combo = new ComboboxAction("New lines connect to previous one: ");
  options->addAction(line_options_combo);
  // Add a save choices
  QAction *save_choices = new QAction("Save choices");
  options->addAction(save_choices);
  // connect the action
  connect(save_choices, &QAction::triggered, this, &GUI::SaveChoices);





  // create all toolbars
  createToolbars();


  //add_lower_toolbar->setVisible(false);
  //lToolbar.lower_toolbar->toggleViewAction()->setChecked(false)->trigger();
  //toggle_lower_toolbar->setChecked(true);


  //test


  //QPixmap quit_pic("exit.png");
  //QAction *quit = toolbar->addAction(QIcon(quit_pic),"Quit");
  //connect(quit, &QAction::triggered, qApp, &QApplication::quit);

  // MainWidget

  mainWidget = new MainWidget(this);
  this->setCentralWidget(mainWidget);
  mainWidget->InitScrollBar();
  //h_layout = new QHBoxLayout();
  //mainWidget->setLayout(h_layout);
  //mainWidget->set_Layout(new QHBoxLayout());

  // create QGraphicsScene
  //scene = new QGraphicsScene(this);
  //scene = new QGraphicsScene(mainWidget);
  //mainWidget->set_Scene(new QGraphicsScene(mainWidget));
  //mainWidget->set_Scene(new OwnGraphicsScene(mainWidget));

  // create a view for it and add the view to the layout
  //view = new QGraphicsView(scene, mainWidget);
  //mainWidget->set_View(new QGraphicsView(mainWidget->getScene(), mainWidget));
  //h_layout->addWidget(view);
  //mainWidget->getLayout()->addWidget(mainWidget->getView());

  // make the view central widget
  //this->setCentralWidget(view);



}


void GUI::LineMode()
{

  if (line_mode->isChecked())
  {
    // Set off other modes and activate line mode
    mainWidget->getScene()->LineMode(true);
    delete_mode->setChecked(false);
    add_img_mode->setChecked(false);
    delete_img_mode->setChecked(false);
    cut_image_mode->setChecked(false);
    bezier_mode->setChecked(false);
  }
  else
  {
    mainWidget->getScene()->LineMode(false);
  }
}

void GUI::DeleteMode()
{
  if (delete_mode->isChecked())
  {
    // Set off other modes and activate delete mode
    mainWidget->getScene()->DeleteMode(true);
    line_mode->setChecked(false);
    add_img_mode->setChecked(false);
    delete_img_mode->setChecked(false);
    cut_image_mode->setChecked(false);
    bezier_mode->setChecked(false);
  }
  else
  {
    mainWidget->getScene()->DeleteMode(false);
  }

}

// Trigger clear mode
void GUI::ClearMode()
{
  mainWidget->getScene()->ClearMode();
}

// Clear whole scene
void GUI::ClearAll()
{
  mainWidget->getScene()->ClearAll();
}

// Save scene to an image

void GUI::saveImage()
{
  OwnGraphicsScene *scene = mainWidget->getScene();

  //scene->clearSelection();
  //scene->setSceneRect(scene->itemsBoundingRect());
  QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::transparent);

  QPainter painter (&image);
  scene->render(&painter);

  // create a file dialog for user to save the image
  QFileDialog dialog (this);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setFileMode(QFileDialog::AnyFile);
  dialog.setNameFilter(tr("Images (*.jpeg *.png)"));
  if (dialog.exec())
  {
    QStringList names = dialog.selectedFiles();
    // try to save the image
    bool ret = image.save(names[0]);

    if (ret)
    {
      // saved
      QMessageBox::information(this, "Information", "Image saved successfully!");
    }
    else
    {
      QMessageBox::warning(this, "Warning", "Image saving failed!");
    }
  }



}

// Load an image for the scene
void GUI::openImage()
{
  // Create a QFileDialog
  QString imagename = QFileDialog::getOpenFileName(this, tr("Open image"),QDir::currentPath(), tr("*.png *.jpg "));
  bool ret = mainWidget->getScene()->setImage(imagename);
  if (ret == true)
  {
    // image opened successfully
    // inform user
    QMessageBox::information(this,"Information", "Image loaded successfully!");
  }
  else
  {
    QMessageBox::warning(this, "Warning", "Image loading failed!");
  }

}

// Check if image_add mode activated or stopped
// If activated, test if image can be added to the scene (calls scene imgMode)
// If image not possible to add, informs user
void GUI::ImgMode()
{
  if (add_img_mode->isChecked())
  {
    bool ret = mainWidget->getScene()->imgMode(true);
    if (ret == false)
    {
      // deactivate mode button
      add_img_mode->setChecked(false);
      QMessageBox::information(this, "Information", "Load an image first!");
    }
    // image mode activated
    // deactivate other modes
    line_mode->setChecked(false);
    delete_mode->setChecked(false);
    delete_img_mode->setChecked(false);
    cut_image_mode->setChecked(false);
    bezier_mode->setChecked(false);
  }
  else
  {
    // deactivate image mode
    mainWidget->getScene()->imgMode(false); // no need to check the return value
  }

}

// Delete images, activates the delete img mode in the scene
void GUI::DeleteImgMode()
{
  if (delete_img_mode->isChecked())
  {
    // set other modes off
    line_mode->setChecked(false);
    delete_mode->setChecked(false);
    add_img_mode->setChecked(false);
    cut_image_mode->setChecked(false);
    bezier_mode->setChecked(false);
    mainWidget->getScene()->DeleteImgMode(true);
  }
  else
  {
    mainWidget->getScene()->DeleteImgMode(false);
  }
}

// Activate or inactivate cut image mode
void GUI::CutImageMode()
{
  if (cut_image_mode->isChecked())
  {
    // set other modes off
    line_mode->setChecked(false);
    delete_mode->setChecked(false);
    add_img_mode->setChecked(false);
    delete_img_mode->setChecked(false);
    bezier_mode->setChecked(false);

    // activate mode
    mainWidget->getScene()->CutImageMode(true);
    // Set the lower toolbar enabled and hide the main toolbar
    HideSelectToolbar(false);
    HideMainToolbar(true);

  }
  else
  {
    mainWidget->getScene()->CutImageMode(false);
    HideModeToolbar(true);
    // unhide the main toolbar
    HideMainToolbar(false);
  }
}


// Hide/unhide the polygon toolbar from user
// hide == true -> hide, hide == false -> unhide
void GUI::HidePolygonToolbar(bool hide)
{
  if (hide)
  {
    polyToolbar.polygon_toolbar->setVisible(false);
  }
  else
  {
    polyToolbar.polygon_toolbar->setVisible(true);
  }
}


// Hide/unhide the mode toolbar from user
// hide == true -> hide, hide == false -> unhide
void GUI::HideModeToolbar(bool hide)
{
  if (hide)
  {
    modeToolbar.mode_toolbar->setVisible(false);
  }
  else
  {
    modeToolbar.mode_toolbar->setVisible(true);
  }
}

// Hide/unhide the main toolbar from user
// Called from CutImageMode
// hide == true -> hide, hide == false -> unhide
void GUI::HideMainToolbar(bool hide)
{
  if (hide)
  {
    main_toolbar->setVisible(false);
  }
  else
  {
    main_toolbar->setVisible(true);
  }
}

// Hide/unhide the select toolbar from user
// hide == true -> hide, hide == false -> unhide
void GUI::HideSelectToolbar(bool hide)
{
  if (hide)
  {
    selectToolbar.select_img_toolbar->setVisible(false);
  }
  else
  {
    selectToolbar.select_img_toolbar->setVisible(true);
  }
}



// This method creates all toolbars (long method)
// Called from constructor

void GUI::createToolbars()
{
  // create a toolbar
  main_toolbar = addToolBar("Main Toolbar");

  // add a checkable line mode button
  QPixmap draw_line(draw_line_img);
  line_mode = main_toolbar->addAction(QIcon(draw_line),"Line mode");
  line_mode->setCheckable(true);
  line_mode->setChecked(true);
  connect(line_mode, &QAction::triggered, this, &GUI::LineMode);

  // add a checkable delete line button
  QPixmap delete_line(delete_line_img);
  delete_mode = main_toolbar->addAction(QIcon(delete_line),"Delete line");
  delete_mode->setCheckable(true);
  connect(delete_mode, &QAction::triggered, this, &GUI::DeleteMode);

  // add a clear previous points button
  //main_toolbar->addSeparator();
  QPixmap clear_points(clear_points_img);
  clear_mode = main_toolbar->addAction(QIcon(clear_points),"Clear previous point(s)");
  connect(clear_mode, &QAction::triggered, this, &GUI::ClearMode);

  // add a action for bezier mode
  main_toolbar->addSeparator();
  QPixmap bezier_img(bezier_pic_img);
  bezier_mode = main_toolbar->addAction(QIcon(bezier_img), "Bezier mode");
  //bezier_mode->setCheckable(true);
  //bezier_mode->setChecked(false);
  connect(bezier_mode, &QAction::triggered, this, &GUI::BezierMode);


  // add a clear all button
  main_toolbar->addSeparator();
  QPixmap clear_all(clear_all_img);
  clear_all_mode = main_toolbar->addAction(QIcon(clear_all), "Clear all");
  connect(clear_all_mode, &QAction::triggered, this, &GUI::ClearAll);

  // add an add image button
  main_toolbar->addSeparator();
  QPixmap add_img(image_sketch_img);
  add_img_mode = main_toolbar->addAction(QIcon(add_img),"Add image");
  add_img_mode->setCheckable(true);
  add_img_mode->setChecked(false);
  connect(add_img_mode, &QAction::triggered, this, &GUI::ImgMode);


  // add an image delete mode button
  QPixmap delete_img(image_delete_img);
  delete_img_mode = main_toolbar->addAction(QIcon(delete_img), "Delete image");
  delete_img_mode->setCheckable(true);
  delete_img_mode->setChecked(false);
  connect(delete_img_mode, &QAction::triggered, this, &GUI::DeleteImgMode);


  // add a cut image mode button
  QPixmap image_cut(image_cut_img);
  cut_image_mode = main_toolbar->addAction(QIcon(image_cut), "Cut image");
  cut_image_mode->setCheckable(true);
  cut_image_mode->setChecked(false);
  connect(cut_image_mode, &QAction::triggered, this, &GUI::CutImageMode);


  // Create SelectImgToolbar
  selectToolbar.select_img_toolbar = addToolBar("Select image");
  selectToolbar.info = new QLabel(" Select an image to cut and then press continue ");
  selectToolbar.select_img_toolbar->addWidget(selectToolbar.info);
  selectToolbar.select_img_toolbar->addSeparator();
  // Add the continue button
  QPixmap continue_pic = QPixmap(continue_img);
  QPixmap cancel_pic = QPixmap(cancel_img);
  selectToolbar.continue_button = selectToolbar.select_img_toolbar->addAction(continue_pic, "Continue");
  selectToolbar.continue_button->setCheckable(true);
  selectToolbar.continue_button->setChecked(false);
  connect(selectToolbar.continue_button, &QAction::triggered, this, &GUI::ContinueFromSelect);
  // Add cancel button, connect to CancelFromSelect
  selectToolbar.select_img_toolbar->addSeparator();
  selectToolbar.cancel = selectToolbar.select_img_toolbar->addAction(cancel_pic, "Cancel");
  selectToolbar.cancel->setCheckable(true);
  selectToolbar.cancel->setChecked(false);
  connect(selectToolbar.cancel, &QAction::triggered, this, &GUI::CancelFromSelect);
  // Hide the select toolbar
  HideSelectToolbar(true);

  // Create mode Toolbar
  modeToolbar.mode_toolbar = addToolBar("Mode toolbar");
  // Add a combobox with valid 2 options: Polygon cut, Path cut
  modeToolbar.combobox = new QComboBox();
  modeToolbar.combobox->addItem(tr("Select mode"));
  modeToolbar.combobox->addItem(tr("Polygon cut"));
  modeToolbar.combobox->addItem(tr("Path cut"));
  modeToolbar.mode_toolbar->addWidget(modeToolbar.combobox);
  // Add a continue and cancel button
  // Connect those also to the correct actions
  modeToolbar.mode_toolbar->addSeparator();
  modeToolbar.continue_button = modeToolbar.mode_toolbar->addAction(continue_pic, "Continue");
  connect(modeToolbar.continue_button, &QAction::triggered, this, &GUI::ContinueFromMode);
  modeToolbar.mode_toolbar->addSeparator();
  modeToolbar.cancel = modeToolbar.mode_toolbar->addAction(cancel_pic, "Cancel");
  connect(modeToolbar.cancel, &QAction::triggered, this, &GUI::CancelFromMode);
  // Hide the mode toolbar
  HideModeToolbar(true);


  // Add PolygonToolbar for polygon image cutting options
  addToolBarBreak();
  polyToolbar.polygon_toolbar = addToolBar("Polygon toolbar");

  /*polyToolbar.endpoints_text = new QLabel(" Previous point endpoint enabled ");
  polyToolbar.polygon_toolbar->addWidget(polyToolbar.endpoints_text);
  polyToolbar.endpoints = polyToolbar.polygon_toolbar->addAction("Endpoints");
  // Set endpoints always enabled
  polyToolbar.endpoints->setCheckable(true);
  polyToolbar.endpoints->setChecked(true);*/

  polyToolbar.polygon_toolbar->addSeparator();
  polyToolbar.final_point_text = new QLabel("Finished cut: connects the first and the last point ");
  polyToolbar.polygon_toolbar->addWidget(polyToolbar.final_point_text);
  //QPixmap finish_pic = QPixmap(finish_img);
  polyToolbar.final_point = polyToolbar.polygon_toolbar->addAction(continue_pic, "Finished cut");
  // Set checkable and disabled, connect
  polyToolbar.final_point->setCheckable(true);
  polyToolbar.final_point->setChecked(false);
  connect(polyToolbar.final_point, &QAction::triggered, this, &GUI::SetPolyFinal);

  polyToolbar.polygon_toolbar->addSeparator();
  polyToolbar.remove_text = new QLabel("Remove previous point ");
  QPixmap remove_point_pic = QPixmap(remove_point_img);
  polyToolbar.polygon_toolbar->addWidget(polyToolbar.remove_text);
  polyToolbar.remove = polyToolbar.polygon_toolbar->addAction(remove_point_pic, "Remove point");
  // Set checkable and disabled, connect
  polyToolbar.remove->setCheckable(true);
  polyToolbar.remove->setChecked(false);
  connect(polyToolbar.remove, &QAction::triggered, this, &GUI::RemovePolyPrevious);

  polyToolbar.polygon_toolbar->addSeparator();
  polyToolbar.cancel = polyToolbar.polygon_toolbar->addAction(cancel_pic, "Cancel");
  // Set checkable and connect
  polyToolbar.cancel->setCheckable(true);
  polyToolbar.cancel->setChecked(false);
  connect(polyToolbar.cancel, &QAction::triggered, this, &GUI::CancelFromPoly);

  // Hide the lower toolbar
  HidePolygonToolbar(true);


  // Create the BezierToolbar
  bezierToolbar.bezier_toolbar = addToolBar("Bezier toolbar");
  bezierToolbar.options = new QComboBox();
  // Note: options order is crusial in BezierToolbarOptionsSaved
  bezierToolbar.options->addItem(tr("Start point locking"));
  bezierToolbar.options->addItem(tr("Lock only when connected"));
  bezierToolbar.options->addItem(tr("Lock always"));
  bezierToolbar.options->addItem(tr("Never lock"));
  bezierToolbar.bezier_toolbar->addWidget(bezierToolbar.options);
  QPixmap save_button = QPixmap(save_button_img);
  bezierToolbar.save_options = bezierToolbar.bezier_toolbar->addAction(save_button, "Save options");
  // Connect save options
  connect(bezierToolbar.save_options, &QAction::triggered, this, &GUI::BezierToolbar_OptionsSaved);
  bezierToolbar.bezier_toolbar->addSeparator();
  bezierToolbar.save_bezier = bezierToolbar.bezier_toolbar->addAction(continue_pic, "Save Bezier");
  QPixmap bezier_remove_pic = QPixmap(bezier_remove_img);
  bezierToolbar.remove_bezier = bezierToolbar.bezier_toolbar->addAction(bezier_remove_pic, "Remove Bezier");
  bezierToolbar.bezier_toolbar->addSeparator();
  bezierToolbar.cancel = bezierToolbar.bezier_toolbar->addAction(cancel_pic, "Cancel");
  // Connect save_bezier and cancel
  connect(bezierToolbar.save_bezier, &QAction::triggered, this, &GUI::BezierToolbar_SaveBezier);
  connect(bezierToolbar.remove_bezier, &QAction::triggered, this, &GUI::BezierToolbar_Remove);
  connect(bezierToolbar.cancel, &QAction::triggered, this, &GUI::BezierToolbar_Cancel);
  // Hide the toolbar
  HideBezierToolbar(true);



}

// User wants to cancel image cutting
// Unhide the main toolbar
// Hide the select toolbar
void GUI::CancelFromSelect()
{
  HideSelectToolbar(true);
  HideMainToolbar(false);
  // disable cancel button
  selectToolbar.cancel->setChecked(false);

  // Set also image cutting mode disabled
  mainWidget->getScene()->CutImageMode(false);
  cut_image_mode->setChecked(false);

}

// User has selected an image, check the image exists
// if image ok, continue to the mode select
// otherwise call CancelFromSelect
void GUI::ContinueFromSelect()
{
  // disable continue_button
  selectToolbar.continue_button->setChecked(false);

  HideSelectToolbar(true);
  // check if image exists
  if( mainWidget->getScene()->SelectCutImg())
  {
    // image found, enter to the mode select toolbar
    HideModeToolbar(false);
  }
  else
  {
    // no image found, inform user and call CancelFromSelect
    QMessageBox::warning(this, "No image found", "Click a valid image position!");
    CancelFromSelect();
  }

}

// Cancel from mode select
// Hide mode select toolbar and unhide main toolbar
void GUI::CancelFromMode()
{
  // disable the cancel button
  modeToolbar.cancel->setChecked(false);
  HideModeToolbar(true);
  HideMainToolbar(false);

  // Set also image cutting mode disabled
  mainWidget->getScene()->CutImageMode(false);
  cut_image_mode->setChecked(false);
}

// Continue based on the combobox value
void GUI::ContinueFromMode()
{
  // set continue button off
  modeToolbar.continue_button->setChecked(false);

  int index = modeToolbar.combobox->currentIndex();
  if (index == 0)
  {
    // Invalid option
    // Inform user with QMessageBox and return with CancelFromMode
    QMessageBox::warning(this, "Invalid cut mode", "Choose Polygon cut or Path cut!");
    CancelFromMode();
  }

  else if (index == 1)
  {
    // Polygon cut, assign mode to the scene
    mainWidget->getScene()->SetImgCutMode(index);

    // Hide the mode toolbar and unhide polygon toolbar
    HideModeToolbar(true);
    HidePolygonToolbar(false);

  }
  else if (index == 2)
  {
    // not implemented yet
    CancelFromMode();
  }
}

// Cancel from polygon cut mode to the main toolbar mode
void GUI::CancelFromPoly()
{
  // turn cancel button off
  polyToolbar.cancel->setChecked(false);

  // Hide poly toolbar and unhide main toolbar
  HidePolygonToolbar(true);
  HideMainToolbar(false);
  // Set also image cutting mode disabled
  mainWidget->getScene()->CutImageMode(false);
  cut_image_mode->setChecked(false);

}

// Cuts the pixmap
// Returns to the main toolbox
void GUI::SetPolyFinal()
{
  // turn the button off
  polyToolbar.final_point->setChecked(false);

  // Calls the OwnGraphicsScene wrapper call for cutting the image
  mainWidget->getScene()->CutPixmapItem();
  // Hides polygon_toolbar and unhides main_toolbar
  // by calling CancelFromPoly
  CancelFromPoly();
}


//  Removes the latest added point
void GUI::RemovePolyPrevious()
{
  // set the button off
  polyToolbar.remove->setChecked(false);
  mainWidget->getScene()->RemovePolyPrevious();
}


// User has changed options
void GUI::SaveChoices()
{
  // Set the correct line_connect value to OwnGraphicsScene
  int combo_index = line_options_combo->ComboIndex();
  mainWidget->getScene()->setConnectLines(combo_index);

  // Show a QMessageBox to user
  QMessageBox::information(this, "Information", "Selected options saved");
}

// Bezier action triggered
void GUI::BezierMode()
{
  // deactivate other mode
  line_mode->setChecked(false);
  delete_mode->setChecked(false);
  add_img_mode->setChecked(false);
  delete_img_mode->setChecked(false);
  cut_image_mode->setChecked(false);

  // Activate Bezier mode
  mainWidget->getScene()->BezierMode(true);
  HideBezierToolbar(false);
  HideMainToolbar(true);

}

/*  BezierToolbar options have been saved */
void GUI::BezierToolbar_OptionsSaved()
{
  int index = bezierToolbar.options->currentIndex();
  if (index)
  {
    // Send updated option to OwnGraphicsScene
    mainWidget->getScene()->modifyBezierOptions(index);
    QMessageBox::information(this, "Information", "Selected options saved");

  }
  else
  {
    // Non-correct option selected
    QMessageBox::warning(this, "Warning", "Invalid option");
  }
}

/*  Save the Bezier */
void GUI::BezierToolbar_SaveBezier()
{
  mainWidget->getScene()->BezierReady();
}

/*  Remove current Bezier */
void GUI::BezierToolbar_Remove()
{
  mainWidget->getScene()->EraseBezier();
}

/*  Go back to main toolbar */
void GUI::BezierToolbar_Cancel()
{
  mainWidget->getScene()->BezierMode(false);
  // Activate correct toolbar
  HideBezierToolbar(true);
  HideMainToolbar(false);
}


/*  A small wrapper method used to hide BezierToolbar */
void GUI::HideBezierToolbar(bool hide)
{
  if (hide)
  {
    bezierToolbar.bezier_toolbar->setVisible(false);
  }
  else
  {
    bezierToolbar.bezier_toolbar->setVisible(true);
  }
}
