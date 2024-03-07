#include "Sin_Dialogue.h"

bool Sin_Dialogue::IsLoad = false;

Sin_Dialogue::Sin_Dialogue()
{
}

Sin_Dialogue::~Sin_Dialogue()
{
}

void Sin_Dialogue::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialBG_LitHell.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Sin_001.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Sin_002.png");

		IsLoad = true;
	}

	DarkHell_Renderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	LitHell_Renderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	Down_ImageRenderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
	Up_ImageRenderer = CreateImageRenderer(SinRenderOrder::UnderBackGround);
}

void Sin_Dialogue::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);
}
