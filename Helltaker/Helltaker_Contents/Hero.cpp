#include "Hero.h"

#include <EngineCore/EngineCore.h>


Hero::Hero()
{}

Hero::~Hero()
{}

void Hero::BeginPlay()
{
	MoveActor::BeginPlay();

	Renderer = CreateImageRenderer(0);
	Renderer->SetImage("Hero0022.bmp");
	
	// 앞의 좌표 Actor와의 상대위치
	// {0, 0} => Actor 위치가 렌더 이미지 중심 위치
	// 뒤의 크기로 렌더 이미지 크기 변환
	Renderer->SetTransform({ {0, 0}, {70, 70} });

	// Set 이미지의 앞의 좌표부터 뒤의 크기만큼 이미지를 자른다.
	// 이미지 크기 벗어나면 인식을 못함
	Renderer->SetImageCuttingTransform({ {0, 0}, {89, 92} });
	
	
	//HeroRenderer->SetImageToScale("Hero0022.bmp");
	//HeroRenderer->SetImageCuttingTransform();
}

void Hero::Tick(float _DeltaTime)
{
	MoveActor::Tick(_DeltaTime);

	MoveCheck(_DeltaTime);
	MoveOneBlock(_DeltaTime);
}