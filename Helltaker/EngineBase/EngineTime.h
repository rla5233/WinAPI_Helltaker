#pragma once
// #include <chrono> 최신 시간 재는 헤더 std.
#include <Windows.h>

// 설명 :
class EngineTime
{
public:
	// constrcuter destructer
	EngineTime();
	~EngineTime();

	// delete Function
	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	// 시간측정을 시작하겠다.
	void TimeCheckStart();

	// 지금까지 얼마 지났어?
	float TimeCheck();

	double GetDeltaTime()
	{
		return DeltaTime;
	}

protected:

private:
	__int64 Count64;
	LARGE_INTEGER Count;
	LARGE_INTEGER PrevTime;
	LARGE_INTEGER CurTime;
	double dCount;
	double DeltaTime;

	// 기본적으로 CPU하드 웨어 적으로 내부에 Count를 하는 부분이 존재합니다.
	// 쉽게 설명하자면 컴퓨터는 켜는 순간 CPU가 동작하면서 0 1 2 3 4 5 6
	// 초가 아닙니다 그런데 이녀석이 정말 초당 오차가 거의 없을 정도로 일정하게 샙니다.
	// ex) 컴퓨터 켰다 0 
	// ex) 1초 10000000
	// ex) 2초 20000000
	// ex) 3초 29999990
	// ex) 4초 40000000
	// ex) 5초 50000001

	// 윈도우는 이런 함수를 제공합니다.
	// 지금까지 얼마나 샜어?
	// ex) 얼마나샜어 150

	// 넌 초당 얼마를 샐수 있어?
	// ex) 100

	// 시작
	// 넌 초당 얼마를 샐수 있어?
	// int Count = 100;
	// 
	// 얼마나 샜어?
	// int CurTime = 100;
	// int PrevTime = CurTime;
	// ~~~~~~~~~~~~~~~~~~~~ 한프레임이 지났다.
	// 얼마나 샜어?
	// CurTime = 120;
	//                    120         100     / 100
	// float DeltaTime = (CurTime - PrevTime) / Count;
	// PrevTime = CurTime;
	// ~~~~~~~~~~~~~~~~~~~~ 한프레임이 지났다.
	// 얼마나 샜어?
	// CurTime = 320;
	//                    320         120     / 100
	// float DeltaTime = (CurTime - PrevTime) / Count;
	// PrevTime = CurTime;
};

