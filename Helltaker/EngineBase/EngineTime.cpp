#include "EngineTime.h"
#include <Windows.h>

EngineTime::EngineTime()
{
	TimeCheckStart();
}

EngineTime::~EngineTime()
{
}

//typedef union _LARGE_INTEGER {
//    struct {
//        DWORD LowPart;
//        LONG HighPart;
//    } DUMMYSTRUCTNAME;
//    struct {
//        DWORD LowPart;
//        LONG HighPart;
//    } u;
//    LONGLONG QuadPart;
//} LARGE_INTEGER;


void EngineTime::TimeCheckStart()
{
	// 초당 샐수 있는 양인데.
	QueryPerformanceFrequency(&Count);

	QueryPerformanceCounter(&PrevTime);

	dCount = static_cast<double>(Count.QuadPart);
}

float EngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);

	// 정밀도를 높이기 위해서 double로 계산한다.
	double dTick = static_cast<double>(Tick);
	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	return static_cast<float>(DeltaTime);
}