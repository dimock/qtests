#include "foldingcontainer.h"
#include <QLayout>
#include <QLabel>
#include <QApplication>

QFoldingContainer::QFoldingContainer(QWidget * parent /* = 0*/) :
  QWidget(parent), contentWidget_(0), captionLayout_(0), contentLayout_(0)
{
  setAttribute(Qt::WA_DeleteOnClose);

  // create widget's caption
  QLabel * theLabel = new QLabel(tr("Test Widget"), this);

  captionLayout_ = new QVBoxLayout;
  captionLayout_->addWidget(theLabel);

  // create main layout for both content and caption
  mainLayout_ = new QVBoxLayout;
  mainLayout_->addLayout(captionLayout_);
  
  setLayout(mainLayout_);
  
  adjustSize();
}

QFoldingContainer::~QFoldingContainer()
{
  killContent();
}

void QFoldingContainer::killContent()
{
  if ( contentWidget_ && contentLayout_ )
  {
    contentWidget_->setParent(0);
    mainLayout_->removeItem(contentLayout_);
    contentLayout_->removeWidget(contentWidget_);
    delete contentLayout_;
    delete contentWidget_;
  }

  contentWidget_ = 0;
  contentLayout_ = 0;
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

  contentLayout_ = new QVBoxLayout;
  contentWidget_ = content;
  contentWidget_->setParent(this);
  mainLayout_->addLayout(contentLayout_);
  contentLayout_->addWidget(contentWidget_);

  adjustSize();
}

void QFoldingContainer::collapse()
{
}

void QFoldingContainer::expand()
{
}

void QFoldingContainer::onExpanded(bool expanded)
{
}
