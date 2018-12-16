/**
  *   @file SpinBoxAction.hpp
  *   @brief Header for class SpinBoxAction
  */


#pragma once

/*  Includes */
#include <QWidget>
#include <QWidgetAction>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

/**
  *   @class SpinBoxAction
  *   @brief QWidgetAction derived class which implements QSpinBox as an action
  */
class SpinBoxAction: public QWidgetAction
{
  public:
    /**
      *   @brief Default constructor
      */
    SpinBoxAction(const QString &name);

    /**
      *   @brief Set limits for spinbox
      *   @param min Min int value
      *   @param max Max int value
      *   @param default_value Default (starting) value for spinbox
      *   @param suffix Suffix which is shown after values
      */
    void setLimits(int min, int max, const QString suffix);

    /**
      *   @brief Get current spinbox value
      *   @return Returns current values as an int
      */
    int getCurrentValue();

    /**
      *   @brief Set default (starting) value for spinbox
      *   @param default_value New value for spinbox
      */
    void setDefaultValue(int default_value);

  private:
    QSpinBox *spinbox;

};
