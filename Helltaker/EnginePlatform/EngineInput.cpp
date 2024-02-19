#include "EngineInput.h"

std::map<int, UEngineInput::EngineKey> UEngineInput::AllKeys;

bool UEngineInput::AnykeyDown = false;
bool UEngineInput::AnykeyPress = false;
bool UEngineInput::AnykeyUp = false;
bool UEngineInput::AnykeyFree = true;

void UEngineInput::EngineKey::KeyCheck(float _DeltaTime)
{

	// 이 키가 눌렸다는 거죠?
	// if (0 != GetAsyncKeyState('A'))
	// A키가 눌렸다면
	if (0 != GetAsyncKeyState(Key))
	{
		if (true == Free)
		{
			UpTime;
			PressTime = 0.0f;
			// 이전까지 이 키는 눌리고 있지 않았다
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else if (true == Down)
		{
			UpTime = 0.0f;
			PressTime += _DeltaTime;
			// 이전까지 이 키는 눌리고 있었다.
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		UpTime += _DeltaTime;
		if (true == Press)
		{
			PressTime = 0.0f;
			// 이전까지 이 키는 눌리고 있었다.
			Down = false;
			Press = false;
			Up = true;
			Free = false;
		}
		else if (true == Up)
		{
			PressTime = 0.0f;
			// 이전까지 이 키는 안눌리고 있었고 앞으로도 안눌릴거다.
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}

	}
}

UEngineInput::UEngineInput()
{
}

UEngineInput::~UEngineInput()
{
}

void UEngineInput::InputInit()
{
	AllKeys[VK_LBUTTON] = EngineKey(VK_LBUTTON);
	AllKeys[VK_RBUTTON] = EngineKey(VK_RBUTTON);
	AllKeys[VK_CANCEL] = EngineKey(VK_CANCEL);
	AllKeys[VK_MBUTTON] = EngineKey(VK_MBUTTON);
	AllKeys[VK_BACK] = EngineKey(VK_BACK);
	AllKeys[VK_TAB] = EngineKey(VK_TAB);
	AllKeys[VK_CLEAR] = EngineKey(VK_CLEAR);
	AllKeys[VK_RETURN] = EngineKey(VK_RETURN);
	AllKeys[VK_SHIFT] = EngineKey(VK_SHIFT);
	AllKeys[VK_LSHIFT] = EngineKey(VK_LSHIFT);
	AllKeys[VK_CONTROL] = EngineKey(VK_CONTROL);
	AllKeys[VK_MENU] = EngineKey(VK_MENU);
	AllKeys[VK_PAUSE] = EngineKey(VK_PAUSE);
	AllKeys[VK_CAPITAL] = EngineKey(VK_CAPITAL);
	// AllKeys[VK_KANA] = EngineKey(VK_KANA);
	//AllKeys[VK_HANGEUL] = EngineKey(VK_HANGEUL);
	//AllKeys[VK_HANGUL] = EngineKey(VK_HANGUL);
	AllKeys[VK_IME_ON] = EngineKey(VK_IME_ON);
	AllKeys[VK_JUNJA] = EngineKey(VK_JUNJA);
	AllKeys[VK_FINAL] = EngineKey(VK_FINAL);
	AllKeys[VK_HANJA] = EngineKey(VK_HANJA);
	AllKeys[VK_KANJI] = EngineKey(VK_KANJI);
	AllKeys[VK_IME_OFF] = EngineKey(VK_IME_OFF);
	AllKeys[VK_ESCAPE] = EngineKey(VK_ESCAPE);
	AllKeys[VK_CONVERT] = EngineKey(VK_CONVERT);
	AllKeys[VK_NONCONVERT] = EngineKey(VK_NONCONVERT);
	AllKeys[VK_ACCEPT] = EngineKey(VK_ACCEPT);
	AllKeys[VK_MODECHANGE] = EngineKey(VK_MODECHANGE);
	AllKeys[VK_SPACE] = EngineKey(VK_SPACE);
	AllKeys[VK_PRIOR] = EngineKey(VK_PRIOR);
	AllKeys[VK_NEXT] = EngineKey(VK_NEXT);
	AllKeys[VK_END] = EngineKey(VK_END);
	AllKeys[VK_HOME] = EngineKey(VK_HOME);
	AllKeys[VK_LEFT] = EngineKey(VK_LEFT);
	AllKeys[VK_UP] = EngineKey(VK_UP);
	AllKeys[VK_RIGHT] = EngineKey(VK_RIGHT);
	AllKeys[VK_DOWN] = EngineKey(VK_DOWN);
	AllKeys[VK_SELECT] = EngineKey(VK_SELECT);
	AllKeys[VK_PRINT] = EngineKey(VK_PRINT);
	AllKeys[VK_EXECUTE] = EngineKey(VK_EXECUTE);
	AllKeys[VK_SNAPSHOT] = EngineKey(VK_SNAPSHOT);
	AllKeys[VK_INSERT] = EngineKey(VK_INSERT);
	AllKeys[VK_DELETE] = EngineKey(VK_DELETE);
	AllKeys[VK_HELP] = EngineKey(VK_HELP);
	AllKeys[VK_LWIN] = EngineKey(VK_LWIN);
	AllKeys[VK_RWIN] = EngineKey(VK_RWIN);
	AllKeys[VK_APPS] = EngineKey(VK_APPS);
	AllKeys[VK_SLEEP] = EngineKey(VK_SLEEP);
	AllKeys[VK_NUMPAD0] = EngineKey(VK_NUMPAD0);
	AllKeys[VK_NUMPAD1] = EngineKey(VK_NUMPAD1);
	AllKeys[VK_NUMPAD2] = EngineKey(VK_NUMPAD2);
	AllKeys[VK_NUMPAD3] = EngineKey(VK_NUMPAD3);
	AllKeys[VK_NUMPAD4] = EngineKey(VK_NUMPAD4);
	AllKeys[VK_NUMPAD5] = EngineKey(VK_NUMPAD5);
	AllKeys[VK_NUMPAD6] = EngineKey(VK_NUMPAD6);
	AllKeys[VK_NUMPAD7] = EngineKey(VK_NUMPAD7);
	AllKeys[VK_NUMPAD8] = EngineKey(VK_NUMPAD8);
	AllKeys[VK_NUMPAD9] = EngineKey(VK_NUMPAD9);
	AllKeys[VK_MULTIPLY] = EngineKey(VK_MULTIPLY);
	AllKeys[VK_ADD] = EngineKey(VK_ADD);
	AllKeys[VK_SEPARATOR] = EngineKey(VK_SEPARATOR);
	AllKeys[VK_SUBTRACT] = EngineKey(VK_SUBTRACT);
	AllKeys[VK_DECIMAL] = EngineKey(VK_DECIMAL);
	AllKeys[VK_DIVIDE] = EngineKey(VK_DIVIDE);
	AllKeys[VK_F1] = EngineKey(VK_F1);
	AllKeys[VK_F2] = EngineKey(VK_F2);
	AllKeys[VK_F3] = EngineKey(VK_F3);
	AllKeys[VK_F4] = EngineKey(VK_F4);
	AllKeys[VK_F5] = EngineKey(VK_F5);
	AllKeys[VK_F6] = EngineKey(VK_F6);
	AllKeys[VK_F7] = EngineKey(VK_F7);
	AllKeys[VK_F8] = EngineKey(VK_F8);
	AllKeys[VK_F9] = EngineKey(VK_F9);
	AllKeys[VK_F10] = EngineKey(VK_F10);
	AllKeys[VK_F11] = EngineKey(VK_F11);
	AllKeys[VK_F12] = EngineKey(VK_F12);
	AllKeys[VK_F13] = EngineKey(VK_F13);
	AllKeys[VK_F14] = EngineKey(VK_F14);
	AllKeys[VK_F15] = EngineKey(VK_F15);
	AllKeys[VK_F16] = EngineKey(VK_F16);
	AllKeys[VK_F17] = EngineKey(VK_F17);
	AllKeys[VK_F18] = EngineKey(VK_F18);
	AllKeys[VK_F19] = EngineKey(VK_F19);
	AllKeys[VK_F20] = EngineKey(VK_F20);
	AllKeys[VK_F21] = EngineKey(VK_F21);
	AllKeys[VK_F22] = EngineKey(VK_F22);
	AllKeys[VK_F23] = EngineKey(VK_F23);
	AllKeys[VK_F24] = EngineKey(VK_F24);
	AllKeys['-'] = EngineKey(VK_OEM_MINUS);
	AllKeys['+'] = EngineKey(VK_OEM_PLUS);
	AllKeys[VK_OEM_4] = EngineKey(VK_OEM_4);
	AllKeys[VK_OEM_6] = EngineKey(VK_OEM_6);

	for (int i = 'A'; i <= 'Z'; i++)
	{
		AllKeys[i] = EngineKey(i);
	}

	for (int i = '0'; i <= '9'; i++)
	{
		AllKeys[i] = EngineKey(i);
	}

}

void UEngineInput::KeyCheckTick(float _DeltaTime)
{
	bool KeyCheck = false;

	for (std::pair<const int, EngineKey>& Key : AllKeys)
	{
		EngineKey& CurKey = Key.second;
		CurKey.KeyCheck(_DeltaTime);

		if (true == CurKey.Press)
		{
			KeyCheck = true;
		}
	}

	// 어떤키든 눌렸다는 이야기
	if (true == KeyCheck)
	{
		if (true == AnykeyFree)
		{
			// 이전까지 이 키는 눌리고 있지 않았다
			AnykeyDown = true;
			AnykeyPress = true;
			AnykeyUp = false;
			AnykeyFree = false;
		}
		else if (true == AnykeyDown)
		{
			// 이전까지 이 키는 눌리고 있었다.
			AnykeyDown = false;
			AnykeyPress = true;
			AnykeyUp = false;
			AnykeyFree = false;
		}
	}
	else
	{
		if (true == AnykeyPress)
		{
			// 이전까지 이 키는 눌리고 있었다.
			AnykeyDown = false;
			AnykeyPress = false;
			AnykeyUp = true;
			AnykeyFree = false;
		}
		else if (true == AnykeyUp)
		{
			// 이전까지 이 키는 안눌리고 있었고 앞으로도 안눌릴거다.
			AnykeyDown = false;
			AnykeyPress = false;
			AnykeyUp = false;
			AnykeyFree = true;
		}

	}
}

class InputInitCreator
{
public:
	InputInitCreator()
	{
		UEngineInput::InputInit();
	}
};

InputInitCreator CreateValue = InputInitCreator();