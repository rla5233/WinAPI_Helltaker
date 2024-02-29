#include "ChapterSin.h"

bool ChapterSin::IsLoad = false;
const std::vector<const char*> ChapSin_Script1 =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "고위 기소관 저지먼트",
	/* 2  Script 1  */ "마치 천 번은 죽은 것 같은 느낌이다. 하지만 불길은\n사그라들고... 어찌됐든 당신은 아직 살아있는 것 같다.",
	/* 3  Script 2  */ "칩입자 녀석, 이제야 찾았다!\n넌	아직 죽을 수 없어.",
	/* 4  Script 3  */ "나와 함께 오랜 시간을 보내야 할 거다.",
	/* 5  Script 4  */ "죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!",
	/* 6  Script 5  */ "침입자야, 죄악의 기계가 마음에 드느냐?",
	/* 7  Script 6  */ "이만 굴복하고 삼켜져라!",
	/* 8  Script 7  */ "희망을 버려라! 저 녀석의 운명은 이미 정해졌다!",
	/* 9  Script 8  */ "정숙하라! 이제 진짜 시작이다!",
	/* 10 Script 9  */ "너를 이곳으로 이끌었던 것들이 사슬이 되어 너를 휘감지.",
	/* 11 Script 10 */ "너의 교만, 탐욕, 그리고 욕정. 네 고통은 자초한 거다.",
	/* 12 Script 11 */ "그 어떤 권위도 형벌을 넘어설 수 없다!",
	/* 13 Script 12 */ "진정 사슬을 부수고 빠져나갈 수 있을 것 같느냐?",
	/* 14 Script 13 */ "희망은 실망을, 그리고 실망은 절망을 낳는다.",
	/* 15 Script 14 */ "그리고 절망의 사슬이 가장 즐거운 법이지.",
	/* 15 Script 14 */ "그래! 네가 행한 모든 것들을 후회하라!",

	/* 2 MenuBar1 */ "네 헤어 스타일이 마음에 드는데.",
	/* 2 MenuBar2 */ "그 옷 끝내주는데! 10점 만점에 10점!",
	/* 15 Script 14 */ "거짓말! 기만으로 네 운명을 벗어날 수는 없다!",
	
	/* 2 MenuBar1 */ "알아. 그래서 내가 솔직한 거지.",
	/* 2 MenuBar2 */ "그 손톱도 마음에 들어!",
	/* 15 Script 14 */ "그래? 그렇다면, '고맙다!'라고 해야겠지?",
	/* 15 Script 14 */ "이제 다시 시련을 시작한다!",
	
	/* 15 Script 14 */ "진정한 고통이 시작되기 전에 남길 말이라도 있느냐?",
	/* 2 MenuBar1 */ "널 먼저 찾지 않은 게 후회스러워.",
	/* 2 MenuBar2 */ "너에게 형벌을 받을 수 있으니 죄악도 좋은거 같아.",

	/* 15 Script 14 */ "값싼 아부는 집어치워! 일을 어렵게 만들지 마!",
	/* 2 MenuBar1 */ "그리고 눈이 이렇게 참 예쁘잖아.",
	/* 2 MenuBar2 */ "좀 전에 헤어스타일이 좋다고 말했었나?",
	
	/* 15 Script 14 */ "있잖아, 나도 별로 이러고 싶진 않은데. 하지만 이미 계약이\n확정됐어. 네 저주를 막을 수 없다고.",

};

const std::vector<const char*> ChapSin_Script2 =
{
	/* 0  Demon	   */ "세 쌍둥이 악마 케르베로스",
	/* 1  Demon	   */ "피곤한 악마 판데모니카",
	/* 2  Demon	   */ "지옥의 CEO 루시퍼",
	/* 3  Demon	   */ "끝내주는 악마 저스티스",
	/* 4  Demon	   */ "호기심 많은 천사 아자젤",
	/* 5  Demon	   */ "상스러운 악마 즈드라다",
	/* 6  Demon	   */ "시큰둥한 악마 말리나",
	/* 6  Demon	   */ "음란한 악마 모데우스",
	/* 6  Script 1 */ "안돼, 포기하지 마! 우릴 데리고 나가야지!",
	/* 7  Script 2 */ "그리고 커피도 타 주셔야죠.",
	/* 8  Script 3 */ "이런, 저지먼트. 이 녀석은 모르고 있겠지만, 내 거야. 그냥\n내버려 둘 수는 없어?",
	/* 9  Script 4 */ "그만! 고위 기소관, 즉시 물러날 것을 명한다!",
	/* 10 Script 5 */ "저지먼트, 계속 해 봐! 잘 나가는데!",
	/* 11 Script 6 */ "그래요, 계속하세요. 이거 분명 A+ 받을 만한 소재에요.",
	/* 12 Script 7 */ "이 망할 놈들아! 내가 지옥의 여왕이라고! 왜 아무도 내말을\n안듣는거야!",
	/* 13 Script 7 */ "말린카는 재수도 없지. 기껏 찾은 겜스퍼거 친구가 죽게\n생겼네.",
	/* 13 Script 7 */ "내 운수가 이러니 쟤가 네크로폴리스를 하게 됐어.",
	/* 13 Script 7 */ "차라리 나 혼자 독차지할 걸...",


};

ChapterSin::ChapterSin()
{
}

ChapterSin::~ChapterSin()
{
}

void ChapterSin::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialogueBG_Sin_001.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialogueBG_Sin_002.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialBG_LitHell.png");

		IsLoad = true;
	}
}

void ChapterSin::LevelStart(ULevel * _PrevLevel)
{

}

void ChapterSin::CutSceneStart()
{}

void ChapterSin::ChangeChapter()
{}

void ChapterSin::SelectStart()
{}

void ChapterSin::SelectMenu()
{}

void ChapterSin::BadEndStart()
{}

void ChapterSin::BadEndSetting()
{}

void ChapterSin::SuccessStart()
{}
