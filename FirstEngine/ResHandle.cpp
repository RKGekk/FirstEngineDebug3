#include "ResHandle.h"
#include "memoryUtility.h"
#include "ResCache.h"

ResHandle::ResHandle(Resource& resource, char* buffer, unsigned int size, ResCache* pResCache)
	: m_resource(resource) {
	m_buffer = buffer;
	m_size = size;
	m_extra = NULL;
	m_pResCache = pResCache;
}

ResHandle::~ResHandle() {
	SAFE_DELETE_ARRAY(m_buffer);
	m_pResCache->MemoryHasBeenFreed(m_size);
}

const std::string ResHandle::GetName() {
	return m_resource.m_name;
}

unsigned int ResHandle::Size() const {
	return m_size;
}

char* ResHandle::Buffer() const {
	return m_buffer;
}

char* ResHandle::WritableBuffer() {
	return m_buffer;
}

std::shared_ptr<IResourceExtraData> ResHandle::GetExtra() {
	return m_extra;
}

void ResHandle::SetExtra(std::shared_ptr<IResourceExtraData> extra) {
	m_extra = extra;
}