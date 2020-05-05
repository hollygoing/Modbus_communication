#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "mcmodbusrtu.h"

int timeSet = 50;//全局变量的定义
int time_sp = 50;
unsigned short address = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mmrtu=new McModbusRTU();
    connect(mmrtu,&McModbusRTU::McModbusRTUMessage,this,&MainWindow::McModbusRTUMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::closeEvent(QCloseEvent *ev){ //有错 先注释了
//    linkserver->LinkServerClose();
//}

void MainWindow::McModbusRTUMessage(unsigned char mID, int mFunction, QByteArray Data){
    //若采集数据为普通数据时候
    ShortToOther ChangeTemp;
    //ChangeTemp.mshort[0]=(Data[i*2+ii*4]<<8)|(Data[i*2+ii*4+1]&0xFF);
    //qDebug()<<"bbb" + QString::number(ChangeTemp.mshort[0]);
    //所采集数据是Float数据类型时候
     for(int i=0;i<2;i++){
         ChangeTemp.mshort[i]=(Data[i*2]<<8)|(Data[i*2+1]&0xFF);//前高位后低位
     }
//     DataTemp[ii]=ChangeTemp.mfloat;
//     std::cout<< "0"<<std::endl;
     std::cout<< (Data[0]<<8) <<std::endl;
     std::cout<< (Data[1]&0xFF) <<std::endl;
     std::cout<< (Data[2]<<8) <<std::endl;
     std::cout<< (Data[3]&0xFF) <<std::endl;
}

void MainWindow::on_pushButton_4_clicked()
{
    if(mmrtu->LinkUart(ui->lineEdit_3->text())>5){
        statusBar()->showMessage("连接成功");
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    s_work();
}
