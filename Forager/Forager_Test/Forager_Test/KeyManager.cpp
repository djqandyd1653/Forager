	#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		keyDown.set(i, false);		// i��° ��Ʈ�� false�� �ʱ�ȭ
		keyUp.set(i, true);			// i��° ��Ʈ�� true�� �ʱ�ȭ
	}
	return S_OK;
}

void KeyManager::Release()
{
	ReleaseSingleton();
}


bool KeyManager::IsOnceKeyDown(int key)
{
	/*
		�Լ� ȣ�� ������ ����Ű(VK_...)�� � �������� Ȯ���� ����
		1. 0x0000 => ���� �����ӿ� �������� ���� ȣ��������� �������� ����
		2. 0x0001 => ���� �����ӿ� �������� �ְ� ȣ��������� �������� ����
		3. 0x8000 => ���� �����ӿ� �������� ���� ȣ��������� �����ִ� ����
		4. 0x8001 => ���� �����ӿ� �������� �ְ� ȣ��������� �����ִ� ����
	*/

	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!GetKeyDown()[key]) // !GetKeyDown()[key] == KeyDown[key] == false;
		{
			SetKeyDown(key, true);
			return true;
		}
	}
	else
	{
		SetKeyDown(key, false);
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) // return�� false�� ���
	{
		SetKeyUp(key, false);
	}
	else
	{
		if (!GetKeyUp()[key])
		{
			SetKeyUp(key, true);
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}
