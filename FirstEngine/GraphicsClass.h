#pragma once

#include <Windows.h>
#include <memory>

#include "D3DClass.h"
#include "EngineOptions.h"
#include "TextureHolder.h"
#include "TextureShaderClass.h"
#include "CameraClass.h"

class GraphicsClass {
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&) = delete;
	GraphicsClass& operator=(const GraphicsClass&) = delete;
	~GraphicsClass();

	bool Initialize(std::shared_ptr<EngineOptions> options, HWND hwnd);
	void Shutdown();

	std::shared_ptr<D3DClass> GetD3D();
	std::shared_ptr<TextureHolder> GetTexture();
	std::shared_ptr<TextureShaderClass> GetShader();
	std::shared_ptr<CameraClass> GetCamera();

private:
	std::shared_ptr<D3DClass>			m_Direct3D;
	std::shared_ptr<TextureHolder>		m_TextureHolder;
	std::shared_ptr<TextureShaderClass> m_TextureShader;
	std::shared_ptr<CameraClass>		m_Camera;
};