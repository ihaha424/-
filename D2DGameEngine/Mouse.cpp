#include "framework.h"
#include "Mouse.h"
#include "InputAction.h"

Math::Vector3 Mouse::curMousePosition = {};
bool	Mouse::isMouseInClient = false;

HRESULT Mouse::Initialize(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8& LPDInput)
{
	HRESULT hr = S_OK;

	hr = LPDInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	if (SUCCEEDED(hr))
		hr = mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (SUCCEEDED(hr))
		hr = mouse->SetDataFormat(&c_dfDIMouse);

	if (SUCCEEDED(hr))
		hr = mouse->Acquire();

	if (SUCCEEDED(hr))
		mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);

	GetCursorPos(&mousePos);
	ScreenToClient(GetActiveWindow(), &mousePos);

	return hr;
}
void Mouse::Update()
{
	HRESULT hr;
	hr = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(hr)) {
		// ����̽��� ��Ŀ���� �Ҿ����� �ٽ� ��� �õ�
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
			mouse->Acquire();
		}
		return;
	}
	for (unsigned char key = 0; key < mouseSize; key++)
	{
		if (mouseState.rgbButtons[key] & 0x80)
			InputAction::GetInstance()->AddInputKey(key, MouseInput);
	}
	curMousePosition += Math::Vector3(mouseState.lX, mouseState.lY, mouseState.lZ);
	
}

const BYTE* Mouse::GetPressData()
{
	return mouseState.rgbButtons;
}