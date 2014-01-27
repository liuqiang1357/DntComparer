#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QDomDocument>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class Biaotou
{
public:
    qint16 lieshu;
    qint32 hangshu;
    void dubiaotou(QString &filename,QDataStream &input,QLabel *label);
    void clear()
    {
        lieshu=0;
        hangshu=0;
    }

};

class Liexinxi
{
public:
    QVector<qint16> liebiaotizishu;
    QVector<QString> liebiaoti;
    QVector<qint8> lieleixing;

    void duliexinxi(QDataStream &input,Biaotou &biaotou);
    void clear()
    {
        liebiaotizishu.clear();
        liebiaoti.clear();
        lieleixing.clear();
    }
};

class Shujuti
{
public:
    QVector<QString> hangbiaoti;
    QVector<QString> hangbianhao;
    QVector<QString> hangshuju;
    bool dushujuti(QDataStream &input,bool &stopflag,Ui::MainWindow *ui,Biaotou &biaotou,Liexinxi &liexinxi,QDomDocument *dom,QVector<int> &suoyin,bool jiazai);
    void clear()
    {
        hangshuju.clear();
        hangbiaoti.clear();
        hangbianhao.clear();
    }
};

class Dnt
{
public:
    Biaotou biaotou;
    Liexinxi liexinxi;
    Shujuti shujuti;
    bool dudnt(QString &fileNameDir,bool &stopflag,Ui::MainWindow *ui,QLabel *label,QDomDocument *dom,QVector<int> &suoyin,bool jiazai);
    void clear()
    {
        biaotou.clear();
        liexinxi.clear();
        shujuti.clear();
    }
};



class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_exit_triggered();

    void on_action_about_triggered();

    void on_pushButton_dnt1_clicked();

    void on_pushButton_dnt2_clicked();

    void on_pushButton_compare_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_xlsx_clicked();

    void on_lineEdit_dnt1_textChanged(const QString &arg1);

    void on_lineEdit_dnt2_textChanged(const QString &arg1);

    void on_actionDnt1_triggered();

    void on_actionDnt2_triggered();

    void on_action_compare_triggered();

private:
    Ui::MainWindow *ui;

    QString fileNameDir1;

    QString fileNameDir2;

    Dnt dnt1;

    Dnt dnt2;

    QLabel *label1 ;

    QLabel *label2 ;

    QDomDocument *dom;

    QVector<int> suoyin;

    bool jiazai;

    bool stopflag;

    bool yunxing;


};

#endif // MAINWINDOW_H
