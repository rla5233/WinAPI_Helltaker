#include "ChapterManager.h"

#include "ContentsHelper.h"
#include "HitActor.h"
#include "BackGround.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Thorn.h"
#include "Scene.h"
#include "Demon.h"
#include "Hero.h"
#include "UI.h"

#include "Chapter2.h"
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
		ContentsHelper::LoadFolder("Scene", "Transition");

		// 디버그 용
		ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
		ContentsHelper::LoadImg("Debuging", "RedPoint.png");

		IsLoad = true;
	}
}

void ChapterManager::SetChapterStartLocation(int _X, int _Y)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	FVector Point = FVector(_X, _Y) * TileScale;
	ChapterStartLocation = Point + FVector(TileScale.X * 0.1f, TileScale.Y * 0.25f);
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

void ChapterManager::CreateChapterInfoVec(const std::vector<std::vector<bool>>& _Map)
{
	ChapterWidth = static_cast<int>(_Map[0].size());
	ChapterHeight = static_cast<int>(_Map.size());
	ChapterInfoVec.resize(ChapterHeight);
	for (int i = 0; i < ChapterHeight; i++)
	{
		ChapterInfoVec[i].resize(ChapterWidth);
	}

	for (int Y = 0; Y < _Map.size(); Y++)
	{
		for (int X = 0; X < _Map[Y].size(); X++)
		{
			ChapterInfoVec[Y][X].IsVaild = _Map[Y][X];
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

void ChapterManager::CreateTransition()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	TransitionActor = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Transition));
	TransitionActor->SetName("Transition");
	TransitionActor->CreateImageRenderer(RenderOrder::Transition);
	TransitionActor->SetActorLocation(WinScale.Half2D());
	TransitionActor->GetRenderer()->SetTransform({ { 0, 0 }, WinScale });
	TransitionActor->GetRenderer()->SetImage("Transition");
	TransitionActor->GetRenderer()->CreateAnimation("Transition", "Transition", 0, 28, TransitionInter, false);
	AllActors[reinterpret_cast<__int64>(TransitionActor)] = TransitionActor;
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

void ChapterManager::SpawnDemon(int _X, int _Y, std::string_view _Name)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Demon* NewDemon =  SpawnActor<Demon>(static_cast<int>(UpdateOrder::Demon));
	NewDemon->SetName(_Name);
	NewDemon->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewDemon->SetDemon(_Name);
	AllActors[reinterpret_cast<__int64>(NewDemon)] = NewDemon;
}

void ChapterManager::SpawnSkeleton(int _X, int _Y)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Skeleton* NewSkeleton = SpawnActor<Skeleton>(static_cast<int>(UpdateOrder::Skeleton));
	NewSkeleton->SetName("Skeleton");
	NewSkeleton->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewSkeleton->SetLocationPoint({ _X, _Y });
	ChapterInfoVec[_Y][_X].Other = NewSkeleton;
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
	ChapterInfoVec[_Y][_X].Other = NewStone;
	AllActors[reinterpret_cast<__int64>(NewStone)] = NewStone;
}

void ChapterManager::SpawnThorn(int _X, int _Y, EThornState _State)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Thorn* NewThorn = SpawnActor<Thorn>(static_cast<int>(UpdateOrder::Thorn));
	NewThorn->SetName("Thorn");
	NewThorn->SetActorLocation(ChapterPointToLocation(_X, _Y) + TileScale.Half2D());
	NewThorn->StateChange(_State);
	AllActors[reinterpret_cast<__int64>(NewThorn)] = NewThorn;
}

HitActor* ChapterManager::GetHitActor(FVector _Point)
{
	return GetHitActor(_Point.iX(), _Point.iY());
}

HitActor* ChapterManager::GetHitActor(int _X, int _Y)
{
	return ChapterInfoVec[_Y][_X].Other;
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
	
	CreateTransition();
	StateChange(EChapterState::Transition);
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
	// 디버깅 용
	if (nullptr == PlayerHero)
	{
		return;
	}

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

void ChapterManager::Transition(float _DeltaTime)
{
	if (true == TransitionActor->GetRenderer()->IsCurAnimationEnd())
	{
		TransitionActor->GetRenderer()->ActiveOff();
		StateChange(EChapterState::Idle);
	}
}

void ChapterManager::TransitionStart()
{
	TransitionActor->GetRenderer()->AnimationReset();
	TransitionActor->GetRenderer()->ChangeAnimation("Transition");
}

void ChapterManager::Reset(float _DeltaTime)
{
	if (true == TransitionActor->GetRenderer()->IsCurAnimationEnd())
	{
		TransitionActor->GetRenderer()->ActiveOff();
		StateChange(EChapterState::Idle);
	}
}

void ChapterManager::ResetStart()
{
	LevelEnd(nullptr);
	LevelStart(nullptr);
}

void ChapterManager::CutSecene(float _DeltaTime)
{
}

void ChapterManager::CutSeceneStart()
{
	GEngine->CreateLevel<Chapter2>("Chapter2");
	GEngine->ChangeLevel("Chapter2");
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
	case EChapterState::Transition:
		Transition(_DeltaTime);
		break;
	case EChapterState::CutScene:
		CutSecene(_DeltaTime);
		break;
	case EChapterState::Reset:
		Reset(_DeltaTime);
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
		case EChapterState::Transition:
			TransitionStart();
			break;
		case EChapterState::CutScene:
			CutSeceneStart();
			break;
		case EChapterState::Reset:
			ResetStart();
			break;
		case EChapterState::End:
			break;
		}
	}

	State = _State;
}