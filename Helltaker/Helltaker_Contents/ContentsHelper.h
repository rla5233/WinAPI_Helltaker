#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>

const Color8Bit HELLTAKER_WHITE = Color8Bit(255, 255, 255, 0);
const Color8Bit HELLTAKER_GRAY = Color8Bit(125, 125, 125, 0);
const Color8Bit HELLTAKER_RED = Color8Bit(230, 77, 81, 255);

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

enum class EMainMenuState
{
	None,
	Begin,
	Enter,
	Select,
	NewGame,
	EnterChapter,
	Exit
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

enum class EDemonState
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
	Move,
	Death
};

enum class EThornState
{
	None,
	Idle,
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

enum class ECutSceneState
{
	None,
	Enter,
	Select,
	BadEnd,
	Success,
	Reset
};