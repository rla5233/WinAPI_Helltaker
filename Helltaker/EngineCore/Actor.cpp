#include "Actor.h"
#include "ImageRenderer.h"

AActor::AActor()
{
}

AActor::~AActor()
{
	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (nullptr == ImageRenderer)
		{
			MsgBoxAssert("이미지 랜더러가 nullptr인 상황이 있었습니다");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();

	for (UCollision* Collision : Collisions)
	{
		if (nullptr == Collision)
		{
			MsgBoxAssert("이미지 랜더러가 nullptr인 상황이 있었습니다");
		}

		delete Collision;
		Collision = nullptr;
	}

	Collisions.clear();

}

void AActor::SetActive(bool _Active, float _ActiveTime /*= 0.0f*/)
{
	UTickObject::SetActive(_Active, _ActiveTime);

	// 자신이 관리하고 있는 랜더러들도 다 죽여야 한다.
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->SetActive(_Active, _ActiveTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->SetActive(_Active, _ActiveTime);
	}
}

void AActor::ChildTick(float _DeltaTime)
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Tick(_DeltaTime);
	}
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
}

UImageRenderer* AActor::CreateImageRenderer(int _Order /*= 0*/)
{
	UImageRenderer* Component = new UImageRenderer();
	UActorComponent* ActorCom = Component;
	ActorCom->SetOwner(this);
	ActorCom->SetOrder(_Order);
	ActorCom->BeginPlay();
	Renderers.push_back(Component);
	return Component;
}


UCollision* AActor::CreateCollision(int _Order /*= 0*/)
{
	UCollision* Component = new UCollision();
	UActorComponent* ActorCom = Component;
	ActorCom->SetOwner(this);
	ActorCom->SetOrder(_Order);
	ActorCom->BeginPlay();
	Collisions.push_back(Component);
	return Component;
}

void AActor::Destroy(float _DestroyTime /*= 0.0f*/)
{
	// 액터는 자신을 죽이면서
	UTickObject::Destroy(_DestroyTime);

	// 자신이 관리하고 있는 랜더러들도 다 죽여야 한다.
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Destroy(_DestroyTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->Destroy(_DestroyTime);
	}

}

void AActor::CheckReleaseChild()
{

	{
		std::list<UImageRenderer*>::iterator StartIter = Renderers.begin();
		std::list<UImageRenderer*>::iterator EndIter = Renderers.end();

		for (; StartIter != EndIter;)
		{
			UImageRenderer* Renderer = StartIter.operator*();

			if (nullptr == Renderer)
			{
				MsgBoxAssert("Collision가 nullptr인 경우가 존재했습니다");
				return;
			}

			if (false == Renderer->IsDestroy())
			{
				++StartIter;
				continue;
			}

			delete Renderer;
			Renderer = nullptr;
			StartIter = Renderers.erase(StartIter);
		}
	}

	{
		std::list<UCollision*>::iterator StartIter = Collisions.begin();
		std::list<UCollision*>::iterator EndIter = Collisions.end();

		for (; StartIter != EndIter;)
		{
			UCollision* Collision = StartIter.operator*();

			if (nullptr == Collision)
			{
				MsgBoxAssert("Collision가 nullptr인 경우가 존재했습니다");
				return;
			}

			if (false == Collision->IsDestroy())
			{
				++StartIter;
				continue;
			}

			delete Collision;
			Collision = nullptr;
			StartIter = Collisions.erase(StartIter);
		}
	}
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	// 부모의 함수를 호출하는게 기본이다.
	UTickObject::DestroyUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->DestroyUpdate(_DeltaTime);
	}
}

void AActor::ActiveUpdate(float _DeltaTime)
{
	// 부모의 함수를 호출하는게 기본이다.
	UTickObject::ActiveUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveUpdate(_DeltaTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->ActiveUpdate(_DeltaTime);
	}
}

void AActor::AllRenderersActiveOff()
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveOff();
	}
}

void AActor::AllRenderersActiveOn()
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveOn();
	}
}