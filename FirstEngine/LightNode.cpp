#include "LightNode.h"
#include "RenderPass.h"

LightNode::LightNode(const unsigned int actorId, BaseRenderComponent* renderComponent, const LightProperties& props, const DirectX::XMFLOAT4X4* t)
	: SceneNode(actorId, renderComponent, RenderPass::RenderPass_NotRendered, t) {
	m_LightProps = props;
}