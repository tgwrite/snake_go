#pragma once
#pragma execution_character_set("utf-8")

#include "./include/GameMusicEffect.h"

GameMusicEffect gameMusicEffectObj = GameMusicEffect();

void GameMusicEffect::playBackGroundMusic(int musicMode) {
	switch (musicMode){
	case MUSIC_MODE_MENU:
		PlaySound(TEXT(MENU_BACKGROUND_MUSIC_PATH), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	case MUSIC_MODE_GAMING:
		PlaySound(TEXT(BACKGROUND_MUSIC_PATH_02), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	case MUSIC_MODE_HARD:
		PlaySound(TEXT(BACKGROUND_MUSIC_PATH_03), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	case MUSIC_MODE_EAT_FOOD:
		mciSendString(L"play C:\\workspace_cpp\\game_snake\\resource\\music\\game_eat_food_music.wav", NULL, 0, NULL);
		break;
	case MUSIC_MODE_GAME_OVER:
		PlaySound(TEXT(BACKGROUND_MUSIC_GAME_OVER), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	default:
		break;
	}
}