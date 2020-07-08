#pragma once

#include <DirectXMath.h>
#include <list>
#include <memory>

#include "D3DRenderer.h"
#include "LightNode.h"
#include "SystemClass.h"

class D3DRenderer11 : public D3DRenderer {
public:
	D3DRenderer11() {
		m_backgroundColor[0] = 0.5f;
		m_backgroundColor[1] = 0.5f;
		m_backgroundColor[2] = 0.5f;
		m_backgroundColor[3] = 1.0f;
	}

	virtual void VShutdown() { D3DRenderer::VShutdown(); }

	virtual void VSetBackgroundColor(BYTE bgA, BYTE bgR, BYTE bgG, BYTE bgB) {
		m_backgroundColor[0] = float(bgA) / 255.0f;
		m_backgroundColor[1] = float(bgR) / 255.0f;
		m_backgroundColor[2] = float(bgG) / 255.0f;
		m_backgroundColor[3] = float(bgB) / 255.0f;
	}

	virtual bool VPreRender();
	virtual bool VPostRender();
	virtual HRESULT VOnRestore();
	virtual void VCalcLighting(std::list<std::shared_ptr<LightNode>>* lights, int maximumLights) {}

	// These three functions are done for each shader, not as a part of beginning the render - so they do nothing in D3D11.
	virtual void VSetWorldTransform(const DirectX::XMFLOAT4X4* m) {}
	virtual void VSetViewTransform(const DirectX::XMFLOAT4X4* m) {}
	virtual void VSetProjectionTransform(const DirectX::XMFLOAT4X4* m) {}

protected:
	float								m_backgroundColor[4];
};