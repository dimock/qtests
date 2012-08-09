#include "iconwidget.h"
#include "thepanel.h"
#include "foldingcontainer.h"
#include <QImage>
#include <QPainter>

TheIcon::TheIcon(QWidget * parent) :
  QWidget(parent)
{
  icons_[0] = new QImage( QString(":/images/collapsed.png"));
  icons_[1] = new QImage( QString(":/images/expanded.png"));
}

void TheIcon::paintEvent(QPaintEvent * )
{
  if ( !parent() || !parent()->parent() )
    return;

  ThePanel * panel = dynamic_cast<ThePanel*>(parent()->parent());
  if ( !panel )
    return;

  QFoldingContainer * container = panel->getFoldingContainer();
  if ( !container )
    return;

  int n = container->isExpanded() ? 1 : 0;

  QPainter painter(this);

  painter.drawImage(0, 0, *icons_[n]);
}

QSize TheIcon::sizeHint() const
{
  QSize sz = icons_[1]->size();
  return sz;
}