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
	
	// ���� ��ǥ Actor���� �����ġ
	// {0, 0} => Actor ��ġ�� ���� �̹��� �߽� ��ġ
	// ���� ũ��� ���� �̹��� ũ�� ��ȯ
	Renderer->SetTransform({ {0, 0}, {70, 70} });

	// Set �̹����� ���� ��ǥ���� ���� ũ�⸸ŭ �̹����� �ڸ���.
	// �̹��� ũ�� ����� �ν��� ����
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