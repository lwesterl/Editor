/**
  *   @file ComboboxAction.hpp
  *   @author Lauri Westerholm
  *   @brief Header for ComboboxAction class
  */

#pragma once


/*    INCLUDES    */

#include <QWidget>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QString>


/**
  *   @class ComboboxAction
  *   @brief Implements own QComboBox
  *   @details This class implements a QComboBox which can be added to a menuBar
  */

class ComboboxAction: public QWidgetAction
{
  public:

  /**
    *   @brief Constructor for ComboboxAction
    *   @param info String which is added to info label
    */
    ComboboxAction(const QString &info);

  /**
    *   @brief Get combobox index
    *   @return Returns combobox index
    *   @details Calls QComboBox currentIndex()
    */
    int ComboIndex();

  private:
    QComboBox *combobox;
    QVBoxLayout *layout;
    QWidget *default_widget;

};
