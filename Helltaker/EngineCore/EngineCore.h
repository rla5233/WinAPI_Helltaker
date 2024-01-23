#pragma once
#include <EnginePlatform\EngineWindow.h>

// 설명 :
class EngineCore
{
public:
	// constrcuter destructer
	EngineCore();
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// 하나는 무조건 만들어지고 사라질일이 없을것이므ㅗ.
	EngineWindow MainWindow;

	void CoreInit(HINSTANCE _Init);

	virtual void EngineStart();
	virtual void EngineUpdate();
	virtual void EngineEnd();

protected:

private:
	bool EngineInit = false;

};


#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
	USERCORE NewUserCore; \
	EngineCore* Ptr = &NewUserCore; \
	Ptr->CoreInit(hInstance); \
	Ptr->EngineStart(); \
	EngineWindow::WindowMessageLoop(); \
}