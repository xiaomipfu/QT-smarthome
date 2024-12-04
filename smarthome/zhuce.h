#ifndef ZHUCE_H
#define ZHUCE_H

#include <QWidget>
#include <qdebug.h>
#include <QMessageBox>
#include "databaseop.h"
#include <QString>
class login;


namespace Ui {
class zhuce;
}

class zhuce : public QWidget
{
    Q_OBJECT

public:
    explicit zhuce(QWidget *parent = nullptr);
    ~zhuce();
    databaseop* pdatabase;
    QString sql;

    login* login;

private slots:
    void on_pushButton_clicked();

private:
    Ui::zhuce *ui;
};

#endif // ZHUCE_H
