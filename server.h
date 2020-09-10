#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QTime>

#define MAX 10

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT
private:
    void sendMessage(const QString &);

public slots:
    void slotNewConnection();
    void slotReadClient();
public:
    Server(QWidget *parent = nullptr);
    ~Server();
    int mc = 0; // count of recieaved message
    int mi = 0; // index of viewer message
    int port = 6666;

    QString mass[MAX];
    QList<QString> mess;
    QTcpServer *server;
    QTcpSocket *client;



private slots:
    void on_btnBack_clicked();

    void on_btnNext_clicked();

private:
    Ui::Server *ui;
    void shiftMessage();
};
#endif // SERVER_H
