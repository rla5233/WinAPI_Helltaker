#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class ContentsHelper
{
public:

	static FVector GetWindowScale();
	static float GetOneTileWidth();

protected:

private:
	// constructor destructor
	ContentsHelper();
	~ContentsHelper();

};

enum class UpdateOrder
{
	BackGround,
	Dialogue,
	Character,
	Hero,
	Skeleton
};

enum class RenderOrder
{
	BackGround,
	Dialogue,
	Character,
	Hero,
	Skeleton
};

enum class EMainMenuState
{
	Begin,
	Enter,
	Exit
};
