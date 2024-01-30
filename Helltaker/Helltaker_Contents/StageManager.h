#pragma once
#include <vector>
#include <EngineCore/Level.h>

// ���� : Stage ���� Ŭ����
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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

private:
	const float OneBlockDistance = 60.0f;
	std::vector<std::vector<bool>> IsEmptyTile;

};
