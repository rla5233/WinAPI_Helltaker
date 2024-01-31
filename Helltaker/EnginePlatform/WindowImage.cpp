#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>

// 윈도우에서 이미지를 사용하기 위해서 지원하는 라이브러리.
// 헤더랑 다르게 라이브러리는 #pragma comment 통해서 추가 해야 한다.
#pragma comment(lib, "Msimg32.lib")

#include <objidl.h>
#include <gdiplus.h>

// Png를 로드하는 기능을 윈도우 기본 라이브러리만으로 지원해주지 않기 때문ㅇ
// GDIPlus를 사용해야 한다.
// GIDPlus는 윈도우가 초기 윈도우의 그래픽 시스템을 개선해서 추가한 라이브러리입니다.

#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage()
{}

UWindowImage::~UWindowImage()
{
	// 윈도우가 할당해준거지만
	// 정리는 우리가 해주는게 좋습니다.
	DeleteObject(hBitMap);
	DeleteDC(ImageDC);

}

FVector UWindowImage::GetScale()
{
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}

bool UWindowImage::Create(HDC _MainDC)
{
	ImageDC = _MainDC;

	if (nullptr == ImageDC)
	{
		return false;
	}

	return true;
}

bool UWindowImage::Load(UWindowImage* _Image)
{
	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	if (".BMP" == UpperExt)
	{
		//HINSTANCE hInst,  이 이미지를 사용할 프로그램을 알려달라는건데. nullptr넣어도 괜찮다.
		//LPCSTR name, // 경로
		//UINT type, // 이미지 타입
		//int cx, // 이미지를 로드할 크기 X 0을 넣으면 전체 크기로 로드
		//int cy, // 이미지를 로드할 크기 Y 0을 넣으면 전체 크기로 로드
		//UINT fuLoad 로드 옵션

		// 비트맵을 제어할수 있는 핸들입니다.
		// 비트맵을 그릴수 있는 핸들은 아닙니다.
		// 그린다는 목적을 가진 핸들과
		// 비트맵을 로드한다는 목적의 핸들이 다르다는 것입니다.
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
		ImageType = EWIndowImageType::IMG_BMP;
	}
	else if (".PNG" == UpperExt)
	{
		ULONG_PTR gdiplusToken = 0;
		// Gdiplus헤더의 함수들은 전부다 Gdiplus 네임스페이스 안에 들어있어요.
		// GDi를 사용하겠다는 시작 
		// GDIPlus를 사용해본적이 거의 없는데 이번에 Png가 로드가 안되면 여러분들이 귀찮아 할것같아서
		// 로드하는걸 알아봤는데.
		// Png를 그대로 출력하는 함수도 있었는데. 
		// 겁나게 느렸습니다.
		// 게임을 못만들정도였다.
		// 그건 포기
		// 로드는 가능한데. png로 사용하면 안되기 때문에
		// Png로 로드한 녀석을 Bmp로 바꾸면 무리없이 되서 그 방식으로 하기로 했습니다.
		Gdiplus::GdiplusStartupInput gdistartupinput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);

		// 유니코드로 되었습니다.
		// 그래서 멀티바이트 경로를 유니코드 경로로 변경하는 함수가 필요한데.
		std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());

		// 어떤 문자열에 기반해서 만들어졌는지 알수 없죠?
		// 그냥 모든 문자열에 대비할 방법을 찾아야 합니다.
		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);

		if (Gdiplus::Status::Ok != stat)
		{
			MsgBoxAssert("Png 형식 리소스 로드에 실패했습니다.");
		}

		ImageType = EWIndowImageType::IMG_PNG;
	}

	// 그릴수있고 이미지에 간섭할수 있는 권한이다.
	// 어디에 그릴거냐.
	// 어디속해서 어디에 그려질 DC냐를 넣어줘야 합니다.
	// 당연히 하나뿐인 mainwindow의 DC를 넣어주면 됩니다.
	// 그릴수 있는 권한이 자신이 뭘 그려야하는지를 알려줘야 합니다.
	// ImageDC야 너는 BitMap그려야 해.
	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// hBitMap에서 얻어오겠다.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	// ImageDC를 만들면 내부에서 1,1크기의 HBITMAP을 만든다.



	// 두가지를 사용할건데.
	// Png때와 bmp일대 로드하는 방식이 달라요.

	return true;
}

bool UWindowImage::Create(UWindowImage* _Image, const FVector& _Scale)
{
	// 시작이 먼저 이미지를 만든다.


	// HBITMAP 비트맵 이미지의 메모리권한
	HANDLE ImageHandle = CreateCompatibleBitmap(_Image->ImageDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// hBitMap에서 얻어오겠다.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

void UWindowImage::BitCopy(UWindowImage* _CopyImage, const FTransform& _Trans)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}
	// 렉탱글이 아니고
	// 이미지로 그려야합니다

	// HDC hdc, // => 어떤 이미지에
	// int x,   // => 이 크기로
	// int y,   // 
	// int cx,  // => 
	// int cy,  
	// HDC hdcSrc,  
	// int x1,  
	// int y1, 
	// DWORD rop

	// 윈도우
	HDC hdc = ImageDC;
	// 이미지
	HDC hdcSrc = _CopyImage->ImageDC;
	BitBlt(
		hdc, 							  // HDC hdc, // 
		_Trans.iLeft(), 				  // int x,   // 
		_Trans.iTop(), 				  // int y,   // 
		_Trans.GetScale().iX(), 		  // int cx,  // 
		_Trans.GetScale().iY(),		  // int cy,  
		hdcSrc,							// HDC hdcSrc, 
		0,								// int x1,  
		0,								// int y1, 
		SRCCOPY							// DWORD rop => 이미지 그대로 고속 복사를 해라.
	);
}

void UWindowImage::TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, const FTransform& _ImageTrans, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}

	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft = _ImageTrans.GetPosition().iX();
	int ImageTop = _ImageTrans.GetPosition().iY();
	int ImageScaleX = _ImageTrans.GetScale().iX();
	int ImageScaleY = _ImageTrans.GetScale().iY();

	HDC hdc = ImageDC;
	// 이미지
	HDC hdcSrc = _CopyImage->ImageDC;
	TransparentBlt(
		hdc, 							  // HDC hdc, // 
		RenderLeft, 		  // int x,   // 
		RenderTop, 		  // int y,   // 
		RenderScaleX,		  // int cx,  // 
		RenderScaleY,		  // int cy,  
		hdcSrc,							// HDC hdcSrc, 
		ImageLeft,   							// int y1, 
		ImageTop,   							// int x1,  
		ImageScaleX, 							// int y1, 
		ImageScaleY, 							// int y1, 
		_Color.Color						// DWORD rop => 이미지 그대로 고속 복사를 해라.
	);
	// 이미지의 어떤 부위를 그릴지를 정해줄수가 있다.
}