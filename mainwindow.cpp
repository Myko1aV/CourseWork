#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"poizd.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<QMediaPlayer>
Poizd baza;
bool sound=true;
QMediaPlayer* player;
QString name="";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    player = new QMediaPlayer;
    ui->setupUi(this);
    window = nullptr;
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,95);
    ui->tableWidget->setColumnWidth(5,95);
    ui->tableWidget->setColumnWidth(6,110);
    ui->plainTextEdit->setVisible(0);
    ui->pushButton_4->setVisible(0);
    ui->pushButton_6->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete window;
}

void MainWindow::on_pushButton_pressed()
{
    try{
        if(baza.getSize()==0) throw (QString)"Open file to continue";
        if(window==nullptr){
            window = new MainWindow1(this);
            window->show();
            window->fromA(baza,sound,player);
        }
        if(window->isActiveWindow()==false){
            window=nullptr;
        }

    }catch(QString eror){
        if(sound==true){
            player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/Open-file-to-continue1607163516.mp3"));
            player->setVolume(50);
            player->play();
        }
        QMessageBox::critical(this, "Critical",eror);
        return;
    }
}
void MainWindow::on_actionOpen_triggered(){
    try{
        QString current_file="";
        QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
        QFile file(fileName);
        current_file=fileName;
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){
            QString er ="File opening is failed , try again";
            throw er;
        }
        if(!fileName.endsWith(".txt")){
            throw (QString)"File is not .txt ,please choose another file";
        }
        setWindowTitle(fileName);
        name=current_file;
        baza<<current_file;
    }catch(QString eror){
        if(sound==true){
            if(eror=="File is not .txt ,please choose another file") player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-is-not-txt-Please-choose1607164357.mp3"));
            else if(eror=="File opening is failed , try again") player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-opening-is-failed--try-a1607164785.mp3"));
            else if(eror=="The file is empty , choose another")  player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/The-file-is-empty--choose-ano1607164985.mp3"));
            else if(eror=="File is successfully opened") player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach_new/File-is-successfully-opened1607350400.mp3"));
            else player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-could-not-be-opened1607165061.mp3"));
            player->setVolume(50);
            player->play();
        }
        if(eror=="File is successfully opened"){
            QMessageBox::information(this, "File opening",eror);
        }
        else{
            QMessageBox::critical(this, "Critical",eror);
            return;
        }
    }
    catch(const std::exception &ex){
        QMessageBox::warning(this, "warning",ex.what());
        return;
    }
    int a=baza.getSize();
    ui->tableWidget->setRowCount(a);
    ui->tableWidget->setColumnCount(7);
    for (int i=0;i<a;++i) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(baza.getiNomer(i))));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(baza.getiStart(i))));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(baza.getiEnd(i))));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::fromStdString(baza.getiMiddle(i))));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(baza.getiDepart(2*i))+":"+QString::number(baza.getiDepart(2*i+1))));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(baza.getiArrive(2*i))+":"+QString::number(baza.getiArrive(2*i+1))));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(baza.getiLenght(i))));
        ui->actionOpen->setDisabled(true);
    }
}

void MainWindow::on_pushButton_5_pressed()
{
    try {
        if(baza.getSize()==0) throw (QString)"Open file to continue";
        QVector<double>v;
        v=baza.sortBySpid(baza);
        ui->tableWidget->setColumnCount(8);
        ui->tableWidget->setRowCount(baza.getSize());
        ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Швидкість"));
        for(int i=0;i<baza.getSize();++i){
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(baza.getiNomer(i))));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(baza.getiStart(i))));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(baza.getiEnd(i))));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::fromStdString(baza.getiMiddle(i))));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(baza.getiDepart(2*i))+":"+QString::number(baza.getiDepart(2*i+1))));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(baza.getiArrive(2*i))+":"+QString::number(baza.getiArrive(2*i+1))));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(baza.getiLenght(i))));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem(QString::number(v[i])+"км/год"));
        }
    }catch(QString eror){
        if(sound==true){
            player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/Open-file-to-continue1607163516.mp3"));
            player->setVolume(50);
            player->play();
        }
        QMessageBox::critical(this, "Critical",eror);
        return;
    }}

void MainWindow::on_actionNew_triggered()
{
    if(baza.getSize()==0){
        ui->plainTextEdit->setVisible(0);
        ui->pushButton_4->setVisible(0);
        ui->pushButton_6->setVisible(0);
        ui->actionOpen->setEnabled(1);
        ui->actionOpen->setEnabled(true);
    }
    ui->actionOpen->setEnabled(true);
    baza.clear();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_2_pressed()
{
    try{
        Poizd b=Poizd(baza);
        QVector<int>p;
        if(baza.getSize()==0) throw (QString)"Open file to continue";
        b.group(b,ui->tableWidget);
    }catch(QString eror){
        if(sound==true){
            player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/Open-file-to-continue1607163516.mp3"));
            player->setVolume(50);
            player->play();
        }
        QMessageBox::critical(this, "Critical",eror);
        return;
    }
}

void MainWindow::on_pushButton_3_pressed()
{
    try {
        if(baza.getSize()==0) throw (QString)"Open file to continue";
        Poizd p=baza;
        p.mergeSort(0,p.getSize()-1);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setRowCount(baza.getSize());

        for(int i=0;i<baza.getSize();++i){
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(baza.getiNomer(i))));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(baza.getiStart(i))));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(baza.getiEnd(i))));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::fromStdString(baza.getiMiddle(i))));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(baza.getiDepart(2*i))+":"+QString::number(baza.getiDepart(2*i+1))));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(baza.getiArrive(2*i))+":"+QString::number(baza.getiArrive(2*i+1))));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(baza.getiLenght(i))));
        }
    }catch(QString eror){
        if(sound==true){
            player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/Open-file-to-continue1607163516.mp3"));
            player->setVolume(50);
            player->play();
        }
        QMessageBox::critical(this, "Critical",eror);
    }
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSave_triggered()
{
    try{
        if(baza.getSize()==0) throw (QString)"Open file to continue";
        baza>>name;
    }
    catch(QString eror){
        if(sound==true){
            if(eror=="Open file to continue")player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/Open-file-to-continue1607163516.mp3"));
            else if(eror=="File is successfully saved")player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-is-successfully-saved1607170796.mp3"));

            player->setVolume(50);
            player->play();
        }
        QMessageBox::critical(this, "Critical",eror);
        return;
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    try{
        QString current_file="";
        QString fileName = QFileDialog::getSaveFileName(this, "Save as");
        QFile file(fileName);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QString ch="File saving is failed , try again";
            throw ch;
        }
        current_file=fileName;
        if(!fileName.endsWith(".txt")){
            throw (QString)"File is not .txt ,please choose another file";
        }
        baza>>fileName;
    }catch (QString eror) {
        if(sound==true){
            if(eror=="File is not .txt ,please choose another file") player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-is-not-txt-Please-choose1607164357.mp3"));
            else if(eror=="File saving is failed , try again") player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-saving-is-failed--try-ag1607166950.mp3"));
            else if(eror=="File is successfully saved")player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-is-successfully-saved1607170796.mp3"));
            else player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/Kursach/Kursach/File-could-not-be-opened1607165061.mp3"));
            player->setVolume(50);
            player->play();
        }
        if(eror=="File is successfully saved"){
            QMessageBox::information(this, "File saving",eror);
        }
        else
        { QMessageBox::critical(this, "Critical",eror);
            return;
        }
    }
    catch(const std::exception &ex){
        QMessageBox::warning(this, "warning",ex.what());
        return;
    }
}

void MainWindow::on_actionSound_changed()
{
    sound=(!sound);
    if(sound==false)
    {
        player->setMuted(true);
    }
    if(sound==true){
        player->setMuted(false);
    }
}
void Poizd::merge(int left, int mid, int right) {
    int leftN = mid - left + 1;
    int rightN = right - mid;
    string L[leftN], R[rightN],L6[leftN], R6[rightN],L7[leftN], R7[rightN];
    int L1[leftN], R1[rightN],L2[leftN], R2[rightN],L3[leftN], R3[rightN],L4[leftN], R4[rightN],L5[leftN], R5[rightN];
    double L8[leftN], R8[rightN];
    for (int i = 0; i < leftN; i++){
        L[i] = start[left + i];
        L1[i]=nomer[left+i];
        L2[i]=depart[2*(left+i)];
        L3[i]=depart[2*(left+i)+1];
        L4[i]=arrive[2*(left+i)];
        L5[i]=arrive[2*(left+i)+1];
        L6[i]=middle[left+i];
        L7[i]=end[left+i];
        L8[i]=lenght[left+i];
    }
    for (int j = 0; j < rightN; j++){
        R[j] = start[mid + 1 + j];
        R1[j]=nomer[mid + 1 + j];
        R2[j]=depart[2*(mid + 1 + j)];
        R3[j]=depart[2*(mid + 1 + j)+1];
        R4[j]=arrive[2*(mid + 1 + j)];
        R5[j]=arrive[2*(mid + 1 + j)+1];
        R6[j]=middle[mid + 1 + j];
        R7[j]=end[mid + 1 + j];
        R8[j]=lenght[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < leftN && j < rightN) {
        if (L[i] <= R[j]) {
            start[k] = L[i];
            nomer[k] = L1[i];
            middle[k] = L6[i];
            end[k] = L7[i];
            depart[2*k] = L2[i];
            depart[2*k+1] = L3[i];
            arrive[2*k] = L4[i];
            arrive[2*k+1] = L5[i];
            lenght[k] = L8[i];
            i++;
        } else {
            start[k] = R[j];
            nomer[k] = R1[j];
            middle[k] = R6[j];
            end[k] = R7[j];
            depart[2*k] = R2[j];
            depart[2*k+1] = R3[j];
            arrive[2*k] = R4[j];
            arrive[2*k+1] = R5[j];
            lenght[k] = R8[j];
            j++;
        }
        k++;
    }
    while (i < leftN) {
        start[k] = L[i];
        nomer[k] = L1[i];
        middle[k] = L6[i];
        end[k] = L7[i];
        depart[2*k] = L2[i];
        depart[2*k+1] = L3[i];
        arrive[2*k] = L4[i];
        arrive[2*k+1] = L5[i];
        lenght[k] = L8[i];
        i++;
        k++;
    }
    while (j < rightN) {
        start[k] = R[j];
        nomer[k] = R1[j];
        middle[k] = R6[j];
        end[k] = R7[j];
        depart[2*k] = R2[j];
        depart[2*k+1] = R3[j];
        arrive[2*k] = R4[j];
        arrive[2*k+1] = R5[j];
        lenght[k] = R8[j];
        j++;
        k++;
    }
}
void Poizd::mergeSort(int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        baza.mergeSort(left, mid);
        baza.mergeSort(mid + 1, right);
        baza.merge(left, mid, right);
    }
}

//void MainWindow::on_pushButton_6_pressed()
//{
//    ui->plainTextEdit->setVisible(0);
//    ui->pushButton_4->setVisible(0);
//    ui->pushButton_6->setVisible(0);
//    ui->actionOpen->setEnabled(1);
//}

//void MainWindow::on_actionRead_from_keyboard_triggered()
//{
//    ui->plainTextEdit->setVisible(1);
//    ui->pushButton_4->setVisible(1);
//    ui->pushButton_6->setVisible(1);
//    ui->actionOpen->setEnabled(0);
//}

//void MainWindow::on_pushButton_4_pressed()
//{
//    QVector<int>nomer;
//    QVector<string>start;
//    QVector<string>end;
//    QVector<string>middle;
//    QVector<int>depart;
//    QVector<int>arrive;
//    QVector<double>lenght;
//    QString s=ui->plainTextEdit->toPlainText();
//    for (int i=0;i<s.size();i++){
//        if(s[i]=="\n"){
//            s.replace(s[i]," ");
//        }
//    }
//    QStringList l =s.split(" ");
//    for (int i=0 ;i<l.size();i++) {
//        nomer.push_back(l[9*i].toInt());
//        start.push_back(l[9*i+1].toStdString());
//        end.push_back(l[9*i+2].toStdString());
//        middle.push_back(l[9*i+3].toStdString());
//        depart.push_back(l[9*i+4].toInt());
//        depart.push_back(l[9*i+5].toInt());
//        arrive.push_back(l[9*i+6].toInt());
//        arrive.push_back(l[9*i+7].toInt());
//        lenght.push_back(l[9*i+8].toInt());
//    }
//    baza=Poizd(nomer,start,end,middle,depart,arrive,lenght);
//}
