#include "EngineFile.h"
#include "EngineDebug.h"
#include "EngineSerializer.h"

UEngineFile::UEngineFile()
{
}

UEngineFile::UEngineFile(std::filesystem::path _Path)
	: UEnginePath(_Path)
{

}

UEngineFile::~UEngineFile()
{
	Close();
}

void UEngineFile::Close()
{
	if (nullptr != FileHandle)
	{
		fclose(FileHandle);
	}
}

void UEngineFile::Open(IOOpenMode _OpenType, IODataType _DataType)
{
	std::string Path = GetFullPath();

	std::string Mode;

	switch (_OpenType)
	{
	case IOOpenMode::Write:
		OpenMode = IOOpenMode::Write;
		Mode += "w";
		break;
	case IOOpenMode::Read:
		OpenMode = IOOpenMode::Read;
		Mode += "r";
		break;
	default:
		break;
	}

	switch (_DataType)
	{
	case IODataType::Binary:
		Mode += "b";
		break;
	case IODataType::Text:
		Mode += "t";
		break;
	default:
		break;
	}

	fopen_s(&FileHandle, Path.c_str(), Mode.c_str());

	if (nullptr == FileHandle)
	{
		MsgBoxAssert("파일 오픈에 실패했습니다" + Path);
	}
}

void UEngineFile::Save(UEngineSerializer& _Data)
{
	std::vector<char>& SaveData = _Data.Data;

	if (OpenMode != IOOpenMode::Write)
	{
		MsgBoxAssert("쓰기 모드로 오픈하지 않은 파일로 쓰려고 했습니다.");
	}

	char* StartPtr = &SaveData[0];
	fwrite(StartPtr, SaveData.size(), 1, FileHandle);
}

__int64 UEngineFile::GetFileSize()
{
	return static_cast<int>(std::filesystem::file_size(Path));
}

void UEngineFile::Load(UEngineSerializer& _Data)
{
	if (OpenMode != IOOpenMode::Read)
	{
		MsgBoxAssert("읽기 모드로 오픈하지 않은 파일로 읽으려고 했습니다.");
	}

	__int64 Size = GetFileSize();
	_Data.BufferResize(static_cast<int>(Size));
	fread(&_Data.Data[0], Size, 1, FileHandle);
}