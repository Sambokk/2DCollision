#include "pch.h"
#include "KeyManager.h"

int keyCode[(int)KEY::LAST] =
{
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	'1','2','3','4','5','6','7','8','9','0',
	'Q','W','E','R','T','Y','U','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',

	VK_MENU,    // ALT,
	VK_CONTROL, // CTRL,
	VK_LSHIFT,  // LSHIFT,
	VK_SPACE,   // SPACE,
	VK_RETURN,  // ENTER,
	VK_ESCAPE,  // ESC,
	VK_TAB,     //TAB

	VK_LBUTTON, // LBTN
	VK_RBUTTON, // RBTN
};

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::initialize()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		keyInfos.push_back(KeyInfo{ KEY_STATE::NONE, false });
	}
}

void KeyManager::update()
{
	//윈도우 포커싱 알아내기
	HWND hWnd = GetFocus();

	//윈도우가 포커싱 중일 때
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			//키가 눌려있다.
			if (GetAsyncKeyState(keyCode[i]) & 0x8000)
			{
				if (keyInfos[i].isPrevPush)
				{
					// 이전에도 눌러 있었다.
					keyInfos[i].state = KEY_STATE::HOLD;
				}
				else
				{
					keyInfos[i].state = KEY_STATE::DOWN;
				}
				keyInfos[i].isPrevPush = true;
			}
			//키가 눌려있지 않다.
			else
			{
				if (keyInfos[i].isPrevPush)
				{
					keyInfos[i].state = KEY_STATE::UP;
				}
				else
				{
					keyInfos[i].state = KEY_STATE::NONE;
				}

				keyInfos[i].isPrevPush = false;
			}
		}
	}

	//윈도우가 포커싱 중이 아닐 때,
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			keyInfos[i].isPrevPush = false;

			if (keyInfos[i].state == KEY_STATE::DOWN || keyInfos[i].state == KEY_STATE::HOLD)
			{
				keyInfos[i].state = KEY_STATE::UP;
				keyInfos[i].isPrevPush = true;
			}
			else if (keyInfos[i].state == KEY_STATE::UP)
			{
				keyInfos[i].state = KEY_STATE::NONE;
				keyInfos[i].isPrevPush = false;
			}
		}
	}
}
