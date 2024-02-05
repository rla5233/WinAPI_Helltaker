#pragma once
#include <string>
#include <string_view>
#include <vector>

#include <EngineBase/EngineMath.h>
#include <EngineCore/Level.h>

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

	void SetStageStartLocation(FVector _Point);

	FVector StagePointToLocation(FVector _Point);
	FVector StagePointToLocation(int _X, int _Y);

	void CreateStageMap(int _X, int _Y);

	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

private:
	FVector StageStartLocation = FVector::Zero;
	
	std::vector<std::vector<bool>> StageMap;
	std::vector<std::vector<bool>> IsEmptyTile;
};
