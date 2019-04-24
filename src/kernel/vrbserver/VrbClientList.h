/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef VRBCLIENTLIST_H
#define VRBCLIENTLIST_H
#include <util/coExport.h>
#include <vrbclient/SessionID.h>
#include <net/message_types.h>
#include <string>
#include <set>
#include <vector>
namespace covise
{
class TokenBuffer;
class Connection;
class Message;
}

namespace vrb
{
class ServerInterface;

enum VRBSERVEREXPORT Columns {
    Master,
    ID,
    Group,
    User,
    Host,
    Email,
    URL,
    IP,
};
class VRBSERVEREXPORT VRBSClient
{
public:
    ///Vrb Server client that holds a connection and information about the client
    ///send = false if you dont want to inform the client immediatly about the contact
    VRBSClient(covise::Connection *c, const char *ip, const char *name , bool send = true, bool deleteClient = true);
    virtual ~VRBSClient();
    ///set clientinformation and inform the client about its server id and session
    virtual void setContactInfo(const char *ip, const char *n, vrb::SessionID &session);
    ///store userinfo like email, pc-name, ...
    virtual void setUserInfo(const char *userInfo);
    covise::Connection *conn;
    std::string getName() const;
    std::string getIP() const;
    int getID() const;
    vrb::SessionID &getSession();
    virtual void setSession(const vrb::SessionID &g);
    vrb::SessionID &getPrivateSession();
    void setPrivateSession(vrb::SessionID &g);
    int getMaster();
    virtual void setMaster(bool m);
    std::string getUserInfo();
    std::string getUserName();
    int getSentBPS();
    int getReceivedBPS();
    void setInterval(float i);
    void addBytesSent(int b);
    void addBytesReceived(int b);
    void getInfo(covise::TokenBuffer &rtb);
    bool hasFileLoaded(const std::string &fileName);
    bool addLoadedFile(const std::string &fileName);
	//return true if a file request to this client for fileName was already unsuccessful
	bool doesNotKnowFile(const std::string& fileName);
	void addUnknownFile(const std::string& fileName);
protected:
    //list of directories that this client has loaded
    std::set<std::string> m_loadedFiles;
	std::set<std::string> m_unknownFiles;
    std::string address;
    std::string m_name;
    std::string userInfo;
    int myID = -1;
    vrb::SessionID m_publicSession, m_privateSession;
    int m_master = false;
    long bytesSent = 0;
    long bytesReceived = 0;
    double lastRecTime = -1.;
    double lastSendTime = -1.;
    float interval = 0;
    int bytesSentPerInterval = 0;
    int bytesReceivedPerInterval = 0;
    int bytesSentPerSecond = 0;
    int bytesReceivedPerSecond = 0;
	bool deleteClient = true;
    
    double time();

};

class VRBSERVEREXPORT VRBClientList
{
protected:
    std::set<VRBSClient *> m_clients;
    std::set<std::string> m_knownFiles;

public:
    VRBSClient *get(covise::Connection *c);
    VRBSClient *get(const char *ip);
    VRBSClient *get(int id);
    VRBSClient *getMaster(const vrb::SessionID &session);
    VRBSClient *getNextInGroup(const vrb::SessionID &id);
    VRBSClient *getNthClient(int N);
    std::vector<VRBSClient *> getClientsWithUserName(const std::string &name);
    int getNextFreeClientID();
    ///client becomes master and all other clients in clients in session lose master state
    void setMaster(VRBSClient *client);
    void setInterval(float i);
    void deleteAll();
    ///send mesage to every member of the session
    void sendMessage(covise::TokenBuffer &stb, const vrb::SessionID &group = vrb::SessionID(0, "all", false), covise::covise_msg_type type = covise::COVISE_MESSAGE_VRB_GUI);
    ///send message to the client with id
    void sendMessageToID(covise::TokenBuffer &stb, int id, covise::covise_msg_type type = covise::COVISE_MESSAGE_VRB_GUI);
    void sendMessageToAll(covise::TokenBuffer &tb, covise::covise_msg_type type = covise::COVISE_MESSAGE_VRB_GUI);
	static std::string cutFileName(const std::string& fileName);
    int numInSession(vrb::SessionID &Group);
    int numberOfClients();
    void addClient(VRBSClient *cl);
    void removeClient(VRBSClient *cl);
	/// remove client with connection c
	void remove(covise::Connection *c);
    ///send Message to all clients but the sender of the message
    void passOnMessage(covise::Message * msg, const vrb::SessionID &session = vrb::SessionID(0, "", false));
    ///write the info of all clients in the tokenbuffer
    void collectClientInfo(covise::TokenBuffer &tb);
    VRBSClient *getLoadedFileClient(const std::string &fileName);
    bool insertFile(std::string &fileName);
    bool removeFile(std::string &fileName);
	VRBSClient* getNextPossibleFileOwner(const std::string& fileName, const vrb::SessionID& id);
};
extern VRBSERVEREXPORT VRBClientList clients;

}
#endif