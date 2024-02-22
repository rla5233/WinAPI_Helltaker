#include "Chapter9.h"

bool Chapter9::IsLoad = false;

const std::vector<const char*> Chap9_Script
{
	/* 0 Demon	  */ "시큰둥한 악마 말리나",
	/* 1 Script 1 */ "대단하네, 또 골 빈 멍청이들이야...\n너같이 못생긴 놈은 처음인데, 지옥에서 뭘 하고 있어?",
	/* 2 MenuBar1 */ "너랑 같이 놀고 싶은데.",
	/* 3 MenuBar2 */ "기분 좋은데. 더 매도해 줘",
	/* 4 Failed	  */ "기가막히네 마조 변태나 또 보고.",
	/* 5 Bad End  */ "말리나가 팔을 휘두르자 작살 난 당신 목에서 피가 분수처럼\n터져 나왔다.",
	/* 6 Success  */ "뭐... 게임? 그래, 안 될 게 어디있어. 턴제 전략 게임이\n괜찮다면야."
};

Chapter9::Chapter9()
{
}

Chapter9::~Chapter9()
{
}

void Chapter9::BeginPlay()
{}

void Chapter9::LevelStart(ULevel * _PrevLevel)
{}

void Chapter9::CutSceneStart()
{}

void Chapter9::SelectStart()
{}

void Chapter9::SelectMenu()
{}

void Chapter9::BadEndStart()
{}

void Chapter9::BadEndSetting()
{}

void Chapter9::SuccessStart()
{}

void Chapter9::ChangeChapter()
{}