#pragma once

#include <memory>
#include <map>

#include "IEventData.h"
#include "Actor.h"
#include "ActorFactory.h"
#include "BaseEngineState.h"
#include "ProcessManager.h"

class BaseEngineLogic {

protected:
	std::map<unsigned int, std::shared_ptr<Actor>>	m_actors;
	std::shared_ptr<ActorFactory>					m_pActorFactory;
	BaseEngineState									m_State;			// engine state: loading, running, etc.
	float											m_Lifetime;			//indicates how long this engine has been in session
	std::shared_ptr<ProcessManager>					m_pProcessManager;	// a engine logic entity

public:
	BaseEngineLogic();
	BaseEngineLogic(const BaseEngineLogic&) = delete;
	BaseEngineLogic& operator=(const BaseEngineLogic&) = delete;
	~BaseEngineLogic();
	bool Init();

	virtual void VOnUpdate(float time, float elapsedTime);

	virtual std::weak_ptr<Actor> VGetActor(const unsigned int actorId);

	void RequestNewActorDelegate(std::shared_ptr<IEventData> pEventData);
	BaseEngineState GetEngineState();
	void SetEngineState(BaseEngineState es);
};
