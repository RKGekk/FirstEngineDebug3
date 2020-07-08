#pragma once

#include <memory>

#include "SceneNode.h"

class RootNode : public SceneNode {
public:
	RootNode();
	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual HRESULT VRenderChildren(Scene* pScene);
	virtual bool VRemoveChild(unsigned int id);
	virtual bool VIsVisible(Scene* pScene) const { return true; }
};