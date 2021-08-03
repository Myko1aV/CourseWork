#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QMessageBox>
#include <QPushButton>
#include <math.h>
#include <poizd.h>
#include "mainwindow.h"
#include<QMediaPlayer>
bool a = true;
bool b = false;
bool c = false;
Poizd baz;
bool sound1=false;
QMediaPlayer* player1;
MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    player1=new QMediaPlayer;
    ui->setupUi(this);

    ui->lineEdit_2->setHidden(0);
    ui->lineEdit_3->setHidden(0);
    ui->lineEdit_4->setHidden(0);
    ui->lineEdit_5->setHidden(0);
    ui->lineEdit->setVisible(true);
    ui->lineEdit_8->setHidden(1);
    ui->label->setText("Input station name and time interval");
}
void MainWindow1::fromA(Poizd z ,bool s,QMediaPlayer*q)
{
    baz=Poizd(z);
    sound1=s;
    player1=q;
}
MainWindow1::~MainWindow1()
{
    delete ui;
}
void MainWindow1::on_pushButton_pressed()
{
    try{
        QString st,en,d1,d2,a1,a2,s;
        st=ui->lineEdit->text();
        d2=ui->lineEdit_3->text();
        a1=ui->lineEdit_4->text();
        a2=ui->lineEdit_5->text();
        d1=ui->lineEdit_2->text();
        en=ui->lineEdit_8->text();
        if(st!=nullptr && d1!=nullptr && d2!=nullptr&& a1!=nullptr && a2!=nullptr){
            for(int i=0;i<st.size();++i){
                if(!st[i].isLetter()){
                    throw (QString)"Enter station name using only letters";
                }
            }
            for (int i=0;i<2;i++) {
                if(d1[i].isLetter()||d2[i].isLetter()||a1[i].isLetter()||a2[i].isLetter())
                    throw (QString)"Enter time using only numbers";
            }
            if(d1.toInt()>24||d1.toInt()<0|| d2.toInt()>59||d2.toInt()<0||a1.toInt()>24||a1.toInt()<0||a2.toInt()>59||a2.toInt()<0){
                throw (QString)"Enter corect time";
            }
            if(st[0].isLower())st[0]=st[0].toUpper();
            double a,b;
            a=(d1.toInt()+d2.toDouble()/60.0);
            b=(a1.toInt()+a2.toDouble()/60.0);
            if(ui->comboBox->currentIndex()==0){
                QString s=baz.search(st.toStdString(),a,b,baz,0);
                QMessageBox::information(this,"",s,"Ok");
            }
            else {
                QString s=baz.search(st.toStdString(),a,b,baz,1);
                QMessageBox::information(this,"",s,"Ok");
            }
        }
        else if(c==true){
            for(int i=0;i<en.size();++i){
                if(!en[i].isLetter()){
                    throw (QString)"Enter station name using only letters";
                }
            }if(en[0].isLower())en[0]=en[0].toUpper();
            QString s=baz.search(en.toStdString(),baz);
            QMessageBox::information(this,"",s,"Ok");
        }
        else{
            throw (QString) "Input correct search data";
        }
    }catch(QString eror){
        if(sound1==true){
            if(eror=="Enter station name using only letters")player1->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach_new/Enter-station-name-using-only-1607350435.mp3"));
            else if(eror=="Enter time using only numbers") player1->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach_new/Enter-time-using-only-numbers1607350506.mp3"));
            else if(eror=="Enter corect time")player1->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach_new/Enter-correct-time1607350460.mp3"));
            else if(eror=="Nothing found,change your search parameters ")player1->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach_new/Nothing-foundchange-your-sear1607352137.mp3"));
            else player1->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/Input-correct-search-data1607168420.mp3"));
            player1->setVolume(50);
            player1->play();
        }
        QMessageBox::critical(this,"Input erorr",eror,"ok");
        ui->lineEdit->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_2->clear();
        return;
    }
}
void MainWindow1::on_pushButton_2_pressed()
{
    close();
}
void MainWindow1::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex()==0){
        ui->lineEdit_2->setHidden(0);
        ui->lineEdit_3->setHidden(0);
        ui->lineEdit_4->setHidden(0);
        ui->lineEdit_5->setHidden(0);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_8->setHidden(1);
        ui->label->setText("Input station name and time interval");
        a=true;
        b=false;
        c=false;
    }
    else if(ui->comboBox->currentIndex()==1){
        ui->lineEdit_2->setHidden(0);
        ui->lineEdit_3->setHidden(0);
        ui->lineEdit_4->setHidden(0);
        ui->lineEdit_5->setHidden(0);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_8->setHidden(1);
        ui->label->setText("Input station name and time interval");
        b=true;
        a=false;
        c=false;
    }
    else if(ui->comboBox->currentIndex()==2){
        ui->label->setText("Input station name:");
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(0);
        ui->lineEdit_3->setHidden(true);
        ui->lineEdit_4->setHidden(true);
        ui->lineEdit_5->setHidden(true);
        ui->lineEdit_8->setVisible(1);
        c=true;
        b=false;
        a=false;
    }
}
