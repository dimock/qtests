#include <QApplication>
#include <QListWidget>
#include "foldingcontainer.h"
#include "thewidget.h"
#include "thepanel.h"

int main(int argn, char * argv[])
{
  QApplication qapp(argn, argv);

  ThePanel * p = new ThePanel(0);

  p->show();

  qapp.exec();
}
