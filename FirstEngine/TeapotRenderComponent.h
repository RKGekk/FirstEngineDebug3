#pragma once

#include <memory>

#include "BaseRenderComponent.h"

class TeapotRenderComponent : public BaseRenderComponent {
public:
    static const char* g_Name;
    virtual const char* VGetName() const;

protected:
    virtual std::shared_ptr<SceneNode> VCreateSceneNode() override;  // factory method to create the appropriate scene node
};