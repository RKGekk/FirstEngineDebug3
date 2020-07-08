#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <memory>

class Scene;
class SceneNodeProperties;

class ISceneNode {
public:
	virtual const SceneNodeProperties* const VGet() const = 0;

	virtual void VSetTransform(const DirectX::XMFLOAT4X4* toWorld, const DirectX::XMFLOAT4X4* fromWorld = NULL) = 0;

	virtual HRESULT VOnUpdate(Scene* pScene, DWORD const elapsedMs) = 0;
	virtual HRESULT VOnRestore(Scene* pScene) = 0;

	virtual HRESULT VPreRender(Scene* pScene) = 0;
	virtual bool VIsVisible(Scene* pScene) const = 0;
	virtual HRESULT VRender(Scene* pScene) = 0;
	virtual HRESULT VRenderChildren(Scene* pScene) = 0;
	virtual HRESULT VPostRender(Scene* pScene) = 0;

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid) = 0;
	virtual bool VRemoveChild(unsigned int id) = 0;
	virtual HRESULT VOnLostDevice(Scene* pScene) = 0;

	virtual ~ISceneNode() {};
};