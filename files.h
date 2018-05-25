#ifndef FILES_H
#define FILES_H

#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QString>
#include <QObject>
#include <QTextStream>
#include <QMessageBox>
#include <vector>
using namespace std;

class Files
{
public:
    Files();
    ~Files();
    QString readFile(const QString &address,const QString &portName);
    QString newFile(const QString filename);
    vector<QString> readFile(const QString &address);
    int fileSize(const QString filename);
    void deletePng(const QString &filename);
    void writeLog(const QString &str);
private:
    QDir dir;
    QString path=dir.currentPath();
};

#endif // FILES_H
