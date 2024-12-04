#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QMessageBox>
#include <QThread>
#include "databaseop.h"
#include "ying1.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);




    QPixmap touxiang;
    if(false == touxiang.load("qrc:/1.png"))
    {
        qDebug()<<"头像图片加载失败"<<endl;
    }

   // ui->label->setPixmap(touxiang);//放置头像
    ui->label->setScaledContents(true);
    ui->mima->setPlaceholderText("请输入密码");
    ui->zhanghao->setPlaceholderText("请输入账号");
    this->setStyleSheet("background-image: url(':/1.png');"// 表示图像路径，可以是资源文件，也可以是绝对或相对路径。
                        "background-repeat: no-repeat;"//防止背景图重复。
                         "background-position: center;");//将背景图居中显示。

    QFile file(":/login.qss"); // 假设style.qss位于资源文件中
        if (file.open(QFile::ReadOnly))
        {
            QString stylesheet = QString(file.readAll());//读取文件中的所有内容返回给QString的构造函数
            setStyleSheet(stylesheet); // 应用全局样式
            file.close();
           // qDebug()<<"资源文件设置成功"<<endl;
        }


        pdatabase=new  databaseop;
        sql = "CREATE TABLE user(\
               usename varchar(255),\
               password varchar(255)\
               );";
        //sql="INSERT INTO user VALUES ('xiao','234');";
        //pdatabase->excutSql(sql);

       query = new QSqlQuery(pdatabase->database);


}

login::~login()
{
    //delete pdatabase;
    delete ui;

}

void login::on_pushButton_clicked()
{
    qDebug()<<"按下了登录键"<<endl;

    if (false == pdatabase->database.open())
    {
        qDebug() << "Error: Failed to connect database." << pdatabase->database.lastError();
    }
    qDebug() <<"dakai"<<endl;

     sql = "SELECT * FROM user;";
    pdatabase->excutSql(query,sql);


    //int row = 0;//第0行
       //遍历查询到的所有的记录

    bool loginSuccessful = false; // 标志变量，初始为false

    while (query->next()) {
        QString name = query->value(0).toString();
        QString password = query->value(1).toString();

        if (name == ui->zhanghao->text() && password == ui->mima->text()) {
            loginSuccessful = true; // 登录成功，将标志设置为true
            break; // 找到匹配，退出循环
        }
    }

    // 根据标志显示消息框
    if (loginSuccessful)
    {
        MainWindow *chuang = new MainWindow;
        hide();
        chuang->show();
    }
    else
    {
        QMessageBox::about(this, "登录失败", "账号或者密码错误");
    }




//    if(ui->mima->text()=="123" &&ui->zhanghao->text()=="xiao")
//    {
//        MainWindow *chuang=new MainWindow;
//        hide();

//        //QMessageBox::about(this,"登录成功","登录成功！正在进入系统");
//        //QThread::sleep(2);
//        chuang->show();
//    }
//    else
//    {

//        QMessageBox::about(this,"登录失败","账号或者密码错误");
//    }


}

//按下注册按钮
void login::on_pushButton_2_clicked()
{

    hide();
    zhuce.login=this;
    zhuce.close();
    zhuce.show();

}
