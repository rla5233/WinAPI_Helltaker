#include "Helltaker_ContentsCore.h"

#include "Opening.h"
#include <EngineBase/EngineDirectory.h>

Helltaker_ContentsCore::Helltaker_ContentsCore()
{
}

Helltaker_ContentsCore::~Helltaker_ContentsCore()
{
}

void Helltaker_ContentsCore::BeginPlay()
{
	UEngineCore::BeginPlay();

	MainWindow.SetClearColor(Color8Bit(2, 2, 27, 255));
	MainWindow.SetWindowScale({ 1920, 1080 });
	SetFrame(60);

    CreateLevel<Opening>("Opening");
    ChangeLevel("Opening");
}

void Helltaker_ContentsCore::WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath)
{
	_OutWindowTitle = "HellTaker";

	UEngineDirectory ResourcesPath = UEngineDirectory();
	ResourcesPath.MoveParent();
	ResourcesPath.Move("Resources");
	ResourcesPath.Move("UI");
	std::string IconPath = ResourcesPath.AppendPath("Icon.ico");
	_SmallIconPath = IconPath;
}