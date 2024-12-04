#ifndef TIANQI_H
#define TIANQI_H

#include <QMainWindow>

namespace Ui {
class tianqi;
}

class tianqi : public QMainWindow
{
    Q_OBJECT

public:
    explicit tianqi(QWidget *parent = nullptr);
    ~tianqi();

private:
    Ui::tianqi *ui;
};

#endif // TIANQI_H
