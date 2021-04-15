#ifndef PEER_H
#define PEER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

enum PeerStatus {
    INIT,
    SYNCHRONIZED,
    INI_SUBS_OK,
    APP_QUIT,
};

class Peer : public QObject
{
    Q_OBJECT
public:
    Peer(QTcpSocket* tcp_socket, QObject* parent = nullptr);
    ~Peer();

    QString peer_id(QHostAddress addr, quint16 port);



    /**
     * @brief sendMessage send the message to the peer
     * @param message
     */
    void sendMessage(QString message);

    /**
     * @brief sendBye tells peers that this app is about to quit
     */
    void sendBye();

    /**
     * @brief bind to a regex
     * @param bindId
     * @param regex
     */
    void bind(int bindId, QString regex);

    /**
     * @brief unBind from a regex
     * @param bindId
     */
    void unBind(int bindId);

    /**
     * @brief end_initial_bindings
     */
    void end_initial_bindings();

    /**
     * @brief sendId
     * @param port of the TCP socket
     * @param myName name of this apliation
     */
    void sendId(quint16 port, QString myName);

    QString name() {return appName;}

signals:
    void message(QString id, QStringList params);
    void peerDied(Peer*);

private:
    void process();
    void parseMessage(QByteArray message);
    void subscribe(QString id, QString regex);
    void unsubscribe(QString id);
    void handle_message(QString id, QString params);

    void send_data(int type, QString ident, QString params);

    QString peerId;
    QString appName;
    QTcpSocket* socket;
    quint16 appPort;
    QByteArray rcv_array;
    PeerStatus status;

    QMap<QString /*numerical identifier*/, QString /*regex*/> subscriptions;
};

#endif // PEER_H