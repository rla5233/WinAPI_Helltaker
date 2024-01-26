#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"


EngineCore* GEngine = nullptr;

EngineCore::EngineCore()
	: MainWindow()
{}

EngineCore::~EngineCore()
{}

void EngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck();
	double dDeltaTime = MainTimer.GetDeltaTime();


	// 100프레임으로 실행되는 컴퓨터가 있다면
	// 0.01이 나와야 한다.
	// float Time;
	// Time += 0.01f;
	// 
	// 우리는 50프레임으로 제한하고 싶다.
	// 0.02가 나와야 한다.
	// FrameTime = 1 / 50.0; =>
	// FrameTime = 0.02;
	// CurFrameTime += 0.01;
	// 0.01             0.02
	// CurFrameTime <= FrameTime
	// CurFrameTime += 0.01;
	// 0.0203000        0.02
	// CurFrameTime <= FrameTime
	// 돌아야한다.
	// 0.0003000
	// CurFrameTime -= FrameTime;

	if (1 <= Frame)
	{
		//               5.0f
		CurFrameTime += DeltaTime;

		//  0.00001        0.016666675
		if (CurFrameTime <= FrameTime)
		{
			return;
		}

		//  0.0167         0.016666675
		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	EngineInput::KeyCheckTick(DeltaTime);

	if (nullptr == CurLevel)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	// 레벨이 먼저 틱을 돌리고
	CurLevel->Tick(DeltaTime);
	// 액터와 부가적인 오브젝트들의 틱도 돌리고 => 행동하고
	CurLevel->LevelTick(DeltaTime);
	// 랜더러들의 랜더를 통해서 화면에 그림도 그린다 => 그리고
	CurLevel->LevelRender(DeltaTime);
	// 정리한다.(죽어야할 오브젝트들은 다 파괴한다)
	CurLevel->LevelRelease(DeltaTime);


	//HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	//Rectangle(WindowDC, -200, -200, 3000, 3000);
}

void EngineCore::EngineTick()
{

	// 렉이라는 현상은 프레임사이에 한번에 많은 시간을 소모하는 함수를 호출하면
	// 델타타임이 증가하는 현상을 말한다.
	// EX) for문 1000만번 돌리는데 5초가 걸렸다.
	//    5.0
	//    => 한번에 5.0초 동안 가야할 양을 한프레임만에 이동해버리니까 순간이동하듯이 보이게 된다.

	GEngine->CoreTick();

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
	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();
	EngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	EngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void EngineCore::BeginPlay()
{

}

void EngineCore::Tick(float _DeltaTime)
{

}

void EngineCore::End()
{

}

void EngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 체인지 하려고 했습니다");
	}

	// 눈에 보여야할 레벨이죠?
	CurLevel = AllLevel[UpperName];
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}