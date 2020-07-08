#pragma once

#include <DirectXMath.h>
#include <memory>
#include <list>

#include "tinyxml.h"

#include "IGameView.h"
#include "ProcessManager.h"
#include "IScreenElement.h"
#include "IRenderer.h"
#include "ScreenElementScene.h"
#include "CameraNode.h"
#include "BaseEngineState.h"
#include "IEventData.h"

// This is a view onto the game - which includes anything visual or audible.
// It gets messages about the changes in game state.
class HumanView : public IGameView {
	friend class GameCodeApp;

protected:
	unsigned int m_ViewId;
	unsigned int m_ActorId;

	ProcessManager* m_pProcessManager;				// strictly for things like button animations, etc.

	float m_currTick;		// time right now
	float m_lastDraw;		// last time the game rendered
	bool m_runFullSpeed;	// set to true if you want to run full speed

	virtual void VRenderText() {};

public:
	bool LoadGame(TiXmlElement* pLevelData);

protected:
	virtual bool VLoadGameDelegate(TiXmlElement* pLevelData) { VPushElement(m_pScene);  return true; }

public:
	// Implement the IGameView interface, except for the VOnRender() method, which is renderer specific
	virtual HRESULT VOnRestore();
	virtual HRESULT VOnLostDevice();
	virtual void VOnRender(double fTime, float fElapsedTime);
	virtual GameViewType VGetType() { return GameViewType::GameView_Human; }
	virtual unsigned int VGetId() const { return m_ViewId; }

	virtual void VOnAttach(unsigned int vid, unsigned int aid) {
		m_ViewId = vid;
		m_ActorId = aid;
	}

	virtual void VOnUpdate(const int deltaMilliseconds);

	// Virtual methods to control the layering of interface elements
	virtual void VPushElement(std::shared_ptr<IScreenElement> pElement);
	virtual void VRemoveElement(std::shared_ptr<IScreenElement> pElement);

	void TogglePause(bool active);

	virtual ~HumanView();
	HumanView(std::shared_ptr<IRenderer> renderer);

	std::list<std::shared_ptr<IScreenElement>> m_ScreenElements;	// a game screen entity

	//Camera adjustments.
	virtual void VSetCameraOffset(const DirectX::XMFLOAT4& camOffset);

	std::shared_ptr<ScreenElementScene> m_pScene;
	std::shared_ptr<CameraNode> m_pCamera;

	void HandleGameState(BaseEngineState newState) {};

	// Added post press - this helps the network system attach views to the right actor.
	virtual void VSetControlledActor(unsigned int actorId) { m_ActorId = actorId; }

	// Event delegates
	void GameStateDelegate(std::shared_ptr<IEventData> pEventData);

private:
	void RegisterAllDelegates(void);
	void RemoveAllDelegates(void);
};