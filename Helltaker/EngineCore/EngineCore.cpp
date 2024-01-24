#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"

EngineCore* GEngine = nullptr;

EngineCore::EngineCore()
{}

EngineCore::~EngineCore()
{}

void EngineCore::EngineUpdate()
{
	int a = 0;
}

void EngineCore::EngineEnd()
{
	// std::map<std::string, ULevel*>::iterator StartI

	for (std::pair<const std::string, ULevel*>& _Pair : GEngine->AllLevel)
	{
		if (nullptr == _Pair.second)
		{
			continue;
		}

		delete _Pair.second;
		_Pair.second = nullptr;
	}

	GEngine->AllLevel.clear();
}

void EngineCore::EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore)
{
	EngineCore* Ptr = _UserCore;
	GEngine = Ptr;
	Ptr->CoreInit(_hInstance);
	Ptr->Start();
	EngineWindow::WindowMessageLoop(EngineUpdate, EngineEnd);
}

void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	EngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	EngineInit = true;
}

void EngineCore::Start()
{

}

void EngineCore::Update()
{

}

void EngineCore::End()
{

}

