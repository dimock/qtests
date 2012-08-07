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
  widgetLayout_(0), pixmapLayout_(0), pixmapWidget_(0), height_(20), collapsed_(false),
  contentPixmap_(0)
{
  setAttribute(Qt::WA_DeleteOnClose);

  // create widget's caption
  QLabel * theLabel = new QLabel(tr("Test Widget"), this);

  captionLayout_ = new QVBoxLayout;
  QHBoxLayout * captionHlayout = new QHBoxLayout;
  captionLayout_->addLayout(captionHlayout);
  captionHlayout->addWidget(theLabel, 1, Qt::AlignLeft);

  collapseButton_ = new QPushButton(tr("-"), this);
  collapseButton_->setCheckable(true);
  captionHlayout->addWidget(collapseButton_);
  connect(collapseButton_, SIGNAL(toggled(bool)), this, SLOT(onCollapsed(bool)));

  // create main layout for both content and caption
  mainLayout_ = new QVBoxLayout;
  mainLayout_->addLayout(captionLayout_);
  
  setLayout(mainLayout_);
  
  //setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  adjustSize();
}

QFoldingContainer::~QFoldingContainer()
{
  killContent();
}

void QFoldingContainer::killContent()
{
  if ( contentWidget_ )
  {
    delete widgetLayout_;
    delete pixmapLayout_;
    delete contentWidget_;
    delete pixmapWidget_;
  }

  widgetLayout_ = 0;
  pixmapLayout_ = 0;
  contentWidget_ = 0;
  pixmapWidget_ = 0;
  contentPixmap_ = 0;
}

void QFoldingContainer::enableAnimation(bool enable)
{
}

void QFoldingContainer::setAnimationDuration(int ms)
{
}

void QFoldingContainer::setContent(QWidget * content)
{
  killContent();

  if ( !content )
    return;

  // store content widget
  contentWidget_ = content;

  /** firstly create layout for widget
   */

  // create layout for content panel
  widgetLayout_ = new QVBoxLayout;
  mainLayout_->addLayout(widgetLayout_);
  widgetLayout_->setContentsMargins(0,0,0,0);
  widgetLayout_->addWidget(contentWidget_, 1);
  
  // create widget for pixmap content representation
  pixmapLayout_ = new QVBoxLayout;
  pixmapLayout_->setContentsMargins(0,0,0,0);
  pixmapWidget_ = new PixmapWidget(this);
  mainLayout_->addLayout(pixmapLayout_);
  pixmapLayout_->addWidget(pixmapWidget_, 1);

  // set content panel as content widget parent
  contentWidget_->setParent(this);

  updateContent();

  //setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  adjustSize();
}

void QFoldingContainer::collapse()
{
  collapsed_ = true;
  collapseButton_->setText(tr("+"));
  updateContent();
}

void QFoldingContainer::expand()
{
  collapsed_ = false;
  collapseButton_->setText(tr("-"));
  updateContent();
}

void QFoldingContainer::updateContent()
{
  if ( !contentWidget_ )
    return;

  pixmapWidget_->setVisible(collapsed_);
  contentWidget_->setVisible(!collapsed_);

  if ( collapsed_ )
  {
    QSize sz = contentWidget_->size();
    contentPixmap_ = new QPixmap(sz);
    contentWidget_->show();
    contentPixmap_->grabWidget(contentWidget_);
    contentWidget_->hide();
    //QPainter painter(contentPixmap_);
    //painter.fillRect(0, 0, sz.width(), sz.height(), Qt::black);

    //QGraphicsScene * scene = new QGraphicsScene();
    ////contentWidget_->setParent(0);
    //QGraphicsProxyWidget * widget = scene->addWidget(contentWidget_);
    //contentWidget_->repaint();
    //contentWidget_->show();
    //scene->render(&painter, QRectF(0, 0, sz.width(), sz.height()), QRect(0, 0, sz.width(), sz.height()), Qt::KeepAspectRatio);
    //scene->removeItem(widget);
    //widget->setWidget(0);
    //contentWidget_->hide();
    //pixmapWidget_->show();
    //delete widget;
    //delete scene;
    pixmapWidget_->setPixmap(contentPixmap_);
  }
  else
  {
    contentWidget_->setParent(this);
    delete contentPixmap_;
    contentPixmap_ = 0;
    pixmapWidget_->setPixmap(0);
  }

  update();
//  updateGeometry();
}

void QFoldingContainer::onCollapsed(bool collapsed)
{
  if ( collapsed )
    collapse();
  else
    expand();
}
