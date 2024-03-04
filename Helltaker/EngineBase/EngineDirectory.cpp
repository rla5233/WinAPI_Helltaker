#include "EngineDirectory.h"
#include "EngineFile.h"
#include "EngineString.h"
#include "EngineDebug.h"

UEngineDirectory::UEngineDirectory()
{
}

UEngineDirectory::UEngineDirectory(const UEnginePath& _Path)
	: UEnginePath(_Path.GetFullPath())
{

}

UEngineDirectory::~UEngineDirectory()
{
}

void UEngineDirectory::AllFileRecursive(
	const std::string_view _Path,
	std::list<UEngineFile>& _Result,
	std::vector<std::string> _Ext /*= std::vector<std::string>()*/,
	bool _Recursive /*= false*/)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = UEngineString::ToUpper(Ext.string());

		if (true == Entry.is_directory())
		{
			if (true == _Recursive)
			{
				AllFileRecursive(Path.string(), _Result, _Ext, _Recursive);
			}
			continue;
		}

		if (0 == _Ext.size())
		{
			_Result.push_back(UEngineFile(Path.string()));
			continue;
		}

		bool Check = false;

		for (size_t i = 0; i < _Ext.size(); i++)
		{
			if (_Ext[i] == UpperExt)
			{
				Check = true;
			}
		}

		if (true == Check)
		{
			_Result.push_back(UEngineFile(Path.string()));
		}

	}
}

UEngineFile UEngineDirectory::NewFile(std::string_view FileName)
{
	std::string NewFilePath = GetFullPath() + "\\" + FileName.data();
	return std::filesystem::path(NewFilePath);
}

std::list<UEngineFile> UEngineDirectory::AllFile(
	std::vector<std::string> _Ext /*= std::vector<std::string>()*/,
	bool _Rescursive /*= false*/
)
{
	std::list<UEngineFile> Result;

	for (size_t i = 0; i < _Ext.size(); i++)
	{
		_Ext[i] = UEngineString::ToUpper(_Ext[i]);
	}

	AllFileRecursive(Path.string(), Result, _Ext, _Rescursive);
	return Result;
}

std::list<UEngineDirectory> UEngineDirectory::AllDirectory(bool _Recursive/* = false*/)
{
	std::list<UEngineDirectory> Result;
	AllDirectoryRecursive(Path.string(), Result, _Recursive);
	return Result;
}

void UEngineDirectory::AllDirectoryRecursive(const std::string_view _Path, std::list<UEngineDirectory>& _Result, bool _Recursive/* = false*/)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = UEngineString::ToUpper(Ext.string());

		if (true != Entry.is_directory())
		{
			continue;
		}

		_Result.push_back(UEngineDirectory(Path));

		if (true == _Recursive)
		{
			AllDirectoryRecursive(Path.string(), _Result, _Recursive);
		}
	}
}

void UEngineDirectory::MoveToSearchChild(std::string_view _Path)
{
	while (true)
	{
		std::list<UEngineDirectory> Dir = AllDirectory();

		for (UEngineDirectory& _Dir : Dir)
		{
			std::string UpperLeft = UEngineString::ToUpper(_Dir.GetFileName());
			std::string UpperRight = UEngineString::ToUpper(_Path);

			if (UpperLeft == UpperRight)
			{
				Move(_Path);
				return;
			}
		}

		if (IsRoot())
		{
			MsgBoxAssert("루트디렉토리까지 존재하지 않는 경로 입니다." + std::string(_Path));
		}

		MoveParent();
	}
}