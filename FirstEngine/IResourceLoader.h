#pragma once

#include <string>
#include <memory>

class ResHandle;

class IResourceLoader {
public:
	virtual std::string VGetPattern() = 0;
	virtual bool VUseRawFile() = 0;
	virtual bool VDiscardRawBufferAfterLoad() = 0;
	virtual bool VAddNullZero() { return false; }
	virtual unsigned int VGetLoadedResourceSize(char* rawBuffer, unsigned int rawSize) = 0;
	virtual bool VLoadResource(char* rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle) = 0;
};