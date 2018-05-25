#ifndef QHISTORYWIDGET_H
#define QHISTORYWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QQuickView>
#include <QLineEdit>
#include <QLabel>
#include "files.h"


class QhistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QhistoryWidget(QWidget *parent = nullptr);
    ~QhistoryWidget();
public:
    QPushButton *m_pButton;
private:
    QWidget *topWidget;
    QLineEdit *m_plineEdit;
    QLabel *topLabel;
    Files *files;




signals:

public slots:

private slots:
    void ClickButton();
};

#endif // QHISTORYWIDGET_H
