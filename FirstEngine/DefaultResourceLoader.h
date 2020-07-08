#pragma once

#include <memory>
#include <string>

#include "IResourceLoader.h"
#include "ResHandle.h"

class DefaultResourceLoader : public IResourceLoader {
public:
	virtual bool VUseRawFile();
	virtual bool VDiscardRawBufferAfterLoad();
	virtual unsigned int VGetLoadedResourceSize(char* rawBuffer, unsigned int rawSize);
	virtual bool VLoadResource(char* rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle);
	virtual std::string VGetPattern();
};