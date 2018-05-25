#include "qaboutwidget.h"

QaboutWidget::QaboutWidget(QWidget *parent) : QWidget(parent)
{
    QQuickView *pView = new QQuickView();
    QWidget *pWidget = QWidget::createWindowContainer(pView, this);
    pView->setResizeMode(QQuickView::SizeRootObjectToView);

    topWidget = new QWidget;
    files=new Files();

    QHBoxLayout *phLayout=new QHBoxLayout(topWidget);
    QVBoxLayout *pLayout = new QVBoxLayout();

    m_pButton = new QPushButton("查询");
//    phLayout->addWidget(m_pButton);
    topLabel=new QLabel("关于");


    pLayout->addWidget(pWidget);
    pLayout->addWidget(topLabel);
    pLayout->addWidget(topWidget);
    pLayout->addStretch();

    setLayout(pLayout);

    connect(m_pButton, SIGNAL(clicked()), this, SLOT(ClickButton()));

}

QaboutWidget::~QaboutWidget()
{

}
void QaboutWidget::ClickButton()
{

}
