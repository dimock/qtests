#include "captionwidget.h"
#include "foldingcontainer.h"
#include "thepanel.h"
#include "iconwidget.h"

#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QLinearGradient>

TheCaption::TheCaption(QWidget * parent) :
  QWidget(parent)
{
  icon_ = new TheIcon(this);
  captionLabel_ = new QLabel( tr("expanded"), this );
  mainLayout_ = new QHBoxLayout;
  mainLayout_->addWidget(icon_, 0);
  mainLayout_->addWidget(captionLabel_, 0);
  setLayout(mainLayout_);
  adjustSize();
}

void TheCaption::paintEvent(QPaintEvent *)
{
  if ( !parent() )
    return;

  ThePanel * panel = dynamic_cast<ThePanel*>(parent());
  if ( !panel )
    return;

  QFoldingContainer * container = panel->getFoldingContainer();
  if ( !container )
    return;

  captionLabel_->setText(container->isExpanded() ? tr("Expanded") : tr("Collapsed") );

  QPainter painter(this);

  Qt::GlobalColor color = container->isExpanded() ? Qt::red : Qt::blue;

  QSize sz = size();
  QPen pen(Qt::NoPen);
  painter.setPen(pen);
  QLinearGradient grad(QPointF(0,0), QPointF(0,sz.height()));
  grad.setColorAt(0, color);
  grad.setColorAt(1, Qt::white);
  QBrush brush(grad);
  painter.setBrush(brush);
  painter.drawRoundedRect( QRectF(0,0,sz.width(),sz.height()), 5, 5, Qt::AbsoluteSize );
}
