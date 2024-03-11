#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>

#define DEBUG

const Color8Bit HELLTAKER_WHITE = Color8Bit(255, 255, 255, 0);
const Color8Bit HELLTAKER_GRAY = Color8Bit(125, 125, 125, 0);
const Color8Bit HELLTAKER_RED1 = Color8Bit(230, 77, 81, 255);
const Color8Bit HELLTAKER_RED2 = Color8Bit(205, 20, 16, 255);

class Point
{
public:
	int X = -1;
	int Y = -1;

public:
	void operator=(Point _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
	}

	Point operator+(Point _Other)
	{
		Point Result = *this;
		Result.X += _Other.X;
		Result.Y += _Other.Y;
		return Result;
	}

	Point& operator+=(Point _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	bool operator==(Point _Other)
	{
		return X == _Other.X && Y == _Other.Y;
	}

public:
	static const Point Zero;
	static const Point Left;
	static const Point Right;
	static const Point Up;
	static const Point Down;
};

struct SinTile
{
	union
	{
		struct
		{
			int X;
			int Y;
		};

		__int64 Key;
	};
};


// Ό³Έν :
class ContentsHelper
{
public:
	static FVector GetWindowScale();
	static FVector GetTileScale();
	static void LoadImg(std::string_view _Path, std::string_view _Name);
	static void LoadFolder(std::string_view _Path, std::string_view _Name);
	static void LoadSound(std::string_view _Path, std::string_view _Name);
	static void SoundPlay(std::string_view _Name);

	static FVector RandomCirclePoint(FVector _Center, float _Radius);

	static float LerpClampf(float p1, float p2, float d1)
	{
		if (0.0f >= d1)
		{
			d1 = 0.0f;
		}

		if (1.0f <= d1)
		{
			d1 = 1.0f;
		}

		return Lerpf(p1, p2, d1);
	}

	static float Lerpf(float p1, float p2, float d1)
	{
		return (p1 * (1.0f - d1)) + (p2 * d1);
	}

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
	RenderActor,
	HitActor,
	Hero,
	Effect,
	SceneBackGround,
	Scene,
	Character,
	UI,
	Text,
	Transition
};

enum class RenderOrder
{
	None,
	BackGround,
	RenderActor,
	HitActor,
	Hero,
	Effect,
	SceneBackGround,
	Scene,
	Character,
	UI,
	Text,
	Transition
};

enum class EChapterType
{
	None,
	Default,
	Sin
};

enum class EBackGroundType
{
	None,
	Default,
	Sin,
};

enum class EMainMenuState
{
	None,
	Begin,
	Enter,
	Select,
	SelectChapter,
	NewGame,
	EnterChapter,
	Exit
};

enum class EEpilogueState
{
	None,
	Enter,
	LucyCutScene,
	ModCutScene,
	JusCutScene,
	PandCutScene,
	MalCutScene,
	ZdCutScene,
	AzCutScene,
	CerCutScene,
	Change
};

enum class EChapterState
{
	None,
	Idle,
	HeroDeath,
	CutScene,
	Reset,
	End
};

enum class ECutSceneState
{
	None,
	Enter,
	Select,
	BadEnd,
	Success,
};

enum class ESinState
{
	None,
	Opening,
	Intro,
	Phase1,
	Phase2,
	CutScene,
	HeroDeath,
	Reset,
	SinChage,
	SinEnd
};

enum class ESinSceneState
{
	None,
	Enter,
	Select,
	Success,
	End
};

enum class EHeroState
{
	None,
	Idle,
	Move,
	Kick,
	Hit,
	Victory,
	Death
};

enum class ECharacterState
{
	None,
	Idle,
	Appear
};

enum class ESinHeroState
{
	None,
	Idle,
	MoveY,
	Hit
};

enum class EDemonState
{
	None,
	Idle,
	Victory,
	Sin_Appear
};

enum class EHitActorState
{
	None,
	Idle,
	Hit,
	Move,
	Death
};

enum class EThornState
{
	None,
	Idle,
	Move,
	Up,
	Down
};

enum class EKeyComponentState
{
	None,
	Idle,
	Hit,
	Death
};

enum class EKeyComponentType
{
	None,
	Key,
	LockBox
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


// Sin
enum class SinUpdateOrder
{
	None,
	UnderBackGround,
	BackGround,
	Bottom,
	Mid,
	Top,
	Hero,
	Transition
};

enum class SinRenderOrder
{
	None,
	UnderBackGround,
	BackGround,
	Bottom,
	Mid,
	Hero,
	SmallVChain,
	Top,
	Transition
};

enum class ESinPitState
{
	None,
	Idle,
	Move
};

enum class ESinGearState
{
	None,
	Idle,
	Working,
	Stop
};

enum class ESinHeroLifeState
{
	None,
	Idle,
	HeroHit
};

enum class ESinBridgeState
{
	None,
	Idle,
	Move
};

enum class ESinSkullState
{
	None,
	Idle,
	Move
};

enum class ESinPistonState
{
	None,
	Idle,
	Move
};

enum class ESinPistonType
{
	None,
	Up,
	Down
};

enum class ESinChainLinkState
{
	None,
	Idle,
	Move
};

enum class ESinSmallChainType
{
	None,
	Ver,
	Hor
};

enum class ESinPhase
{
	None,
	Phase1,
	Phase2
};

enum class ESinSmallChainState
{
	None,
	Idle,
	Move,
	Show,
	Hit,
	Death
};

enum class ESinHitChainState
{
	None,
	Idle,
	Move,
	Hit,
	Death
};

enum class ESinHitChainHpState
{
	None,
	Idle,
	Hit,
	Death
};

enum class ESinHitChainType
{
	None,
	Left,
	Right
};

enum class ESinDialogueState
{
	None,
	Idle,
	Lightning,
	Move,
};

enum class ESinJudgeState
{
	None,
	Intro_Appear,
	Chap3_Fly
};