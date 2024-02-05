#include "Hero.h"

#include "ContentsHelper.h"

#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>


Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::BeginPlay()
{
	MoveActor::BeginPlay();
	
	// 여기 부터 Test
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Characters\\Chapter\\Hero");
	UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.AppendPath("Right_Idle"));

	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Right_Idle");
	Renderer->SetTransform({ {0,0}, {90, 90} });
	Renderer->CreateAnimation("Right_Idle", "Right_Idle", 0, 11, 0.07f, true);
	Renderer->ChangeAnimation("Right_Idle");
}

void Hero::LoadRenderImage(std::string_view _Name)
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Stage\\Hero");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.GetFullPath() + "\\" + _Name.data());
}

void Hero::SetRenderImage(std::string_view _Name)
{
	FVector Scale = ContentsHelper::GetWindowScale();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage(_Name);
	Renderer->SetTransform({ {0, 0}, {Scale.X / 20, Scale.Y / 10 } });
	Renderer->SetImageCuttingTransform({ {0, 0}, {89, 92} });
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	MoveCheck(_DeltaTime);
	MoveOneBlock(_DeltaTime);
}