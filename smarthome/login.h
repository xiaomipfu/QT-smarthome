#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QDebug>
#include "mainwindow.h"
#include "databaseop.h"
#include <QMessageBox>
#include "zhuce.h"
#include <QStandardItem>



namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:

    explicit login(QWidget *parent = nullptr);
    ~login();
    databaseop* pdatabase;
    QString sql;
    zhuce zhuce;
    QSqlQuery * query;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
