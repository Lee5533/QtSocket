#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket();
    on_pushButton_Connect_clicked();

}

MainWindow::~MainWindow()
{
    delete this->socket;
    delete ui;
}

void MainWindow::on_pushButton_Connect_clicked()
{
        QString IP="127.0.0.1";
        int port=5150;
        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost(IP, port);

        //等待连接成功
        if(!socket->waitForConnected(30000))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";
}

void MainWindow::on_pushButton_Send_clicked()
{
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
     //获取文本框内容并以ASCII码形式发送
    socket->write(ui->textEdit_Send->toPlainText().toLatin1());
    socket->flush();
}
