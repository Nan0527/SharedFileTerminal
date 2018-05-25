#include "barcode.h"
#include <QDebug>
#include <QCoreApplication>
Barcode::Barcode()
{

}
Barcode::~Barcode()
{

}

void Barcode::printBarcode(const QString &strTitle)
{
    //打印部分
    //这里先生成图片
    QString strImagePath("");
    strImagePath = QCoreApplication::applicationDirPath() + "//test.png";//获取当前文件夹路径
    struct zint_symbol * my_symbol = ZBarcode_Create();
    my_symbol->symbology = BARCODE_CODE93;//二維碼:BARCODE_AZTEC  //條形碼:BARCODE_CODE93,BARCODE_CODE128
    my_symbol->scale=0.5;//改變比例，默認1.0

    strcpy(my_symbol->outfile, strImagePath.toLocal8Bit().toStdString().c_str());
    ZBarcode_Encode(my_symbol, (unsigned char*)strTitle.toLocal8Bit().toStdString().c_str(), 0);//傳入條形碼編導
    ZBarcode_Print(my_symbol, 0);
    ZBarcode_Delete(my_symbol);
    //绘制
    QPrinter printer;
    QPrintDialog printdialog(&printer);//    QPrintDialog printdialog(&printer, this);
    if (printdialog.exec())//调用打印驱动
    { //这里我如何保证不进行拉伸呢
//        QString strname = printer.printerName();
        int dpi = printer.logicalDpiX();
        int nmm = printer.paperRect(QPrinter::Millimeter).width();
        int width = std::min(nmm, 60)*(dpi*1.0/25.4);     //这里选择80mm纸张
        QPainter painter(&printer);
        QImage image(strImagePath, "PNG");

        QRect rtwindow = painter.window();
        QRect rtview = painter.viewport();
        int nmax = 0;
        if (image.width() + 20 < width)
        {
            nmax = std::max(image.width() + 20, width);
        }else{
            nmax = std::min(image.width() + 20, width);
        }
        QRect rtimage(0, 0, nmax, rtwindow.height());
        QRect rtimageview(0, 0, nmax, rtview.height());
        int nmin = std::min(image.width(), nmax - 60);
        QRectF rtdes(40, 10, nmin, 100);
        QRectF rtsrc(0, 0, image.width(), image.height());
        painter.setWindow(rtimage);
        painter.setViewport(rtimageview);
        painter.drawImage(rtdes, image, rtsrc);
        painter.setWindow(rtwindow);
        painter.setViewport(rtview);
    }
//    QFile::remove(strImagePath);//QFile file(strImagePath);//这里再删除图片
}

// iFormat 为1表示打印成PDF，否则表示输出到打印机
// strHtml是HTML格式的打印内容，strPdfFile是PDF文件路径。
void Barcode::printDocument(const QString &strHtml,const QString &strPdfFile, int iFormat = 1)
{
    QPrinter p;
//    QPrintDialog printDialog(&p);
    QTextDocument doc;
    doc.setHtml(strHtml);
//    if(printDialog.exec())
//    {
    if (iFormat == 1)
    {
        p.setPageSize(QPrinter::A4);
        p.setOutputFormat(QPrinter::PdfFormat);
        p.setOutputFileName(strPdfFile);
        doc.print(&p);
    }else{
        doc.setPageSize(QSizeF(p.logicalDpiX()*(60/25.4),
        p.logicalDpiY()*(35/25.4)));
//        p.setResolution(30);
//        p.setPrintRange(p.CurrentPage);
        p.setOutputFormat(QPrinter::NativeFormat);
        doc.print(&p);
    }
//    }
}

void Barcode::createBarcode(const QString &strTitle,const int dimensions)
{
    QString strImagePath;
//    strImagePath = QCoreApplication::applicationDirPath() + "//"+strTitle+".png";
    struct zint_symbol * my_symbol = ZBarcode_Create();
    my_symbol->show_hrt=0;//0為隱藏文字 1為不隱藏
    if(dimensions==1)//維度
    {
        strImagePath = QCoreApplication::applicationDirPath() + "//Barcode.png";
        my_symbol->symbology=BARCODE_CODE93;// BARCODE_CODE128 BARCODE_HIBC_128//條形碼
//        my_symbol->height=30;
    }else{
        strImagePath = QCoreApplication::applicationDirPath() + "//test.png";
        my_symbol->symbology=BARCODE_QRCODE;//二維碼
        my_symbol->scale=0.5;//圖片放縮比例
    }
//      ZBarcode_Encode(my_symbol,(unsigned char*)identify_code,0);
    strcpy(my_symbol->outfile, strImagePath.toLocal8Bit().toStdString().c_str());
    ZBarcode_Encode(my_symbol, (unsigned char*)strTitle.toLocal8Bit().toStdString().c_str(), 0);//傳入條形碼編導
    ZBarcode_Print(my_symbol, 0);
    ZBarcode_Delete(my_symbol);
}

bool Barcode::SetBarCode(double x, double y,double length, double width)//把条形码或二维码插入到excel里
{
    //设置参数代码
    bool bar = false;
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    // 打开工作簿方式一：新建
    work_books->dynamicCall("Add"); // 新建一个工作簿
    QAxObject* workbook = excel.querySubObject("ActiveWorkBook"); // 获取当前工作簿
    QAxObject *pWorksheet = workbook->querySubObject("Sheets(int)", 1);  //Sheets(int)也可换用Worksheets(int)
    // cellX->dynamicCall("SetValue(conts QVariant&)", 100); // 设置单元格的值
    QAxObject *shapes = pWorksheet->querySubObject("Shapes");
    qDebug()<<"hello 1";
    if( shapes )
    {
       qDebug()<<"hello 2";
       QAxObject *emptyCell = pWorksheet->querySubObject("Cells(int,int)", 1,1 );
       emptyCell->dynamicCall("Select(void)");// 先选中一个空白的地方
    //         emptyCell->setProperty("Value", "Java");  //设置单元格值
    //         QString picDir=QString(".//test.png");
       QString picDir=QString("C:\\log\\Barcode.png");
       shapes->dynamicCall("AddPicture( QString&, bool, bool, double, double, double, double)",picDir,true,true,x,y,length,width);//最后面四个参数意义分别是x坐标，y坐标,长度，宽度
       QAxObject *cell_3_1 = pWorksheet->querySubObject("Cells(int,int)", 3, 1);
       cell_3_1->setProperty("Value", "Material");
    //           QAxObject *range = pWorksheet->querySubObject("Range(QVariant)","$B$1:$D$1");
    //           range->dynamicCall("Select(void)");
       bar = true;
    }
    else
    {
       bar = false;
    }
    system("del C:\\log\\Barcode.png");
    return bar;
}

void Barcode::changeImageSize(const QString &strTitle, int height, int width)//未完成
{
    QString strImagePath = QCoreApplication::applicationDirPath() + "//R"+strTitle+".png";
//    QPixmap map(strImagePath);
//    map = map.scaled(height, width);
//    map.save(strImagePath);
    QPixmap pix(strImagePath);
    QPainter painter;
    painter.drawPixmap(0,0,pix);
    QPixmap pix2=pix.scaled(QSize(50,30));
    painter.drawPixmap(0,0,pix2);
    pix2.save(strImagePath);
}
//labol样式编写设定
QString Barcode::strHtml(const QString &strTitle, const QString &strUer, const QString &strVal, const QString &strLot, const QString &strDC, const QString &strLocal, const QString &strQty, QString freq, QString spn, QString width, QString height)
{
    height=30;
    width=90;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString m_day =current_date_time.toString("yyyy-MM-dd");
    QString strImagePath = QCoreApplication::applicationDirPath() + "//Barcode.png";
    QString ImagePath = QCoreApplication::applicationDirPath() + "//test.png";
//    QString strImagePath = QCoreApplication::applicationDirPath() + "//R"+strTitle+".png";
    QString strhtml=QString("<HTML><HEAD><TITLE></TITLE><META charset=UTF-8></HEAD><BODY>"
                            "<div style = 'font-size:10px; margin-left:30px'>"
                            "<span>User:%1 &nbsp;DAT:%9</span> <br>"
                            "<span>ID &nbsp;<img src='%2' width='%12' height='%13'> &nbsp;&nbsp; <img src='%11'width='40' height='55'></span> <br>"
                            "<span>(R)%3&nbsp;Freq:%10MHz</span><br> "
                            "<span>VAL:%4 &nbsp;</span><br>"
                            "<span>LOC:%5&nbsp;SPN:%8</span><br>"
                            "<span>D/C:%6&nbsp;QTY:%7</span>"
                            "</div></BODY></HTML>").arg(strUer).arg(strImagePath).arg(strTitle).arg(strVal).arg(strLocal).arg(strDC).arg(strQty).arg(spn).arg(m_day).arg(freq).arg(ImagePath).arg(width).arg(height);
    return strhtml;
}
//QString Barcode::strHtml(const QString &strTitle, const QString &strUer, const QString &strVal, const QString &strLot, const QString &strDC, const QString &strLocal, const QString &strQty, QString freq, QString spn)
//{
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString m_day =current_date_time.toString("yyyy-MM-dd");
//    QString strImagePath = QCoreApplication::applicationDirPath() + "//Barcode.png";
//    QString ImagePath = QCoreApplication::applicationDirPath() + "//test.png";
//    //    QString strImagePath = QCoreApplication::applicationDirPath() + "//R"+strTitle+".png";
//    QString strhtml=QString("<HTML><HEAD><TITLE></TITLE><META charset=UTF-8></HEAD><BODY>"
//                            "<div style = 'font-size:10px; margin-left:30px'>"
//                            "<span>Desc  &nbsp;  &nbsp; User:%1</span> <br>"
//                            "<span>ID &nbsp;<img src='%2' width='90' height='30'>&nbsp;<img src='%12'width='40' height='55'></span> <br>"
//                            "<span>(R)%3 &nbsp; SPN:%11</span><br> "
//                            "<span>VAL:%4 &nbsp;</span><br>"
//                            "<span>LOC:%5&nbsp;Freq:%10MHz</span><br>"
//                            "<span>D/C:%6&nbsp;QTY:%7</span><br>"
//                            "<span>Lot:%8&nbsp;DAT:%9</span>"
//                            "</div></BODY></HTML>").arg(strUer).arg(strImagePath).arg(strTitle).arg(strVal).arg(strLocal).arg(strDC).arg(strQty).arg(strLot).arg(m_day).arg(freq).arg(spn).arg(ImagePath);
//    return strhtml;
//}






//QString Barcode::strHtml(const QString &strTitle, const QString &strUer, const QString &strVal, const QString &strLot, const QString &strDC, const QString &strLocal, const QString &strQty, QString freq, QString spn)
//{
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString m_day =current_date_time.toString("yyyy-MM-dd");
//    QString strImagePath = QCoreApplication::applicationDirPath() + "//Barcode.png";
//    //    QString strImagePath = QCoreApplication::applicationDirPath() + "//R"+strTitle+".png";
//    QString strhtml=QString("<HTML><HEAD><TITLE></TITLE><META charset=UTF-8></HEAD><BODY>"
//                            "<div style = 'font-size:10px; margin-left:30px'>"
//                            "<span>前期測試階段</span> <br>"
//                            "<span>Desc  &nbsp;  &nbsp; User:%1</span> <br>"
//                            "<span>ID &nbsp;<img src='%2' width='90' height='20'></span> <br>"
//                            "<span>(R)%3 &nbsp; SPN:%11</span> <br> "
//                            "<span>VAL: %4 &nbsp;</span> <br>"
//                            "<span>LOC:%5</span> <br>"
//                            "<span>D/C:%6 &nbsp; QTY:%7 </span> <br>"
//                            "<span>Lot:%8 &nbsp; DAT:%9</span>"
//                            "<br><span>Freq:%10MHz</span>"
//                            "</div></BODY></HTML>").arg(strUer).arg(strImagePath).arg(strTitle).arg(strVal).arg(strLocal).arg(strDC).arg(strQty).arg(strLot).arg(m_day).arg(freq).arg(spn);
//    return strhtml;
//}

//QString Barcode::strHtml(const QString &strTitle, const QString &strUer, const QString &strVal, const QString &strLot, const QString &strDC, const QString &strLocal, const QString &strQty)
//{
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString m_day =current_date_time.toString("yyyy-MM-dd");
//    QString strImagePath = QCoreApplication::applicationDirPath() + "//R"+strTitle+".png";
//    QString strhtml=QString("<HTML><HEAD><TITLE></TITLE><META charset=UTF-8></HEAD><BODY>"
//                            "<div style = 'font-size:7px; margin-left:20px'><span>Desc &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; User %1</span> <br>"
//                            "<span>ID &nbsp;<img src='%2' width='90' height='20'></span> <br>"
//                            "<span>(R)%3</span> <br> "
//                            "<span>VAL &nbsp; %4 &nbsp; LOC &nbsp; %5</span> <br>"
//                            "<span>D/C &nbsp;%7 &nbsp; QTY &nbsp; %6 </span> <br>"
//                            "<span>Lot &nbsp; %8 &nbsp; DAT &nbsp; %9</span>"
//                            "</div></BODY></HTML>").arg(strUer).arg(strImagePath).arg(strTitle).arg(strVal).arg(strLocal).arg(strDC).arg(strQty).arg(strLot).arg(m_day);
//    return strhtml;
//}




//QString strhtml=QString("<HTML><HEAD><TITLE></TITLE><META charset=UTF-8></HEAD><BODY>"
//                        "<div style = 'font-size:10px; margin-left:30px'>"
//                        "<span>Desc  &nbsp;  &nbsp; User:%1</span> <br>"
//                        "<span>ID &nbsp;<img src='%2' width='90' height='30'>&nbsp;<img src='%11'width='40' height='55'></span> <br>"
//                        "<span>(R)%3</span><br> "
//                        "<span>VAL:%4 &nbsp;</span><br>"
//                        "<span>LOC:%5&nbsp;Freq:%10MHz</span><br>"
//                        "<span>D/C:%6&nbsp;QTY:%7</span><br>"
//                        "<span>SPN:%8&nbsp;DAT:%9</span>"
//                        "</div></BODY></HTML>").arg(strUer).arg(strImagePath).arg(strTitle).arg(strVal).arg(strLocal).arg(strDC).arg(strQty).arg(spn).arg(m_day).arg(freq).arg(ImagePath);
