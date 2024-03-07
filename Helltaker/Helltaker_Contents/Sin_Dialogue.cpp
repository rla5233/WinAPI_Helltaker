#include "Sin_Dialogue.h"

#include "SinCutSceneManager.h"
#include "Sin_Judge.h"

bool Sin_Dialogue::IsLoad = false;

const FVector Sin_Dialogue::HellScale = { 1.021f, 0.7592f };
const FVector Sin_Dialogue::DownSinScale = { 1.021f, 0.504f };
const FVector Sin_Dialogue::UpSinScale = { 1.021f, 0.626f };
const float Sin_Dialogue::PosType_0 = -0.034f;
const float Sin_Dialogue::PosType_1 = -0.654f;


Sin_Dialogue::Sin_Dialogue()
{
}

Sin_Dialogue::~Sin_Dialogue()
{
}

void Sin_Dialogue::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_LitHell.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Sin_001.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Sin_002.png");

		IsLoad = true;
	}

	DarkHell_Renderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	LitHell_Renderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	Down_ImageRenderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	Up_ImageRenderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	
	SetHell();
}

void Sin_Dialogue::SetHell()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosY = WinScale.Y * (0.032f);
	DarkHell_Renderer->SetImage("DialBG_DarkHell.png");
	DarkHell_Renderer->SetTransform({ { 0.0f, PosY }, WinScale * HellScale });

	LitHell_Renderer->SetImage("DialBG_LitHell.png");
	LitHell_Renderer->SetTransform({ { 0.0f, PosY }, WinScale * HellScale });
	LitHell_Renderer->ActiveOff();
}

void Sin_Dialogue::SetSin(int _PosType)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float UpPosY = 0.0f;

	PosType = _PosType;
	switch (PosType)
	{
	case 1:
		UpPosY = WinScale.Y * PosType_1;
		break;
	default:
		UpPosY = WinScale.Y * PosType_0;
		break;
	}

	Up_ImageRenderer->SetImage("DialogueBG_Sin_001.png");
	Up_ImageRenderer->SetTransform({ { 0.0f, UpPosY }, WinScale * UpSinScale });
	
	float DownPosY = UpPosY + WinScale.Y * (0.564f);
	Down_ImageRenderer->SetImage("DialogueBG_Sin_002.png");
	Down_ImageRenderer->SetTransform({ { 0.0f, DownPosY }, WinScale * DownSinScale });
}

void Sin_Dialogue::IdleStart()
{
}

void Sin_Dialogue::Idle(float _DeltaTime)
{
}

void Sin_Dialogue::LightningStart()
{
	LitHell_Renderer->ActiveOn();
	FadeOutOn();
}

void Sin_Dialogue::Lightning(float _DeltaTime)
{
	FadeOutUpdate(LitHell_Renderer, _DeltaTime);

	if (false == IsFadeOutOn())
	{
		LitHell_Renderer->ActiveOff();
 		
		GetSinCutSceneChapter()->GetJudge()->StateChange(ESinJudgeState::Intro_Appear);
 		StateChange(ESinDialogueState::Move);
	}
}

void Sin_Dialogue::MoveStart()
{
	SetImageRendererMove();
}

void Sin_Dialogue::Move(float _DeltaTime)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	ImgMoveUpdate(	
		{ Up_ImageRenderer , Down_ImageRenderer }, 
		{ StartPos, {StartPos.X, StartPos.Y + WinScale.Y * (0.564f)} },
		{ TargetPos, {TargetPos.X, TargetPos.Y + WinScale.Y * (0.564f)} },
		_DeltaTime, 
		4.0f);

	if (false == IsImgMoveOn())
	{
		StateChange(ESinDialogueState::Idle);
	}
}

void Sin_Dialogue::SetImageRendererMove()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = Up_ImageRenderer->GetPosition();

	StartPos = CurPos;

	switch (PosType)
	{
	case 1:
		TargetPos = { CurPos.X,  WinScale.Y * PosType_0 };
		PosType = 0;
		break;
	default:
		TargetPos = { CurPos.X,  WinScale.Y * PosType_1 };
		PosType = 1;
		break;
	}

	ImgMoveOn();
}

void Sin_Dialogue::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Sin_Dialogue::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinDialogueState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinDialogueState::Lightning:
		Lightning(_DeltaTime);
		break;
	case ESinDialogueState::Move:
		Move(_DeltaTime);
		break;
	}
}

void Sin_Dialogue::StateChange(ESinDialogueState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinDialogueState::Idle:
			IdleStart();
			break;
		case ESinDialogueState::Lightning:
			LightningStart();
			break;
		case ESinDialogueState::Move:
			MoveStart();
			break;
		}
	}

	State = _State;
}
