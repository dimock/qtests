#include "thewidget.h"
#include <QPainter>
#include <QMouseEvent>

TheWidget::TheWidget(QWidget * parent) :
QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
}

TheWidget::~TheWidget()
{
}

void TheWidget::mouseMoveEvent(QMouseEvent * e)
{
  if ( !e )
    return;

  if ( e->buttons() & Qt::LeftButton )
  {
    const QPoint & p = e->pos();
    if ( polygones_.size() == 0 )
      polygones_.push_back(QPolygon());
    polygones_.back().push_back(p);
    pos_ = p;
  }

  update();
}

void TheWidget::mousePressEvent(QMouseEvent * e)
{
  if ( !e )
    return;

  if ( e->button() == Qt::LeftButton )
  {
    polygones_.push_back(QPolygon());
    pos_ = e->pos();
  }
}

void TheWidget::paintEvent(QPaintEvent * e)
{
  QPainter painter(this);

  QRect rc(0, 0, size().width(), size().height());

  QBrush brush(Qt::white);
  painter.fillRect(rc, brush);

  QPen pen(Qt::SolidLine);
  pen.setColor(Qt::red);
  painter.setPen(pen);

  for (PolygonesArray::iterator i = polygones_.begin(); i != polygones_.end(); ++i)
  {
    painter.drawPolygon(*i);
  }
}
