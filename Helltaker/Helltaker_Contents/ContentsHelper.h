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
	Skeleton,
	Stone,
	Devil,
	Hero,
	Effect,
	UI
};

enum class RenderOrder
{
	None,
	BackGround,
	Dialogue,
	Character,
	Skeleton,
	Stone,
	Devil,
	Hero,
	Effect,
	UI
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

enum class EChapterState
{
	None,
	Idle,
	Secene,
	Reset,
	End
};

enum class EHeroState
{
	None,
	Idle,
	Move,
	Kick,
	Victory,
	Death
};

enum class EDevilState
{
	None,
	Idle,
	Victory
};

enum class EHitActorState
{
	None,
	Idle,
	Hit,
	HitMoveEnd,
	Death
};

enum class EActorSeeDir
{
	None,
	Left,
	Right
};

enum class EMoveActorDir
{
	None,
	Left,
	Right,
	Up,
	Down
};