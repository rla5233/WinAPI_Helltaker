#pragma once
#include "EnginePath.h"
#include <list>

class UEngineFile;
// 설명 :
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineDirectory();
	UEngineDirectory(const UEnginePath& _Path);
	~UEngineDirectory();

	// delete Function
	//UEngineDirectory(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	void MoveToSearchChild(std::string_view _Path);

	// AAA.Png;
	// AAA.pNg;

	/// <summary>
	/// 파일을 전부다 찾아주는 함수
	/// </summary>
	/// <param name="_Ext">확장자들 소문자 대문자 가리지 않음.</param>
	/// <param name="_Rescursive">하위 폴더까지 다 뒤질꺼냐.</param>
	/// <returns></returns>
	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

	// std::list<UEnginePath> AllPath(bool _Recursive = false);

	// 미래를 생각하지 않는 노가다 방식
	std::list<UEngineDirectory> AllDirectory(bool _Recursive = false);

	UEngineFile NewFile(std::string_view FileName);

protected:

private:
	void AllDirectoryRecursive(const std::string_view _Path, std::list<UEngineDirectory>& _Result, bool _Recursive = false);
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};

