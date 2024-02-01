#include "RenderActor.h"

RenderActor::RenderActor()
{
}

RenderActor::~RenderActor()
{
}

void RenderActor::LoadAndSetRenderImage(std::string_view _Name)
{
	LoadRenderImage(_Name);
	SetRenderImage(_Name);
}