#include "EngineDirectory.h"
#include "EngineFile.h"
#include "EngineString.h"

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


	// const Monster& NewMonster;
	// NewMonster.Fight
	// NewMonster.Damage

	// const std::filesystem::directory_entry& Entry
	// Entry.

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		// Entry 디렉토리의 정보를 담고 있는 C++이 지원해주는 객체입니다.
		// 객체는 우리가 고민할 필요가 없다.
		// 객체라면 우리가 할껀 .찍어보는것 밖에 없다.

		// 특정 경로 안에 있는 또다른 폴더
		// 폴더라는 거네
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