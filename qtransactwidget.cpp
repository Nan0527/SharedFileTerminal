#include "qtransactwidget.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
QtransactWidget::QtransactWidget(QWidget *parent) : QWidget(parent)
{
    QQuickView *pView = new QQuickView();
    QWidget *pWidget = QWidget::createWindowContainer(pView, this);
    pView->setResizeMode(QQuickView::SizeRootObjectToView);

    topWidget = new QWidget;
    checkBoxWidget= new QWidget;
    files=new Files();
    barcode=new Barcode();
    QHBoxLayout *phLayout=new QHBoxLayout(topWidget);
    QHBoxLayout *checkBoxLayout=new QHBoxLayout(checkBoxWidget);


    m_pButton = new QPushButton("开始办理");
    phLayout->addWidget(m_pButton);
    topLabel=new QLabel("需要材料清单");
    vector<QString> checkBoxRes=files->readFile(".//transactInitial.ini");
    for(int i=0;i<checkBoxRes.size();i++)
    {
        checkBoxLayout->addStretch();// 添加伸缩
        QCheckBox *pCheckBox = new QCheckBox(checkBoxRes.at(i));
        checkBoxLayout->addWidget(pCheckBox);
    }
    checkBoxLayout->addStretch();// 添加伸缩
    checkBoxLayout->setSpacing(10);
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pWidget);
    pLayout->addWidget(topLabel);
    pLayout->addWidget(checkBoxWidget);
    pLayout->addWidget(topWidget);
    pLayout->addStretch();

    setLayout(pLayout);

    connect(m_pButton, SIGNAL(clicked()), this, SLOT(ClicktransactButton()));

}
QtransactWidget::~QtransactWidget()
{
    delete barcode;
    delete files;
}

void QtransactWidget::ClicktransactButton()
{
    //请求二维码内容
    QString code="https://www.baidu.com/?tn=93308895_hao_pg";//待完善
    barcode->createBarcode(code,2);

    QQuickView *view = new QQuickView;
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl(QStringLiteral("qrc:/code.qml")));
//    view->setFlags(Qt::FramelessWindowHint);//无边框
    view->setColor(QColor(Qt::transparent));//透明
    view->show();
//    ::Sleep(10000);
//    view->close();
}
