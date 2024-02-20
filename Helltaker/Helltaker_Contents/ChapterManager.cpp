#include "ChapterManager.h"

#include "ContentsHelper.h"
#include "BackGround.h"
#include "Character.h"
#include "HitActor.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Thorn.h"
#include "Scene.h"
#include "Demon.h"
#include "Hero.h"
#include "Text.h"
#include "UI.h"

#include "Chapter2.h"
#include "RenderActor.h"

#include <math.h>
#include <vector>

bool ChapterManager::IsLoad = false;
std::set<std::string> ChapterManager::ChapterSet;

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
		ContentsHelper::LoadImg("Chapter\\Component", "LockBox.png");
		ContentsHelper::LoadFolder("Chapter\\Component", "Key");

#ifdef DEBUG
		// 디버그 용
		ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
		ContentsHelper::LoadImg("Debuging", "RedPoint.png");

		ContentsHelper::LoadFolder("Scene", "Transition");
#endif 
		IsLoad = true;
	}
}

void ChapterManager::M_SetChapterStartLocation(FVector _Value)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ChapterStartLocation = _Value * WinScale;
}

void ChapterManager::M_SetChapterEndPoint(Point _Point)
{
	EndPoint = _Point;
}

// 맵좌표를 윈도우 위치로 변환하는 함수
FVector ChapterManager::ChapterPointToLocation(FVector _Point) const
{
	return ChapterPointToLocation(Point(_Point.iX(), _Point.iY()));
}

FVector ChapterManager::ChapterPointToLocation(Point _Point) const
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Location = ChapterStartLocation;
	Location += FVector(_Point.X, _Point.Y) * ContentsHelper::GetTileScale();
	// 오차 보정
	Location += {fmod(WinScale.X, 19.0f), fmod(WinScale.Y, 10.8f)};
	return Location;
}

void ChapterManager::M_CreateTileInfoVec(const std::vector<std::vector<bool>>& _Map)
{
	ChapterWidth = static_cast<int>(_Map[0].size());
	ChapterHeight = static_cast<int>(_Map.size());
	TileInfoVec.resize(ChapterHeight);
	for (int i = 0; i < ChapterHeight; i++)
	{
		TileInfoVec[i].resize(ChapterWidth);
	}

	for (int Y = 0; Y < _Map.size(); Y++)
	{
		for (int X = 0; X < _Map[Y].size(); X++)
		{
			TileInfoVec[Y][X].IsVaild = _Map[Y][X];
		}
	}
}

void ChapterManager::M_SetChapterHitAcotrInfo(Point _Point, HitActor* const _HitActor)
{
	TileInfoVec[_Point.Y][_Point.X].Other = _HitActor;
}

void ChapterManager::M_SetChapterThornInfo(Point _Point, bool _IsUp)
{
	TileInfoVec[_Point.Y][_Point.X].IsThorn = _IsUp;
}

void ChapterManager::CreateBG(std::string_view _Name)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ChapterBG = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	ChapterBG->CreateBackGround(_Name);
	AllMapActors[reinterpret_cast<__int64>(ChapterBG)] = ChapterBG;
}

void ChapterManager::M_CreateChapterUI(int _ChapterNumber)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	UI* ChapterUI = SpawnActor<UI>(static_cast<int>(UpdateOrder::UI));
	ChapterUI->SetActorLocation(WinScale.Half2D());
	ChapterUI->SetName("ChapterUI");
	ChapterUI->CreateImageRenderer(RenderOrder::UI);
	ChapterUI->GetImageRenderer()->SetImage(ChapterUI->GetName() + ".png");
	ChapterUI->GetImageRenderer()->SetTransform({ {0,0}, WinScale });
	ChapterNumber = _ChapterNumber;
	AllMapActors[reinterpret_cast<__int64>(ChapterUI)] = ChapterUI;

	Text* ChapterNum = SpawnActor<Text>(static_cast<int>(UpdateOrder::Text));
	ChapterNum->SetActorLocation({ WinScale.X * 0.89f, WinScale.Y * 0.775f });
	ChapterNum->SetName("ChapterNum");
	ChapterNum->CreateTextRenderer(RenderOrder::Text);
	ChapterNum->SetTextTransForm({ {0,0}, {0,0} });
	ChapterNum->TextSetting(90, Color8Bit::White);
	ChapterNum->SetText(std::to_string(ChapterNumber));  
	AllMapActors[reinterpret_cast<__int64>(ChapterNum)] = ChapterNum;

	BottomText = SpawnActor<Text>(static_cast<int>(UpdateOrder::Text));
	BottomText->SetActorLocation({ WinScale.X * 0.612f, WinScale.Y * 0.953f });
	BottomText->SetName("BottomText");
	BottomText->CreateTextRenderer(RenderOrder::Text);
	BottomText->SetTextTransForm({ {0,0}, {0,0} });
	BottomText->TextSetting(38, Color8Bit::White);
	BottomText->SetText("재시작 [R키]");
	AllMapActors[reinterpret_cast<__int64>(BottomText)] = BottomText;

	HeroActionPoint = SpawnActor<Text>(static_cast<int>(UpdateOrder::Text));
	HeroActionPoint->SetActorLocation({ WinScale.X * 0.11f, WinScale.Y * 0.775f });
	HeroActionPoint->CreateTextRenderer(RenderOrder::Text);
	HeroActionPoint->SetTextTransForm({ {0,0},{0,0} });
	HeroActionPoint->TextSetting(90, Color8Bit::White);
	AllMapActors[reinterpret_cast<__int64>(HeroActionPoint)] = HeroActionPoint;
}

void ChapterManager::CreateTransition()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	TransitionActor = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Transition));
	TransitionActor->SetName("Transition");
	TransitionActor->CreateImageRenderer(RenderOrder::Transition);
	TransitionActor->SetActorLocation(WinScale.Half2D());
	TransitionActor->GetImageRenderer()->SetTransform({ { 0, 0 }, WinScale });
	TransitionActor->GetImageRenderer()->SetImage("Transition");
	TransitionActor->GetImageRenderer()->CreateAnimation("Transition", "Transition", 0, 28, TransitionInter, false);
	AllMapActors[reinterpret_cast<__int64>(TransitionActor)] = TransitionActor;
}

void ChapterManager::M_SpawnHero(Point _Point, int _ActionPoint)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Hero* NewHero = SpawnActor<Hero>(static_cast<int>(UpdateOrder::Hero));
	NewHero->SetName("Hero");
	NewHero->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	NewHero->SetLocationPoint({ _Point.X, _Point.Y });
	NewHero->SetActionPoint(_ActionPoint);
	PlayerHero = NewHero;
	HeroActionPoint->SetText(std::to_string(PlayerHero->GetActionPoint()));
	AllMapActors[reinterpret_cast<__int64>(NewHero)] = NewHero;
}

void ChapterManager::M_SpawnDemon(Point _Point, std::string_view _Name)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	ChapterDemon =  SpawnActor<Demon>(static_cast<int>(UpdateOrder::Demon));
	ChapterDemon->SetName(_Name);
	ChapterDemon->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	ChapterDemon->SetDemon(_Name);

	TileInfoVec[_Point.Y][_Point.X].IsVaild = false;
	AllMapActors[reinterpret_cast<__int64>(ChapterDemon)] = ChapterDemon;
}

void ChapterManager::M_SpawnSkeleton(Point _Point)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Skeleton* NewSkeleton = SpawnActor<Skeleton>(static_cast<int>(UpdateOrder::Skeleton));
	NewSkeleton->SetName("Skeleton");
	NewSkeleton->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	NewSkeleton->SetLocationPoint({ _Point });

	if (nullptr != TileInfoVec[_Point.Y][_Point.X].Other)
	{
		MsgBoxAssert("HitActor Already Exist");
	}

	TileInfoVec[_Point.Y][_Point.X].Other = NewSkeleton;
	AllMapActors[reinterpret_cast<__int64>(NewSkeleton)] = NewSkeleton;
}

void ChapterManager::M_SpawnStone(Point _Point, std::string_view _Name)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Stone* NewStone = SpawnActor<Stone>(static_cast<int>(UpdateOrder::Stone));
	NewStone->SetName("Stone");
	NewStone->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	NewStone->SetLocationPoint(_Point);
	NewStone->SetStoneImg(_Name);

	if (nullptr != TileInfoVec[_Point.Y][_Point.X].Other)
	{
		MsgBoxAssert("HitActor Already Exist");
	}

	TileInfoVec[_Point.Y][_Point.X].Other = NewStone;
	AllMapActors[reinterpret_cast<__int64>(NewStone)] = NewStone;
}

void ChapterManager::M_SpawnThorn(Point _Point, EThornState _State)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Thorn* NewThorn = SpawnActor<Thorn>(static_cast<int>(UpdateOrder::Thorn));
	NewThorn->SetName("Thorn");
	NewThorn->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	NewThorn->SetPoint(_Point);
	NewThorn->StateChange(_State);

	AllThorn.push_back(NewThorn);
	AllMapActors[reinterpret_cast<__int64>(NewThorn)] = NewThorn;
}

void ChapterManager::M_SpawnKey(Point _Point)
{
	FVector TileScale = ContentsHelper::GetTileScale();

}

// 수정
HitActor* ChapterManager::M_GetHitActor(FVector _Point)
{
	return M_GetHitActor(Point(_Point.iX(), _Point.iY()));
}

HitActor* ChapterManager::M_GetHitActor(Point _Point)
{
	return TileInfoVec[_Point.Y][_Point.X].Other;
}

void ChapterManager::M_DestroyHitActor(__int64 _HitActor)
{
	AllMapActors.erase(_HitActor);
}

void ChapterManager::M_ChangeThornState()
{
	if (true == IsThornChange)
	{
		for (Thorn* Thorn : AllThorn)
		{
			if (nullptr == Thorn)
			{
				MsgBoxAssert("Thorn is nullptr");
			}

			switch (Thorn->GetState())
			{
			case EThornState::Up:
				Thorn->StateChange(EThornState::Down);
				break;
			case EThornState::Down:
				Thorn->StateChange(EThornState::Up);
				break;
			}
		}
	}
}

void ChapterManager::M_UpdateHeroActionPoint()
{
	std::string PointStr = std::to_string(PlayerHero->GetActionPoint());
	
	if (0 >= std::stoi(PointStr))
	{
		PointStr = "X";
	}

	HeroActionPoint->SetText(PointStr);
}

void ChapterManager::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	
	CreateTransition();	
}

void ChapterManager::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	TileInfoVec.clear();
	AllThorn.clear();

	for (std::pair<const __int64, AActor*>& Actor : AllMapActors)
	{
		if (nullptr == Actor.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor.second->Destroy(0.0f);
		Actor.second = nullptr;
	}

	AllMapActors.clear();
}

void ChapterManager::Idle(float _DeltaTime)
{
	if (true == TransitionActor->GetImageRenderer()->IsCurAnimationEnd())
	{
		TransitionActor->GetImageRenderer()->ActiveOff();
	}

	ResetCheck();

	if (EHeroState::Death == PlayerHero->GetHeroState())
	{
		M_StateChange(EChapterState::HeroDeath);
	}	

	Point HeroLocationPoint = PlayerHero->GetLocationPoint();
	if (HeroLocationPoint.X == EndPoint.X && HeroLocationPoint.Y == EndPoint.Y)
	{
		M_StateChange(EChapterState::CutScene);
	}

	// Debug
	if (UEngineInput::IsPress('P'))
	{
		M_StateChange(EChapterState::CutScene);
	}
}

void ChapterManager::IdleStart()
{
	TransitionActor->GetImageRenderer()->ActiveOn();
	TransitionActor->GetImageRenderer()->ChangeAnimation("Transition", false, 19);
	ChapterBG->BackGroundChange(ChapterBG->GetName() + ".png");
	PlayerHero->SeeDirChange(EActorSeeDir::Right);
	PlayerHero->StateChange(EHeroState::Idle);
}

void ChapterManager::HeroDeath(float _DeltaTime)
{
	if (true == PlayerHero->GetImageRenderer()->IsCurAnimationEnd())
	{
		M_StateChange(EChapterState::Reset);
	}
}

void ChapterManager::HeroDeathStart()
{
	for (std::pair<const __int64, AActor*> MapActors : AllMapActors)
	{
		if (nullptr == MapActors.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		MapActors.second->AllRenderersActiveOff();
	}

	PlayerHero->AllRenderersActiveOn();
	ChapterBG->AllRenderersActiveOn();
	ChapterBG->BackGroundChange("DefaultBG.png");
}

void ChapterManager::CutScene(float _DeltaTime)
{
	ResetCheck();
}

void ChapterManager::CutSceneStart()
{
	for (std::pair<const __int64, AActor*> MapActors : AllMapActors)
	{
		if (nullptr == MapActors.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		MapActors.second->ActiveOff();
		MapActors.second->AllRenderersActiveOff();
	}

	ChapterBG->ActiveOn();
	ChapterBG->AllRenderersActiveOn();
	ChapterBG->BackGroundChange("DefaultBG.png");
}

void ChapterManager::Reset(float _DeltaTime)
{
	if (19 == TransitionActor->GetImageRenderer()->GetCurAnimationFrame())
	{
		LevelEnd(nullptr);
		LevelStart(nullptr);
	}
}

void ChapterManager::ResetStart()
{
	TransitionActor->GetImageRenderer()->ActiveOn();
	TransitionActor->GetImageRenderer()->AnimationReset();
	TransitionActor->GetImageRenderer()->ChangeAnimation("Transition");
}

void ChapterManager::ResetCheck()
{
	if (UEngineInput::IsPress('R'))
	{
		M_StateChange(EChapterState::Reset);
	}
}

void ChapterManager::End(float _DeltaTime)
{
	switch (ChapterEndOrder)
	{
	case 0:
		if (true == PlayerHero->GetImageRenderer()->IsCurAnimationEnd())
		{
			TransitionActor->GetImageRenderer()->ActiveOn();
			TransitionActor->GetImageRenderer()->AnimationReset();
			TransitionActor->GetImageRenderer()->ChangeAnimation("Transition");
			++ChapterEndOrder;
		}
		break;
	case 1:
		if (19 == TransitionActor->GetImageRenderer()->GetCurAnimationFrame())
		{
			ChangeChapter();
		}
		break;
	}

}

void ChapterManager::EndStart()
{
	for (std::pair<const __int64, AActor*> MapActors : AllMapActors)
	{
		if (nullptr == MapActors.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		MapActors.second->ActiveOn();		
		MapActors.second->AllRenderersActiveOn();
	}

	TransitionActor->GetImageRenderer()->ActiveOff();
	BottomText->GetTextRenderer()->ActiveOff();
	ChapterBG->BackGroundChange(ChapterBG->GetName() + ".png");
	PlayerHero->StateChange(EHeroState::Victory);
	ChapterDemon->StateChange(EDemonState::Victory);
	ChapterEndOrder = 0;
}

void ChapterManager::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	M_StateUpdate(_DeltaTime);
}

void ChapterManager::M_StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EChapterState::Idle:
		Idle(_DeltaTime);
		break;
	case EChapterState::HeroDeath:
		HeroDeath(_DeltaTime);
		break;
	case EChapterState::CutScene:
		CutScene(_DeltaTime);
		break;
	case EChapterState::Reset:
		Reset(_DeltaTime);
		break;
	case EChapterState::End:
		End(_DeltaTime);
		break;
	}
}

void ChapterManager::M_StateChange(EChapterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EChapterState::Idle:
			IdleStart();
			break;
		case EChapterState::HeroDeath:
			HeroDeathStart();
			break;
		case EChapterState::CutScene:
			CutSceneStart();
			break;
		case EChapterState::Reset:
			ResetStart();
			break;
		case EChapterState::End:
			EndStart();
			break;
		}
	}

	State = _State;
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
			GreenPoint[Y][X]->SetActorLocation(ChapterPointToLocation(Point(X, Y)));
			GreenPoint[Y][X]->CreateImageRenderer(RenderOrder::UI);

			if (true == TileInfoVec[Y][X].IsVaild)
			{
				GreenPoint[Y][X]->GetImageRenderer()->SetImage("GreenPoint.png");
			}
			else
			{
				GreenPoint[Y][X]->GetImageRenderer()->SetImage("RedPoint.png");
			}

			GreenPoint[Y][X]->GetImageRenderer()->SetTransform({ { 0,0 }, {2, 2} });
			AllMapActors[reinterpret_cast<__int64>(GreenPoint[Y][X])] = GreenPoint[Y][X];
		}
	}
}