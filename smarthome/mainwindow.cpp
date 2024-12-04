#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setStyleSheet("background-image: url(':/background.jpg');"// 表示图像路径，可以是资源文件，也可以是绝对或相对路径。
//                        "background-repeat: no-repeat;"//防止背景图重复。
//                         "background-position: center;");//将背景图居中显示。

    resize(500, 500);
//    ui->spinBox->setStyleSheet(
//                "QSpinBox {"
//                 "   background-color: #f0f0f0;"
//                 "   border: 2px solid #888888;"
//                 "   border-radius: 5px;"
//                 "   padding: 5px;"
//                 "   font-size: 16px;"
//                 "}"
//                 "QSpinBox::up-button, QSpinBox::down-button {"
//                 "   background-color: #c0c0c0;"
//                 "   border: none;"
//                 "   width: 20px;"
//                 "}"
//                 "QSpinBox::up-button:hover, QSpinBox::down-button:hover {"
//                 "   background-color: #a0a0a0;"
//                 "}"
//    );
    QPixmap kong_pixmap;
    QPixmap yusan_pixmap;
    kong_pixmap.load(":/kongtiao.png");
    yusan_pixmap.load(":/yusan.png");
    ui->yusan_label->setPixmap(yusan_pixmap);
    ui->kong_label->setPixmap(kong_pixmap);


    //show();




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{


}

//音乐盒
void MainWindow::on_pushButton_clicked()
{

    hide();
    ying1.show();

}
