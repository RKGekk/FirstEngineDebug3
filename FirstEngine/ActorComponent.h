#pragma once

#include <memory>

#include "tinyxml.h"
class Actor;

class ActorComponent {
	friend class ActorFactory;

protected:
	std::shared_ptr<Actor> m_pOwner;

public:
	virtual ~ActorComponent();

	virtual bool VInit(TiXmlElement* pData) = 0;
	virtual const char* VGetName() const = 0;

	virtual void VPostInit(void) {}
	virtual void VUpdate(int deltaMs) {}
	virtual void VOnChanged(void) {}
	virtual unsigned int VGetId(void) const;

	static unsigned int GetIdFromName(const char* componentStr);

	void SetOwner(std::shared_ptr<Actor> pOwner);
};