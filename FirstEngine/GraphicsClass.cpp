#include "GraphicsClass.h"

GraphicsClass::GraphicsClass() {
	m_Direct3D = nullptr;
}

GraphicsClass::~GraphicsClass() {}

bool GraphicsClass::Initialize(std::shared_ptr<EngineOptions> options, HWND hwnd) {
	bool result;

	// Create the Direct3D object.
	m_Direct3D = std::shared_ptr<D3DClass>(new D3DClass);
	if (!m_Direct3D) {
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(options, hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = std::shared_ptr<CameraClass>(new CameraClass);
	if (!m_Camera) {
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -3.0f);

	m_TextureHolder = std::shared_ptr<TextureHolder>(new TextureHolder);
	if (!m_TextureHolder) {
		return false;
	}

	// Initialize the texture holder object.
	std::vector<std::string> textures{ "stone01.tga", "stone02.tga" };
	result = m_TextureHolder->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), textures);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the textures.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = std::shared_ptr<TextureShaderClass>(new TextureShaderClass);
	if (!m_TextureShader) {
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown() {

	// Release the Direct3D object.
	if (m_Direct3D) {
		m_Direct3D->Shutdown();
	}

	return;
}

std::shared_ptr<D3DClass> GraphicsClass::GetD3D() {
	return m_Direct3D;
}

std::shared_ptr<TextureHolder> GraphicsClass::GetTexture() {
	return m_TextureHolder;
}

std::shared_ptr<TextureShaderClass> GraphicsClass::GetShader() {
	return m_TextureShader;
}

std::shared_ptr<CameraClass> GraphicsClass::GetCamera() {
	return m_Camera;
}
