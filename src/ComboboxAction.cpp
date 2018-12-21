/**
  *   @file ComboboxAction.cpp
  *   @author Lauri Westerholm
  *   @brief Contains ComboboxAction class
  */


#include "../include/ComboboxAction.hpp"


// Constructor

ComboboxAction::ComboboxAction(const QString &info): QWidgetAction(NULL)
{
  // Create a new QWidget
  default_widget = new QWidget(NULL);
  // create the combobox
  combobox = new QComboBox();
  combobox->addItem("Yes");
  combobox->addItem("No");

  // create a vertical layout
  layout = new QVBoxLayout();
  QLabel *info_label = new QLabel(info);
  layout->addWidget(info_label);
  layout->addWidget(combobox);

  // set the layout
  default_widget->setLayout(layout);
  setDefaultWidget(default_widget);

}

// A small wrapper to access combobox index value
int ComboboxAction::ComboIndex()
{
  return combobox->currentIndex();
}

/*  Change item text */
void ComboboxAction::setItemText(int index, const QString text)
{
  if (index < combobox->count() && index > -1)
  {
    // index ok
    combobox->setItemText(index, text);
  }
}

/*  Add a new item */
void ComboboxAction::addItem(const QString text)
{
  combobox->addItem(text);
}
