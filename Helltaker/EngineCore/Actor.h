#pragma once
#include <EngineBase\Transform.h>
#include "TickObject.h"
#include <EngineBase\NameObject.h>
#include "ImageRenderer.h"
#include "Collision.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class UImageRenderer;
class UCollision;

// 설명 : A가 붙은 오브젝트는 화면에 위치가 존재해야한다.
// Level->SpawnActor를 통해서 만들면
// 레벨이 자연스럽게 자신의 관리하에 두고 언제나 Tick을 실행해준다.
class AActor : public UNameObject, public UTickObject
{
	friend ULevel;

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	FVector GetActorLocation()
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	ULevel* GetWorld()
	{
		return World;
	}

	template<typename EnumType>
	UCollision* CreateCollision(EnumType _Order = 0)
	{
		return CreateCollision(static_cast<int>(_Order));
	}

	template<typename EnumType>
	UImageRenderer* CreateImageRenderer(EnumType _Order = 0)
	{
		return CreateImageRenderer(static_cast<int>(_Order));
	}

	UCollision* CreateCollision(int _Order = 0);
	UImageRenderer* CreateImageRenderer(int _Order = 0);

	void Destroy(float _DestroyTime = 0.0f) override;
	void DestroyUpdate(float _DeltaTime) override;

	void ActiveUpdate(float _DeltaTime) override;

	void CheckReleaseChild();

	void AllRenderersActiveOff();
	void AllRenderersActiveOn();

	void SetActive(bool _Active, float _ActiveTime = 0.0f) override;

protected:
	void Tick(float _DeltaTime) override;
	void ChildTick(float _DeltaTime);

private:
	std::list<UImageRenderer*> Renderers;
	std::list<UCollision*> Collisions;

	ULevel* World = nullptr;
	FTransform Transform = FTransform();

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

