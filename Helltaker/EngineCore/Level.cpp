#include "Level.h"
#include "Actor.h"

ULevel::ULevel()
{}

ULevel::~ULevel()
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (nullptr == Actor)
			{
				continue;
			}

			delete Actor;
			Actor = nullptr;
		}
	}
}

void ULevel::ActorTick(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (false == Actor->IsOn())
			{
				continue;
			}

			Actor->Tick(_DeltaTime);
		}
	}
}


void ULevel::ActorInit(AActor* _NewActor)
{
	// 생성자에서는 레벨이 세팅되지 않아서 Get
	_NewActor->SetWorld(this);
	_NewActor->BeginPlay();
}
