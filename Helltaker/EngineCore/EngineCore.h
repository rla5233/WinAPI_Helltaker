#pragma once
#include <EngineBase\EngineDebug.h>
#include <EnginePlatform\EngineWindow.h>
#include <map>

class ULevel;
// 설명 :
class EngineCore
{
public:
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// 하나는 무조건 만들어지고 사라질일이 없을것이므ㅗ.
	// 코어가 윈도우를 가지고
	EngineWindow MainWindow;

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);

	void CoreInit(HINSTANCE _Init);

	virtual void Start();
	virtual void Update();
	virtual void End();

	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		if (true == AllLevel.contains(_Name.data()))
		{
			MsgBoxAssert(std::string(_Name) + "이라는 이름의 Level을 또 만들려고 했습니다");
		}

		LevelType* NewLevel = new LevelType();
		AllLevel.insert(std::pair<std::string, ULevel*>(_Name, NewLevel));
	}

protected:
	EngineCore();

private:
	bool EngineInit = false;
	std::map<std::string, ULevel*> AllLevel;

	static void EngineUpdate();
	static void EngineEnd();
};

extern EngineCore* GEngine;


#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
    LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	EngineCore::EngineStart(hInstance, &NewUserCore); \
}