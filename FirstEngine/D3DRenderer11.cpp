#include "D3DRenderer11.h"

HRESULT D3DRenderer11::VOnRestore() {
	HRESULT hr;
	hr = D3DRenderer::VOnRestore();
	if (FAILED(hr)) { return hr; }

	return S_OK;
}

bool D3DRenderer11::VPreRender() {

	std::shared_ptr<GraphicsClass> graphics = SystemClass::GetGraphics();
	graphics->GetD3D()->BeginScene(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);

	return true;
}

bool D3DRenderer11::VPostRender(void) {
	return true;
}