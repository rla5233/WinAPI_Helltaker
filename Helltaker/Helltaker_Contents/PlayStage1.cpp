#include "PlayStage1.h"
#include "Hero.h"
#include "Skeleton.h"

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
	StageManager::BeginPlay();

	// �������� ����
	CreateStageMap(7, 7);
	SetStageStartLocation({ 7, 7 });

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

	Hero* NewHero = SpawnActor<Hero>();
	NewHero->SetActorLocation(StagePointToLocation(6, 0));
	NewHero->SetLocationPoint({ 6, 0 });
	
	//Skeleton* NewSkeleton = SpawnActor<Skeleton>();
	//NewSkeleton->SetActorLocation(StagePointToLocation(2, 1));
	//NewSkeleton->SetLocationPoint({ 2, 1 });
}
