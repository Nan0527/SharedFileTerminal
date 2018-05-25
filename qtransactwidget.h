#ifndef QTRANSACTWIDGET_H
#define QTRANSACTWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QQuickView>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <vector>
#include <QMessageBox>
#include "files.h"
#include "barcode.h"

class QtransactWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QtransactWidget(QWidget *parent = nullptr);
    ~QtransactWidget();

public:
    QPushButton *m_pButton;
private:
    QWidget *topWidget;
    QWidget *checkBoxWidget;
    QLineEdit *m_plineEdit;
    QLabel *topLabel;
    Files *files;
    Barcode *barcode;
signals:

public slots:
    void ClicktransactButton();
};

#endif // QTRANSACTWIDGET_H
