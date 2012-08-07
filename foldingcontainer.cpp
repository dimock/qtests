#include "foldingcontainer.h"
#include <QLayout>
#include <QLabel>
#include <QApplication>
#include <QPushButton>

QFoldingContainer::QFoldingContainer(QWidget * parent /* = 0*/) :
  QWidget(parent), contentWidget_(0), contentPanel_(0), captionLayout_(0),
  contentPanelLayout_(0), contentWidgetLayout_(0), height_(20), collapsed_(false)
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
  
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  adjustSize();
}

QFoldingContainer::~QFoldingContainer()
{
  killContent();
}

void QFoldingContainer::killContent()
{
  if ( contentWidget_ && contentPanelLayout_ )
  {
    mainLayout_->removeItem(contentPanelLayout_);
    contentPanelLayout_->removeWidget(contentPanel_);

    delete contentPanelLayout_;
    delete contentPanel_;
  }

  contentWidget_ = 0;
  contentPanelLayout_ = 0;
  contentWidgetLayout_ = 0;
  contentPanel_ = 0;
}

void QFoldingContainer::paintEvent(QPaintEvent * e)
{
  if ( !contentPanel_ || !contentWidget_ )
    return;

  //QSize sz = contentPanel_->size();
  //contentPanel_->resize(sz.width(), collapsed_ ? height_ : sz.height());
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

  // store content widget
  contentWidget_ = content;

  /** firstly create additional panel for content widget
   */

  // create layout for content panel
  contentPanelLayout_ = new QVBoxLayout;

  // add content panel layout to main layout
  mainLayout_->addLayout(contentPanelLayout_);
  contentPanelLayout_->setContentsMargins( QMargins(0,0,0,0) );
  
  // create panel for content widget
  contentPanel_ = new QWidget(this);

  // add content panel to its layout
  contentPanelLayout_->addWidget(contentPanel_, 1);
  contentPanelLayout_->setAlignment( Qt::AlignBottom | Qt::AlignHCenter );


  /** then create layout inside the content panel and insert content widget into it
   */

  // create layout for content widget (inside the content panel)
  contentWidgetLayout_ = new QVBoxLayout;

  // add layout for content widget
  contentPanel_->setLayout(contentWidgetLayout_);

  contentWidgetLayout_->setContentsMargins( QMargins(0,0,0,0) );
  //contentWidgetLayout_->setAlignment( Qt::AlignBottom | Qt::AlignHCenter );

  // add content widget to its layout
  contentWidgetLayout_->addWidget(contentWidget_, 0 );

  // set content panel as content widget parent
  contentWidget_->setParent(contentPanel_);


  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  adjustSize();
}

void QFoldingContainer::collapse()
{
  collapsed_ = true;
  collapseButton_->setText(tr("+"));
  update();
  updateGeometry();
}

void QFoldingContainer::expand()
{
  collapsed_ = false;
  collapseButton_->setText(tr("-"));
  update();
  updateGeometry();
}

void QFoldingContainer::onCollapsed(bool collapsed)
{
  if ( collapsed )
    collapse();
  else
    expand();
}

QSize QFoldingContainer::sizeHint() const
{
  int sx = captionLayout_->sizeHint().width();
  if ( contentPanelLayout_ && sx < contentPanelLayout_->sizeHint().width() )
    sx = contentPanelLayout_->sizeHint().width();

  int sy = captionLayout_->sizeHint().height();
  if ( contentPanelLayout_ )
  {
    if ( collapsed_ )
      sy += 20;
    else
      sy += contentPanelLayout_->sizeHint().height();
  }

  return QSize(sx, sy);
}