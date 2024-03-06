#include "ChapterManager.h"

#include "ContentsHelper.h"
#include "KeyComponent.h"
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

#include <EnginePlatform/EngineSound.h>
#include <math.h>
#include <vector>

bool ChapterManager::IsLoad = false;

const float ChapterManager::TransitionInter = 0.0435f;
const float ChapterManager::HeroDelayTime = 0.15f;
std::set<std::string> ChapterManager::ChapterSet;

UEngineSoundPlayer ChapterManager::ChapterBGMPlayer;

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
		ContentsHelper::LoadImg("Debuging", "GreenPoint.png");
		ContentsHelper::LoadImg("Debuging", "RedPoint.png");
		ContentsHelper::LoadFolder("Scene", "Transition");

		ContentsHelper::LoadSound("Sound\\BGM", "Vitality.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "transition_on.wav");
		ContentsHelper::LoadSound("Sound\\Effect", "transition_off.wav");
		
		ChapterBGMPlayer = UEngineSound::SoundPlay("Vitality.wav");
		ChapterBGMPlayer.Loop();
		ChapterBGMPlayer.Off();

		IsLoad = true;
	}
}

void ChapterManager::M_SetChapterStartLocation(FVector _Value)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ChapterStartLocation = _Value * WinScale;
}

FVector ChapterManager::ChapterPointToLocation(Point _Point) const
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Location = ChapterStartLocation;
	Location += FVector(_Point.X, _Point.Y) * ContentsHelper::GetTileScale();
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

	FVector ImgScale = ChapterBG->GetImageRenderer()->GetImage()->GetScale();
	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * (ImgScale.Y / 1080) };

	FVector CameraPos = { 0.0f, (Scale.Y - WinScale.Y) / 2.0f };
	SetCameraPos(CameraPos);

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
	ChapterUI->GetImageRenderer()->CameraEffectOff();
	ChapterNumber = _ChapterNumber;
	AllMapActors[reinterpret_cast<__int64>(ChapterUI)] = ChapterUI;

	Text* ChapterNum = SpawnActor<Text>(static_cast<int>(UpdateOrder::Text));
	ChapterNum->SetActorLocation({ WinScale.X * 0.89f, WinScale.Y * 0.775f });
	ChapterNum->SetName("ChapterNum");
	ChapterNum->CreateTextRenderer(RenderOrder::Text);
	ChapterNum->SetTextTransForm({ {0,0}, {0,0} });
	ChapterNum->TextSetting(90, Color8Bit::White);
	ChapterNum->SetText(std::to_string(ChapterNumber));  
	ChapterNum->GetTextRenderer()->CameraEffectOff();
	AllMapActors[reinterpret_cast<__int64>(ChapterNum)] = ChapterNum;

	BottomText = SpawnActor<Text>(static_cast<int>(UpdateOrder::Text));
	BottomText->SetActorLocation({ WinScale.X * 0.612f, WinScale.Y * 0.953f });
	BottomText->SetName("BottomText");
	BottomText->CreateTextRenderer(RenderOrder::Text);
	BottomText->SetTextTransForm({ {0,0}, {0,0} });
	BottomText->TextSetting(38, Color8Bit::White);
	BottomText->SetText("재시작 [R키]"); 
	BottomText->GetTextRenderer()->SetTextEffect(2);
	BottomText->GetTextRenderer()->CameraEffectOff();

	AllMapActors[reinterpret_cast<__int64>(BottomText)] = BottomText;

	HeroActionPoint = SpawnActor<Text>(static_cast<int>(UpdateOrder::Text));
	HeroActionPoint->SetActorLocation({ WinScale.X * 0.11f, WinScale.Y * 0.775f });
	HeroActionPoint->CreateTextRenderer(RenderOrder::Text);
	HeroActionPoint->SetTextTransForm({ {0,0},{0,0} });
	HeroActionPoint->TextSetting(90, Color8Bit::White);
	HeroActionPoint->GetTextRenderer()->CameraEffectOff();
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
	TransitionActor->GetImageRenderer()->CameraEffectOff();
	TransitionActor->GetImageRenderer()->ActiveOff();
	AllMapActors[reinterpret_cast<__int64>(TransitionActor)] = TransitionActor;
}

void ChapterManager::TransitionOn()
{
	TransitionActor->GetImageRenderer()->ActiveOn();
	TransitionActor->GetImageRenderer()->AnimationReset();
	TransitionActor->GetImageRenderer()->ChangeAnimation("Transition");
	UEngineSound::SoundPlay("transition_on.wav");
}

void ChapterManager::M_SpawnHero(Point _Point, int _ActionPoint)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	PlayerHero = SpawnActor<Hero>(static_cast<int>(UpdateOrder::Hero));
	PlayerHero->SetName("Hero");
	PlayerHero->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	PlayerHero->SetLocationPoint({ _Point.X, _Point.Y });
	PlayerHero->SetActionPoint(_ActionPoint);
	PlayerHero->StateChange(EHeroState::Idle);
	HeroActionPoint->SetText(std::to_string(PlayerHero->GetActionPoint()));
	AllMapActors[reinterpret_cast<__int64>(PlayerHero)] = PlayerHero;
}

void ChapterManager::M_SpawnDemon(Point _Point, std::string_view _Name, const FTransform& _FTransform)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Demon* ChapterDemon = SpawnActor<Demon>(static_cast<int>(UpdateOrder::RenderActor));
	ChapterDemon->SetName(_Name);
	ChapterDemon->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	ChapterDemon->SetDemon(_Name, _FTransform);
	ChapterDemon->SetLocationPoint(_Point);
	ChapterDemon->StateChange(EDemonState::Idle);

	AllChapterDemon.push_back(ChapterDemon);
	TileInfoVec[_Point.Y][_Point.X].IsVaild = false;
	AllMapActors[reinterpret_cast<__int64>(ChapterDemon)] = ChapterDemon;
}

void ChapterManager::M_SpawnSkeleton(Point _Point)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	Skeleton* NewSkeleton = SpawnActor<Skeleton>(static_cast<int>(UpdateOrder::HitActor));
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
	Stone* NewStone = SpawnActor<Stone>(static_cast<int>(UpdateOrder::HitActor));
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
	Thorn* NewThorn = SpawnActor<Thorn>(static_cast<int>(UpdateOrder::RenderActor));
	NewThorn->SetName("Thorn");
	NewThorn->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	NewThorn->SetPoint(_Point);
	NewThorn->StateChange(_State);

	AllThorn.push_back(NewThorn);
	AllMapActors[reinterpret_cast<__int64>(NewThorn)] = NewThorn;
}

void ChapterManager::M_SpawnKeyComponent(Point _Point, EKeyComponentType _Type)
{
	FVector TileScale = ContentsHelper::GetTileScale();
	KeyComponent* NewKeyComponent = SpawnActor<KeyComponent>(static_cast<int>(UpdateOrder::RenderActor));
	NewKeyComponent->SetActorLocation(ChapterPointToLocation(_Point) + TileScale.Half2D());
	NewKeyComponent->SetLocationPoint(_Point);

	switch (_Type)
	{
	case EKeyComponentType::Key:
		NewKeyComponent->SetName("Key");
		NewKeyComponent->SetKeyComponentType(EKeyComponentType::Key);
		Key = NewKeyComponent;
		break;
	case EKeyComponentType::LockBox:
		NewKeyComponent->SetName("LockBox");
		NewKeyComponent->SetKeyComponentType(EKeyComponentType::LockBox);
		TileInfoVec[_Point.Y][_Point.X].Other = NewKeyComponent;
		LockBox = NewKeyComponent;
		break;
	}

	NewKeyComponent->StateChange(EKeyComponentState::Idle);
	AllMapActors[reinterpret_cast<__int64>(NewKeyComponent)] = NewKeyComponent;
}

HitActor* ChapterManager::M_GetHitActor(Point _Point) const
{
	return TileInfoVec[_Point.Y][_Point.X].Other;
}

void ChapterManager::M_DestroyHitActor(__int64 _Key)
{
	if (false == AllMapActors.contains(_Key))
	{
		MsgBoxAssert("HitActor Not Exist.")
	}

	AllMapActors.erase(_Key);
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

void ChapterManager::M_BottomTextRendererOff()
{
	BottomText->AllRenderersActiveOff();
}

FVector ChapterManager::M_GetHeroLocation() const
{
	return PlayerHero->GetActorLocation();
}

Point ChapterManager::M_GetHeroLocationPoint() const
{
	return PlayerHero->GetLocationPoint();
}

Point ChapterManager::M_GetHeroNextLocationPoint() const
{
	return PlayerHero->GetNextLocationPoint();
}

EHeroState ChapterManager::M_GetHeroState() const
{
	return PlayerHero->GetHeroState();
}

void ChapterManager::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	
	CreateTransition();	
}

void ChapterManager::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	for (size_t i = 0; i < TileInfoVec.size(); i++)
	{
		TileInfoVec[i].clear();
	}
	TileInfoVec.clear();

	AllThorn.clear();
	AllChapterDemon.clear();

	for (std::pair<const __int64, AActor*>& Actor : AllMapActors)
	{
		if (nullptr == Actor.second)
		{
			MsgBoxAssert("Actor is nullptr");
		}

		Actor.second->Destroy();
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

	HeroDelayTimeUpdate(_DeltaTime);
	ResetCheck();
	CutSceneCheck();

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
	UEngineSound::SoundPlay("transition_off.wav");
	ChapterBGMPlayer.On();
}

void ChapterManager::HeroDeath(float _DeltaTime)
{
	if (true == PlayerHero->GetImageRenderer()->IsCurAnimationEnd())
	{
		M_StateChange(EChapterState::Reset);
	}
}

// 수정 (Hero 이펙트 제거 가능?)
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
	PlayerHero->AllEffectActiveOff();
	ChapterBG->AllRenderersActiveOn();
	ChapterBG->BackGroundChange("DefaultBG.png");
}

void ChapterManager::HeroDelayTimeUpdate(float _DeltaTime)
{
	if (false == PlayerHero->GetCanActionCheck())
	{
		if (0.0f >= HeroDelayTimeCount)
		{
			PlayerHero->SetCanActionCheck(true);
			HeroDelayTimeCount = HeroDelayTime;
			return;
		}

		HeroDelayTimeCount -= _DeltaTime;
	}
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

		if (nullptr != dynamic_cast<Text*>(MapActors.second))
		{
			MapActors.second->AllRenderersActiveOff();
		}

		if (nullptr != dynamic_cast<UI*>(MapActors.second))
		{
			MapActors.second->AllRenderersActiveOff();
		}
	}
	
	if (nullptr != PlayerHero)
	{
		PlayerHero->ActiveOff();
	}
}

void ChapterManager::CutSceneCheck()
{
	Point HeroCurPoint = PlayerHero->GetLocationPoint();
	for (Demon* Demon : AllChapterDemon)
	{
		Point DemonPoint = Demon->GetLocationPoint();
		if (DemonPoint + Point::Left == HeroCurPoint ||
			DemonPoint + Point::Right == HeroCurPoint ||
			DemonPoint + Point::Up == HeroCurPoint ||
			DemonPoint + Point::Down == HeroCurPoint)
		{
			M_StateChange(EChapterState::CutScene);
		}
	}
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
	TransitionOn();
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
	ResetCheck();

	switch (ChapterEndOrder)
	{
	case 0:
		if (true == PlayerHero->GetImageRenderer()->IsCurAnimationEnd())
		{
			TransitionOn();
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

		MapActors.second->AllRenderersActiveOn();
		MapActors.second->ActiveOn();		
	}

	TransitionActor->GetImageRenderer()->ActiveOff();
	BottomText->GetTextRenderer()->ActiveOff();
	ChapterBG->BackGroundChange(ChapterBG->GetName() + ".png");
	PlayerHero->StateChange(EHeroState::Victory);

	for (Demon* ChapterDemon : AllChapterDemon)
	{
		ChapterDemon->StateChange(EDemonState::Victory);
	}

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

void ChapterManager::CameraPosUpdate(const FVector& _Pos)
{
	if (true == IsCameraPosUpdateOn)
	{
		AddCameraPos(_Pos);
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

bool ChapterManager::IsKeyPoint()
{
	if (nullptr == Key)
	{
		return false;
	}

	return PlayerHero->GetNextLocationPoint() == Key->GetLocationPoint();
}

bool ChapterManager::IsLockBoxPoint()
{
	if (nullptr == LockBox)
	{
		return false;
	}

	return PlayerHero->GetNextLocationPoint() == LockBox->GetLocationPoint();
}

void ChapterManager::DeleteKey()
{
	if (nullptr == Key)
	{
		return;
	}

	Key->StateChange(EKeyComponentState::Death);
	Key = nullptr;
}

void ChapterManager::DeleteLockBox()
{
	if (nullptr == LockBox)
	{
		return;
	}

	LockBox->StateChange(EKeyComponentState::Death);
	LockBox = nullptr;
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