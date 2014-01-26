#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"

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

bool Shujuti::dushujuti(QDataStream &input,bool &stopflag,Ui::MainWindow *ui,Biaotou &biaotou,Liexinxi &liexinxi,QDomDocument *dom,QVector<int> &suoyin,bool jiazai)
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

    int _NameID=-1;
    int _NameIDParam=-1;
    QDomNodeList messagelist=dom->elementsByTagName("message");

    int NameID=0;
    QString NameIDParam;

    int tmp5;
    QString tmp6;
    QStringList tmp7;
    int tmp8;

    for(int i=0;i<lieshu1;i++)
    {
        if (liexinxi.liebiaoti.value(i)==QString("_NameID"))
        {
            _NameID=i;
        }
        if (liexinxi.liebiaoti.value(i)==QString("_NameIDParam"))
        {
            _NameIDParam=i;
        }

    }


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
        hangbianhao.append(QString::number(geshi0));

        hangshuju1="mystart";
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
            if (j==_NameID)
            {
                NameID=geshi3;
            }
            if (j==_NameIDParam)
            {
                NameIDParam=geshi1;
            }

        }

        hangshuju.append(hangshuju1.remove("mystart||"));

        if (jiazai)
        {
            if (_NameID!=-1)
            {
                tmp5=suoyin.indexOf(int(NameID));
                if(tmp5>0)
                {
                    tmp6= messagelist.at(tmp5).toElement().text();
                    if (tmp6.length()<30){
                        if (tmp6.contains("{0}"))
                        {
                            if (_NameIDParam!=-1)
                            {
                                tmp7=NameIDParam.split(',');
                                for(int k=0 ;k<30;k++)
                                {
                                    if(tmp6.contains("{"+QString::number(k)+"}"))
                                    {
                                        if (tmp7.value(k).contains('{'))
                                        {
                                            tmp8=suoyin.indexOf(tmp7.value(k).remove('{').remove('}').toInt());
                                            if (tmp8>0)
                                            {
                                                tmp6.replace("{"+QString::number(k)+"}",messagelist.at(tmp8).toElement().text());
                                            }
                                        }
                                        else
                                        {
                                            tmp6.replace("{"+QString::number(k)+"}",tmp7.value(k));
                                        }
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                        hangbiaoti.append(QString::number(i+1)+","+tmp6);
                    }
                    else
                    {
                        hangbiaoti.append(QString::number(i+1));
                    }
                }
                else
                {
                    hangbiaoti.append(QString::number(i+1));
                }
            }
            else
            {
                hangbiaoti.append(QString::number(i+1));
            }
        }
        else
        {
            hangbiaoti.append(QString::number(i+1));
        }
    }
    ui->statusBar->showMessage(QObject::tr("载入文件成功."),10000);
    return true;
}

bool Dnt::dudnt(QString &fileNameDir,bool &stopflag,Ui::MainWindow *ui,QLabel *label,QDomDocument *dom,QVector<int> &suoyin,bool jiazai)
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
    if(this->shujuti.dushujuti(input,stopflag,ui,this->biaotou,this->liexinxi,dom,suoyin,jiazai))
        return true;
    else
        return false;
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
        ui->lineEdit_dnt2->setText(fileNameDir1);
    }
    fileNameDir1=ui->lineEdit_dnt1->text();
    fileNameDir2=ui->lineEdit_dnt2->text();
}

void MainWindow::on_pushButton_dnt2_clicked()
{
    QString dir=QFileInfo(fileNameDir2).absolutePath();
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
    if (!dnt1.dudnt(fileNameDir1,stopflag,this->ui,label1,dom,suoyin,jiazai))
    {
        ui->statusBar->showMessage(QObject::tr("dnt1打开失败."),10000);
        yunxing= false;
        return;
    }
    else
    {
        if(!dnt2.dudnt(fileNameDir2,stopflag,this->ui,label2,dom,suoyin,jiazai))
        {
            ui->statusBar->showMessage(QObject::tr("dnt2打开失败."),10000);
            yunxing= false;
            return;
        }
        else
            ui->statusBar->showMessage(QObject::tr("文件打开成功."),10000);
        qApp->processEvents ();
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

    ui->statusBar->showMessage(QObject::tr("正在进行比较.."),10000);
    qApp->processEvents ();

    int hangshu1=dnt1.biaotou.hangshu;
    int hangshu2=dnt2.biaotou.hangshu;

    QVector<QString> *hangshuju1=&(dnt1.shujuti.hangshuju);
    QVector<QString> *hangshuju2=&(dnt2.shujuti.hangshuju);
    QVector<QString> *hangbiaoti1=&(dnt1.shujuti.hangbiaoti);
    QVector<QString> *hangbiaoti2=&(dnt2.shujuti.hangbiaoti);
    QVector<QString> *hangbianhao1=&(dnt1.shujuti.hangbianhao);
    QVector<QString> *hangbianhao2=&(dnt2.shujuti.hangbianhao);



    int TS[hangshu1];
    for (int i=0;i<hangshu1;i++)
    {
        TS[i]=-1;
    }
    int TD[hangshu2];
    for (int i=0;i<hangshu2;i++)
    {
        TD[i]=-1;
    }



    for(int i=0;i<hangshu1;i++)
    {
        for(int j=0;j<hangshu2;j++)
        {
            if(TD[j]==-1)
            {
                if(hangbianhao1->value(i)==hangbianhao2->value(j))
                {
                    TS[i]=j;
                    if (hangshuju1->value(i)==hangshuju2->value(j))
                    {
                        TD[j]=1;
                    }
                    else
                    {
                        TD[j]=0;
                    }
                    break;
                }
            }
        }
    }
    ui->statusBar->showMessage(QObject::tr("正在生成表格.."),10000);
    if (stopflag)
    {
        ui->statusBar->showMessage(QObject::tr("停止比较."),10000);
        yunxing= false;
        return;
    }
    qApp->processEvents ();

    ui->tableWidget->setColumnCount(lieshu+1);

    QList<QString> HorizontalHeaderLabels=dnt1.liexinxi.liebiaoti.toList();
    HorizontalHeaderLabels.insert(0,QObject::tr("_nRow"));
    ui->tableWidget->setHorizontalHeaderLabels(HorizontalHeaderLabels);
    ui->tableWidget->resizeColumnsToContents();
    if (stopflag)
    {
        ui->statusBar->showMessage(QObject::tr("停止比较."),10000);
        yunxing= false;
        return;
    }
    qApp->processEvents ();



    QTableWidget*tableWidget1=ui->tableWidget;
    QTableWidgetItem *tmp1;
    QStringList tmp2;
    QTableWidgetItem *tmp3;
    QStringList tmp4;
    int rowcount=0;
    int cur_row=0;
    QVector<qint8> *lieleixing1=&(dnt1.liexinxi.lieleixing);


    rowcount++;
    tableWidget1->setRowCount(rowcount);
    tmp1=new QTableWidgetItem("dnt1<-->dnt2.");
    tableWidget1->setVerticalHeaderItem(cur_row,tmp1);
    cur_row++;

    for(int i=0;i<hangshu1;i++)
    {
        if (i%20==0)
        {
            ui->statusBar->showMessage(QObject::tr("正在生成表格.."),10000);
            if (stopflag)
            {
                ui->statusBar->showMessage(QObject::tr("停止比较."),10000);
                yunxing= false;
                return;
            }
            qApp->processEvents ();
        }
        if(TS[i]!=-1 && TD[TS[i]]==0)
        {
            int j=TS[i];
            rowcount+=2;
            tableWidget1->setRowCount(rowcount);

            tmp1=new QTableWidgetItem(hangbiaoti1->value(i));
            tmp3=new QTableWidgetItem(hangbiaoti2->value(j));

            tmp1->setTextColor(Qt::red);
            tmp3->setTextColor(Qt::blue);

            tableWidget1->setVerticalHeaderItem(cur_row,tmp1);
            tableWidget1->setVerticalHeaderItem(cur_row+1,tmp3);



            tmp1=new QTableWidgetItem(hangbianhao1->value(i));
            tmp3=new QTableWidgetItem(hangbianhao2->value(j));

            tmp1->setTextAlignment(Qt::AlignRight);
            tmp3->setTextAlignment(Qt::AlignRight);

            tableWidget1->setItem(cur_row,0,tmp1);
            tableWidget1->setItem(cur_row+1,0,tmp3);



            tmp2=hangshuju1->value(i).split("||");
            tmp4=hangshuju2->value(j).split("||");
            for(int k=0;k<lieshu;k++)
            {
                tmp1=new QTableWidgetItem(tmp2.value(k));
                tmp3=new QTableWidgetItem(tmp4.value(k));
                if(lieleixing1->value(k)==1)
                {
                    tmp1->setTextAlignment(Qt::AlignLeft);
                    tmp3->setTextAlignment(Qt::AlignLeft);
                }
                else
                {
                    tmp1->setTextAlignment(Qt::AlignRight);
                    tmp3->setTextAlignment(Qt::AlignRight);
                }
                if(tmp2.value(k)!=tmp4.value(k))
                {
                    tmp1->setTextColor(Qt::red);
                    tmp3->setTextColor(Qt::blue);
                }
                tableWidget1->setItem(cur_row,k+1,tmp1);
                tableWidget1->setItem(cur_row+1,k+1,tmp3);
            }

            cur_row+=2;
        }
    }




    rowcount++;
    tableWidget1->setRowCount(rowcount);
    tmp1=new QTableWidgetItem("   ");
    tableWidget1->setVerticalHeaderItem(cur_row,tmp1);
    cur_row++;

    rowcount++;
    tableWidget1->setRowCount(rowcount);
    tmp1=new QTableWidgetItem("dnt1中删除的行.");
    tableWidget1->setVerticalHeaderItem(cur_row,tmp1);
    cur_row++;

    for(int i=0;i<hangshu1;i++)
    {
        if (i%20==0)
        {
            ui->statusBar->showMessage(QObject::tr("正在生成表格.."),10000);
            if (stopflag)
            {
                ui->statusBar->showMessage(QObject::tr("停止比较."),10000);
                yunxing= false;
                return;
            }
            qApp->processEvents ();
        }
        if(TS[i]==-1)
        {
            rowcount++;
            tableWidget1->setRowCount(rowcount);

            tmp1=new QTableWidgetItem(hangbiaoti1->value(i));
            tmp1->setTextColor(Qt::red);
            tableWidget1->setVerticalHeaderItem(cur_row,tmp1);

            tmp1=new QTableWidgetItem(hangbianhao1->value(i));
            tmp1->setTextAlignment(Qt::AlignRight);
            tmp1->setTextColor(Qt::red);
            tableWidget1->setItem(cur_row,0,tmp1);

            tmp2=hangshuju1->value(i).split("||");
            for(int j=0;j<lieshu;j++)
            {
                tmp1=new QTableWidgetItem(tmp2.value(j));
                if (lieleixing1->value(i)==1)
                {
                    tmp1->setTextAlignment(Qt::AlignLeft);
                }
                else
                {
                    tmp1->setTextAlignment(Qt::AlignRight);
                }
                tmp1->setTextColor(Qt::red);
                tableWidget1->setItem(cur_row,j+1,tmp1);
            }
            cur_row++;
        }

    }




    rowcount++;
    tableWidget1->setRowCount(rowcount);
    tmp1=new QTableWidgetItem("   ");
    tableWidget1->setVerticalHeaderItem(cur_row,tmp1);
    cur_row++;

    rowcount++;
    tableWidget1->setRowCount(rowcount);
    tmp1=new QTableWidgetItem("dnt2中新增的行.");
    tableWidget1->setVerticalHeaderItem(cur_row,tmp1);
    cur_row++;

    for(int i=0;i<hangshu2;i++)
    {
        if(TD[i]==-1)
        {
            if (i%20==0)
            {
                ui->statusBar->showMessage(QObject::tr("正在生成表格.."),10000);
                qApp->processEvents ();
                if (stopflag)
                {
                    ui->statusBar->showMessage(QObject::tr("停止比较."),10000);
                    yunxing= false;
                    return;
                }
            }
            rowcount++;
            tableWidget1->setRowCount(rowcount);

            tmp1=new QTableWidgetItem(hangbiaoti2->value(i));
            tmp1->setTextColor(Qt::blue);
            tableWidget1->setVerticalHeaderItem(cur_row,tmp1);

            tmp1=new QTableWidgetItem(hangbianhao2->value(i));
            tmp1->setTextAlignment(Qt::AlignRight);
            tmp1->setTextColor(Qt::blue);
            tableWidget1->setItem(cur_row,0,tmp1);

            tmp2=hangshuju2->value(i).split("||");
            for(int j=0;j<lieshu;j++)
            {
                tmp1=new QTableWidgetItem(tmp2.value(j));
                if (lieleixing1->value(i)==1)
                {
                    tmp1->setTextAlignment(Qt::AlignLeft);
                }
                else
                {
                    tmp1->setTextAlignment(Qt::AlignRight);
                }
                tmp1->setTextColor(Qt::blue);
                tableWidget1->setItem(cur_row,j+1,tmp1);
            }
            cur_row++;
        }

    }

    ui->tableWidget->resizeColumnsToContents();
    ui->statusBar->showMessage(QObject::tr("比较完成."),10000);

    yunxing= false;
}

void MainWindow::on_pushButton_stop_clicked()
{
    stopflag=true;
}


void MainWindow::on_pushButton_xlsx_clicked()
{

    if(yunxing)
    {
        return;
    }
    else
    {
        yunxing= true;
    }
    QTXLSX_USE_NAMESPACE;

    QString dir=QFileInfo(fileNameDir1).absolutePath();
    QString saveDir=QFileDialog::getSaveFileName(this,"",dir,"xlsx Files(*.xlsx)");

    QXlsx::Document xlsx;
    QTableWidget*tableWidget1=ui->tableWidget;
    int hangshu1=tableWidget1->rowCount();
    int lieshu1= tableWidget1->columnCount();
    QTableWidgetItem *tmp1;
    Format format1;
    QString txt1;

    xlsx.write(1,1,"");
    for(int j=0;j<lieshu1;j++)
    {
        tmp1=tableWidget1->horizontalHeaderItem(j);
        if(tmp1!=NULL)
        {
            format1.setFontColor(tmp1->textColor());
            xlsx.write(1,j+2,tmp1->text(),format1);
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
        tmp1=tableWidget1->verticalHeaderItem(i);
        if(tmp1!=NULL)
        {
            format1.setFontColor(tmp1->textColor());
            txt1=tmp1->text();
            xlsx.write(i+2,1,txt1,format1);
            if(txt1.contains("dnt"))
            {
                continue;
            }
            else if(txt1=="   ")
            {
                continue;
            }
        }
        else
        {
            xlsx.write(i+2,1,QString::number(i+1));
        }

        tmp1=tableWidget1->item(i,0);
        if(tmp1!=NULL)
        {
            format1.setFontColor(tmp1->textColor());
            xlsx.write(i+2,2,tmp1->text().toInt(),format1);
        }
        else
        {
            xlsx.write(i+2,2,"");
        }
        for(int j=1;j<lieshu1;j++)
        {

            tmp1=tableWidget1->item(i,j);
            if(tmp1!=NULL)
            {
                format1.setFontColor(tmp1->textColor());
                if(dnt1.liexinxi.lieleixing.value(j-1)==1)
                {
                    xlsx.write(i+2,j+2,tmp1->text(),format1);
                }
                else if(dnt1.liexinxi.lieleixing.value(j-1)<=3)
                {
                    xlsx.write(i+2,j+2,tmp1->text().toInt(),format1);
                }
                else if(dnt1.liexinxi.lieleixing.value(j-1)<=5)
                {
                    xlsx.write(i+2,j+2,tmp1->text().toDouble(),format1);
                }
                cout<<dnt1.liexinxi.lieleixing.value(i-1)<<endl;
            }
            else
            {
                xlsx.write(i+2,j+2,"");
            }
        }
    }

    statusBar()->showMessage(tr("正在保存xlsx..."),10000);
    xlsx.saveAs(saveDir);
    statusBar()->showMessage(tr("成功导出xlsx."),10000);
    yunxing= false;

}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::information(0,tr("关于"), tr("\n\"DntComparer v1.0\" -20130125\n"
                                            "---------------------\n"
                                            "Author:xiaot\tEmail:liuqiang1357@163.com\t\n"
                                            "Qt:5.0.2\t\tmingw:4.8.0\n"
                                            "on Microsoft Windows 7 (32-bit)\n"));
}
