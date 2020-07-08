#pragma once

#include <Windows.h>

#include "GameViewType.h"

class IGameView {
public:
	virtual HRESULT VOnRestore() = 0;
	virtual void VOnRender(double fTime, float fElapsedTime) = 0;
	virtual HRESULT VOnLostDevice() = 0;
	virtual GameViewType VGetType() = 0;
	virtual unsigned int VGetId() const = 0;
	virtual void VOnAttach(unsigned int vid, unsigned int aid) = 0;

	virtual void VOnUpdate(unsigned long deltaMs) = 0;

	virtual ~IGameView() {};
};