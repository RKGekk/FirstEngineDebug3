#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <memory>
#include <list>
#include <map>

class BaseEngineLogic;
class SceneNode;
class MatrixStack;
class ISceneNode;
class IEventData;
class Actor;
class CameraNode;
class IRenderer;

class Scene {
protected:
	std::shared_ptr<SceneNode>							m_Root;
	std::shared_ptr<CameraNode>						 	m_Camera;
	std::shared_ptr<IRenderer>							m_Renderer;

	std::shared_ptr<MatrixStack>						m_MatrixStack;
	std::map<unsigned int, std::shared_ptr<ISceneNode>>	m_ActorMap;
	std::shared_ptr<BaseEngineLogic>					m_GameLogic;

public:
	Scene(std::shared_ptr<IRenderer> renderer);
	virtual ~Scene();

	HRESULT OnRender();
	HRESULT OnRestore();
	HRESULT OnLostDevice();
	HRESULT OnUpdate(const int deltaMilliseconds);

	std::shared_ptr<ISceneNode> FindSceneNode(unsigned int actorId);
	std::shared_ptr<Actor> FindActor(unsigned int actorId);

	bool AddChild(unsigned int actorId, std::shared_ptr<ISceneNode> kid);
	bool RemoveChild(unsigned int actorId);

	// event delegates
	void NewRenderComponentDelegate(std::shared_ptr<IEventData> pEventData);
	void ModifiedRenderComponentDelegate(std::shared_ptr<IEventData> pEventData);
	void DestroyActorDelegate(std::shared_ptr<IEventData> pEventData);
	void MoveActorDelegate(std::shared_ptr<IEventData> pEventData);

	void SetCamera(std::shared_ptr<CameraNode> camera);
	const std::shared_ptr<CameraNode> GetCamera() const;

	void PushAndSetMatrix(const DirectX::XMFLOAT4X4& toWorld);
	void PopMatrix();

	const DirectX::XMFLOAT4X4 GetTopMatrix();

	std::shared_ptr<IRenderer> GetRenderer() { return m_Renderer; }
};