#include "ActorFactory.h"
#include "TransformComponent.h"
#include "TeapotRenderComponent.h"

unsigned int ActorFactory::GetNextActorId() {
    return ++m_lastActorId;
}

ActorFactory::ActorFactory() {
    m_lastActorId = 0;

    m_componentFactory.Register<TransformComponent>(ActorComponent::GetIdFromName(TransformComponent::g_Name));
    m_componentFactory.Register<TeapotRenderComponent>(ActorComponent::GetIdFromName(TeapotRenderComponent::g_Name));
}

std::shared_ptr<Actor> ActorFactory::CreateActor(const char* actorResource, TiXmlElement* overrides, const DirectX::XMMATRIX* initialTransform, const unsigned int serversActorId) {

    // TODO: preload resources
    const char* demoStart =
        R"(
			<Actor type="Teapot" resource="actors\player_teapot.xml">
				<TransformComponent>
					<Position x="0" y="0" z="0"/>
					<YawPitchRoll x="0" y="0" z="0"/>
				</TransformComponent>
                <TeapotRenderComponent>
                    <Color r="0" g="0" b="1.0" a="1.0"/>
                </TeapotRenderComponent>
			</Actor>
		)";

    TiXmlDocument xml;
    xml.Parse(demoStart);

    // Grab the root XML node
    TiXmlElement* pRoot = xml.RootElement();
    if (!pRoot) {
        return std::shared_ptr<Actor>();
    }

    // create the actor instance
    unsigned int nextActorId = serversActorId;
    if (nextActorId == 0) {
        nextActorId = GetNextActorId();
    }
    std::shared_ptr<Actor> pActor(new Actor(nextActorId));
    if (!pActor->Init(pRoot)) {
        return std::shared_ptr<Actor>();
    }

    bool initialTransformSet = false;

    // Loop through each child element and load the component
    for (TiXmlElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement()) {
        std::shared_ptr<ActorComponent> pComponent(VCreateComponent(pNode));
        if (pComponent) {
            pActor->AddComponent(pComponent);
            pComponent->SetOwner(pActor);
        }
        else {
            // If an error occurs, we kill the actor and bail.  We could keep going, but the actor is will only be 
            // partially complete so it's not worth it.  Note that the pActor instance will be destroyed because it
            // will fall out of scope with nothing else pointing to it.
            return std::shared_ptr<Actor>();
        }
    }

    if (overrides) {
        ModifyActor(pActor, overrides);
    }

    // This is a bit of a hack to get the initial transform of the transform component set before the 
    // other components (like PhysicsComponent) read it.
    //shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::g_Name));
    //if (pInitialTransform && pTransformComponent) {
    //    pTransformComponent->SetPosition(pInitialTransform->GetPosition());
    //}

    // Now that the actor has been fully created, run the post init phase
    pActor->PostInit();

    return pActor;
}

std::shared_ptr<ActorComponent> ActorFactory::VCreateComponent(TiXmlElement* pData) {
    const char* name = pData->Value();
    std::shared_ptr<ActorComponent> pComponent(m_componentFactory.Create(ActorComponent::GetIdFromName(name)));

    // initialize the component if we found one
    if (pComponent) {
        if (!pComponent->VInit(pData)) {
            return std::shared_ptr<ActorComponent>();
        }
    }
    else {
        return std::shared_ptr<ActorComponent>();  // fail
    }

    // pComponent will be NULL if the component wasn't found. This isn't necessarily an error since you might have a
    // custom CreateComponent() function in a sub class.
    return pComponent;
}


void ActorFactory::ModifyActor(std::shared_ptr<Actor> pActor, TiXmlElement* overrides) {
    // Loop through each child element and load the component
    for (TiXmlElement* pNode = overrides->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement()) {
        unsigned int componentId = ActorComponent::GetIdFromName(pNode->Value());
        std::shared_ptr<ActorComponent> pComponent = MakeStrongPtr(pActor->GetComponent<ActorComponent>(componentId));
        if (pComponent) {
            pComponent->VInit(pNode);

            // added post press to ensure that components that need it have
            // Events generated that can notify subsystems when changes happen.
            // This was done to have SceneNode derived classes respond to RenderComponent
            // changes.
            pComponent->VOnChanged();
        }
        else {
            pComponent = VCreateComponent(pNode);
            if (pComponent) {
                pActor->AddComponent(pComponent);
                pComponent->SetOwner(pActor);
            }
        }
    }
}