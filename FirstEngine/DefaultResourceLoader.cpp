#include "DefaultResourceLoader.h"

bool DefaultResourceLoader::VUseRawFile() {
	return true;
}

bool DefaultResourceLoader::VDiscardRawBufferAfterLoad() {
	return true;
}

unsigned int DefaultResourceLoader::VGetLoadedResourceSize(char* rawBuffer, unsigned int rawSize) {
	return rawSize;
}

bool DefaultResourceLoader::VLoadResource(char* rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle) {
	return true;
}

std::string DefaultResourceLoader::VGetPattern() {
	return "*";
}