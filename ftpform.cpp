#include "ftpform.h"
#include "ui_ftpform.h"

ftpForm::ftpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ftpForm)
{
    ui->setupUi(this);
    manager = new FtpManager("192.168.136.144","zhj","123456",21,this);
    manager2 = new FtpManager("192.168.136.144","zhj","123456",21,this);
    connect(manager,SIGNAL(G_getProgressVal(int)),SLOT(S_updateProgess(int)));
    connect(manager2,SIGNAL(G_getProgressVal(int)),SLOT(S_updateProgess2(int)));
}

ftpForm::~ftpForm()
{
    delete ui;
}

//更新进度条

void ftpForm::S_updateProgess(int _val)
{

    ui->progressBar->setValue(_val);
}


//更新进度条
void ftpForm::S_updateProgess2(int _val)
{

    ui->progressBar_2->setValue(_val);
}


//普通下载
void ftpForm::on_downloadBn_clicked()
{
    manager->S_dloadFile("续传","G:/QTWorkspace.zip");
}

//普通上传
void ftpForm::on_uploadBn_clicked()
{
    manager->S_uloadFile(QString("G:/学习"),"续传");
}

//下载（续传）
void ftpForm::on_downloadBn_2_clicked()
{
    manager2->S_dloadFile("续传","G:/QTWorkspace.zip",true);
}

//停止
void ftpForm::on_abort_clicked()
{
    manager2->S_abort();
}

//上传（续传）
void ftpForm::on_abort_2_clicked()
{
    manager2->S_uloadFile("D:/QFtp续传.rar","QFtp续传.rar",true);
}

//停止
void ftpForm::on_abort_3_clicked()
{
    manager->S_abort();
}

//显示文件列表
void ftpForm::on_downloadBn_3_clicked()
{
    manager->S_list();
}
