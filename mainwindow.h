#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include "qnavigationwidget.h"
#include "qsearchwidget.h"
#include "qtransactwidget.h"
#include "qhistorywidget.h"
#include "qaboutwidget.h"

enum CursorPos{Default,Right,Left,Bottom,Top,TopRight,TopLeft,BottomRight,BottomLeft};
struct pressWindowsState
{
    bool    MousePressed;
    bool   IsPressBorder;
    QPoint  MousePos;
    QPoint  WindowPos;
    QSize PressedSize;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QMainWindow *parent=0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QWidget *rightWidget;
    QWidget *topWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *topLayout;
    QNavigationWidget *navigationWidget;
    QSearchWidget *searchwidget;
    QtransactWidget *transactwidget;
    QhistoryWidget *historywidget;
    QaboutWidget *aboutwidget;
    QPushButton *exitBtn;
    QPushButton *setupBtn;
    QLabel *titleLabel;

private:
    void search();
    void mouseMoveRect(const QPoint &p);
private  slots:
//    void ClickExitButton();



protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    pressWindowsState m_state;
    int m_border;
    CursorPos m_curPos;

};	

#endif
