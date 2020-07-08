#include "CameraNode.h"
#include "Scene.h"
#include "SceneNodeProperties.h"
#include "SystemClass.h"

CameraNode::CameraNode(DirectX::XMFLOAT4X4 const* t) : SceneNode(0, nullptr, RenderPass::RenderPass_0, t) {

	m_bActive = true;
	m_DebugCamera = false;
	m_pTarget = std::shared_ptr<SceneNode>();
	m_CamOffsetVector = { 0.0f, 1.0f, -10.0f, 0.0f };

	std::shared_ptr<EngineOptions> eo = SystemClass::GetEngineOptions();
	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(eo->m_fov, eo->m_aspectRatio, eo->m_screenNear, eo->m_screenDepth);
	DirectX::XMStoreFloat4x4(&m_Projection, P);

	m_Frustum = DirectX::BoundingFrustum(P);
}

HRESULT CameraNode::VRender(Scene* pScene) {
	if (m_DebugCamera) {
		pScene->PopMatrix();
		pScene->PushAndSetMatrix(m_Props->ToWorld());
	}

	return S_OK;
}

HRESULT CameraNode::VOnRestore(Scene* pScene) {

	pScene->GetRenderer()->VSetProjectionTransform(&m_Projection);
	return S_OK;
}

HRESULT CameraNode::SetViewTransform(Scene* pScene) {
	//If there is a target, make sure the camera is
	//rigidly attached right behind the target
	if (m_pTarget) {
		DirectX::XMFLOAT4X4 mat = m_pTarget->VGet()->ToWorld();
		DirectX::XMFLOAT4 at = m_CamOffsetVector;

		DirectX::XMMATRIX matX = DirectX::XMLoadFloat4x4(&mat);
		DirectX::XMVECTOR atX = DirectX::XMLoadFloat4(&at);
		DirectX::XMVECTOR out = DirectX::XMVector4Transform(atX, matX);
		DirectX::XMFLOAT4 atWorld;
		DirectX::XMStoreFloat4(&atWorld, out);

		mat.m[3][0] += atWorld.x;
		mat.m[3][1] += atWorld.y;
		mat.m[3][2] += atWorld.z;

		VSetTransform(&mat);
	}

	m_View = VGet()->FromWorld();

	pScene->GetRenderer()->VSetViewTransform(&m_View);
	return S_OK;
}

// Returns the concatenation of the world and view projection, which is generally sent into vertex shaders
DirectX::XMFLOAT4X4 CameraNode::GetWorldViewProjection(Scene* pScene) {
	DirectX::XMFLOAT4X4 world = pScene->GetTopMatrix();
	DirectX::XMFLOAT4X4 view = VGet()->FromWorld();

	DirectX::XMMATRIX worldX = DirectX::XMLoadFloat4x4(&world);
	DirectX::XMMATRIX viewX = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX projX = DirectX::XMLoadFloat4x4(&m_Projection);
	DirectX::XMMATRIX out = DirectX::XMMatrixMultiply(worldX, viewX);
	out = DirectX::XMMatrixMultiply(out, projX);

	DirectX::XMFLOAT4X4 worldViewProj;
	DirectX::XMStoreFloat4x4(&worldViewProj, out);

	return worldViewProj;
}