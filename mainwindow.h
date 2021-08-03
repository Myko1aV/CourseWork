#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow1.h"
#include "poizd.h"
#include<QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Poizd task4(Poizd);
    ~MainWindow();
signals:
    void send(Poizd,bool,QMediaPlayer* pl);
private slots:
    void on_pushButton_pressed();

    void on_actionOpen_triggered();

    void on_pushButton_5_pressed();

    void on_actionNew_triggered();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionSound_changed();

//    void on_pushButton_6_pressed();

//    void on_actionRead_from_keyboard_triggered();

//    void on_pushButton_4_pressed();

private :
    Ui::MainWindow *ui;
    MainWindow1 *window;
};
#endif // MAINWINDOW_H
