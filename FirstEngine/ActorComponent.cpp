#include "ActorComponent.h"
#include "HashedString.h"

ActorComponent::~ActorComponent(void) {
	m_pOwner.reset();
}

unsigned int ActorComponent::GetIdFromName(const char* componentStr) {
	void* rawId = HashedString::hash_name(componentStr);
	return reinterpret_cast<unsigned int>(rawId);
}

unsigned int ActorComponent::VGetId(void) const {
	return GetIdFromName(VGetName());
}

void ActorComponent::SetOwner(std::shared_ptr<Actor> pOwner) {
	m_pOwner = pOwner;
}