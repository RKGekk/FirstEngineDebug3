#include <iostream>
#include <memory>

#include "FastDelegate.h"
#include "FastDelegateBind.h"

#include "BaseEventData.h"
#include "IEventManager.h"
#include "EvtData_New_Actor.h"

#include "EventManager.h"
#include "Actor.h"
#include "ActorComponent.h"
#include "TransformComponent.h"
#include "ActorFactory.h"

#include "BaseEngineLogic.h"

#include "ISceneNode.h"
#include "Scene.h"

#include "SystemClass.h"

#include "Process.h"
#include "ProcessManager.h"
#include "CountProcess.h"

int main() {

	std::unique_ptr<SystemClass> System(new SystemClass);
	if (System->Initialize()) {
		System->Run();
	}
	// Shutdown and release the system object.
	System->Shutdown();

	//std::shared_ptr<BaseEngineLogic> gameLogic1(new BaseEngineLogic());

	//EventManager* m_pEventManager = new EventManager("GameCodeApp Event Mgr", true);

	//IEventManager::Get()->VAddListener(fastdelegate::MakeDelegate(gameLogic1.get(), &BaseGameLogic::RequestNewActorDelegate), EvtData_New_Actor::sk_EventType);

	//ActorFactory actorFactory;
	//std::shared_ptr<Actor> actor = actorFactory.CreateActor("Teapot", nullptr, nullptr, 0);

	//std::shared_ptr<EvtData_New_Actor> pNewActorEvent(new EvtData_New_Actor(actor->GetId()));
	//IEventManager::Get()->VQueueEvent(pNewActorEvent);

	//Scene scene1(gameLogic1);
	////scene1.AddChild(actor->GetId(), nullptr);

	//IEventManager::Get()->VUpdate(20);

	/*std::shared_ptr<ProcessManager> m_pProcessManager(new ProcessManager);
	std::shared_ptr<CountProcess> m_pCountProcess1(new CountProcess);
	std::shared_ptr<CountProcess> m_pCountProcess2(new CountProcess);
	m_pCountProcess1->AttachChild(m_pCountProcess2);
	m_pProcessManager->AttachProcess(m_pCountProcess1);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);
	m_pProcessManager->UpdateProcesses(10);*/

	//std::cin.get();
	return 0;
}