#include "zhuce.h"
#include "ui_zhuce.h"
#include <QString>
#include "login.h"


zhuce::zhuce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);

}

zhuce::~zhuce()
{
    delete ui;
}

void zhuce::on_pushButton_clicked()
{
    qDebug()<<"按下注册键"<<endl;
    //if(ui->password->text()!=ui->password2->text())
    //{
       // QMessageBox::about(this,"注册失败","两次密码不一致");
    //
    //else
    {
        pdatabase=new  databaseop;
        //if(ui->zhanghao->size()<sizeof(char[1024])&&ui->password<1024)

//        sql = "CREATE TABLE user(\
//               usename varchar(255),\
//               password varchar(255)\
//               );";
        sql=QString("INSERT INTO user VALUES ('%1','%2');").arg(ui->zhanghao->text()).arg(ui->password->text());
        QSqlQuery query;
        pdatabase->excutSql(&query,sql);
        QMessageBox::about(this,"注册成功","成功！");
        this->hide();
        login->show();
    }
}
