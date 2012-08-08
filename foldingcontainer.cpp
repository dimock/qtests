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
  QWidget(parent), contentWidget_(0), captionLayout_(0),
  widgetLayout_(0), pixmapLayout_(0), pixmapWidget_(0)
{
  setAttribute(Qt::WA_DeleteOnClose);

  // create widget's caption
  QLabel * theLabel = new QLabel(tr("Test Widget"), this);

  captionLayout_ = new QVBoxLayout;
  captionLayout_->setContentsMargins(0,0,0,0);
  QHBoxLayout * captionHlayout = new QHBoxLayout;
  captionLayout_->addLayout(captionHlayout);
  captionHlayout->addWidget(theLabel, 1, Qt::AlignLeft);

  collapseButton_ = new QPushButton(tr("-"), this);
  collapseButton_->setCheckable(true);
  captionHlayout->addWidget(collapseButton_);
  connect(collapseButton_, SIGNAL(toggled(bool)), this, SLOT(onCollapsed(bool)));

  // create main layout for both content and caption
  mainLayout_ = new QVBoxLayout;
  mainLayout_->setContentsMargins(0,0,0,0);
  mainLayout_->addLayout(captionLayout_);

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

  // add pixmap layout
  mainLayout_->addLayout(pixmapLayout_);

  updateContent(false);

  adjustSize();
}

void QFoldingContainer::collapse()
{
  collapseButton_->setText(tr("+"));
  updateContent(true);
}

void QFoldingContainer::expand()
{
  collapseButton_->setText(tr("-"));
  updateContent(true);
}

void QFoldingContainer::updateContent(bool start)
{
  if ( !contentWidget_ )
    return;

  if ( isCollapsed() )
  {
    pixmapWidget_->setPixmap(QPixmap::grabWidget(contentWidget_));
    pixmapWidget_->startAnimation(start ? -1 : 0, start ? 100 : 0);
  }
  else
    pixmapWidget_->startAnimation(start ? +1 : 0, start ? 0 : 100);

  if ( !start )
  {
    pixmapWidget_->setVisible(isCollapsed());
    contentWidget_->setVisible(!isCollapsed());
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
  pixmapWidget_->setVisible(isCollapsed());
  contentWidget_->setVisible(!isCollapsed());
}

void QFoldingContainer::onCollapsed(bool collapsed)
{
  if ( collapsed )
    collapse();
  else
    expand();
}

bool QFoldingContainer::isCollapsed() const
{
  return collapseButton_ && collapseButton_->isChecked();
}
