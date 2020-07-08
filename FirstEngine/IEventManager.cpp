#include "IEventManager.h"

#include "EvtData_Environment_Loaded.h"
#include "EvtData_New_Actor.h"
#include "EvtData_Move_Actor.h"
#include "EvtData_Destroy_Actor.h"
#include "EvtData_Request_New_Actor.h"

IEventManager* g_pEventMgr = NULL;
GenericObjectFactory<IEventData, unsigned long> g_eventFactory;

IEventManager* IEventManager::Get(void) {
    return g_pEventMgr;
}

IEventManager::IEventManager(const char* pName, bool setAsGlobal) {
    if (setAsGlobal) {
        if (g_pEventMgr) {
            delete g_pEventMgr;
        }

        g_pEventMgr = this;
    }
    g_eventFactory.Register<EvtData_Environment_Loaded>(EvtData_Environment_Loaded::sk_EventType);
    g_eventFactory.Register<EvtData_New_Actor>(EvtData_New_Actor::sk_EventType);
    g_eventFactory.Register<EvtData_Move_Actor>(EvtData_Move_Actor::sk_EventType);
    g_eventFactory.Register<EvtData_Destroy_Actor>(EvtData_Destroy_Actor::sk_EventType);
    g_eventFactory.Register<EvtData_Request_New_Actor>(EvtData_Request_New_Actor::sk_EventType);
}

IEventManager::~IEventManager(void) {
    if (g_pEventMgr == this)
        g_pEventMgr = NULL;
}
