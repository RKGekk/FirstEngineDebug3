#include "HumanView.h"
#include "SystemClass.h"

#include <DirectXCollision.h>
#include "FastDelegate.h"
#include "FastDelegateBind.h"

HumanView::HumanView(std::shared_ptr<IRenderer> renderer) {
	m_pProcessManager = new ProcessManager;

	m_ViewId = 0;

	// move, new, and destroy actor events and others
	RegisterAllDelegates();

	SystemClass::GetEngineLogic()->SetEngineState(BaseEngineState::BGS_Initializing); // what is the current game state

	if (renderer) {

		// Moved to the HumanView class post press
		m_pScene.reset(new ScreenElementScene(renderer));

		DirectX::XMFLOAT4X4 identity;
		DirectX::XMStoreFloat4x4(&identity, DirectX::XMMatrixIdentity());

		m_pCamera.reset(new CameraNode(&identity));

		m_pScene->VAddChild(0, m_pCamera);
		m_pScene->SetCamera(m_pCamera);
	}
}


HumanView::~HumanView() {
	// RemoveAllDelegates handle move, new, and destroy actor events.
	RemoveAllDelegates();

	while (!m_ScreenElements.empty()) {
		m_ScreenElements.pop_front();
	}

	SAFE_DELETE(m_pProcessManager);
}

bool HumanView::LoadGame(TiXmlElement* pLevelData) {
	// call the delegate method
	return VLoadGameDelegate(pLevelData);
}

void HumanView::VOnRender(double fTime, float fElapsedTime) {
	// Is it time to draw?
	if (fTime == m_lastDraw) {
		return;
	}

	if (SystemClass::GetRenderer()->VPreRender()) {

		for (auto i = m_ScreenElements.begin(); i != m_ScreenElements.end(); ++i) {
			if ((*i)->VIsVisible()) {
				(*i)->VOnRender(fTime, fElapsedTime);
			}
		}

		VRenderText();

		// record the last successful paint
		m_lastDraw = fTime;
	}

	SystemClass::GetRenderer()->VPostRender();
}

HRESULT HumanView::VOnRestore() {
	HRESULT hr = S_OK;
	for (auto i = m_ScreenElements.begin(); i != m_ScreenElements.end(); ++i) {
		hr = (*i)->VOnRestore();
		if (FAILED(hr)) { return hr; }
	}

	return hr;
}

// Recursively calls VOnLostDevice for everything attached to the HumanView. 
HRESULT HumanView::VOnLostDevice() {
	HRESULT hr;

	for (auto i = m_ScreenElements.begin(); i != m_ScreenElements.end(); ++i) {
		hr = (*i)->VOnLostDevice();
		if (FAILED(hr)) { return hr; }
	}

	return S_OK;
}

void HumanView::TogglePause(bool active) {
	// Pause or resume audio	
	if (active) {
		
	}
	else {
		
	}
}

void HumanView::VOnUpdate(const int deltaMilliseconds) {
	m_pProcessManager->UpdateProcesses(deltaMilliseconds);

	// This section of code was added post-press. It runs through the screenlist
	// and calls VOnUpdate. Some screen elements need to update every frame, one 
	// example of this is a 3D scene attached to the human view.
	for (auto i = m_ScreenElements.begin(); i != m_ScreenElements.end(); ++i) {
		(*i)->VOnUpdate(deltaMilliseconds);
	}
}

void HumanView::VPushElement(shared_ptr<IScreenElement> pElement) {
	m_ScreenElements.push_front(pElement);
}

void HumanView::VRemoveElement(shared_ptr<IScreenElement> pElement) {
	m_ScreenElements.remove(pElement);
}

// Sets a camera offset, useful for making a 1st person or 3rd person game
void HumanView::VSetCameraOffset(const DirectX::XMFLOAT4 & camOffset) {
	if (m_pCamera) {
		m_pCamera->SetCameraOffset(camOffset);
	}
}

// Aggregates calls to manage event listeners for the HumanView class.
void HumanView::RegisterAllDelegates() {
	IEventManager* pGlobalEventManager = IEventManager::Get();
	
}

void HumanView::RemoveAllDelegates(void) {
	IEventManager* pGlobalEventManager = IEventManager::Get();
}

void HumanView::GameStateDelegate(std::shared_ptr<IEventData> pEventData) {
	
}