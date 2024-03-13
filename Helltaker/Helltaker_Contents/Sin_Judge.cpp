#include "Sin_Judge.h"

#include "SinCutSceneManager.h"
#include "Sin_Dialogue.h"
#include "BackGround.h"

const float Sin_Judge::FadeOutDelayTime = 0.2f;

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
		case ESinJudgeState::Chap3_Fly:
			Chap3_FlyStart();
			break;
		}
	}

	State = _State;
}