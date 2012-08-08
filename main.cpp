#include <QApplication>
#include <QListWidget>
#include "foldingcontainer.h"
#include "thewidget.h"

int main(int argn, char * argv[])
{
  QApplication qapp(argn, argv);
  QFoldingContainer * w = new QFoldingContainer;

  if ( 0 )
  {
    QListWidget * lw = new QListWidget;

    for (int i = 0; i < 20; ++i)
    {
      QString qstr;
      qstr.sprintf("Item number %d", i);
      lw->addItem(qstr);
    }

    w->setContent(lw);
  }
  else
  {
    TheWidget * tw = new TheWidget;
    w->setContent(tw);
  }

  w->setAnimationDuration(1000);
  w->setAnimationStepsNum(20);
  w->show();

  qapp.exec();
}
