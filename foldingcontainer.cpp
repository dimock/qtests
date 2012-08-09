#include "foldingcontainer.h"
#include "pixmapwidget.h"
#include <QLayout>
#include <QLabel>
#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

QFoldingContainer::QFoldingContainer(QWidget * parent /* = 0*/) :
  QWidget(parent), contentWidget_(0),
  widgetLayout_(0), pixmapLayout_(0), pixmapWidget_(0),
  expanded_(true)
{
  setAttribute(Qt::WA_DeleteOnClose);

  // create main layout for both content and caption
  mainLayout_ = new QVBoxLayout;

  // create widget for pixmap content representation
  pixmapLayout_ = new QVBoxLayout;
  pixmapLayout_->setContentsMargins(0,0,0,0);
  pixmapWidget_ = new PixmapWidget(this);
  pixmapLayout_->addWidget(pixmapWidget_, 1);

  connect(pixmapWidget_, SIGNAL(stopAnimationSignal()), this, SLOT(onStopAnimation()));
 
  setLayout(mainLayout_);
  
  adjustSize();
}

QFoldingContainer::~QFoldingContainer()
{
  killContent();
}

void QFoldingContainer::killContent()
{
  if ( pixmapLayout_ )
    mainLayout_->removeItem(pixmapLayout_);

  delete widgetLayout_;
  delete contentWidget_;

  widgetLayout_ = 0;
  contentWidget_ = 0;
}

void QFoldingContainer::enableAnimation(bool enable)
{
}

bool QFoldingContainer::isExpanded() const
{
  return expanded_;
}

void QFoldingContainer::setAnimationDuration(int ms)
{
  if ( pixmapWidget_ )
    pixmapWidget_->setAnimationDuration(ms);
}

void QFoldingContainer::setAnimationStepsNum(int num)
{
  if ( pixmapWidget_ )
    pixmapWidget_->setAnimationStepsNum(num);
}

void QFoldingContainer::setContent(QWidget * content)
{
  killContent();

  if ( !content )
    return;

  // store content widget
  contentWidget_ = content;

  // set content panel as content widget parent
  contentWidget_->setParent(this);

  // create layout for content panel
  widgetLayout_ = new QVBoxLayout;
  mainLayout_->addLayout(widgetLayout_);
  widgetLayout_->setContentsMargins(0,0,0,0);
  widgetLayout_->addWidget(contentWidget_, 1);
  mainLayout_->setContentsMargins(0,0,0,0);

  // add pixmap layout
  mainLayout_->addLayout(pixmapLayout_);

  updateContent(false);

  adjustSize();
}

void QFoldingContainer::collapse()
{
  expanded_ = false;
  updateContent(true);
}

void QFoldingContainer::expand()
{
  expanded_ = true;
  updateContent(true);
}

void QFoldingContainer::updateContent(bool start)
{
  if ( !contentWidget_ )
    return;

  if ( !expanded_ )
  {
    pixmapWidget_->setPixmap(QPixmap::grabWidget(contentWidget_));
    pixmapWidget_->startAnimation(start ? -1 : 0, start ? 100 : 0);
  }
  else
    pixmapWidget_->startAnimation(start ? +1 : 0, start ? 0 : 100);

  if ( !start )
  {
    pixmapWidget_->setVisible(!expanded_);
    contentWidget_->setVisible(expanded_);
  }
  else
  {
    pixmapWidget_->setVisible(true);
    contentWidget_->setVisible(false);
  }

  update();
}

void QFoldingContainer::onStopAnimation()
{
  pixmapWidget_->setVisible(!expanded_);
  contentWidget_->setVisible(expanded_);
}

void QFoldingContainer::setExpanded(bool expanded)
{
  expanded_ = expanded;
  if ( !expanded_ )
    collapse();
  else
    expand();
}
