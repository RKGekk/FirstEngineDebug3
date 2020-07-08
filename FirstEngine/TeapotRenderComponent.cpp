#include "TeapotRenderComponent.h"
#include "TransformComponent.h"
#include "memoryUtility.h"
#include "Actor.h"
#include "SystemClass.h"
#include "RenderPass.h"

const char* TeapotRenderComponent::g_Name = "TeapotRenderComponent";

const char* TeapotRenderComponent::VGetName() const {
	return g_Name;
}

std::shared_ptr<SceneNode> TeapotRenderComponent::VCreateSceneNode() {
	// get the transform component
	std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::g_Name));
	if (pTransformComponent) {
		BaseRenderComponent* weakThis(this);

		switch (SystemClass::GetRendererType()) {
			case Renderer::Renderer_D3D11: {
				DirectX::XMFLOAT4X4 rot;
				DirectX::XMStoreFloat4x4(&rot, DirectX::XMMatrixIdentity());
				std::shared_ptr<SceneNode> parent(new SceneNode(m_pOwner->GetId(), weakThis, RenderPass::RenderPass_Actor, &pTransformComponent->GetTransform4x4f()));
				return parent;
			}

			default: {}
			break;
		}
	}

	return std::shared_ptr<SceneNode>();
}