#pragma once

#include <memory>
#include <string>

#include "Resource.h"
#include "IResourceExtraData.h"

class ResCache;

class ResHandle {
	friend class ResCache;

protected:
	Resource m_resource;
	char* m_buffer;
	unsigned int m_size;
	std::shared_ptr<IResourceExtraData> m_extra;
	ResCache* m_pResCache;

public:
	ResHandle(Resource& resource, char* buffer, unsigned int size, ResCache* pResCache);

	virtual ~ResHandle();

	const std::string GetName();
	unsigned int Size() const;
	char* Buffer() const;
	char* WritableBuffer();

	std::shared_ptr<IResourceExtraData> GetExtra();
	void SetExtra(std::shared_ptr<IResourceExtraData> extra);
};