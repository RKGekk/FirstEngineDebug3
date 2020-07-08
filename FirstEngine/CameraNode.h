#pragma once

#include <DirectXCollision.h>
#include <memory>

#include "SceneNode.h"
#include "BaseRenderComponent.h"

// A camera node controls the D3D view transform and holds the view
// frustum definition
class CameraNode : public SceneNode {
public:

	CameraNode(DirectX::XMFLOAT4X4 const* t);

	virtual HRESULT VRender(Scene* pScene);
	virtual HRESULT VOnRestore(Scene* pScene);
	virtual bool VIsVisible(Scene* pScene) const { return m_bActive; }

	const DirectX::BoundingFrustum& GetFrustum() { return m_Frustum; }
	void SetTarget(std::shared_ptr<SceneNode> pTarget) {
		m_pTarget = pTarget;
	}
	void ClearTarget() { m_pTarget = std::shared_ptr<SceneNode>(); }
	std::shared_ptr<SceneNode> GetTarget() { return m_pTarget; }

	DirectX::XMFLOAT4X4 GetWorldViewProjection(Scene* pScene);
	HRESULT SetViewTransform(Scene* pScene);

	DirectX::XMFLOAT4X4 GetProjection() { return m_Projection; }
	DirectX::XMFLOAT4X4 GetView() { return m_View; }

	void SetCameraOffset(const DirectX::XMFLOAT4& cameraOffset) {
		m_CamOffsetVector = cameraOffset;
	}

protected:

	DirectX::BoundingFrustum	m_Frustum;
	DirectX::XMFLOAT4X4			m_Projection;
	DirectX::XMFLOAT4X4			m_View;
	bool						m_bActive;
	bool						m_DebugCamera;
	std::shared_ptr<SceneNode>	m_pTarget;
	DirectX::XMFLOAT4			m_CamOffsetVector;	//Direction of camera relative to target.
};