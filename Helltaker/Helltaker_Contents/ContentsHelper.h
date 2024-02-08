#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>

// ���� :
class ContentsHelper
{
public:

	static FVector GetWindowScale();
	static FVector GetTileScale();
	static void LoadImg(std::string_view _Path, std::string_view _Name);
	static void LoadFolder(std::string_view _Path, std::string_view _Name);

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
	SelectChapter,
	EnterChapter,
	Exit
};

enum class EHeroState
{
	None,
	LIdle,
	LMove,
	LKick,
	LVictory,
	RIdle,
	RMove,
	RKick,
	RVictory,
	Death
};
