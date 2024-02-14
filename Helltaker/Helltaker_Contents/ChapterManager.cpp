#include "ChapterManager.h"

#include "ContentsHelper.h"
#include "HitActor.h"
#include "BackGround.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Devil.h"
#include "Hero.h"
#include "UI.h"

#include "RenderActor.h"
#include <math.h>
#include <vector>

bool ChapterManager::IsLoad = false;

ChapterManager::ChapterManager()
{
}

ChapterManager::~ChapterManager()
{
}

void ChapterManager::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("UI", "ChapterUI.png");
		IsLoad = true;
	}

	StateChange(EChapterState::Idle);
}

void ChapterManager::SetChapterStartLocation(int _X, int _Y)
{
	FVector Point = { _X, _Y };
	ChapterStartLocation = Point * ContentsHelper::GetTileScale();
}

void ChapterManager::SetChapterEndPoint(int _X, int _Y)
{
	EndPoint_X = _X;
	EndPoint_Y = _Y;
}

// 맵좌표를 윈도우 위치로 변환하는 함수
FVector ChapterManager::ChapterPointToLocation(FVector _Point) const
{
	return ChapterPointToLocation(_Point.iX(), _Point.iY());
}

FVector ChapterManager::ChapterPointToLocation(int _X, int _Y) const
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Location = ChapterStartLocation;
	Location += FVector(_X, _Y) * ContentsHelper::GetTileScale();
	// 오차 보정
	Location += {fmod(WinScale.X, 19.0f), fmod(WinScale.Y, 10.8f)};
	return Location;
}

void ChapterManager::CreateChapterVec(const std::vector<std::vector<bool>>& _Map)
{
	ChapterWidth = static_cast<int>(_Map[0].size());
	ChapterHeight = static_cast<int>(_Map.size());
	ChapterVec.resize(ChapterHeight);
	for (int i = 0; i < ChapterHeight; i++)
	{
		ChapterVec[i].resize(ChapterWidth);
	}

	for (int Y = 0; Y < _Map.size(); Y++)
	{
		for (int X = 0; X < _Map[Y].size(); X++)
		{
			ChapterVec[Y][X] = _Map[Y][X];
		}
	}

	IsChapterVecInit = true;
}

void ChapterManager::CreateHitActorVec()
{
	if (false == IsChapterVecInit)
	{
		MsgBoxAssert("ChapterMap is Not Exist");
	}

	HitActorVec.resize(ChapterHeight);
	for (int i = 0; i < ChapterHeight; i++)
	{
		HitActorVec[i].resize(ChapterWidth);
	}

	for (int Y = 0; Y < ChapterHeight; Y++)
	{
		for (int X = 0; X < ChapterWidth; X++)
		{
			HitActorVec[Y][X] = nullptr;
		}
	}
}

void ChapterManager::CreateBG(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	BackGround* ChapterBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	ChapterBG->CreateBackGround(_Name);
	AllActors[reinterpret_cast<__int64>(ChapterBG)] = ChapterBG;
}

void ChapterManager::CreateChapterUI()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	UI* ChapterUI = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	ChapterUI->SetActorLocation(WinScale.Half2D());
	ChapterUI->SetName("ChapterUI");
	ChapterUI->CreateImageRenderer(RenderOrder::UI);
	ChapterUI->GetRenderer()->SetImage(ChapterUI->GetName() + ".png");
	ChapterUI->GetRenderer()->SetTransform({ {0,0}, WinScale });
	AllActors[reinterpret_cast<__int64>(ChapterUI)] = ChapterUI;
}

void ChapterManager::SpawnHero(int _X, int _Y)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Hero* NewHero = SpawnActor<Hero>(static_cast<int>(UpdateOrder::Hero));
	NewHero->SetName("Hero");
	NewHero->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewHero->SetLocationPoint({ _X, _Y });
	PlayerHero = NewHero;
	AllActors[reinterpret_cast<__int64>(NewHero)] = NewHero;
}

void ChapterManager::SpawnDevil(int _X, int _Y, std::string_view _Name)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Devil* NewDevil =  SpawnActor<Devil>(static_cast<int>(UpdateOrder::Devil));
	NewDevil->SetName(_Name);
	NewDevil->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewDevil->SetDevil(_Name);
	AllActors[reinterpret_cast<__int64>(NewDevil)] = NewDevil;
}

void ChapterManager::SpawnSkeleton(int _X, int _Y)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Skeleton* NewSkeleton = SpawnActor<Skeleton>(static_cast<int>(UpdateOrder::Skeleton));
	NewSkeleton->SetName("Skeleton");
	NewSkeleton->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewSkeleton->SetLocationPoint({ _X, _Y });
	HitActorVec[_Y][_X] = NewSkeleton;
	AllActors[reinterpret_cast<__int64>(NewSkeleton)] = NewSkeleton;
}

void ChapterManager::SpawnStone(int _X, int _Y, std::string_view _Name)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Stone* NewStone = SpawnActor<Stone>(static_cast<int>(UpdateOrder::Stone));
	NewStone->SetName("Stone");
	NewStone->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewStone->SetLocationPoint({ _X, _Y });
	NewStone->SetStoneImg(_Name);
	HitActorVec[_Y][_X] = NewStone;
	AllActors[reinterpret_cast<__int64>(NewStone)] = NewStone;
}

HitActor* ChapterManager::GetHitActor(FVector _Point)
{
	return GetHitActor(_Point.iX(), _Point.iY());
}

HitActor* ChapterManager::GetHitActor(int _X, int _Y)
{
	return HitActorVec[_Y][_X];
}

void ChapterManager::DestroyHitActor(__int64 _HitActor)
{
	AllActors.erase(_HitActor);
}


// 디버그용
void ChapterManager::ShowLocationPoint()
{
	std::vector<std::vector<UI*>> GreenPoint;
	
	GreenPoint.resize(ChapterHeight);
	for (int i = 0; i < ChapterHeight; i++)
	{
		GreenPoint[i].resize(ChapterWidth);
	}
	
	for (int Y = 0; Y < ChapterHeight; Y++)
	{
		for (int X = 0; X < ChapterWidth; X++)
		{
			GreenPoint[Y][X] = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
			GreenPoint[Y][X]->SetActorLocation(ChapterPointToLocation(X, Y));
			GreenPoint[Y][X]->CreateImageRenderer(RenderOrder::UI);
			
			if (ChapterVec[Y][X])
			{
				GreenPoint[Y][X]->GetRenderer()->SetImage("GreenPoint.png");
			}
			else
			{
				GreenPoint[Y][X]->GetRenderer()->SetImage("RedPoint.png");
			}
			
			GreenPoint[Y][X]->GetRenderer()->SetTransform({ { 0,0 }, {2, 2} });
			AllActors[reinterpret_cast<__int64>(GreenPoint[Y][X])] = GreenPoint[Y][X];
		}
	}
}

void ChapterManager::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void ChapterManager::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	for (std::pair<const __int64, AActor*>& Actor : AllActors)
	{
		if (nullptr == Actor.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor.second->Destroy(0.0f);
		Actor.second = nullptr;
	}

	ChapterVec.clear();
	HitActorVec.clear();
	AllActors.clear();
}

void ChapterManager::Idle(float _DeltaTime)
{
	if (true == PlayerHero->GetCanActionCheck())
	{
		if (UEngineInput::IsPress('W') || UEngineInput::IsPress(VK_UP))
		{
			PlayerHero->MoveDirChange(EMoveActorDir::Up);
			PlayerHero->ActionCheck(_DeltaTime, 'W', VK_UP);
		}
		else if (UEngineInput::IsPress('A') || UEngineInput::IsPress(VK_LEFT))
		{
			PlayerHero->MoveDirChange(EMoveActorDir::Left);
			PlayerHero->SeeDirChange(EActorSeeDir::Left);
			PlayerHero->ActionCheck(_DeltaTime, 'A', VK_LEFT);
		}
		else if (UEngineInput::IsPress('S') || UEngineInput::IsPress(VK_DOWN))
		{
			PlayerHero->MoveDirChange(EMoveActorDir::Down);
			PlayerHero->ActionCheck(_DeltaTime, 'S', VK_DOWN);
		}
		else if (UEngineInput::IsPress('D') || UEngineInput::IsPress(VK_RIGHT))
		{
			PlayerHero->MoveDirChange(EMoveActorDir::Right);
			PlayerHero->SeeDirChange(EActorSeeDir::Right);
			PlayerHero->ActionCheck(_DeltaTime, 'D', VK_RIGHT);
		}
	}

	if (UEngineInput::IsPress('R'))
	{
		StateChange(EChapterState::Reset);
	}

	FVector HeroLocationPoint = PlayerHero->GetLocationPoint();
	if (HeroLocationPoint.iX() == EndPoint_X && HeroLocationPoint.iY() == EndPoint_Y)
	{
		StateChange(EChapterState::CutScene);
	}
}

void ChapterManager::IdleStart()
{
	
}

void ChapterManager::Reset(float _DeltaTime)
{
	StateChange(EChapterState::Idle);
}

void ChapterManager::ResetStart()
{
	LevelEnd(nullptr);
	LevelStart(nullptr);
}

void ChapterManager::Secene(float _DeltaTime)
{
}

void ChapterManager::SeceneStart()
{
	int a = 0;
}

void ChapterManager::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}


void ChapterManager::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EChapterState::Idle:
		Idle(_DeltaTime);
		break;
	case EChapterState::Reset:
		Reset(_DeltaTime);
		break;
	case EChapterState::CutScene:
		Secene(_DeltaTime);
		break;
	case EChapterState::End:
		break;
	}
}

void ChapterManager::StateChange(EChapterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EChapterState::Idle:
			IdleStart();
			break;
		case EChapterState::Reset:
			ResetStart();
			break;
		case EChapterState::CutScene:
			SeceneStart();
			break;
		case EChapterState::End:
			break;
		}
	}

	State = _State;
}
