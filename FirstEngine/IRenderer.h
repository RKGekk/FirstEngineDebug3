#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <memory>
#include <list>

#include "IRenderState.h"
#include "LightNode.h"

class IRenderer {
public:
	virtual void VSetBackgroundColor(BYTE bgA, BYTE bgR, BYTE bgG, BYTE bgB) = 0;
	virtual HRESULT VOnRestore() = 0;
	virtual void VShutdown() = 0;
	virtual bool VPreRender() = 0;
	virtual bool VPostRender() = 0;
	virtual void VCalcLighting(std::list<std::shared_ptr<LightNode>>* lights, int maximumLights) = 0;
	virtual void VSetWorldTransform(const DirectX::XMFLOAT4X4* m) = 0;
	virtual void VSetViewTransform(const DirectX::XMFLOAT4X4* m) = 0;
	virtual void VSetProjectionTransform(const DirectX::XMFLOAT4X4* m) = 0;
};