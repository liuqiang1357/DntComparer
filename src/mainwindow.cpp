#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"

void Biaotou:: dubiaotou(QString &filename,QDataStream &input,QLabel *label )
{
    input>>hangshu>>lieshu>>hangshu;
    label->setText(filename+QObject::tr("     ")+QString::number(hangshu)+QObject::tr("x")+QString::number(lieshu)+QObject::tr("   "));
    qApp->processEvents ();
}

void Liexinxi:: duliexinxi(QDataStream &input,Biaotou &biaotou)
{
    qint16 tmp1;
    char tmp2[4096];
    qint8 tmp3;
    int lieshu1=biaotou.lieshu;
    for(int i=0;i<lieshu1;i++)
    {
        input>>tmp1;
        input.readRawData(tmp2,int(tmp1));
        tmp2[tmp1]='\0';
        input>>tmp3;
        liebiaotizishu.append(tmp1);
        liebiaoti.append(tmp2);
        lieleixing.append(tmp3);
    }
    qApp->processEvents ();

}

bool Shujuti::dushujuti(QDataStream &input,bool &stopflag,Ui::MainWindow *ui,Biaotou &biaotou,Liexinxi &liexinxi)
{

    qint32 geshi0;
    char geshi1[4096];
    qint16 tmp1;
    qint32 geshi2;
    qint32 geshi3;
    float geshi4;
    float geshi5;
    int lieshu1=biaotou.lieshu;
    int hangshu1=biaotou.hangshu;
    QVector<qint8>lieleixing1=liexinxi.lieleixing;
    QString hangshuju1;
    ui->statusBar->showMessage(QObject::tr("正在载入文件."),600000);
    for (int i=0;i<hangshu1;i++)
    {
        if (i==50)
        {
            qApp->processEvents ();
        }
        else if (i%1000==0)
        {
            ui->statusBar->showMessage(QObject::tr("正在载入文件 ")+QString::number(int(double(i)*100/double(hangshu1)))+"%",600000);
            if (stopflag)
            {
                ui->statusBar->showMessage(QObject::tr("停止载入文件."),10000);
                return false;
            }
            qApp->processEvents ();
        }

        input>>geshi0;
        hangshuju1=QString::number(geshi0);
        hangbiaoti.append(QString::number(i+1));

        for(int j=0;j<lieshu1;j++)
        {
            if (lieleixing1.value(j)==1 )
            {
                input>>tmp1;
                input.readRawData(geshi1,int(tmp1));
                geshi1[tmp1]='\0';
                hangshuju1=hangshuju1+"||"+geshi1;
            }
            else if (lieleixing1.value(j)==2 )
            {
                input>>geshi2;
                hangshuju1=hangshuju1+"||"+QString::number(geshi2);
            }
            else if (lieleixing1.value(j)==3 )
            {
                input>>geshi3;
                hangshuju1=hangshuju1+"||"+QString::number(geshi3);
            }
            else if (lieleixing1.value(j)==4 )
            {
                input>>geshi4;
                hangshuju1=hangshuju1+"||"+QString::number(geshi4);
            }
            else if (lieleixing1.value(j)==5 )
            {
                input>>geshi5;
                hangshuju1=hangshuju1+"||"+QString::number(geshi5);
            }
            else
            {
                qDebug((QObject::tr("find new type:")+liexinxi.liebiaoti.value(j)+QObject::tr(" lieshu:")+QString::number(j)+QObject::tr(" leixing:")+QString::number(liexinxi.lieleixing.value(j))).toStdString().c_str());
            }
        }

        hangshuju.append(hangshuju1);
    }
    ui->statusBar->showMessage(QObject::tr("载入文件成功."),10000);
    return true;
}

bool Dnt::dudnt(QString &fileNameDir,bool &stopflag,Ui::MainWindow *ui,QLabel *label)
{
    QFile fileNameOpened (fileNameDir);
    QString filename=QFileInfo(fileNameDir).fileName();
    if (!fileNameOpened.open(QIODevice::ReadOnly)){
        return false;
    }
    else
    {
        this->clear();
    }
    QDataStream input(&fileNameOpened);
    input.setByteOrder(QDataStream::LittleEndian);
    input.setFloatingPointPrecision(QDataStream::SinglePrecision);
    this->biaotou.dubiaotou(filename,input,label);
    this->liexinxi.duliexinxi(input,this->biaotou);
    if(this->shujuti.dushujuti(input,stopflag,ui,this->biaotou,this->liexinxi))
        return true;
    else
        return false;
}


void MainWindow::pipeibiaoqian()
{
    int _NameID=0;
    int _NameIDParam=0;
    QDomNodeList messagelist=dom->elementsByTagName("message");

    QTableWidget*tableWidget1=ui->tableWidget;
    int lieshu1=tableWidget1->columnCount();;
    int hangshu1=tableWidget1->rowCount();

    int tmp1;
    QString tmp2;
    QStringList tmp3;
    int tmp4;

    for(int i=0;i<lieshu1;i++)
    {
        if (tableWidget1->horizontalHeaderItem(i)->text()==QString("_NameID"))
        {
            _NameID=i;
        }
        if (tableWidget1->horizontalHeaderItem(i)->text()==QString("_NameIDParam"))
        {
            _NameIDParam=i;
        }

    }

    if (_NameID!=0)
    {
        statusBar()->showMessage(tr("正在匹配标签."),10000);
        for (int i=0;i<hangshu1;i++)
        {

            if (i==30)
            {
                ui->tableWidget->resizeColumnsToContents();
                qApp->processEvents ();
            }
            else if (i%500==0)
            {
                if (stopflag)
                {
                    statusBar()->showMessage(tr("停止匹配标签."),10000);
                    return;
                }
                qApp->processEvents ();
            }


            tmp1=suoyin.indexOf(tableWidget1->item(i,_NameID)->text().toInt());
            if(tmp1>=0)
            {
                tmp2= messagelist.at(tmp1).toElement().text();
                if (tmp2.length()<30){
                    if (tmp2.contains("{0}"))
                    {
                        tmp3=tableWidget1->item(i,_NameIDParam)->text().split(',');
                        for(int j=0 ;j<30;j++)
                        {
                            if(tmp2.contains("{"+QString::number(j)+"}"))
                            {
                                if (tmp3.value(j).contains('{'))
                                {
                                    tmp4=suoyin.indexOf(tmp3.value(j).remove('{').remove('}').toInt());
                                    if (tmp4>=0)
                                    {
                                        tmp2.replace("{"+QString::number(j)+"}",messagelist.at(tmp4).toElement().text());
                                    }
                                }
                                else
                                {
                                    tmp2.replace("{"+QString::number(j)+"}",tmp3.value(j));
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        tableWidget1->setVerticalHeaderItem(i,new QTableWidgetItem(tmp2));
                    }
                    else
                    {
                        tableWidget1->setVerticalHeaderItem(i,new QTableWidgetItem(tmp2));
                    }
                }
            }
        }
        statusBar()->showMessage(tr("匹配标签成功."),10000);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label1 = new QLabel;
    label2 = new QLabel;
    statusBar()->addPermanentWidget(label1);
    statusBar()->addPermanentWidget(label2);

    suoyin.clear();

    yunxing=false;
    stopflag=false;

    QString xmlFileName=QString("uistring.xml");
    QFile xmlFile(xmlFileName);
    if (!xmlFile.open(QIODevice::ReadOnly)){
        statusBar()->showMessage(tr("XML文件载入失败."),5000);
        jiazai=false;
        return;
    }
    dom = new QDomDocument();
    QString errorStr;
    int errorLine;
    int errorColumn;
    if(!dom->setContent(&xmlFile,&errorStr,&errorLine,&errorColumn)){
        xmlFile.close();
        jiazai=false;
        statusBar()->showMessage(tr("XML文件载入失败."),5000);
        return;
    }

    QDomNodeList messagelist=dom->elementsByTagName("message");
    for(int i=0;i<messagelist.count();i++)
    {
        suoyin.append(messagelist.at(i).toElement().attribute("mid").toInt());

    }
    xmlFile.close();

    jiazai=true;
    statusBar()->showMessage(tr("XML文件载入成功."),3000);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_dnt1_clicked()
{

    QString dir=QFileInfo(fileNameDir1).absolutePath();
    fileNameDir1 = QFileDialog::getOpenFileName(this,"",dir,"Dnt Files(*.dnt)");
    if(fileNameDir1!="")
    {
        ui->lineEdit_dnt1->setText(fileNameDir1);
    }
    fileNameDir1=ui->lineEdit_dnt1->text();
    /*
    if(yunxing)
    {
        return;
    }
    else
    {
        yunxing= true;
    }

    QString dir=QFileInfo(fileNameOpenedDir).absolutePath();
    fileNameOpenedDir = QFileDialog::getOpenFileName(this,"",dir,"Dnt Files(*.dnt)");
    QFile fileNameOpened (fileNameOpenedDir);
    QString filename=QFileInfo(fileNameOpenedDir).fileName();
    if (!fileNameOpened.open(QIODevice::ReadOnly)){
        statusBar()->showMessage(tr("文件打开失败."),10000);
        yunxing= false;
        return;
    }
    else
    {
        this->clear();
    }
    QDataStream input(&fileNameOpened);
    input.setByteOrder(QDataStream::LittleEndian);
    input.setFloatingPointPrecision(QDataStream::SinglePrecision);
    this->biaotou.dubiaotou(input);
    label1->setText(filename+tr("     ")+QString::number(biaotou.hangshu)+tr("x")+QString::number(biaotou.lieshu)+tr("   "));
    this->liexinxi.duliexinxi(input,this->biaotou,this->ui);
    this->shujuti.dushujuti(input,this->biaotou,this->liexinxi,this->ui,stopflag);
    if (jiazai)
    {
        this->pipeibiaoqian();
    }
    ui->tableWidget->resizeColumnsToContents();
    fileNameOpened.close();
    yunxing= false;
    */
}

void MainWindow::on_pushButton_dnt2_clicked()
{
    QString dir=QFileInfo(fileNameDir1).absolutePath();
    fileNameDir2 = QFileDialog::getOpenFileName(this,"",dir,"Dnt Files(*.dnt)");
    if (fileNameDir2!="")
    {
        ui->lineEdit_dnt2->setText(fileNameDir2);
    }
    fileNameDir2=ui->lineEdit_dnt2->text();
}

void MainWindow::on_pushButton_compare_clicked()
{
    if(yunxing)
    {
        return;
    }
    else
    {
        yunxing= true;
    }
    stopflag=false;
    fileNameDir1=ui->lineEdit_dnt1->text();
    fileNameDir2=ui->lineEdit_dnt2->text();
    if (!dnt1.dudnt(fileNameDir1,stopflag,this->ui,label1))
    {
        ui->statusBar->showMessage(QObject::tr("dnt1打开失败."),10000);
        yunxing= false;
        return;
    }
    else
    {
        if(!dnt2.dudnt(fileNameDir2,stopflag,this->ui,label2))
        {
            ui->statusBar->showMessage(QObject::tr("dnt2打开失败."),10000);
            yunxing= false;
            return;
        }
        else
            ui->statusBar->showMessage(QObject::tr("文件打开成功."),10000);
    }


    if (dnt1.biaotou.lieshu!=dnt2.biaotou.lieshu)
    {
        ui->statusBar->showMessage(QObject::tr("列数不同,不能比较."),10000);
        yunxing= false;
        return;
    }

    int lieshu=dnt1.biaotou.lieshu;

    for(int i=0;i<lieshu;i++)
    {
        if (dnt1.liexinxi.liebiaoti.value(i)!=dnt2.liexinxi.liebiaoti.value(i))
        {
            ui->statusBar->showMessage(QObject::tr("列标题不同,不能比较."),10000);
            yunxing= false;
            return;
        }
    }

    int hangshu1=dnt1.biaotou.hangshu;
    int hangshu2=dnt2.biaotou.hangshu;

    QVector<QString> *hangshuju1=&(dnt1.shujuti.hangshuju);
    QVector<QString> *hangbiaoti1=&(dnt1.shujuti.hangbiaoti);
    QVector<QString> *hangshuju2=&(dnt2.shujuti.hangshuju);
    QVector<QString> *hangbiaoti2=&(dnt2.shujuti.hangbiaoti);

///*
    for(int i=0;i<hangshu2;i++)
    {
        for(int j=0;j<hangshu1;j++)
        {
            if (hangshuju1->value(i)==hangshuju2->value(i))
            {
                hangbiaoti1->remove(i);
                hangshuju1->remove(i);
                hangbiaoti2->remove(j);
                hangshuju2->remove(j);
                hangshu1--;
                hangshu2--;
                i--;
                j--;
                break;
            }
        }
    }
//*/
    for(int i=0;i<hangshuju2->count();i++)
    {
        cout<<hangbiaoti2->value(i).toStdString().c_str()<<"    ";
        cout<<hangshuju2->value(i).toStdString().c_str()<<endl;
    }


    yunxing= false;
}

void MainWindow::on_pushButton_stop_clicked()
{
    stopflag=true;
}

void MainWindow::on_pushButton_xlsx_clicked()
{
    /*
    if(yunxing)
    {
        return;
    }
    else
    {
        yunxing= true;
    }
    QXlsx::Document xlsx;
    QTableWidget*tableWidget1=ui->tableWidget;
    int hangshu1=tableWidget1->rowCount();
    int lieshu1= tableWidget1->columnCount();


    xlsx.write(1,1,"");
    for(int j=0;j<lieshu1;j++)
    {
        if(tableWidget1->horizontalHeaderItem(j)!=NULL)
        {
            xlsx.write(1,j+2,tableWidget1->horizontalHeaderItem(j)->text());
        }
        else
        {
            xlsx.write(1,j+2,QString::number(j+2));
        }
    }
    for (int i=0;i<hangshu1;i++)
    {
        if (i%1000==0)
        {
            ui->statusBar->showMessage(QObject::tr("正在生成xlsx ")+QString::number(int(double(i)*100/double(hangshu1)))+"%",600000);
            qApp->processEvents ();
        }
        if(tableWidget1->verticalHeaderItem(i)!=NULL)
        {
            xlsx.write(i+2,1,tableWidget1->verticalHeaderItem(i)->text());
        }
        else
        {
            xlsx.write(i+2,1,QString::number(i+1));
        }

        if(tableWidget1->item(i,0)!=NULL)
        {
            xlsx.write(i+2,2,tableWidget1->item(i,0)->text().toInt());
        }
        else
        {
            xlsx.write(i+2,2,"");
        }
        for(int j=1;j<lieshu1;j++)
        {
            if(tableWidget1->item(i,j)!=NULL)
            {
                if(liexinxi.lieleixing.value(j-1)==1)
                {
                    xlsx.write(i+2,j+2,tableWidget1->item(i,j)->text());
                }
                else if(liexinxi.lieleixing.value(j-1)<=3)
                {
                    xlsx.write(i+2,j+2,tableWidget1->item(i,j)->text().toInt());
                }
                else if(liexinxi.lieleixing.value(j-1)<=5)
                {
                    xlsx.write(i+2,j+2,tableWidget1->item(i,j)->text().toDouble());
                }
            }
            else
            {
                xlsx.write(i+2,j+2,"");
            }
        }
    }

    QString saveDir=QFileInfo(fileNameOpenedDir).absolutePath()+"\\"+QFileInfo(fileNameOpenedDir).baseName()+".xlsx";
    statusBar()->showMessage(tr("正在保存xlsx..."),10000);
    xlsx.saveAs(saveDir);
    statusBar()->showMessage(tr("成功导出xlsx."),10000);
    yunxing= false;
    */
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::information(0,tr("关于"), tr("\n\"DNT查看编辑器v2.0\" -20130120\n"
                                            "---------------------\n"
                                            "Author:xiaot\tEmail:liuqiang1357@163.com\t\n"
                                            "Qt:5.0.2\t\tmingw:4.8.0\n"
                                            "on Microsoft Windows 7 (32-bit)\n"));
}
