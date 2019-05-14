/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef COVRCOMMUNICATION_H
#define COVRCOMMUNICATION_H

/*! \file
 \brief  handle collaborative messages

 \author Uwe Woessner <woessner@hlrs.de>
 \author (C) 2001
         Computer Centre University of Stuttgart,
         Allmandring 30,
         D-70550 Stuttgart,
         Germany

 \date   July 2001
 */

namespace covise
{
class Message;
}


#include <map>
#include <set>
#include <vrbclient/regClass.h>
#include <vrbclient/SharedState.h>
#include "ui/Owner.h"
#include <vrbclient/SessionID.h>
#include <net/message_types.h>


namespace vrb {
    class SharedStateManager;
    class VrbClientRegistry;
}
namespace opencover
{
class VRBData;
class IData;
class coVRPartner;
class VrbMenue;
namespace ui
{
class Owner;
class Group;
class FileBrowser;
class Action;
class SelectionList;
};
class COVEREXPORT coVRCommunication: public vrb::regClassObserver, public ui::Owner
{
public:
    enum
    {
        TRANSFORM = 0,
        SCALE,
        MOVE_DNA,
        NUM_LOCKS
    };
    static coVRCommunication *instance();
    void RILock(int lockID);
    void RIUnLock(int lockID);
    void RIRemoteLock(int lockID, int remoteID);
    void RIRemoteUnLock(int lockID, int remoteID);
    bool isRILocked(int lockID);
    bool isRILockedByMe(int lockID);

    ~coVRCommunication();
    void processRenderMessage(const char * key, const char * tmp);
    void processVRBMessage(covise::TokenBuffer &tb);

    bool collaborative(); // returns true, if in collaborative mode
    bool isMaster(); // returns true, if we are master



    static const char *getHostname();
    static const char *getHostaddress();
    static std::string getUsername();
    int getID();
    vrb::SessionID &getPrivateSessionIDx();
    const vrb::SessionID &getSessionID() const;
    void setSessionID(const vrb::SessionID &id);
    int getNumberOfPartners();
    void setFBData(IData *data);
    void handleVRB(covise::Message *msg);
    void setCurrentFile(const char *filename);
    virtual void update(vrb::clientRegClass *theChangedClass);

    void becomeMaster();
    covise::Message *waitForMessage(int messageType);
    std::unique_ptr<vrb::VrbClientRegistry> registry;
    bool sendMessage(covise::Message *msg);
    bool sendMessage(covise::TokenBuffer &tb, covise::covise_msg_type type);
	//add callback that is called after first contact with vrb
	void addOnConnectCallback(std::function<void(void)> function);
	//add callback that is called when vrb disconnects
	void addOnDisconnectCallback(std::function<void(void)> function);
	//set link to covise plugin function to get message from covise socket
	void setWaitMessagesCallback(std::function<std::vector<covise::Message*>(void)> cb);
	//set link to covise plugin function to handle a covise message
	void setHandleMessageCallback(std::function<void(covise::Message *)> cb);

	std::vector<covise::Message*> waitCoviseMessages();
	void handleCoviseMessage(covise::Message* m);
private:
    coVRCommunication();
    static coVRCommunication *s_instance;
    coVRPartner *me = nullptr;
    int RILockArray[1000];
    int randomID;
    bool ignoreRemoteTransform;
    std::map<int, VRBData *> mfbData;
    std::unique_ptr<VrbMenue> m_vrbMenue;
    vrb::SessionID m_privateSessionID;
	std::vector<std::function<void(void)>> onConnectCallbacks;
	std::vector<std::function<void(void)>> onDisconnectCallbacks;
	//covise plugin callbacks
	std::function <std::vector<covise::Message*>(void)> waitMessagesCallback;
	std::function<void(covise::Message*)> handleMessageCallback;
	//inform interested parties about connention to vrb or covise
	void connected();
	//inform interested parties about disconnection from vrb or covise
	void disconnected();
};
}
#endif
