#pragma once

#include <memory>

#include "Scene.h"
#include "IScreenElement.h"
#include "IRenderer.h"

class ScreenElementScene : public IScreenElement, public Scene {
public:
	ScreenElementScene(std::shared_ptr<IRenderer> renderer) : Scene(renderer) {}
	virtual ~ScreenElementScene() {
	}

	// IScreenElement Implementation
	virtual void VOnUpdate(int deltaMS) { OnUpdate(deltaMS); };
	virtual HRESULT VOnRestore() {
		OnRestore(); return S_OK;
	}
	virtual HRESULT VOnRender(double fTime, float fElapsedTime) {
		OnRender(); return S_OK;
	}
	virtual HRESULT VOnLostDevice() {
		OnLostDevice(); return S_OK;
	}
	virtual int VGetZOrder() const { return 0; }
	virtual void VSetZOrder(int const zOrder) {}

	virtual bool VIsVisible() const { return true; }
	virtual void VSetVisible(bool visible) {}
	virtual bool VAddChild(unsigned int id, std::shared_ptr<ISceneNode> kid) { return Scene::AddChild(id, kid); }
};