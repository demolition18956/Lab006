#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tSocket = new QTcpSocket(this);
    connect(tSocket, &QTcpSocket::readyRead, this, &MainWindow::updateEdit);


    tSocket->connectToHost(QHostAddress::LocalHost, 5678,QIODevice::ReadOnly);
    tSocket->waitForConnected();    // Wait for three handshake to complete
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateEdit()
{
    QTextStream incomingMessage(tSocket);

    QString msg = incomingMessage.readAll();
    msg.trimmed();
    qDebug() << msg;
    ui->textEdit->append(msg);

}
