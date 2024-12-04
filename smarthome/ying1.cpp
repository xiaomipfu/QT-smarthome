#include "ying1.h"
#include "ui_ying1.h"

ying1::ying1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ying1)
{
    ui->setupUi(this);
    isPlaying =true;

    player = new QMediaPlayer;//媒体播放器
    playlist = new QMediaPlaylist;//媒体播放列表
    player->setPlaylist(playlist);//将媒体列表放入播放器

    ui->horizontalSlider_2->setValue(50);

    //音乐播放器进度条和槽函数关联
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedSolt(qint64)));
    //音乐播放器播放时长和进度条关联
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChangedSlot(qint64)));
    //播发器音量关联
    //connect(ui->yin_button,entered)


           // ui->yin_button->setAttribute(Qt::WA_Hover); // 允许按钮接收悬浮事件
            //connect(ui->yin_button, &QPushButton::entered, ui->yinliang_Slider, &QSlider::show);
           // connect(ui->yin_button, &QPushButton::left, ui->yinliang_Slider, &QSlider::hide);

    QStringList list;


        list.append("歌曲");
        list.append("专辑");
        list.append("歌手");
        list.append("时长");
        //将声明一个模块表，并放入tableView
        pModel=new QStandardItemModel(4,4,ui->tableView);
        //设置模块表的表头
        pModel->setHorizontalHeaderLabels(list);

        ui->tableView->setModel(pModel);




        //建立数据库连接
           if(QSqlDatabase::contains("qt_sql_default_connection")==true)
           {
               database=QSqlDatabase::database("qt_sql_default_connection");
               qDebug()<<"已经有连接"<<endl;
           }
           else
           {
               database=QSqlDatabase::database("QSQLITE");
               database.setDatabaseName("MyDataBase.db");
               qDebug()<<"创建新连接"<<endl;
           }

           //创建网络管理者
           manager = new QNetworkAccessManager(this);
           //使其和应答函数连接
           connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));



//           setStyleSheet(
//                              //正常状态样式
//                              "QPushButton{"
//                              "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
//                              "border-style:outset;"                  //边框样式（inset/outset）
//                              "border-width:4px;"                     //边框宽度像素
//                              "border-radius:10px;"                   //边框圆角半径像素
//                              "border-color:rgba(255,255,255,30);"    //边框颜色
//                              "font:bold 10px;"                       //字体，字体大小
//                              "color:rgba(0,0,0,100);"                //字体颜色
//                              "padding:6px;"                          //填衬
//                              "}"
//                              //鼠标按下样式
//                              "QPushButton:pressed{"
//                              "background-color:rgba(100,255,100,200);"
//                              "border-color:rgba(255,255,255,30);"
//                              "border-style:inset;"
//                              "color:rgba(0,0,0,100);"
//                              "}"
//                              //鼠标悬停样式
//                              "QPushButton:hover{"
//                              "background-color:rgba(100,255,100,100);"
//                              "border-color:rgba(255,255,255,200);"
//                              "color:rgba(0,0,0,200);"
//                              "}");



           QFile file(":/ying1.qss"); // 假设style.qss位于资源文件中
               if (file.open(QFile::ReadOnly))
               {
                   QString stylesheet = QString(file.readAll());//读取文件中的所有内容返回给QString的构造函数
                   setStyleSheet(stylesheet); // 应用全局样式
                   file.close();
                   qDebug()<<"资源文件设置成功"<<endl;
               }


               manager->get(QNetworkRequest(QUrl(QString("http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=刀郎&type=1&offset=0&total=true&limit=10"))));

}





void ying1::replyFinished(QNetworkReply* reply)
{
    qDebug()<<"--------\"hello\"--------"<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)<<endl;
//    QNetworkRequest::HttpStatusCodeAttribute网址返回的状态码
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)
    {
        qDebug()<<"访问服务器成功"<<endl;
        //qDebug()<<QString(reply->readAll())<<endl;
        parseJson(reply->readAll());
    }

}


void ying1::parseJson(QByteArray byteArray)
{

    int id=-1;
    QString songName;
    QString albumName;
    QString singerName;
    float duration=-1;
    musicIDList.clear();//清空ID号
    playlist->clear();//清空播放列表


    QJsonDocument doc = QJsonDocument::fromJson(byteArray);//直接从字节数组中获得一个JSON文档
    if(doc.isObject())
    {
        qDebug()<<"该文档是一个对象"<<endl;
        QJsonObject obj1 = doc.object();
        if(obj1.contains("result") == false)
        {
            qDebug()<<"错误的JSON对象"<<endl;
            return;
        }
        QJsonValue var = obj1.value("result");
        QJsonObject resultObj = var.toObject();
        if(resultObj.contains("songs") == false)
        {
            qDebug()<<"JSON对象没有歌曲"<<endl;
            return;
        }
        var = resultObj.value("songs");
        if(var.isArray())
        {
            QJsonArray songsArr = var.toArray();
            qDebug()<<"一共搜索到"<<songsArr.size()<<"首歌曲"<<endl;

            for(int i=0;i<songsArr.size();++i)
            {
                QJsonObject songObj =songsArr[i].toObject();

                if(songObj.contains("id"))
                {
                    QJsonValue varID=songObj.value("id");
                    id=varID.toInt();
                }
                if(songObj.contains("name"))
                {
                    QJsonValue varName=songObj.value("name");
                    songName=varName.toString();
                }
                if(songObj.contains("album"))
                {
                    QJsonValue varAlbum=songObj.value("album");
                    if(varAlbum.isObject())
                    {
                        QJsonObject albumObj=varAlbum.toObject();//将专辑转为对象
                        if(albumObj.contains("name"))
                        {
                            QJsonValue varAlbumName=albumObj.value("name");
                            albumName=varAlbumName.toString();//传入专辑名
                        }

                    }//if(varAlbum.isObject())
                }//if(songObj.contains("album"))//歌曲对象内容是专辑
                if(songObj.contains("artists"))
                {
                    QJsonValue varArtists=songObj.value("artists");
                    if(varArtists.isArray())
                    {
                        QJsonArray arrArtists =varArtists.toArray();
                        for(int i=0;i<arrArtists.size();++i)
                        {
                            if(arrArtists[i].isObject())
                            {
                                QJsonObject artistsObj=arrArtists[i].toObject();
                                if(artistsObj.contains("name"))
                                {
                                    QJsonValue varartistName=artistsObj.value("name");
                                    singerName+=varartistName.toString();
                                    singerName+=" ";

                                }
                            }
                        }
                    }
                }

                if(songObj.contains("duration"))
                {
                    QJsonValue varDuration = songObj.value("duration");//获取关键字为duration的元素的值
                    duration = varDuration.toInt()/1000/60.0F;//把值转为整数
                }
                qDebug()<<id<<" "<<songName<<" "<<albumName<<" "<<singerName<<" "<<duration<<endl;
                musicIDList.push_back(id);//将歌id加入链表
                playlist->addMedia(QUrl(QString("http://music.163.com/song/media/outer/url?id=%1.mp3").arg(id)));
                qDebug()<<"加入了网址"<<endl;

                QStandardItem *item = new QStandardItem(songName);//歌名
                pModel->setItem(i, 0, item);
                item = new QStandardItem(albumName);
                pModel->setItem(i, 1, item);
                item = new QStandardItem(singerName);
                pModel->setItem(i, 2, item);
                item = new QStandardItem(QString("%1").arg(duration));
                pModel->setItem(i, 3, item);
                singerName = "";//清空歌手名
            }//for(int i=0;i<songsArr.size();++i)
            playlist->setCurrentIndex(0);

        }//if(var.isArray())
    }//if(doc.isObject())


}

ying1::~ying1()
{
    delete ui;
}

void ying1::on_pushButton_clicked()
{
    qDebug()<<"dianji登录按钮"<<endl;
    {
        manager->get(QNetworkRequest(QUrl(QString("http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=%1&type=1&offset=0&total=true&limit=10").arg(ui->lineEdit->text()))));

    }
}



//点击tableView播放歌曲
void ying1::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<index.row()<<endl;

    playlist->setCurrentIndex(index.row());

    player->play();
}

void ying1::positionChangedSolt(qint64 position)
{
    qDebug()<<position<<endl;
    ui->horizontalSlider->setValue(position);
}

void ying1::durationChangedSlot(qint64 duration)
{
    qDebug()<<"当前歌曲时长"<<duration<<"毫秒"<<endl;
    ui->horizontalSlider->setRange(0,duration);

}

//滑块调节歌曲进度
void ying1::on_horizontalSlider_sliderReleased()
{
    qint64 var=ui->horizontalSlider->value();//得到滑块的值
    player->setPosition(var);//将滑块的值设置为播放器当前的值
}

//按下暂停播放
void ying1::on_pushButton_2_clicked()
{
    isPlaying=!isPlaying;
    if(isPlaying)
    {
        player->pause();
    }
    else

    {
        player->play();
    };



}
//滑块调音量
void ying1::on_horizontalSlider_2_sliderReleased()
{
    ui->horizontalSlider_2->setRange(0,100);
    qint64 var1=ui->horizontalSlider_2->value();
    player->setVolume(var1);
}
//音量图标按下静音
void ying1::on_yin_button_clicked()
{
    player->setVolume(0);
    ui->horizontalSlider_2->setValue(0);
}


//播放当前歌曲的上一首
void ying1::on_pushButton_3_clicked()
{
    player->playlist()->previous();
    player->play();
}
//播放下首歌
void ying1::on_pushButton_4_clicked()
{
    player->playlist()->next();
    player->play();
}





