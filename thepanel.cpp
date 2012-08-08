#include "thepanel.h"
#include "foldingcontainer.h"

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

  stateImages_[0] = new QImage(tr(":/images/collapsed.png"));
  stateImages_[1] = new QImage(tr(":/images/expanded.png"));

  mainLayout_ = new QVBoxLayout;
  captionLayout_ = new QVBoxLayout;
  foldingLayout_ = new QVBoxLayout;

  mainLayout_->addLayout(captionLayout_);
  mainLayout_->addLayout(foldingLayout_);

  QLabel * text = new QLabel(tr("expanded"), this);
  captionLayout_->addWidget(text);
  collapseButton_ = new QPushButton(tr("-"), this);
  collapseButton_->setCheckable(true);
  captionLayout_->addWidget(collapseButton_);

  connect( collapseButton_, SIGNAL(toggled(bool)), this, SLOT(onCollapseExpand(bool)) );

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

void ThePanel::onCollapseExpand(bool)
{
  foldingContainer_->setExpanded( !collapseButton_->isChecked() );
}
