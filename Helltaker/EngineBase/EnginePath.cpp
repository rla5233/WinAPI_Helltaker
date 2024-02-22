#include "EnginePath.h"
#include "EngineDebug.h"
#include <Windows.h>

UEnginePath::UEnginePath()
	: Path(std::filesystem::current_path())
{
	// 과거의 방식
	//char Arr[100];
	//GetCurrentDirectoryA(100, Arr);
	//StringPath = Arr;

	// 내부에서는 윈도우의 함수를 사용하고 있다
	// 내부에서 
}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

UEnginePath::~UEnginePath()
{
}

std::string UEnginePath::GetExtension() const
{
	std::filesystem::path Text = Path.extension();
	return Text.string();
}

std::string UEnginePath::GetFileName() const
{
	std::filesystem::path Text = Path.filename();
	return Text.string();
}

void UEnginePath::Move(std::string_view _Path)
{
	std::filesystem::path NextPath = Path;
	NextPath.append(_Path);

	bool Check = std::filesystem::exists(NextPath);
	if (false == Check)
	{
		MsgBoxAssert(NextPath.string() + "라는 경로는 존재하지 않습니다");
	}

	Path = NextPath;
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

bool UEnginePath::IsFile()
{
	return !std::filesystem::is_directory(Path);
}
bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

std::string UEnginePath::AppendPath(std::string_view _Path)
{
	return Path.string() + "\\" + std::string(_Path);
}