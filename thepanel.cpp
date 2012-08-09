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
  QWidget(parent), caption_(0)
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

  if ( 1 )
  {
    QListWidget * lw = new QListWidget;

    for (int i = 0; i < 20; ++i)
    {
      QString qstr;
      qstr.sprintf("Item number %d", i);
      lw->addItem(qstr);
    }

    foldingContainer_->setContent(lw);
  }
  else
  {
    TheWidget * tw = new TheWidget;
    foldingContainer_->setContent(tw);
  }

  foldingContainer_->setAnimationDuration(300);
  foldingContainer_->setAnimationStepsNum(20);

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