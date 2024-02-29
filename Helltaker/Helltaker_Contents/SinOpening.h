#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class SinOpening : public HellTakerManager
{
public:
	// constructor destructor
	SinOpening();
	~SinOpening();

	// delete Function
	SinOpening(const SinOpening& _Other) = delete;
	SinOpening(SinOpening&& _Other) noexcept = delete;
	SinOpening& operator=(const SinOpening& _Other) = delete;
	SinOpening& operator=(SinOpening&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

	// Chapter
	void CutSceneStart() override;
	void ChangeChapter() override;

	// CutScene
	void Enter(float _DeltaTime) override;

private:
	void EnterOrder1();
	void EnterOrder2();
	void EnterOrder3();

	void SpawnDialogue(Scene*& _Dial, std::string_view _Name, std::string_view _ImageName);

private:
	int EnterOrder = -1;

	Scene* DialBG_DHell = nullptr;
	Scene* DialBG_LHell = nullptr;
	Scene* DialBG_Sin = nullptr;

	static const std::vector<const char*> SinOpening_Script;
	static bool IsLoad;
};
