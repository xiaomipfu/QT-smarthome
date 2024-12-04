#include "tianqi.h"
#include "ui_tianqi.h"

tianqi::tianqi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tianqi)
{
    ui->setupUi(this);
}

tianqi::~tianqi()
{
    delete ui;

}
