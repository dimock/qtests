#include "captionwidget.h"
#include "foldingcontainer.h"
#include "thepanel.h"
#include "iconwidget.h"

#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QLinearGradient>
#include <QPushButton>
#include <QMouseEvent>

TheCaption::TheCaption(QWidget * parent) :
  QWidget(parent)
{
  icon_ = new TheIcon(this);
  captionLabel_ = new QLabel( tr("Expanded"), this );
  closeButton_ = new QPushButton( QIcon(), tr(""), this );

  mainLayout_ = new QHBoxLayout;
  mainLayout_->addWidget(icon_, 0);
  mainLayout_->addWidget(captionLabel_, 1, Qt::AlignVCenter|Qt::AlignRight);
  mainLayout_->addWidget(closeButton_, 0);

  connect(closeButton_, SIGNAL(clicked()), parent, SLOT(close()));
  connect(this, SIGNAL(expandButton()), parent, SLOT(onCollapseExpand()));

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
  grad.setColorAt(0, Qt::white);
  grad.setColorAt(1, color);
  QBrush brush(grad);
  painter.setBrush(brush);
  painter.drawRoundedRect( QRectF(0,0,sz.width(),sz.height()), 5, 5, Qt::AbsoluteSize );
}

void TheCaption::enterEvent(QEvent * e)
{
  QFont font = captionLabel_->font();
  font.setUnderline(true);
  captionLabel_->setFont(font);
  update();
}

void TheCaption::leaveEvent(QEvent * e)
{
  QFont font = captionLabel_->font();
  font.setUnderline(false);
  captionLabel_->setFont(font);
  update();
}

void TheCaption::mousePressEvent(QMouseEvent *)
{
  emit expandButton();
}
