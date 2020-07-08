#include "TextureHolder.h"

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	m_s_Instance = this;
}

bool TextureHolder::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<std::string>& textureFilenames) {
	bool result;

	for (std::string& textureFilename : textureFilenames) {
		result = LoadTexture(device, deviceContext, textureFilename.c_str());
		if (!result) {
			return false;
		}
	}

	return true;
}

bool TextureHolder::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename) {
	bool result;

	// Create the texture object.
	auto& m = m_s_Instance->m_Textures;
	auto& texture = m[filename];

	// Initialize the texture object.
	result = texture.Initialize(device, deviceContext, filename);
	if (!result) {
		return false;
	}

	return true;
}

TextureClass& TextureHolder::GetTexture(std::string const& filename) {
	auto& m = m_s_Instance->m_Textures;
	auto keyValuePair = m.find(filename);
	// auto is equivalent of map<string, Texture>::iterator
	// Did we find a match?
	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		throw;
	}
}