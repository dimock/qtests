#include "pixmapwidget.h"

#include <QPainter>
#include <QPixmap>

PixmapWidget::PixmapWidget(QWidget * parent) :
  QWidget(parent), pixmap_(0)
{
}

PixmapWidget::~PixmapWidget()
{
}

void PixmapWidget::setPixmap(QPixmap * pixmap)
{
  pixmap_ = pixmap;
}

void PixmapWidget::paintEvent(QPaintEvent * e)
{
  if ( !pixmap_ )
    return;

  QPainter painter(this);
  painter.drawImage(0, 0, pixmap_->toImage());
}
