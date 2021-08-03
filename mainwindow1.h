#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QMainWindow>
#include <poizd.h>
#include<QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow1; }
QT_END_NAMESPACE

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow1(QWidget *parent = nullptr);
    void fromA(Poizd,bool,QMediaPlayer*);
    ~MainWindow1();

private slots:

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow1 *ui;
};
#endif // MAINWINDOW1_H
