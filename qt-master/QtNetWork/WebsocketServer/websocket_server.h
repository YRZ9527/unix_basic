
#ifndef WEBSOKCET_SERVER_H
#define WEBSOKCET_SERVER_H
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebsocketServer : public QObject
{
	 Q_OBJECT
public:
	explicit WebsocketServer(quint16 port, bool debug = false, QObject *parent = nullptr);
	~WebsocketServer();
Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

};


#endif