#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"

bool UEngineCore::IsDebugValue = false;
UEngineCore* GEngine = nullptr;

UEngineCore::UEngineCore()
	: MainWindow()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::CoreTick()
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

	// 이것도 옵션
	if (1.0f / 60.0f <= DeltaTime)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	UEngineInput::KeyCheckTick(DeltaTime);


	// 한프레임동안 레벨이 절대로 변하지 않고
	// 프레임이 시작할때 레벨이 변화한다.
	// 지키기 위해서 release 프레임이 실행되는 동안에는 절대로
	// 구조를 바꾸지 않는다.
	if (nullptr != NextLevel)
	{
		// 최초에는 현재 레벨이 존재하지 않을 것이다.
		// 바꿀 레벨이 있다는 이야기입니다.
		if (nullptr != CurLevel)
		{
			// 레베링 끝났음을 알립니다.
			CurLevel->LevelEnd(NextLevel);
		}

		NextLevel->LevelStart(CurLevel);
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}


	if (nullptr == CurLevel)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	GEngine->Tick(DeltaTime);
	// 레벨이 먼저 틱을 돌리고
	CurLevel->Tick(DeltaTime);
	// 액터와 부가적인 오브젝트들의 틱도 돌리고 => 행동하고
	CurLevel->LevelTick(DeltaTime);
	// 랜더러들의 랜더를 통해서 화면에 그림도 그린다 => 그리고
	MainWindow.ScreenClear();
	CurLevel->LevelRender(DeltaTime);
	MainWindow.ScreenUpdate();
	// 정리한다.(죽어야할 오브젝트들은 다 파괴한다)
	CurLevel->LevelRelease(DeltaTime);


	//HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	//Rectangle(WindowDC, -200, -200, 3000, 3000);
}

void UEngineCore::EngineTick()
{

	// 렉이라는 현상은 프레임사이에 한번에 많은 시간을 소모하는 함수를 호출하면
	// 델타타임이 증가하는 현상을 말한다.
	// EX) for문 1000만번 돌리는데 5초가 걸렸다.
	//    5.0
	//    => 한번에 5.0초 동안 가야할 양을 한프레임만에 이동해버리니까 순간이동하듯이 보이게 된다.

	GEngine->CoreTick();

}

void UEngineCore::EngineEnd()
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

void UEngineCore::EngineStart(HINSTANCE _hInstance)
{
	GEngine = this;
	MainTimer.TimeCheckStart();
	CoreInit(_hInstance);
	BeginPlay();
	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void Exit()
{

}

void UEngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	UEngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void UEngineCore::BeginPlay()
{

}

void UEngineCore::Tick(float _DeltaTime)
{

}

void UEngineCore::End()
{

}

void UEngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 체인지 하려고 했습니다");
	}

	// 눈에 보여야할 레벨이죠?
	NextLevel = AllLevel[UpperName];
}

void UEngineCore::LevelInit(ULevel* _Level, std::string_view _Name)
{
	_Level->SetName(_Name);
	_Level->BeginPlay();
}