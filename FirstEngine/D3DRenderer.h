#pragma once

#include "IRenderer.h"

// The D3DRenderer class is designed to implement the IRenderer interface, which abstracts
// the implentation of the renderer technology, which for this engine can be either D3D9 or D3D11.
// It also encapsulates the usefulness of CDXUTDialogResourceManager 
// and CDXUTTextHelper for user interface tasks whether D3D9 or D3D11 is being used.
class D3DRenderer : public IRenderer {
public:

	virtual HRESULT VOnRestore() { return S_OK; }
	virtual void VShutdown() { }
};