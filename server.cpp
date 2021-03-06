#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    //ui->tOut->setText("1234");
    //ui->tOut->("56789");
    server = new QTcpServer(this);
    client = new QTcpSocket(this);
    if(!server->listen(QHostAddress::LocalHost, port))
    {
        QMessageBox::critical(0,"Server Error","Unable to start the server " + server->errorString());
        server->close();
        return ;
    }
    connect(server, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    ui->tOut->setReadOnly(true);
    //ui->tOut->append(z)

}

Server::~Server()
{
    delete ui;
}

void Server::slotNewConnection()
{
    qDebug() << "New connection!";
    client = server->nextPendingConnection();
    connect(client, SIGNAL(disconnected()),client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}

void Server::slotReadClient()
{
    qDebug()<<"New message!";
    if(client->bytesAvailable())
    {
        QByteArray answ;
        answ = client->readAll();
        if(mc == MAX)
        {
            shiftMessage();
            mass[mc] = QString::fromUtf8(answ);
        }
        else{
            mass[mc++] = QString::fromUtf8(answ);

        }
    }
    ui->tOut->setText(mass[mc-1]);
}

void Server::on_btnBack_clicked()
{
    if(mc == 0 || mi == 0)
        return ;
    else
    {
        ui->tOut->setText(mass[--mi]);
    }
}

void Server::on_btnNext_clicked()
{
    if(mc == 0 || mi == MAX)
        return ;
    else
    {
        ui->tOut->setText(mass[++mi]);
    }
}

void Server::shiftMessage()
{
    for(int i = 0; i < MAX - 2; i++)
        mass[i] = mass[i+1];
}
