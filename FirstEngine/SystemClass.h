#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <memory>

#include "inputclass.h"
#include "GameTimer.h"
#include "BaseEngineLogic.h"
#include "Renderer.h"
#include "EngineOptions.h"
#include "EventManager.h"
#include "GraphicsClass.h"
#include "TextureHolder.h"
#include "IRenderer.h"
#include "D3DRenderer.h"
#include "D3DRenderer11.h"

class SystemClass {
public:
	SystemClass();
	SystemClass(const SystemClass&) = delete;
	SystemClass& operator=(const SystemClass&) = delete;
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	static std::shared_ptr<BaseEngineLogic> GetEngineLogic();
	static Renderer GetRendererType();
	static std::shared_ptr<GraphicsClass> GetGraphics();
	static std::shared_ptr<EngineOptions> GetEngineOptions();
	static std::shared_ptr<IRenderer> GetRenderer();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void Update(const GameTimer&);
	bool InitializeWindows();
	void ShutdownWindows();

	LPCWSTR			m_applicationName;
	HINSTANCE		m_hinstance;
	HWND			m_hwnd;

	std::shared_ptr<EngineOptions>			m_engineOptions;

	GameTimer								m_Timer;
	std::shared_ptr<InputClass>				m_Input;
	std::shared_ptr<EventManager>			m_pEventManager;
	static std::shared_ptr<BaseEngineLogic>	m_EngineLogic;
	std::shared_ptr<GraphicsClass>			m_Graphics;
	std::shared_ptr<IRenderer>				m_Renderer;
};