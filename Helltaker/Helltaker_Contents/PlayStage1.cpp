#include "PlayStage1.h"
#include "Player.h"
#include "Monster.h"

#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

UPlayStage1::UPlayStage1()
{
}

UPlayStage1::~UPlayStage1()
{
}

void UPlayStage1::BeginPlay()
{
	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");

	std::list<UEngineFile> AllFileList = ResourcesPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	FVector Location;
	Player* NewPlayer = SpawnActor<Player>();
	Location = FVector(5, 5) * StageManager::GetOneTileDistance();
	NewPlayer->SetActorLocation(Location);
	
	Monster* NewMonster = SpawnActor<Monster>();
	Location = FVector(10, 10) * StageManager::GetOneTileDistance();
	NewMonster->SetActorLocation(Location);
}
