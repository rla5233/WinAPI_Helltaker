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
	None,
	BackGround,
	Dialogue,
	Character,
	UI,
	Hero,
	Skeleton
};

enum class RenderOrder
{
	None,
	BackGround,
	Dialogue,
	Character,
	UI,
	Hero,
	Skeleton
};

enum class EMainMenuState
{
	None,
	Begin,
	Enter,
	SelectMenu,
	Exit
};
