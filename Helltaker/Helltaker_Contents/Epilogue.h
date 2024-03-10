#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class Epilogue : public HellTakerManager
{
public:
	// constructor destructor
	Epilogue();
	~Epilogue();
	
	// delete Function
	Epilogue(const Epilogue& _Other) = delete;
	Epilogue(Epilogue&& _Other) noexcept = delete;
	Epilogue& operator=(const Epilogue& _Other) = delete;
	Epilogue& operator=(Epilogue&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;

private:
	

	static const std::vector<const char*> Epilogue_Script;
	static bool IsLoad;
};

