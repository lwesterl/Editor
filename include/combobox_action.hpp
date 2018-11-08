/**
  *   @file combobox_action.hpp
  *   @author Lauri Westerholm
  *   @brief Header for ComboboxAction class
  */


#ifndef COMBOBOX_ACTION_HEADER
#define COMBOBOX_ACTION_HEADER


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

#endif
