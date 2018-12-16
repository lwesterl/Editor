/**
  *   @file SpinBoxAction.cpp
  *   @brief Contains class SpinBoxAction source code
  */


#include "../include/SpinBoxAction.hpp"


/*  Class SpinBoxAction */

SpinBoxAction::SpinBoxAction(const QString &name): QWidgetAction(NULL)
{
  QWidget *widget = new QWidget(NULL);
  // Create spinbox
  spinbox = new QSpinBox();
  QVBoxLayout *layout = new QVBoxLayout();
  // add name label
  layout->addWidget(new QLabel(name));
  layout->addWidget(spinbox);

  // set layout for the widget
  widget->setLayout(layout);
  setDefaultWidget(widget);
}

/*  Set min and max values, set also suffix */
void SpinBoxAction::setLimits(int min, int max, const QString suffix)
{
  spinbox->setRange(min, max);
  spinbox->setSuffix(suffix);
}

/*  Get current value */
int SpinBoxAction::getCurrentValue()
{
  return spinbox->value();
}

/*  Set default value */
void SpinBoxAction::setDefaultValue(int default_value)
{
  spinbox->setValue(default_value);
}
