#include "Level.h"
#include "Actor.h"
#include <EngineBase\EngineDebug.h>
#include "EngineDebug.h"
#include "EngineCore.h"

ULevel::ULevel()
{
}

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
	AllActor.clear();
}

void ULevel::LevelTick(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			// Ranged for는 중간에 리스트의 원소의 개수가 변경되면 굉장히 불안정해지고
			// 치명적인 오류가 발생할 가능성이 높아진다.
			// 절대로 파괴하지 
			Actor->ActiveUpdate(_DeltaTime);
			Actor->DestroyUpdate(_DeltaTime);
			if (false == Actor->IsActive())
			{
				continue;
			}

			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::LevelRender(float _DeltaTime)
{
	for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
	{
		std::list<UImageRenderer*>& RendererList = OrderListPair.second;
		for (UImageRenderer* Renderer : RendererList)
		{
			// Ranged for는 중간에 리스트의 원소의 개수가 변경되면 굉장히 불안정해지고
			// 치명적인 오류가 발생할 가능성이 높아진다.
			// 절대로 파괴하지 
			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->Render(_DeltaTime);
		}
	}

	if (true == GEngine->IsDebug())
	{
		for (std::pair<const int, std::list<UCollision*>>& OrderListPair : Collisions)
		{
			std::list<UCollision*>& RendererList = OrderListPair.second;
			for (UCollision* Collision : RendererList)
			{
				// Ranged for는 중간에 리스트의 원소의 개수가 변경되면 굉장히 불안정해지고
				// 치명적인 오류가 발생할 가능성이 높아진다.
				// 절대로 파괴하지 
				if (false == Collision->IsActive())
				{
					continue;
				}

				Collision->DebugRender(CameraPos);
			}
		}
		UEngineDebug::PrintDebugText(GEngine->MainWindow.GetBackBufferImage());
	}
}

void ULevel::LevelRelease(float _DeltaTime)
{
	// Tick
	// 랜더링
	// 충돌 등등등이 다 끝나고.

	// 여기서 지우는데.
	// Render의 메모리의 결정권을 가진것은 액터입니다.
	// 앞으로 포인터를 굉장히 여러개로 나눠서 사용하는 경우가 많습니다.
	// 그러면 누가 이에 대한 삭제를 담당해야 하나요?
	// 이건 정답이 없지만 선생님은 만든놈이 하자.
	// new를 한 놈이 한다.


	{
		for (std::pair<const int, std::list<UCollision*>>& OrderListPair : Collisions)
		{
			std::list<UCollision*>& List = OrderListPair.second;

			std::list<UCollision*>::iterator StartIter = List.begin();
			std::list<UCollision*>::iterator EndIter = List.end();

			// 삭제는 절대로 Ranged for로 하면 안되다.
			// for (UImageRenderer* Renderer : RendererList)
			for (; StartIter != EndIter; )
			{
				UCollision* Collision = StartIter.operator*();

				if (false == Collision->IsDestroy())
				{
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}

	{
		for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
		{
			std::list<UImageRenderer*>& List = OrderListPair.second;

			std::list<UImageRenderer*>::iterator StartIter = List.begin();
			std::list<UImageRenderer*>::iterator EndIter = List.end();

			// 삭제는 절대로 Ranged for로 하면 안되다.
			// for (UImageRenderer* Renderer : RendererList)
			for (; StartIter != EndIter; )
			{
				UImageRenderer* Renderer = StartIter.operator*();

				if (false == Renderer->IsDestroy())
				{
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}


	// 선생님은 절대로 실행도중 삭제를 하지 않습니다.
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;

		std::list<AActor*>::iterator StartIter = ActorList.begin();
		std::list<AActor*>::iterator EndIter = ActorList.end();

		for (; StartIter != EndIter;)
		{
			AActor* Actor = StartIter.operator*();

			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor가 nullptr인 경우가 존재했습니다");
				return;
			}

			if (false == Actor->IsDestroy())
			{
				Actor->CheckReleaseChild();
				++StartIter;
				continue;
			}

			delete Actor;
			Actor = nullptr;
			StartIter = ActorList.erase(StartIter);
		}
	}
}


void ULevel::ActorInit(AActor* _NewActor)
{
	// 생성자에서는 레벨이 세팅되지 않아서 Get
	_NewActor->SetWorld(this);
	_NewActor->BeginPlay();
}


