#include "SinOpening.h"

#include "Character.h"
#include "Scene.h"

bool SinOpening::IsLoad = false;
const std::vector<const char*> SinOpening::SinOpening_Script =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "고위 기소관 저지먼트",
	/* 2  Script 1  */ "마치 천 번은 죽은 것 같은 느낌이다. 하지만 불길은\n사그라들고... 어찌됐든 당신은 아직 살아있는 것 같다.",
	/* 3  Script 2  */ "칩입자 녀석, 이제야 찾았다!\n넌 아직 죽을 수 없어.",
	/* 4  Script 3  */ "나와 함께 오랜 시간을 보내야 할 거다.",
	/* 5  Script 4  */ "죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!"
};

SinOpening::SinOpening()
{
}

SinOpening::~SinOpening()
{

}

void SinOpening::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Sin.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_LitHell.png");

		IsLoad = true;
	}
}

void SinOpening::LevelStart(ULevel * _PrevLevel)
{
	HellTakerManager::LevelStart(_PrevLevel);

	GetTransitionActor()->GetImageRenderer()->ActiveOn();
	GetTransitionActor()->GetImageRenderer()->ChangeAnimation("Transition", false, 19);

	M_StateChange(EChapterState::CutScene);
}

void SinOpening::SpawnDialogue(Scene*& _Dial, std::string_view _Name, std::string_view _ImageName)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	_Dial = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	_Dial->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.408f });
	_Dial->SetName(_Name);
	_Dial->CreateImageRenderer(RenderOrder::Scene);
	_Dial->GetImageRenderer()->SetImage(_ImageName);

	FVector ImgScale = _Dial->GetImageRenderer()->GetImage()->GetScale();
	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * 0.504f };
	_Dial->GetImageRenderer()->GetImage()->SetCuttingTransform({ {0, 0}, Scale });
	_Dial->GetImageRenderer()->SetTransform({ {0, 0}, Scale });
}

void SinOpening::CutSceneStart()
{
	CutSceneManager::CutSceneStart();
	
	C_SpawnBooper();

	C_BooperTextSet(SinOpening_Script[2]);
	C_BooperSetTextPosition(2);
	EnterOrder = 0;
}

void SinOpening::Enter(float _DeltaTime)
{
	if (true == GetTransitionActor()->GetImageRenderer()->IsCurAnimationEnd())
	{
		GetTransitionActor()->GetImageRenderer()->ActiveOff();
	}

	switch (EnterOrder)
	{
	case 0:
		EnterOrder1();
		break;
	case 1:
		EnterOrder2();
		break;
	case 2:
		EnterOrder3();
		break;
	}

	// Sample
	//{
	//	FVector WinScale = ContentsHelper::GetWindowScale();
	//	FVector ImgScale = DialBG_Sin->GetImageRenderer()->GetImage()->GetScale();
	//	FVector Scale = { WinScale.X * (ImgScale.X / 1920), WinScale.Y * 0.504f };
	//	DialBG_Sin->GetImageRenderer()->GetImage()->SetCuttingTransform({ {0, count}, Scale });
	//	++count;
	//}
}

void SinOpening::EnterOrder1()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		SpawnDialogue(DialBG_DHell, "DialBG_DHell", "DialBG_DarkHell.png");
		SpawnDialogue(DialBG_LHell, "DialBG_LHell", "DialBG_LitHell.png");
		DialBG_LHell->GetImageRenderer()->SetAlpha(0);
		SpawnDialogue(DialBG_Sin, "DialBG_Sin", "DialogueBG_Sin.png");

		C_SpawnCharacter("???", "DefaultBG.png", SinOpening_Script[0]);
		C_GetSceneCharacter()->GetImageRenderer()->ActiveOff();
		C_BooperTextSet(SinOpening_Script[3]);
		++EnterOrder;
	}
}

void SinOpening::EnterOrder2()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(SinOpening_Script[4]);
		C_BooperSetTextPosition(1);
		++EnterOrder;
	}
}

void SinOpening::EnterOrder3()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		DialBG_LHell->GetImageRenderer()->SetAlpha(1);
		DialBG_LHell->GetImageRenderer();
	}
}

void SinOpening::ChangeChapter()
{

}

