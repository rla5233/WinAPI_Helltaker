#include "ContentsHelper.h"

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
}

FVector ContentsHelper::GetWindowScale()
{
    return GEngine->MainWindow.GetWindowScale();
}

float ContentsHelper::GetOneTileWidth()
{
    return GEngine->MainWindow.GetWindowScale().X / 19;
}


