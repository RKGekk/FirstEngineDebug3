#pragma once

#include <memory>
#include <vector>

#include "ISceneNode.h"
#include "RenderPass.h"

class scene;
class SceneNodeProperties;
class BaseRenderComponent;

class SceneNode : public ISceneNode {
	friend class Scene;

protected:
	std::vector<std::shared_ptr<ISceneNode>>	m_Children;
	SceneNode*									m_pParent;
	std::shared_ptr<SceneNodeProperties>		m_Props;
	BaseRenderComponent*						m_RenderComponent;

public:
	SceneNode(unsigned int actorId, BaseRenderComponent* renderComponent, RenderPass renderPass, const DirectX::XMFLOAT4X4* to = nullptr, const DirectX::XMFLOAT4X4* from = nullptr);

	virtual const SceneNodeProperties* const VGet() const;

	DirectX::XMFLOAT3 GetPosition() const;
	void SetPosition(const DirectX::XMFLOAT3& pos);

	const DirectX::XMFLOAT3 GetWorldPosition() const; // respect ancestor's position
	DirectX::XMFLOAT3 GetDirection() const;

	void SetRadius(const float radius);


// ***** Implementation pure virtual functions *****
	virtual void VSetTransform(const DirectX::XMFLOAT4X4* toWorld, const DirectX::XMFLOAT4X4* fromWorld = NULL);

	virtual HRESULT VOnRestore(Scene* pScene);
	virtual HRESULT VOnUpdate(Scene*, DWORD const elapsedMs);

	virtual HRESULT VPreRender(Scene* pScene) override;
	virtual bool VIsVisible(Scene* pScene) const;
	virtual HRESULT VRender(Scene* pScene);
	virtual HRESULT VRenderChildren(Scene* pScene);
	virtual HRESULT VPostRender(Scene* pScene);

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual bool VRemoveChild(unsigned int id);
	virtual HRESULT VOnLostDevice(Scene* pScene);

	virtual ~SceneNode();
};