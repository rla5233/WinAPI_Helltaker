#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class BackGround : public AActor
{
public:
	// constructor destructor
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void LoadStageBackGround(std::string_view _Name);

protected:

private:
	UImageRenderer* Renderer = nullptr;

};
