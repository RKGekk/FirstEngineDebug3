#include "Scene.h"
#include "RootNode.h"
#include "ISceneNode.h"
#include "IEventData.h"
#include "IEventManager.h"
#include "FastDelegate.h"
#include "memoryUtility.h"
#include "stringUtility.h"
#include "EvtData_Modified_Render_Component.h"
#include "EvtData_New_Render_Component.h"
#include "EvtData_Destroy_Actor.h"
#include "EvtData_Move_Actor.h"
#include "BaseEngineLogic.h"
#include "MatrixStack.h"
#include "Actor.h"
#include "CameraNode.h"
#include "SystemClass.h"
#include "IRenderer.h"

Scene::Scene(std::shared_ptr<IRenderer> renderer) {

	m_Renderer = renderer;

	m_Root.reset(new RootNode());
	m_MatrixStack = std::shared_ptr<MatrixStack>(new MatrixStack());

	IEventManager* pEventMgr = IEventManager::Get();
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::DestroyActorDelegate), EvtData_Destroy_Actor::sk_EventType);
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::MoveActorDelegate), EvtData_Move_Actor::sk_EventType);
	pEventMgr->VAddListener(fastdelegate::MakeDelegate(this, &Scene::ModifiedRenderComponentDelegate), EvtData_Modified_Render_Component::sk_EventType);
}

Scene::~Scene() {
	
	IEventManager* pEventMgr = IEventManager::Get();
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::DestroyActorDelegate), EvtData_Destroy_Actor::sk_EventType);
	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::MoveActorDelegate), EvtData_Move_Actor::sk_EventType);

	pEventMgr->VRemoveListener(fastdelegate::MakeDelegate(this, &Scene::ModifiedRenderComponentDelegate), EvtData_Modified_Render_Component::sk_EventType);
}

HRESULT Scene::OnRender() {
	// The render passes usually go like this 
	// 1. Static objects & terrain
	// 2. Actors (dynamic objects that can move)
	// 3. The Sky
	// 4. Anything with Alpha

	return S_OK;
}

HRESULT Scene::OnRestore() {
	if (!m_Root) {
		return S_OK;
	}

	HRESULT hr;
	hr = m_Renderer->VOnRestore();
	if (FAILED(hr)) { return hr; }

	return m_Root->VOnRestore(this);
}

// All Scene nodes implement VOnLostDevice.
HRESULT Scene::OnLostDevice() {
	if (m_Root) {
		return m_Root->VOnLostDevice(this);
	}
	return S_OK;
}

HRESULT Scene::OnUpdate(const int deltaMilliseconds) {
	if (!m_Root) {
		return S_OK;
	}

	DWORD elapsedTime = 10;
	return m_Root->VOnUpdate(this, elapsedTime);
}

std::shared_ptr<ISceneNode> Scene::FindSceneNode(unsigned int actorId) {
	auto i = m_ActorMap.find(actorId);
	if (i == m_ActorMap.end()) {
		return std::shared_ptr<ISceneNode>();
	}

	return i->second;
}

std::shared_ptr<Actor> Scene::FindActor(unsigned int actorId) {
	return MakeStrongPtr(SystemClass::GetEngineLogic()->VGetActor(actorId));
}

bool Scene::AddChild(unsigned int actorId, std::shared_ptr<ISceneNode> kid) {
	if (actorId != 0) {
		// This allows us to search for this later based on actor id
		m_ActorMap[actorId] = kid;
	}

	return m_Root->VAddChild(kid);
}

bool Scene::RemoveChild(unsigned int actorId) {
	if (actorId == 0) {
		return false;
	}
	std::shared_ptr<ISceneNode> kid = FindSceneNode(actorId);
	m_ActorMap.erase(actorId);
	return m_Root->VRemoveChild(actorId);
}

void Scene::NewRenderComponentDelegate(std::shared_ptr<IEventData> pEventData) {
	std::shared_ptr<EvtData_New_Render_Component> pCastEventData = std::static_pointer_cast<EvtData_New_Render_Component>(pEventData);

	unsigned int actorId = pCastEventData->GetActorId();
	std::shared_ptr<SceneNode> pSceneNode(pCastEventData->GetSceneNode());

	// FUTURE WORK: Add better error handling here.		
	if (FAILED(pSceneNode->VOnRestore(this))) {
		std::string error = "Failed to restore scene node to the scene for actorid " + ToStr(actorId, 10);
		return;
	}

	AddChild(actorId, pSceneNode);
}

void Scene::ModifiedRenderComponentDelegate(std::shared_ptr<IEventData> pEventData) {
	std::shared_ptr<EvtData_Modified_Render_Component> pCastEventData = std::static_pointer_cast<EvtData_Modified_Render_Component>(pEventData);

	unsigned int actorId = pCastEventData->GetActorId();
	if (actorId == 0) {
		return;
	}

	std::shared_ptr<ISceneNode> pSceneNode = FindSceneNode(actorId);
	// FUTURE WORK: Add better error handling here.		
	if (!pSceneNode || FAILED(pSceneNode->VOnRestore(this))) {
		std::string error = "Failed to restore scene node to the scene for actorid " + ToStr(actorId, 10);
	}
}

void Scene::DestroyActorDelegate(std::shared_ptr<IEventData> pEventData) {
	std::shared_ptr<EvtData_Destroy_Actor> pCastEventData = std::static_pointer_cast<EvtData_Destroy_Actor>(pEventData);
	RemoveChild(pCastEventData->GetId());
}

void Scene::MoveActorDelegate(std::shared_ptr<IEventData> pEventData) {
	std::shared_ptr<EvtData_Move_Actor> pCastEventData = std::static_pointer_cast<EvtData_Move_Actor>(pEventData);

	unsigned int actorId = pCastEventData->GetId();
	DirectX::XMFLOAT4X4 transform = pCastEventData->GetMatrix();

	std::shared_ptr<ISceneNode> pNode = FindSceneNode(actorId);
	if (pNode) {
		pNode->VSetTransform(&transform);
	}
}

void Scene::SetCamera(std::shared_ptr<CameraNode> camera) {
	m_Camera = camera;
}

const std::shared_ptr<CameraNode> Scene::GetCamera() const {
	return m_Camera;
}

void Scene::PushAndSetMatrix(const DirectX::XMFLOAT4X4& toWorld) {

	m_MatrixStack->Push();
	m_MatrixStack->MultMatrixLocal(toWorld);
	DirectX::XMFLOAT4X4 mat = GetTopMatrix();
}

void Scene::PopMatrix() {

	m_MatrixStack->Pop();
	DirectX::XMFLOAT4X4 mat = GetTopMatrix();
}

const DirectX::XMFLOAT4X4 Scene::GetTopMatrix() {

	return m_MatrixStack->GetTop();
}
