#include "mainwindow.h"
#include <QDebug>
#include <QStackedWidget>
#include <QListWidget>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏边框
    m_border=4;
    m_state.MousePressed=false;
//    setMinimumSize(400,550);
//    setMaximumSize(800,700);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint); //setting windows tool bar icon invisiable
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mainWidget = new QWidget;
    rightWidget = new QWidget;
    topWidget=new QWidget;
    rightLayout = new QVBoxLayout(rightWidget);
    mainLayout = new QHBoxLayout(mainWidget);
    topLayout=new QHBoxLayout(topWidget);
    navigationWidget = new QNavigationWidget;
    searchwidget=new QSearchWidget;
    transactwidget=new QtransactWidget;
    historywidget=new QhistoryWidget;
    aboutwidget=new QaboutWidget;
    setupBtn = new QPushButton("Normal Button", this);
//    setupBtn=new QPushButton("设置");
    setupBtn->setText("设置");
    exitBtn=new QPushButton("退出");

    titleLabel=new QLabel("共享档案终端");

    //当前程序窗口的大小
    int width = this->geometry().width();
    int height = this->geometry().height();
    qDebug()<<width<<"   "<<height;

    rightWidget->setFixedWidth(this->geometry().width());
    qDebug()<<rightWidget->width()<<"   "<<rightWidget->height();

//    rightWidget->setFixedWidth(800 - navigationWidget->width());
    navigationWidget->setRowHeight(50);
    navigationWidget->addItem("查找");
    navigationWidget->addItem("办理");
    navigationWidget->addItem("历史");
    navigationWidget->addItem("关于");
    topLayout->setSpacing(0);
    topLayout-> setAlignment(Qt::AlignRight);
    topLayout->addWidget(titleLabel);
    topLayout->addWidget(setupBtn);
    topLayout->addWidget(exitBtn);

    //右部的堆栈窗：
    QStackedWidget *stack = new QStackedWidget(this);
    searchwidget->setFixedWidth(this->geometry().width());
    stack->addWidget(searchwidget);//查找
    stack->addWidget(transactwidget);//办理
    stack->addWidget(historywidget);//历史
    stack->addWidget(aboutwidget);//关于

    rightLayout->addWidget(topWidget);
    rightLayout->addWidget(stack, 0, Qt::AlignCenter);
    rightLayout->addStretch();

    mainLayout->setSpacing(0);//设置间距
    mainLayout->setContentsMargins(0, 0, 0, 0);//setContentsMargins与其功能相同，但是可以将左、上、右、下的外边距设置为不同的值。
//    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(navigationWidget);
    mainLayout->addWidget(rightWidget);
    mainLayout->addStretch();// 添加伸缩  放在后面是居左，上面是居右
    setCentralWidget(mainWidget);

//    connect(navigationWidget, &QNavigationWidget::currentItemChanged, this, [=](const int &current){
//        tipsLabel->setText("Item: " + QString::number(current));
//    });
    connect(navigationWidget,&QNavigationWidget::currentItemChanged,this, [=](const int &current){
                stack->setCurrentIndex(current);
            });
    connect( exitBtn, SIGNAL(clicked()), this, SLOT(close()) );

}

MainWindow::~MainWindow()
{

}

void MainWindow::search()
{

}

void MainWindow::mouseMoveRect(const QPoint& p)
{
    if(!m_state.IsPressBorder)
    {
        if( p.x()>width()-m_border&&p.y()<height()-m_border&&p.y()>m_border)//right side
        {
            setCursor(Qt::SizeHorCursor);
            m_curPos= CursorPos::Right;
        }
        else if(p.x()<m_border&&p.y()<height()-m_border&&p.y()>m_border)//left side;
        {
            setCursor(Qt::SizeHorCursor);
            m_curPos= CursorPos::Left;
        }
        else if(p.y()>height()-m_border&&p.x()>m_border&&p.x()<width()-m_border)//bottom side;
        {
            setCursor(Qt::SizeVerCursor);
            m_curPos= CursorPos::Bottom;
        }
        else if(p.y()<m_border&&p.x()>m_border&&p.x()<width()-m_border)
        {
            setCursor(Qt::SizeVerCursor);
            m_curPos=CursorPos::Top;
        }
//corner
        else if(p.y()<m_border&&p.x()>width()-m_border)
        {
            setCursor(Qt::SizeBDiagCursor);
            m_curPos=CursorPos::TopRight;
        }

        else if(p.y()<m_border&&p.x()<m_border)
        {
            setCursor(Qt::SizeFDiagCursor);
            m_curPos=CursorPos::TopLeft;
        }

        else if(p.x()>m_border&&p.y()>height()-m_border)
        {
            setCursor(Qt::SizeFDiagCursor);
            m_curPos=CursorPos::BottomRight;
        }

        else if(p.x()<m_border&&p.y()>height()-m_border)
        {
            setCursor(Qt::SizeBDiagCursor);
            m_curPos=CursorPos::BottomLeft;
        }
////
        else
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    else
    {
        switch (m_curPos) {
        case CursorPos::Right:
        {
           int setW=QCursor::pos().x()-x();
           if(minimumWidth()<=setW&&setW<=maximumWidth())
             setGeometry(x(),y(),setW,height());
            break;
        }
        case CursorPos::Left:
        {
            int setW=x()+width()-QCursor::pos().x();
            int setX=QCursor::pos().x();
            if(minimumWidth()<=setW&&setW<=maximumWidth())
              setGeometry(setX,y(),setW,height());
             break;
        }
        case CursorPos::Bottom:
        {
            int setH=QCursor::pos().y()-y();
            if(minimumHeight()<=setH&&setH<=maximumHeight())
            setGeometry(x(),y(),width(),setH);
            break;
        }
        case CursorPos::Top:
        {
           int setH=y()-QCursor::pos().y()+height();
           if(minimumHeight()<=setH&&setH<=maximumHeight())
             setGeometry(x(),QCursor::pos().y(),width(),setH);
             break;
        }
        case CursorPos::TopRight:
        {
            int setH=y()+height()-QCursor::pos().y();
            int setW=QCursor::pos().x()-x();
            int setY=QCursor::pos().y();
            if(setH>=maximumHeight())
            {
                setY=m_state.WindowPos.y()+m_state.PressedSize.height()-height();
                setH=maximumHeight();
            }
            if(setH<=minimumHeight())
            {
                setY=m_state.WindowPos.y()+m_state.PressedSize.height()-height();
                setH=minimumHeight();
            }
            setGeometry(m_state.WindowPos.x(),setY,setW,setH);
            break;
        }
        case CursorPos::TopLeft:
        {
            int setY=QCursor::pos().y();
            int setX=QCursor::pos().x();

            int setW=pos().x()+width()-setX;
            int setH=pos().y()+height()-setY;
            int totalW= m_state.WindowPos.x()+m_state.PressedSize.width();
            int totalH=m_state.WindowPos.y()+m_state.PressedSize.height();

            if(totalW-setX>=maximumWidth())
            {
                setX=totalW-maximumWidth();
                setW=maximumWidth();
            }
            if(totalW-setX<=minimumWidth())
            {
                setX=totalW-minimumWidth();
                setW=minimumWidth();
            }
            if(totalH-setY>=maximumHeight())
            {
                setY=totalH-maximumHeight();
                setH=maximumHeight();
            }
            if(totalH-setY<=minimumHeight())
            {
                setY=totalH-minimumHeight();
                setH=minimumHeight();
            }
            setGeometry(setX,setY,setW,setH);
            break;
        }
        case CursorPos::BottomRight:
        {
           int setW=QCursor::pos().x()-x();
           int setH=QCursor::pos().y()-y();
           setGeometry(m_state.WindowPos.x(),m_state.WindowPos.y(),setW,setH);
             break;
        }
        case CursorPos::BottomLeft:
        {
            int setW=x()+width()-QCursor::pos().x();
            int setH=QCursor::pos().y()-m_state.WindowPos.y();
            int setX=QCursor::pos().x();
            int totalW= m_state.WindowPos.x()+m_state.PressedSize.width();
            if(totalW-setX>=maximumWidth())
            {
                setX=totalW-maximumWidth();
                setW=maximumWidth();
            }
            if(totalW-setX<=minimumWidth())
            {
                setX=totalW-minimumWidth();
                setW=minimumWidth();
            }
            setGeometry(setX,m_state.WindowPos.y(),setW,setH);
            break;
        }
        default:
            break;
        }
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_state.PressedSize=this->size();
    m_state.IsPressBorder=false;
      setFocus();
      if (event->button() == Qt::LeftButton)
     {
          m_state.WindowPos = this->pos(); //save the prssed position
          if(QRect(m_border+1,m_border+1,width()-(m_border+1)*2,height()-(m_border+1)*2).contains(event->pos()))
          {
              m_state.MousePos = event->globalPos();
              m_state.MousePressed = true;
          }
          else
              m_state.IsPressBorder=true;
      }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    mouseMoveRect(mapFromGlobal(QCursor::pos()));
    if (m_state.MousePressed)
        {
            this->move(m_state.WindowPos + (event->globalPos() - m_state.MousePos));
        }

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
      m_state.IsPressBorder=false;
    if (event->button() == Qt::LeftButton)
    {
        this->m_state.MousePressed = false;
    }
}




//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
//    QListWidget *list=new QListWidget;
//    QListWidgetItem *item=new QListWidgetItem(list,0);
//    item->setSizeHint(QSize(100,100));
//    QWidget *w = new QWidget(list);
//    QHBoxLayout *layout=new QHBoxLayout(w);
//    QPushButton *pushButton=new QPushButton(w);
//    QCheckBox *checkBox=new QCheckBox(w);
//    layout->addWidget(checkBox);
//    layout->addWidget(pushButton);
//    w->setLayout(layout);
//    w->show();
//    list->setItemWidget(item,w);
//    list->show();
