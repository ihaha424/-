#pragma once
#include "IInputDevice.h"

class KeyBoard : public IInputDevice
{
public:
	KeyBoard() {};
	virtual ~KeyBoard();

	HRESULT	Initialize(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8& LPDInput);

	// IInputDevice��(��) ���� ��ӵ�
	void				Update() override;
	virtual const BYTE* GetPressData() override;

private:
	static constexpr unsigned char	keyBoardSize = 0xFF;
	BYTE							curKeyState[keyBoardSize];
	LPDIRECTINPUTDEVICE8			keyboard = nullptr;
};

