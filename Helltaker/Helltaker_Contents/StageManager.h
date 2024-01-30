#pragma once
#include <vector>
#include <EngineCore/Level.h>

// 설명 : Stage 생성 클래스
class StageManager : public ULevel
{
public:
	// constructor destructor
	StageManager();
	~StageManager();

	// delete Function
	StageManager(const StageManager& _Other) = delete;
	StageManager(StageManager&& _Other) noexcept = delete;
	StageManager& operator=(const StageManager& _Other) = delete;
	StageManager& operator=(StageManager&& _Other) noexcept = delete;

	static float GetOneTileDistance()
	{ 
		return OneTileDistance;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

private:
	static const float OneTileDistance;

	std::vector<std::vector<bool>> IsEmptyTile;
};
