#pragma once
#include "EnginePath.h"
#include "EngineSerializer.h"

enum class IOOpenMode
{
	None,
	Write,
	Read,
};

enum class IODataType
{
	Binary,
	Text,
};

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

	__int64 GetFileSize();

	void Open(IOOpenMode _OpenType, IODataType _DataType);

	void Save(UEngineSerializer& _Data);
	void Load(UEngineSerializer& _Data);

	void Close();

protected:

private:
	IOOpenMode OpenMode = IOOpenMode::None;
	FILE* FileHandle = nullptr;

};

