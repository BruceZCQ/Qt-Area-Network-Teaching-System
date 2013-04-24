#ifndef SIMPLECHATSERVER_H
#define SIMPLECHATSERVER_H

#include <QTcpServer>
#include <QList>
#include <QHash>
#include "constvar.h"

class QBuffer;
class QTcpSocket;

class DataTransferServer : public QTcpServer
{
	Q_OBJECT

public:
        DataTransferServer(QObject* parent = 0);
        ~DataTransferServer();
        void startListen();
protected:
    void incomingConnection(int socketfd);
private slots:
    void readyRead();
    void disconnected();
private:
    QSet<QTcpSocket*> clients;
};

#endif // SIMPLECHATSERVER_H
