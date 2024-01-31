#pragma once
#include <vector>

#include <EngineBase/EngineMath.h>
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

	static float GetOneTileWidth()
	{ 
		return OneTileWidth;
	}

	void SetStageStartLocation(FVector _Point)
	{
		StageStartLocation = _Point * OneTileWidth;
	}

	FVector StagePointToLocation(FVector _Point);
	FVector StagePointToLocation(int _X, int _Y);

	void CreateStageMap(int _X, int _Y);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

private:
	static const float OneTileWidth;

	FVector StageStartLocation = FVector::Zero;
	
	std::vector<std::vector<bool>> StageMap;
	std::vector<std::vector<bool>> IsEmptyTile;
};
