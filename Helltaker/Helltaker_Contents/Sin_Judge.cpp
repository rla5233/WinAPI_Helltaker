#include "Sin_Judge.h"

#include "SinCutSceneManager.h"
#include "Sin_Dialogue.h"
#include "BackGround.h"

#include <EngineBase/EngineRandom.h>

const float Sin_Judge::FadeOutDelayTime = 0.2f;
const float Sin_Judge::BindDelayTime = 1.0f;

Sin_Judge::Sin_Judge()
{
}

Sin_Judge::~Sin_Judge()
{
}

void Sin_Judge::BeginPlay()
{
	Character::BeginPlay();
}

void Sin_Judge::Tick(float _DeltaTime)
{
	Character::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Sin_Judge::Intro_AppearStart()
{
	GetImageRenderer()->CreateAnimation("Jud_Intro", "Jud_Intro", { 0, 1, 2, 3 }, { 0.08f, 0.08f, 0.32f, 0.0f }, false);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 1.0f, 0.692f };
	FVector Pos = { 0.0f, -0.0402f };
	GetImageRenderer()->AnimationReset();
	GetImageRenderer()->ChangeAnimation("Jud_Intro");
	GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });

	OrderCount = 0;
}

void Sin_Judge::Intro_Appear()
{
	switch (OrderCount)
	{
	case 0:
		Intro_Appear1();
		break;
	case 1:
		Intro_Appear2();
		break;
	}
}

void Sin_Judge::Intro_Appear1()
{
	++OrderCount;
}

void Sin_Judge::Intro_Appear2()
{
	if (1 == GetImageRenderer()->GetCurAnimationFrame())
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.558f, 0.692f };
		GetImageRenderer()->SetScale(WinScale * Scale);
		GetSinCutSceneChapter()->C_StateChange(ESinSceneState::End);
	}

	if (3 == GetImageRenderer()->GetCurAnimationFrame())
	{
		GetSinCutSceneChapter()->C_StateChange(ESinSceneState::End);
	}

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		StateChange(ESinJudgeState::None);
	}
}


void Sin_Judge::Chap3_ChainStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Chain1Scale = { 0.448f * 0.9f, 0.278f * 0.9f };
	FVector Chain1Pos = { 0.0f, 0.14f };
	UImageRenderer* Renderer1 = AActor::CreateImageRenderer(SinRenderOrder::Mid);
	Renderer1->SetImage("Jud_BindChainF.png");
	Renderer1->SetTransform({ WinScale * Chain1Pos, WinScale * Chain1Scale });
	Renderer1->SetAlpha(0.0f);
	ChainRenderer.push_back(Renderer1);

	UImageRenderer* Renderer2 = AActor::CreateImageRenderer(SinRenderOrder::Bottom);
	Renderer2->SetImage("Jud_BindChainB.png");
	Renderer2->SetTransform({ WinScale * Chain1Pos, WinScale * Chain1Scale });
	Renderer2->SetAlpha(0.0f);
	ChainRenderer.push_back(Renderer2);

	FVector Chain2Scale = { 0.448f * 0.8f, 0.278f * 0.8f };
	FVector Chain2Pos = { 0.0f, 0.06f };
	UImageRenderer* Renderer3 = AActor::CreateImageRenderer(SinRenderOrder::Mid);
	Renderer3->SetImage("Jud_BindChainF.png");
	Renderer3->SetTransform({ WinScale * Chain2Pos, WinScale * Chain2Scale });
	Renderer3->SetAlpha(0.0f);
	ChainRenderer.push_back(Renderer3);

	UImageRenderer* Renderer4 = AActor::CreateImageRenderer(SinRenderOrder::Bottom);
	Renderer4->SetImage("Jud_BindChainB.png");
	Renderer4->SetTransform({ WinScale * Chain2Pos, WinScale * Chain2Scale });
	Renderer4->SetAlpha(0.0f);
	ChainRenderer.push_back(Renderer4);

	FVector ArmScale = { 0.658f, 0.404f };
	FVector ArmPos = { 0.0f, 0.1008f };
	ArmRenderer = AActor::CreateImageRenderer(SinRenderOrder::Mid);
	ArmRenderer->SetImage("Jud_BindAnim_002.png");
	ArmRenderer->SetTransform({ WinScale * ArmPos, WinScale * ArmScale });

	FadeInOn();
	OrderCount = 0;
}

void Sin_Judge::Chap3_Chain(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0:
		ChainFadeAppear(_DeltaTime);
		break;
	case 1:
		ChainFadeOutUpdate(_DeltaTime);
		break;
	case 2:
		ChainFadeInUpdate(_DeltaTime);
		break;
	}
}

void Sin_Judge::ChainFadeAppear(float _DeltaTime)
{
	for (UImageRenderer* Chain : ChainRenderer)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		FadeInUpdate(Chain, _DeltaTime, 0.5f);
	}

	if (false == IsFadeInOn())
	{
		FadeOutOn();
		TimeCount = FadeOutDelayTime;
		++OrderCount;
	}
}

void Sin_Judge::ChainFadeOutUpdate(float _DeltaTime)
{
	if (0.0f <= TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	for (UImageRenderer* Chain : ChainRenderer)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		FadeOutUpdate(Chain, _DeltaTime, 0.2f, 1.0f, 0.5f);
	}

	if (false == IsFadeOutOn())
	{
		FadeInOn();
		OrderCount = 2;
	}
}

void Sin_Judge::ChainFadeInUpdate(float _DeltaTime)
{
	for (UImageRenderer* Chain : ChainRenderer)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		FadeInUpdate(Chain, _DeltaTime, 0.3f, 0.5, 1.0f);
	}

	if (false == IsFadeInOn())
	{
		FadeOutOn();
		TimeCount = FadeOutDelayTime;
		OrderCount = 1;
	}
}

void Sin_Judge::Chap3_BindStart()
{
	ChainRendererRemove();
	ArmRendererRemove();

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { 0.554f, 0.693f };
	FVector Pos = { 0.0f, 0.0f };
	GetImageRenderer()->CreateAnimation(
		"Bind_Start", 
		"Jud_BindAnim", 
		{ 0, 1, 2, 3, 4, 5 },
		{ 0.1f, 0.8f, 0.1f, 0.1f, 0.1f, 0.1f },
		false);

	GetImageRenderer()->CreateAnimation(
		"SingleBind",	
		"Jud_BindAnim",
		{ 5, 6, 7, 6, 5 },
		{ 0.08f, 0.8f, 0.08f, 0.08f, 0.08f },
		false);

	GetImageRenderer()->CreateAnimation(
		"DoubleBind",
		"Jud_BindAnim",
		{ 5, 6, 7, 6, 7, 6, 5 },
		{ 0.08f, 0.1f, 0.1f, 0.6f, 0.08f, 0.08f, 0.08f },
		false);

	GetImageRenderer()->AnimationReset();
	GetImageRenderer()->ChangeAnimation("Bind_Start");
	GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });

	BindBSoundPlay = true;
	BindASoundPlay = true;
	TimeCount = 0.7f;
	OrderCount = 0;
}

void Sin_Judge::Chap3_Bind(float _DeltaTime)
{
	switch (OrderCount)
	{
	case 0:
		Chap3_Bind1(_DeltaTime);
		break;
	case 1:
		Chap3_Bind2(_DeltaTime);
		break;
	case 2:
		Chap3_Bind3(_DeltaTime);
		break;
	case 3:
		Chap3_Bind4(_DeltaTime);
		break;
	case 4:
		Chap3_Bind5(_DeltaTime);
		break;
	}
}

void Sin_Judge::Chap3_Bind1(float _DeltaTime)
{
	if (0.0f <= TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	if (3 == GetImageRenderer()->GetCurAnimationFrame()
		&& true == BindBSoundPlay)
	{
		UEngineSound::SoundPlay("chainMoveB_001.wav");
		BindBSoundPlay = false;
	}

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		GetImageRenderer()->AnimationReset();
		GetImageRenderer()->ChangeAnimation("DoubleBind");
		BindBSoundPlay = true;
		++OrderCount;
	}
}

void Sin_Judge::Chap3_Bind2(float _DeltaTime)
{
	DoubleChainSound();

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		TimeCount = BindDelayTime;
		++OrderCount;
	}
}

void Sin_Judge::Chap3_Bind3(float _DeltaTime)
{
	if (0.0f <= TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	DoubleChainSound();

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		GetImageRenderer()->AnimationReset();
		GetImageRenderer()->ChangeAnimation("SingleBind");

		TimeCount = BindDelayTime;
		++OrderCount;
	}
}

void Sin_Judge::Chap3_Bind4(float _DeltaTime)
{
	SingleChainSound();

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		GetImageRenderer()->AnimationReset();
		GetImageRenderer()->ChangeAnimation("DoubleBind");
		++OrderCount;
	}
}

void Sin_Judge::Chap3_Bind5(float _DeltaTime)
{
	DoubleChainSound();

	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		TimeCount = BindDelayTime;
		OrderCount = 2;
	}
}

void Sin_Judge::ChainRendererRemove()
{
	for (UImageRenderer* Chain : ChainRenderer)
	{
		if (nullptr == Chain)
		{
			MsgBoxAssert("Renderer is nullptr");
		}

		Chain->ActiveOff();
		Chain->Destroy();
		Chain = nullptr;
	}
}

void Sin_Judge::ArmRendererRemove()
{
	ArmRenderer->ActiveOff();
	ArmRenderer->Destroy();
	ArmRenderer = nullptr;
}

void Sin_Judge::SingleChainSound()
{
	if (1 == GetImageRenderer()->GetCurAnimationFrame()
		&& true == BindASoundPlay)
	{
		RandChainASound();
		BindASoundPlay = false;
	}

	if (1 != GetImageRenderer()->GetCurAnimationFrame())
	{
		BindASoundPlay = true;
	}

	if (3 == GetImageRenderer()->GetCurAnimationFrame()
		&& true == BindBSoundPlay)
	{	
		RandChainBSound();
		BindBSoundPlay = false;
	}

	if (3 != GetImageRenderer()->GetCurAnimationFrame())
	{
		BindBSoundPlay = true;
	}
}

void Sin_Judge::DoubleChainSound()
{
	if (1 == GetImageRenderer()->GetCurAnimationFrame()
		&& true == BindASoundPlay)
	{
		RandChainASound();
		BindASoundPlay = false;
	}

	if (4 == GetImageRenderer()->GetCurAnimationFrame()
		&& true == BindASoundPlay)
	{
		RandChainASound();
		BindASoundPlay = false;
	}

	if (1 != GetImageRenderer()->GetCurAnimationFrame()
	 && 4 != GetImageRenderer()->GetCurAnimationFrame())
	{
		BindASoundPlay = true;
	}

	if (5 == GetImageRenderer()->GetCurAnimationFrame()
		&& true == BindBSoundPlay)
	{
		RandChainBSound();
		BindBSoundPlay = false;
	}
	
	if (5 != GetImageRenderer()->GetCurAnimationFrame())
	{
		BindBSoundPlay = true;
	}
}

void Sin_Judge::RandChainBSound()
{
	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);
	switch (RandomValue)
	{
	case 1:
		UEngineSound::SoundPlay("chainMoveB_001.wav");
		break;
	case 2:
		UEngineSound::SoundPlay("chainMoveB_002.wav");
		break;
	}
}

void Sin_Judge::RandChainASound()
{
	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);
	switch (RandomValue)
	{
	case 1:
		UEngineSound::SoundPlay("chainMoveA_001.wav");
		break;
	case 2:
		UEngineSound::SoundPlay("chainMoveA_002.wav");
		break;
	}
}

void Sin_Judge::Chap3_FlyStart()
{	
	GetImageRenderer()->CreateAnimation("Jud_Pose", "Jud_Pose", 0, 2, 0.02f, false);
	GetImageRenderer()->CreateAnimation("Jud_Fly", "Jud_Fly", 0, 4, 0.01f, false);

	GetImageRenderer()->AnimationReset();
	GetImageRenderer()->ChangeAnimation("Jud_Pose");
	OrderCount = 0;
}

void Sin_Judge::Chap3_Fly()
{
	switch (OrderCount)
	{
	case 0:
		Chap3_Fly1();
		break;
	case 1 :
		StateChange(ESinJudgeState::None);
		break;
	}
}

void Sin_Judge::Chap3_Fly1()
{
	if (true == GetImageRenderer()->IsCurAnimationEnd())
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector Scale = { 0.265f, 0.626f};
		FVector Pos = { 0.0f, -0.05f };
		GetImageRenderer()->SetTransform({ WinScale * Pos, WinScale * Scale });
		GetImageRenderer()->AnimationReset();
		GetImageRenderer()->ChangeAnimation("Jud_Fly");

		FVector EffectScale = { 0.885f, 1.574f };
		PentaRenderer = RenderActor::CreateImageRenderer(SinRenderOrder::UnderBackGround);
		PentaRenderer->SetImage("PentaGraphic.png");
		PentaRenderer->SetTransform({ WinScale * Pos, WinScale * EffectScale });

		GetSinCutSceneChapter()->C_GetDialogue()->StateChange(ESinDialogueState::Move);
		GetSinCutSceneChapter()->C_GetUpBG()->AllRenderersActiveOff();

		++OrderCount;
	}
}

void Sin_Judge::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinJudgeState::Intro_Appear:
		Intro_Appear();
		break;
	case ESinJudgeState::Chap3_Chain:
		Chap3_Chain(_DeltaTime);
		break;
	case ESinJudgeState::Chap3_Bind:
		Chap3_Bind(_DeltaTime);
		break;
	case ESinJudgeState::Chap3_Fly:
		Chap3_Fly();
		break;
	}
}

void Sin_Judge::StateChange(ESinJudgeState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinJudgeState::Intro_Appear:
			Intro_AppearStart();
			break;
		case ESinJudgeState::Chap3_Chain:
			Chap3_ChainStart();
			break;
		case ESinJudgeState::Chap3_Bind:
			Chap3_BindStart();
			break;
		case ESinJudgeState::Chap3_Fly:
			Chap3_FlyStart();
			break;
		}
	}

	State = _State;
}