#include "BaseEngineLogic.h"
#include "EvtData_New_Actor.h"

#include <iostream>

BaseEngineLogic::BaseEngineLogic() {
	m_State		= BaseEngineState::BGS_Invalid;
	m_Lifetime	= 0.0f;
}

BaseEngineLogic::~BaseEngineLogic() {}

bool BaseEngineLogic::Init(void) {
    m_pActorFactory.reset(new ActorFactory);
	m_pProcessManager.reset(new ProcessManager);

    return true;
}

void BaseEngineLogic::VOnUpdate(float time, float elapsedTime) {

	int deltaMilliseconds = int(elapsedTime * 1000.0f);
	m_Lifetime += elapsedTime;

	switch (m_State) {
		case BaseEngineState::BGS_Invalid:
		break;

		case BaseEngineState::BGS_Initializing:
		break;

		case BaseEngineState::BGS_LoadingGameEnvironment:
		break;

		case BaseEngineState::BGS_Running: {
			m_pProcessManager->UpdateProcesses(deltaMilliseconds);
		}
		break;

		default:
		break;
	}

	// update game actors
	for (auto it = m_actors.begin(); it != m_actors.end(); ++it) {
		it->second->Update(deltaMilliseconds);
	}

}

std::weak_ptr<Actor> BaseEngineLogic::VGetActor(const unsigned int actorId) {
    auto findIt = m_actors.find(actorId);
    if (findIt != m_actors.end()) {
        return findIt->second;
    }
    return std::weak_ptr<Actor>();
}

void BaseEngineLogic::RequestNewActorDelegate(std::shared_ptr<IEventData> pEventData) {
	std::cout << "Hi from event" << std::endl;

	std::shared_ptr<EvtData_New_Actor> act = std::static_pointer_cast<EvtData_New_Actor>(pEventData);
}

BaseEngineState BaseEngineLogic::GetEngineState() {
	return m_State;
}

void BaseEngineLogic::SetEngineState(BaseEngineState es) {
	m_State = es;
}
