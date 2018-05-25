#ifndef QABOUTWIDGET_H
#define QABOUTWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QQuickView>
#include <QLineEdit>
#include <QLabel>
#include "files.h"


class QaboutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QaboutWidget(QWidget *parent = nullptr);
    ~QaboutWidget();
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

#endif // QABOUTWIDGET_H
