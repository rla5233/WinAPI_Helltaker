#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Sin_Dialogue : public RenderActor
{
public:
	// constructor destructor
	Sin_Dialogue();
	~Sin_Dialogue();

	// delete Function
	Sin_Dialogue(const Sin_Dialogue& _Other) = delete;
	Sin_Dialogue(Sin_Dialogue&& _Other) noexcept = delete;
	Sin_Dialogue& operator=(const Sin_Dialogue& _Other) = delete;
	Sin_Dialogue& operator=(Sin_Dialogue&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Down_ImageRenderer = nullptr;
	UImageRenderer* Up_ImageRenderer = nullptr;
	UImageRenderer* DarkHell_Renderer = nullptr;
	UImageRenderer* LitHell_Renderer = nullptr;

	static bool IsLoad;
};
