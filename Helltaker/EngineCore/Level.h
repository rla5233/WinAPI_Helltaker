#pragma once
#include <EngineBase\NameObject.h>
#include <map>
#include <list>

class AActor;
class UEngineCore;
class UImageRenderer;
// 설명 : U는 그냥 엔진 속해있다는 것을 의미.
class ULevel : public UNameObject
{

	friend UEngineCore;
	friend UImageRenderer;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

	// 어떠한 레벨이 시작할때마다 실행됩니다.
	// 이전레벨이 들어온다.
	virtual void LevelStart(ULevel* _PrevLevel) {};

	// 내가 현재 실행되고 있는 레벨인데.
	// 그 레벨이 끝나는 순간 실행된다.
	virtual void LevelEnd(ULevel* _NextLevel) {};

	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}



protected:

private:
	std::map<int, std::list<AActor*>> AllActor;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);

	std::map<int, std::list<UImageRenderer*>> Renderers;
};

