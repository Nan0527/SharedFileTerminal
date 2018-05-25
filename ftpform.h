#ifndef FTPFORM_H
#define FTPFORM_H

#include <QWidget>
#include "ftpmanager.h"

namespace Ui {
class ftpForm;
}

class ftpForm : public QWidget
{
    Q_OBJECT

public:
    explicit ftpForm(QWidget *parent = 0);
    ~ftpForm();

private:
    Ui::ftpForm *ui;

private slots:
    void S_updateProgess(int);
    void S_updateProgess2(int);

    void on_downloadBn_clicked();

    void on_uploadBn_clicked();

    void on_downloadBn_2_clicked();

    void on_abort_clicked();

    void on_abort_2_clicked();

    void on_abort_3_clicked();

    void on_downloadBn_3_clicked();

private:
    FtpManager *manager;
    FtpManager *manager2;
};

#endif // FTPFORM_H
