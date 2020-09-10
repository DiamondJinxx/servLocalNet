#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->tOut->setText("1234");
    //ui->tOut->("56789");
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::LocalHost, port))
    {
        QMessageBox::critical(0,"Server Error","Unable to start the server " + server->errorString());
        server->close();
        return ;
    }
    connect(server, SIGNAL(newConnection()),this, SLOT());
    ui->tOut->setReadOnly(true);
    //ui->tOut->append(z)

}

Server::~Server()
{
    delete ui;
}

void Server::slotNewConnection()
{
    client = server->nextPendingConnection();
    connect((QObject*)client, SIGNAL(QAbstractSocket::disconnected()),(QObject*)client, SLOT(QObject::deleteLater()));
    connect((QObject*)client, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}

void Server::slotReadClient()
{
    if(client)
}
