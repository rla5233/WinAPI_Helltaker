#pragma once
#include <string>
#include <string_view>
#include <map>


// class Monster 싱글톤이라면 메모리적으로 
// class Monster가 딱 1개만 만들어질수 있어야 한다.

// class UEngineResourcesManager 싱글톤이라면 메모리적으로 
// class UEngineResourcesManager가 딱 1개만 만들어질수 있어야 한다.

class UImage;
// 설명 : 이미지 사운드 등등을 종합 관리할겁니다.
//       게임에서 리소스라고 불리는 객체들을 전부다 이녀석이 관리할 예정.
class UEngineResourcesManager
{
public:
	// delete Function
	UEngineResourcesManager(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager(UEngineResourcesManager&& _Other) noexcept = delete;
	UEngineResourcesManager& operator=(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager& operator=(UEngineResourcesManager&& _Other) noexcept = delete;

	// 싱글톤이라고 한다.
	static UEngineResourcesManager& GetInst()
	{
		// 지역static 싱글톤
		static UEngineResourcesManager Inst = UEngineResourcesManager();
		return Inst;
	}

	// 포인터형 싱글톤
	//static UEngineResourcesManager* GetPInst()
	//{
	//  // 포인터형의 장점
	//  // 1. 내가 삭제하고 싶을때 삭제할수 있다.
	//  // 2. new는 동적할당이죠?
	//  //    new는 가장 마지막에 마지막에 해야한다는 격언이 있다.
	//  //    ?????? 100바이트 아껴서 뭐하게?
	//	if (nullptr == pInst)
	//	{
	//		pInst = new UEngineResourcesManager();
	//	}
	//	
	//	return pInst;
	//}

	// 언제든지 싱글톤 객체를 파괴할수 있다는 장점이 있다.
	// 그럼 왜 파괴하는데?
	//static void Destroy()
	//{
	//	if (nullptr != pInst)
	//	{
	//		delete pInst;
	//		pInst = nullptr;
	//	}
	//	return;
	//}



	// 인터페이스가 없으면 너무 추상적인 생각이다.
	// 생각이 공상가식 프로그래밍.
	// 하드디스크에 있는 이미지를 로드한다.
	UImage* LoadImg(std::string_view _Path);

	UImage* FindImg(std::string_view _Name);



protected:

private:
	// constrcuter destructer
	UEngineResourcesManager();
	~UEngineResourcesManager();

	std::map<std::string, UImage*> Images;

	// C++에서는 이렇게 static으로 자기자신을 자기가 내부에서 만듭니다.
	// 자기자신이 내부에서 여러개 만들면 만들수 있죠.
	// 그걸 딱 1개만 만드는게 싱글톤의 정석
	// static UEngineResourcesManager Inst;
	// static UEngineResourcesManager* pInst;
};

