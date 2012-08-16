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
#include <QStyleOption>

TheCaption::TheCaption(QWidget * parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  icon_ = new TheIcon(this);
  captionLabel_ = new QLabel( tr(""), this );

  QIcon icon;
  icon.addPixmap( QPixmap( tr(":/images/close_normal.png") ), QIcon::Normal );
  icon.addPixmap( QPixmap( tr(":/images/close_active.png") ), QIcon::Active );
  closeButton_ = new QPushButton( icon, tr(""), this );
  closeButton_->setFlat(true);

  mainLayout_ = new QHBoxLayout;
  mainLayout_->addWidget(icon_, 0);
  mainLayout_->addWidget(captionLabel_, 1, Qt::AlignVCenter|Qt::AlignRight);
  mainLayout_->addWidget(closeButton_, 0);

  connect(closeButton_, SIGNAL(clicked()), parent, SLOT(close()));
  connect(this, SIGNAL(expandButton()), parent, SLOT(onCollapseExpand()));

  // doesn't work
  //captionLabel_->setStyleSheet( QObject::tr(" hover { text-decoration: underline } ") );

  updateCaption();

  setLayout(mainLayout_);
  adjustSize();
}

void TheCaption::paintEvent(QPaintEvent *)
{

  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TheCaption::enterEvent(QEvent * )
{
  QFont font = captionLabel_->font();
  font.setUnderline(true);
  captionLabel_->setFont(font);
  update();
}

void TheCaption::leaveEvent(QEvent * )
{
  QFont font = captionLabel_->font();
  font.setUnderline(false);
  captionLabel_->setFont(font);
  update();
}

void TheCaption::updateCaption()
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

  if ( container->isExpanded() )
    setStyleSheet( tr("TheCaption { background-color: QLinearGradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(100, 100, 100, 255)); border-radius: 5px; }") );
  else
    setStyleSheet( tr("TheCaption { background-color: QLinearGradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(180, 180, 180, 255), stop:1 rgba(70, 70, 70, 255)); border-radius: 5px; }") );
}

void TheCaption::mousePressEvent(QMouseEvent *)
{
  emit expandButton();
}
