#ifndef QSEARCHWIDGET_H
#define QSEARCHWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QQuickView>
#include <QLineEdit>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include "files.h"
#include "PageWidget.h"

class PageWidget;


class QSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QSearchWidget(QWidget *parent = nullptr);
    ~QSearchWidget();
    void addItem(const QString &title);
    void setWidth(const int &width);
    void setHeight(const int &height);

public:
    QPushButton *m_pButton;
private:
    QWidget *topWidget;
    QWidget *radioWidget;
    QLineEdit *m_plineEdit;
    QButtonGroup *group;
    QLabel *icoLabel;
    Files *files;
    PageWidget *pageWidget;
private:
    QList<QString> listItems;
    QString backgroundColor;
    QString selectedColor;
    int rowHeight;
    int currentIndex;

signals:
    void currentItemChanged(const int &index);


public slots:


private slots:
    void changeMaxPage(int);
    void ClickSearchButton();



};

#endif // QSEARCHWIDGET_H
