#include "poizd.h"
#include<QMessageBox>
#include<string>
#include <QTableWidget>
#include <QVector>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<QMediaPlayer>
#include <mainwindow.h>
#include "ui_mainwindow.h"

int Poizd::getiNomer(int i)
{
    return nomer[i];
}
string Poizd::getiStart(int i)
{
    return start[i];
}
string Poizd::getiEnd(int i)
{
    return end[i];
}
string Poizd::getiMiddle(int i)
{
    return middle[i];
}
int Poizd::getiDepart(int i)
{
    return depart[i];
}
int Poizd::getiArrive(int i)
{
    return arrive[i];
}
double Poizd::getiLenght(int i)
{
    return lenght[i];
}
int Poizd::getSize()
{
    return nomer.size();
}

void Poizd::clear() //функція очищення вектора
{
    nomer.clear();
    start.clear();
    end.clear();
    middle.clear();
    depart.clear();
    arrive.clear();
    lenght.clear();
}

void Poizd::operator>>(QString fileName)//перевизначений оператор запису в файл
{
    ofstream baza;
    baza.open(fileName.toStdString());
    if(!baza.is_open()){
        throw (QString)"File could not be opened";
    }
    for(int i = 0;i<nomer.size();i++){
        baza<<nomer[i];
        baza<<" ";
        baza<<start[i];
        baza<<" ";
        baza<<end[i];
        baza<<" ";
        baza<<middle[i];
        baza<<" ";
        baza<<depart[2*i];
        baza<< " ";
        baza<<depart[2*i+1];
        baza<<" ";
        baza<<arrive[2*i];
        baza<<" ";
        baza<<arrive[2*i+1];
        baza<<" ";
        baza<<lenght[i];
        if(i!=nomer.size()-1){
            baza<<"\n";
        }
    }
    baza.close();
    throw (QString)"File is successfully saved";
}

void Poizd::operator<<(QString fileName)//перевизначення оператору зчитування з файлу
{
    ifstream baza;
    Poizd baz;
    int no,time1,time2;
    string st,en,mid;
    double len;
    baza.open(fileName.toStdString());
    if(!baza.is_open()){
        throw (QString)"File could not be opened";
    }
    if ( baza.peek() == std::ifstream::traits_type::eof() ){
        throw (QString)"The file is empty , choose another";
    }
    while(!baza.eof()){
        baza >> no;
        nomer.push_back(no);
        baza >> st;
        start.push_back(st);
        baza >> en;
        end.push_back(en);
        baza>>mid;
        middle.push_back(mid);
        baza>>time1;
        depart.push_back(time1);
        baza >> time1;
        depart.push_back(time1);
        baza>>time2;
        arrive.push_back(time2);
        baza >> time2;
        arrive.push_back(time2);
        baza >> len;
        lenght.push_back(len);
    }
    baza.close();
    throw (QString)"File is successfully opened";
}
QString Poizd::search(string str, Poizd p){//функція пошуку поїзда за станцією
    QString s="Found trains : \n";
    for(int i=0;i<p.getSize();i++){
        if(str==p.getiStart(i)||str==p.getiEnd(i)||str==p.getiMiddle(i)){
            s+=QString::number(p.getiNomer(i))+"\n";
        }
    }
    if(s=="Found trains : \n"){
        s="Nothing found,change your search parameters ";
        throw s;
    }
    return s;
}
QString Poizd::search(string str , double a, double b, Poizd p, int k){//пошук поїзда за назвою станції та часовим проміжком
    QString s="Found trains : \n";
    for(int i=0;i<p.getSize();i++){
        double time1=p.getiArrive(2*i)+p.getiArrive(2*i+1)/60.0;
        double time2=p.getiDepart(2*i)+p.getiDepart(2*i+1)/60.0;
        if(k==0){
            if(str==p.getiStart(i) && time2>=a && time2<=b){
                s+=QString::number(p.getiNomer(i))+"\n";
            }}
        else{
            if(str==p.getiEnd(i) && time1>=a && time1<=b){
                s+=QString::number(p.getiNomer(i))+"\n";
            }
        }
    }
    if(s=="Found trains : \n"){
        s="Nothing found,change your search parameters ";
        throw s;
    }
    return s;
}
QVector<double> Poizd::sortBySpid(Poizd pz){//сортування за середньою швидкістю
    QVector<double>spid;
    double b;
    for(int i=0;i<pz.getSize();++i){
        if(pz.getiArrive(2*i)>pz.getiDepart(2*i)){
            b=pz.getiLenght(i)/(pz.getiArrive(2*i)+pz.getiArrive(2*i+1)/60-pz.getiDepart(2*i)+pz.getiDepart(2*i+1)/60);
        }
        else{
            b=pz.getiLenght(i)/(pz.getiArrive(2*i)+pz.getiArrive(2*i+1)/60-pz.getiDepart(2*i)+pz.getiDepart(2*i+1)/60+24);
        }
        spid.push_back(b);//запис у вектор середньої швидкості
    }
    int j;
    int step=pz.getSize()/2;
    while(step>0){ //сортування вектору швидкостей методом Шелла
        for(int i=0 ;i<pz.getSize()-step;i++){
            j=i;
            while ((j>=0)&&(spid[j]>spid[j+step])){
                spid.swapItemsAt(j,j+step);
                nomer.swapItemsAt(j,j+step);
                start.swapItemsAt(j,j+step);
                end.swapItemsAt(j,j+step);
                middle.swapItemsAt(j,j+step);
                depart.swapItemsAt(2*j,2*j+2*step);
                depart.swapItemsAt(2*j+1,2*j+1+2*step);
                arrive.swapItemsAt(2*j+1,2*j+1+2*step);
                arrive.swapItemsAt(2*j,2*j+2*step);
                lenght.swapItemsAt(j,j+step);
                j--;
            }
        }
        step=step/2;
    }
    return spid;
}
void Poizd::group(Poizd pz, QTableWidget *table){ //групування поїздів у яких кінцева та проїздні станці одинакові
    QVector<int>pos;
    for(int i=0 ;i<pz.getSize();i++){
        for(int j=0;j<pz.getSize();j++){
            if(i==j){
                if(i==pz.getSize()-1){
                    break;
                }
                j++;
            }
            if(pz.getiMiddle(i)==pz.getiMiddle(j) && pz.getiEnd(i)==pz.getiEnd(j)){
                pos.push_back(j);
            }
        }
    }
    table->setRowCount(pos.size());
    table->setColumnCount(7);
    for(int i=0;i<pos.size();i++){
        table->setItem(i,0,new QTableWidgetItem(QString::number(pz.getiNomer(pos[i]))));
        table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(pz.getiStart(pos[i]))));
        table->setItem(i,2,new QTableWidgetItem(QString::fromStdString(pz.getiEnd(pos[i]))));
        table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(pz.getiMiddle(pos[i]))));
        table->setItem(i,4,new QTableWidgetItem(QString::number(pz.getiDepart(2*pos[i]))+":"+QString::number(pz.getiDepart(2*pos[i]+1))));
        table->setItem(i,5,new QTableWidgetItem(QString::number(pz.getiArrive(2*pos[i]))+":"+QString::number(pz.getiArrive(2*pos[i]+1))));
        table->setItem(i,6,new QTableWidgetItem(QString::number(pz.getiLenght(pos[i]))));
    }
    table->sortByColumn(3,Qt::SortOrder::AscendingOrder);
}
