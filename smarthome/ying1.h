#ifndef YING1_H
#define YING1_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QMainWindow>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QList>

namespace Ui {
class ying1;
}

class ying1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ying1(QWidget *parent = nullptr);
    ~ying1();
    QSqlDatabase database ;

 void parseJson(QByteArray byteArray);


public slots:
    void replyFinished(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void  positionChangedSolt(qint64 position);

    void durationChangedSlot(qint64 position);

    void on_horizontalSlider_sliderReleased();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_2_sliderReleased();

    void on_yin_button_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ying1 *ui;
    QNetworkAccessManager * manager;
    QStandardItemModel *pModel;
    QMediaPlaylist* playlist;
    QMediaPlayer* player;
    QList<int> musicIDList;
    bool isPlaying ; //判断是否播放
};

#endif // YING1_H
