#pragma once
#include <string>
#include <string_view>
#include <EngineBase\EnginePath.h>
#include <map>

// #include나 이런걸 사용하더라도 실제로 그 코드가 실행되지 않으면
// 컴파일러가 무시한다.
#include "ThirdParty\FMOD\inc\fmod.hpp"

// 이녀석은 선생님 본래 관리 방식을 보여드리겠습니다.

class UEngineSoundPlayer
{
	friend class UEngineSound;

public:
	void On()
	{
		Control->setPaused(false);
	}
	void Off()
	{
		Control->setPaused(true);
	}

	void Loop(int Count = -1)
	{
		Control->setLoopCount(Count);
	}


	void OnOffSwitch()
	{
		bool Check = false;
		Control->getPaused(&Check);

		if (true == Check)
		{
			Control->setPaused(false);
		}
		else {
			Control->setPaused(true);
		}
	}


	void SetLoop(int Count);
	void SetVolume(float _Volume);

private:
	// 이게 사운드 재생에 대한 권한 입니다.
	FMOD::Channel* Control = nullptr;
};

// 설명 :
class UEngineSound
{
	friend class ResControl;
private:
	static std::map<std::string, UEngineSound*> Resources;

public:
	// constrcuter destructer
	UEngineSound();
	~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static UEngineSoundPlayer SoundPlay(std::string_view _Name);

	static void Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static void Load(std::string_view _Path, std::string_view _Name);
	static void Update();

protected:
	void ResLoad(std::string_view _Path);

private:
	FMOD::Sound* SoundHandle = nullptr;

	static void ResourcesRelease();
};

