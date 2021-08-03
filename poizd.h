#ifndef INFOBAZA_H
#define INFOBAZA_H
#include <iostream>
#include <fstream>
#include <string>
#include <QVector>
#include <QTableWidget>

using namespace std;
class Poizd
{
    QVector<int>nomer;
    QVector<string>start;
    QVector<string>end;
    QVector<string>middle;
    QVector<int>depart;
    QVector<int>arrive;
    QVector<double>lenght;

public:
    Poizd()//конструктор за замовчуванням
    {
        int size=nomer.size();
        for(int i=0;i<size;++i){
            nomer[i]=0;
            start[i]=nullptr;
            end[i]=nullptr;
            middle[i]=nullptr;
            depart[i]=0;
            arrive[i]=0;
            lenght[i]=0.0;
        }
    }
    //Конструктор з параметрами
    Poizd(QVector<int>a,QVector<string>b,QVector<string>c,QVector<string>d,QVector<int>e,QVector<int>f,QVector<double>g)
    {
        nomer=a;
        start=b;
        end=c;
        middle=d;
        depart=e;
        arrive=f;
        lenght=g;
    }
    //конструктор копіювання
    Poizd(Poizd const &other)
    {
        nomer=other.nomer;
        start=other.start;
        end=other.end;
        middle=other.middle;
        depart=other.depart;
        arrive=other.arrive;
        lenght=other.lenght;
    }
    int getiNomer(int);
    string getiStart(int);
    string getiEnd(int);
    string getiMiddle(int);
    int getiDepart(int);
    int getiArrive(int);
    double getiLenght(int);
    QString search(string,Poizd);
    QString search(string,double,double,Poizd,int);
    int getSize();
    QVector<double> sortBySpid(Poizd);
    void remove(int);
    void group(Poizd,QTableWidget*);
    void find(long long,QTableWidget*,Poizd);
    void operator>>(QString);
    void operator<<(QString);
    void clear();
    void mergeSort(int,int);
    void merge(int, int, int );

};

#endif // INFOBAZA_H
