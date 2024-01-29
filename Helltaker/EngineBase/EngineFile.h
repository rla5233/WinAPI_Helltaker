#pragma once
#include "EnginePath.h"

// Ό³Έν :
class UEngineFile : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineFile();
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

	// delete Function
	//UEngineFile(const UEngineFile& _Other) = delete;
	//UEngineFile(UEngineFile&& _Other) noexcept = delete;
	//UEngineFile& operator=(const UEngineFile& _Other) = delete;
	//UEngineFile& operator=(UEngineFile&& _Other) noexcept = delete;

protected:

private:

};

