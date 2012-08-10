#include <QApplication>
#include <QListWidget>
#include "foldingcontainer.h"
#include "thewidget.h"
#include "thepanel.h"

int main(int argn, char * argv[])
{
  QApplication qapp(argn, argv);

  ThePanel * p = new ThePanel(0);
  QFoldingContainer * fc = p->getFoldingContainer();

  if ( fc )
  {
    QListWidget * lw = new QListWidget;

    for (int i = 0; i < 20; ++i)
    {
      QString qstr;
      qstr.sprintf("Item number %d", i);
      lw->addItem(qstr);
    }

    fc->setContent(lw);
    fc->setAnimationDuration(300);
    fc->setAnimationStepsNum(20);
    fc->enableAnimation(true);
  }

  p->show();

  qapp.exec();
}
