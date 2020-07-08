#pragma once

#include <Windows.h>

class IScreenElement {
public:
	virtual HRESULT VOnRestore() = 0;
	virtual HRESULT VOnLostDevice() = 0;
	virtual HRESULT VOnRender(double fTime, float fElapsedTime) = 0;
	virtual void VOnUpdate(int deltaMilliseconds) = 0;

	virtual int VGetZOrder() const = 0;
	virtual void VSetZOrder(int const zOrder) = 0;
	virtual bool VIsVisible() const = 0;
	virtual void VSetVisible(bool visible) = 0;

	virtual ~IScreenElement() {};
	virtual bool const operator <(IScreenElement const& other) { return VGetZOrder() < other.VGetZOrder(); }
};