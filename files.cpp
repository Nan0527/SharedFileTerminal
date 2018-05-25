#include "files.h"
#include <QDebug>

Files::Files()
{

}

Files::~Files()
{

}

QString Files::readFile(const QString &address,const QString &portName)//读取文件“节点：”后的内容  按行读取
{
    QString ad=path;
    ad.append("/").append(address);
    QString lineStr;

    QFile f(ad);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL,"提示","Open failed.",QMessageBox::Ok);//文件及文件夹中不能存在中文字符
        f.close();
        return lineStr;
    }
    QTextStream txtInput(&f);
     QList<QString> list;
    while(!txtInput.atEnd())
    {
        list.append(txtInput.readLine());
//        lineStr.append(txtInput.readLine());
    }
    f.close();
    if(list.size()>0)
    {
        for(int i=0;i<list.size();i++)
        {
            if(list.at(i).indexOf(portName)>=0)
            {
                lineStr=list.at(i);
                lineStr.remove(portName+":");
            }
        }
    }
   return lineStr;
}

vector<QString> Files::readFile(const QString &address)
{
    vector<QString> res;
    QString ad=path;
    ad.append("/").append(address);

    QFile f(ad);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL,"提示","Open failed.",QMessageBox::Ok);//文件及文件夹中不能存在中文字符
        f.close();
        return res;
    }
    QTextStream txtInput(&f);
    while(!txtInput.atEnd())
    {
//        qDebug()<<txtInput.readLine().toStdString();
//        if(!txtInput.readLine().trimmed().isEmpty())
//        {
            res.push_back(txtInput.readLine());
//        }
    }
    f.close();
    return res;
}


QString Files::newFile(const QString filename)//创建新文件 并返回路径
{
    QString strPath=path;
    strPath.append("/").append(filename);
    QFile file(strPath);
    if ( file.exists())
    {
            return strPath;
    }
    file.open( QIODevice::WriteOnly );
    file.close();
//    QMessageBox::information(NULL,"提示",strPath,QMessageBox::Ok);
    return strPath;
}

int Files::fileSize(const QString filename)//获取文件的大小
{
    QString strPath=path;
    strPath.append("/").append(filename);
    QFile file(strPath);
    int size=file.size();
    return size;
}

void Files::deletePng(const QString &filename)//删除png文件
{
    QString strImagePath = path + "//R"+filename+".png";
    QString str="del ";
    str.append(strImagePath);
    system(str.toStdString().data());
}

 void Files::writeLog(const QString &str)//写log
 {
     QFile file(".//log.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append)) {
         QTextStream out(&file);
         out << str << "\r\n"<<endl;
     }else{
         return;
     }
 }
