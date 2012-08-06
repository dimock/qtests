#include <QApplication>
#include "foldingcontainer.h"
#include "thewidget.h"

int main(int argn, char * argv[])
{
  QApplication qapp(argn, argv);
  QFoldingContainer * w = new QFoldingContainer;
  QWidget * c = new TheWidget;
  w->setContent(c);
  w->show();
  qapp.exec();
}
