#include "thepanel.h"
#include "foldingcontainer.h"
#include "captionwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QListWidget>
#include <QPushButton>

#include "thewidget.h"

ThePanel::ThePanel(QWidget * parent) :
  QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  mainLayout_ = new QVBoxLayout;
  captionLayout_ = new QVBoxLayout;
  foldingLayout_ = new QVBoxLayout;

  mainLayout_->addLayout(captionLayout_);
  mainLayout_->addLayout(foldingLayout_);

  caption_ = new TheCaption(this);
  captionLayout_->addWidget(caption_);

  foldingContainer_ = new QFoldingContainer(this);
  foldingLayout_->addWidget(foldingContainer_);

  setLayout(mainLayout_);
}

void ThePanel::onCollapseExpand()
{
  foldingContainer_->setExpanded( !foldingContainer_->isExpanded() );
  update();
}

QFoldingContainer * ThePanel::getFoldingContainer()
{
  return foldingContainer_;
}