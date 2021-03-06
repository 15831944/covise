/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef VRB_SERVER_H
#define VRB_SERVER_H

#include <string>
#include <QObject>
#include <QString>
#include <map>
#include <set>
#include <memory>
#include <vrbclient/SessionID.h>
#include <vrbserver/VrbMessageHandler.h>


namespace covise
{
class ServerConnection;
class ServerUdpConnection;
class Connection;
class ConnectionList;
class Message;
}
class QTreeWidgetItem;
class QSocketNotifier;

namespace vrb
{
	class VrbServerRegistry;
class VRBClientList;
class UdpMessage;
}
extern vrb::VRBClientList *vrbClients;

//
//
class VRBServer : public QObject, public vrb::ServerInterface
{
Q_OBJECT
private slots:

    void processMessages();
	void processUdpMessages();
public:
    VRBServer(bool gui);
    ~VRBServer();
    void loop();

	bool startUdpServer();
    int openServer();
    void closeServer();
    void removeConnection(covise::Connection *conn) override;


private:
    bool m_gui;
    QPixmap *pix_master = NULL;
    QPixmap *pix_slave = NULL;
    covise::ServerConnection *sConn = nullptr;
	covise::UDPConnection* udpConn = nullptr;
    QSocketNotifier *serverSN = nullptr;

    vrb::VrbMessageHandler *handler;

    covise::ConnectionList *connections = nullptr;
    int m_tcpPort, m_udpPort; // port Number (default: 31800) covise.config: VRB.TCPPort
  
    covise::Message *msg = nullptr;
	vrb::UdpMessage* udpMsg = nullptr;
	char* ip = new char[16];
    bool requestToQuit = false;

};
#endif


