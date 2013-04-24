#include <QBuffer>
#include <QTcpSocket>
#include "datatransferserver.h"

DataTransferServer::DataTransferServer(QObject* parent) : QTcpServer(parent)
{
}

DataTransferServer::~DataTransferServer()
{
}
void DataTransferServer::incomingConnection(int socketfd)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);
     qDebug() << "New client from:" << client->peerAddress().toString();
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void DataTransferServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine()) {
        QString message  = QString::fromUtf8(client->readLine()).trimmed();
         qDebug() << "Read line message:" << message;
        foreach(QTcpSocket *otherClient, clients)
            otherClient->write(QString(message + "\n").toUtf8());
    }
}

void DataTransferServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    clients.remove(client);
}

void DataTransferServer::startListen()
{
    this->listen(QHostAddress::Any,TRANSFERQUESTION);
    system("startserver.vbs");
}
