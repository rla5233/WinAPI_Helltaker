#pragma once
#include <Windows.h>
#include <assert.h>

namespace EngineDebug
{
#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#define MsgBoxAssert(TEXT) MessageBoxA(nullptr, TEXT, "치명적 에러", MB_OK); assert(false);
}

