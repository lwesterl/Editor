#ifndef Combobox_Action_Header
#define Combobox_Action_Header

#include <QWidget>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QString>


// This class implements a QComboBox which can be added to a menuBar
class ComboboxAction: public QWidgetAction
{
  public:
    ComboboxAction(const QString &info);
    int ComboIndex();

  private:
    QComboBox *combobox;
    QVBoxLayout *layout;
    QWidget *default_widget;

};

#endif
