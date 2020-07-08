#pragma once

#include <map>
#include <string>

#include "TextureClass.h"

class TextureHolder {
private:
    std::map<std::string, TextureClass> m_Textures;
    static TextureHolder* m_s_Instance;

    bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);

public:
    TextureHolder();
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder& operator=(const TextureHolder&) = delete;

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, std::vector<std::string>&);

    static TextureClass& GetTexture(std::string const& filename);
};
