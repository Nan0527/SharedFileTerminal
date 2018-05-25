#include "qsearchwidget.h"
#include <QListWidget>

QSearchWidget::QSearchWidget(QWidget *parent) : QWidget(parent)
{
   // this->resize(800,600);
    QQuickView *pView = new QQuickView();
    QWidget *pWidget = QWidget::createWindowContainer(pView, this);
    pView->setResizeMode(QQuickView::SizeRootObjectToView);
    /*pView->setSource(QUrl("qrc:/test.qml"));*/
    pView->setPosition(0,0);
    files=new Files();

    //顶端查询模块
    topWidget = new QWidget;
    topWidget->showMaximized();
    radioWidget= new QWidget;
    pageWidget = new PageWidget();
    QHBoxLayout *phLayout=new QHBoxLayout(topWidget);
    QHBoxLayout *pradioLayout=new QHBoxLayout(radioWidget);
    m_plineEdit=new QLineEdit(this);
    m_pButton = new QPushButton(this);
    icoLabel=new QLabel;
    m_pButton->setText("查询");
    vector<QString> radioRes=files->readFile(".//searchInitial.ini");


    //设置图标
    QPixmap tempPix = QPixmap(":/image/page.ico");
    tempPix.scaled(QSize(0.5, 0.5), Qt::KeepAspectRatio);
    icoLabel->setAlignment(Qt::AlignCenter);
    icoLabel->setPixmap(tempPix);

    phLayout->addStretch();// 添加伸缩
    phLayout->addWidget(m_plineEdit);
    phLayout->addWidget(m_pButton);
    phLayout->addStretch();
    phLayout->setContentsMargins(10, 10,0, 0);
    //radio按钮
    group = new QButtonGroup;
    for(int i=0;i<radioRes.size();i++)
    {
        pradioLayout->addStretch();// 添加伸缩
        QRadioButton *radio = new QRadioButton(radioRes.at(i));
        group->addButton(radio,i);
        pradioLayout->addWidget(radio);
    }
    pradioLayout->addStretch();// 添加伸缩
    pradioLayout->setSpacing(10);


//添加list布局
    QListWidget *list=new QListWidget;
//    list->setFixedHeight(600);
//    list->setFixedWidth(800);
    QListWidgetItem *item=new QListWidgetItem(list,0);
    list->setIconSize(QSize(110,145));
    item->setSizeHint(QSize(100,100));
    list->setViewMode(QListWidget::IconMode );
    list->setResizeMode(QListWidget::Adjust);
    list->setMovement(QListWidget::Static);
    //QT设置QListwidget平滑滚动
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置垂直滚动条显示方式（ScrollBarAsNeeded：按需显示，ScrollBarAlwaysOff：隐藏，ScrollBarAlwaysOn：常显）
    list->setVerticalScrollMode(QListWidget::ScrollPerPixel);
//    list->verticalScrollBar()->setSingleStep(10);

    QWidget *w = new QWidget(list);
    w->setFixedWidth(700);
    w->showMaximized();
    QHBoxLayout *layout=new QHBoxLayout(w);
    QPushButton *pushButton=new QPushButton(w);
    pushButton->setText("获取");
    QPushButton *pushBtn=new QPushButton(w);
    pushBtn->setText("查看");

    QLabel *lab1 = new QLabel(tr("文件名称   文件名称"));
    lab1->setFixedWidth(100);
    layout->addWidget(lab1);
    layout->addWidget(pushButton);
    layout->addWidget(pushBtn);
    w->setLayout(layout);
    list->setItemWidget(item,w);


 //整体布局
//    QVBoxLayout *pLayout = new QVBoxLayout(pWidget);
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(icoLabel);
    pLayout->addWidget(pWidget);
    pLayout->addWidget(topWidget);
    pLayout->addWidget(radioWidget);
//    pLayout->addStretch();
//    pLayout->setSpacing(10);
//    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->addWidget(list);
    pLayout->addStretch();
    pLayout->addWidget(pageWidget);// 把分页的组件加入到当前窗口
    setLayout(pLayout);


//    widget = new QWidget;
//    listwidget = new QListWidget(this);
//    layout = new QHBoxLayout(widget);
//    lab1 = new QLabel;
//    btn1 = new QPushButton;
//    layout->addWidget(lab1);
//    layout->addWidget(btn1);
//    lab1->setText(tr("把整个widget放入到item中"));
//    btn1->setText(tr("可点击"));
//    widget->setLayout(layout);


    // QML 与 Qt Widgets 通信
    /*QObject *pRoot = (QObject*)pView->rootObject();
    if (pRoot != NULL) {
       connect(pRoot, SIGNAL(qmlSignal()), this, SLOT(receiveFromQml()));
       connect(m_pButton, SIGNAL(clicked(bool)), pRoot, SIGNAL(cSignal()));
    }*/
//    setFixedWidth(800);
    setHeight(500);

    //连接查询功能的信号槽
    connect(m_pButton, SIGNAL(clicked()), this, SLOT(ClickSearchButton()));
    connect(m_plineEdit, SIGNAL(returnPressed()), this, SLOT(ClickSearchButton()));


}

QSearchWidget::~QSearchWidget()
{

}


void QSearchWidget::addItem(const QString &title)
{
    listItems << title;

    update();
}

void QSearchWidget::setWidth(const int &width)
{
    setFixedWidth(width);
}


void QSearchWidget::setHeight(const int &height)
{
    setFixedHeight(height);
}


void QSearchWidget::ClickSearchButton()//查询按钮事件  待完善
{
    QString str=m_plineEdit->text();
    if(str.isEmpty())
        return;
    QList<QAbstractButton*> list = group->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(pButton->text()).arg(strStatus);
    }

    int num;
    changeMaxPage(num);//设置最大页码
//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeMaxPage()));
//    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(changeMaxPage()));

}

void QSearchWidget::changeMaxPage(int num) {
//    pageWidget->setMaxPage(ui->lineEdit->text().toInt());//待修改

    pageWidget->setMaxPage(num);
    pageWidget->setCurrentPage(1);
}
