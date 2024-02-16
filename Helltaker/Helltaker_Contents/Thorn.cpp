#include "Thorn.h"

#include "ContentsHelper.h"
#include "ChapterManager.h"

bool Thorn::IsLoad = false;

Thorn::Thorn()
{
}

Thorn::~Thorn()
{
}

void Thorn::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Thorn", "Thorn_Idle.png");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Up");
		ContentsHelper::LoadFolder("Chapter\\Component\\Thorn", "Thorn_Down");

		IsLoad = true;
	}

	FVector TileScale = ContentsHelper::GetTileScale();
	Renderer = CreateImageRenderer(RenderOrder::Thorn);
	Renderer->SetImage("Thorn_Idle.png");
	Renderer->SetTransform({ { 0.0f, TileScale.Y * 0.05f }, { TileScale * IdleScale } });
	Renderer->CreateAnimation("Thorn_Up", "Thorn_Up", 0, 3, UpDownInter, false);
	Renderer->CreateAnimation("Thorn_Down", "Thorn_Down", 0, 4, UpDownInter, false);	
}

void Thorn::Idle(float _DeltaTime)
{}

void Thorn::IdleStart()
{
	Renderer->SetImage("Thorn_Idle.png");
}

void Thorn::Up(float _DeltaTime)
{

}

void Thorn::UpStart()
{
	Renderer->ChangeAnimation("Thorn_Up");
	GetChapter()->M_SetChapterThornInfo(Point_X, Point_Y, true);
}

void Thorn::Down(float _DeltaTime)
{

}

void Thorn::DownStart()
{
	Renderer->ChangeAnimation("Thorn_Down");
	GetChapter()->M_SetChapterThornInfo(Point_X, Point_Y, false);
}

void Thorn::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Thorn::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EThornState::Idle:
		Idle(_DeltaTime);
		break;
	case EThornState::Up:
		Up(_DeltaTime);
		break;
	case EThornState::Down:
		Down(_DeltaTime);
		break;
	}
}

void Thorn::StateChange(EThornState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EThornState::Idle:
			IdleStart();
			break;
		case EThornState::Up:
			UpStart();
			break;
		case EThornState::Down:
			DownStart();
			break;
		}
	}

	State = _State;
}