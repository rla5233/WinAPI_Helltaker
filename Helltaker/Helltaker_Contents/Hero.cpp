#include "Hero.h"

#include "Helltaker_ContentsCore.h"

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
	RenderActor::BeginPlay();
	
	LoadAndSetRenderImage("Hero0022.bmp");
}

void Hero::LoadRenderImage(std::string_view _Name)
{
	RenderActor::LoadRenderImage(_Name);

	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources\\Stage\\Hero");
	UEngineResourcesManager::GetInst().LoadImg(ResourcesPath.GetFullPath() + "\\" + _Name.data());
}

void Hero::SetRenderImage(std::string_view _Name)
{
	RenderActor::SetRenderImage(_Name);

	FVector Scale = Helltaker_ContentsCore::GetWindowScale();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage(_Name);
	Renderer->SetTransform({ {0, 0}, {Scale.X / 20, Scale.Y / 10 } });
	Renderer->SetImageCuttingTransform({ {0, 0}, {89, 92} });
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);
	RenderActor::Tick(_DeltaTime);

	MoveCheck(_DeltaTime);
	MoveOneBlock(_DeltaTime);
}