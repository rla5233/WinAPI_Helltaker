#include "ContentsHelper.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>
#include <EngineCore/EngineResourcesManager.h>
#include <EnginePlatform/EngineSound.h>

const Point Point::Zero	 = {  0,  0  };
const Point Point::Left	 = { -1,  0  };
const Point Point::Right = {  1,  0  };
const Point Point::Up	 = {  0, -1  };
const Point Point::Down	 = {  0,  1  };

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
}

FVector ContentsHelper::GetWindowScale()
{
    return GEngine->MainWindow.GetWindowScale();
}

FVector ContentsHelper::GetTileScale()
{
	FVector WinScale = GetWindowScale();
	FVector TileScale = { WinScale.X / 19.2f, WinScale.Y / 10.8f};
	return TileScale;
}

void ContentsHelper::LoadImg(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.AppendPath(_Name));
}

void ContentsHelper::LoadFolder(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.AppendPath(_Name));
}

void ContentsHelper::LoadSound(std::string_view _Path, std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move(_Path);
	UEngineSound::Load(ResourcesPath.AppendPath(_Name), _Name);
}

void ContentsHelper::SoundPlay(std::string_view _Name)
{
	UEngineSound::SoundPlay(_Name);
}

FVector ContentsHelper::RandomCirclePoint(FVector _Center, float _Radius)
{
	if (0 == _Radius)
	{
		return _Center;
	}

	float RandomValue = static_cast<float>(rand());
	float Random_X = fmodf(RandomValue, _Radius);
	if (1 == (rand() % 2))
	{
		Random_X *= -1;
	}
	Random_X += _Center.X;

	float Random_Y = 0.0f;
	if (1 == (rand() % 2))
	{
		Random_Y = _Center.Y + sqrtf(powf(_Radius, 2) - powf((Random_X - _Center.X), 2));
	}
	else
	{
		Random_Y = _Center.Y - sqrtf(powf(_Radius, 2) - powf((Random_X - _Center.X), 2));
	}

	return FVector(Random_X, Random_Y);
}
