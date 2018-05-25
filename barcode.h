#ifndef BARCODE_H
#define BARCODE_H

#include <QObject>
#include <QAxObject>
#include "qzint.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QString>
#include <QFile>
#include <QPainter>
#include <QDateTime>
#include <mutex>

class Barcode
{
public:
    Barcode();
    ~Barcode();
    void printBarcode(const QString &strTitle);
    void printDocument(const QString &strHtml, const QString &strPdfFile, int iFormat);
    void createBarcode(const QString &strTitle, const int dimensions);//1：生成條形碼or 2：二維碼
    QString strHtml(const QString &strTitle, const QString &strUer, const QString &strVal, const QString &strLot, const QString &strDC, const QString &strLocal, const QString &strQty, QString freq,QString spn,QString width,QString height);
    void changeImageSize(const QString &strTitle, int height, int width);
private:
    bool SetBarCode(double x, double y,double length, double width);//设置参数代码

};

#endif // BARCODE_H
