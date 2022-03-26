#pragma once
#pragma execution_character_set("utf-8")


#include "./Menu.h"

#define MENU_BACKGROUND_MUSIC_PATH "C:\\workspace_cpp\\game_snake\\resource\\music\\game_menu_music.wav"
#define BACKGROUND_MUSIC_PATH_02 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_02.wav"
#define BACKGROUND_MUSIC_PATH_06 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_06.wav"
#define BACKGROUND_MUSIC_PATH_03 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_03.wav"
#define BACKGROUND_MUSIC_PATH_04 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_04.wav"
#define BACKGROUND_MUSIC_PATH_05 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_05.wav"
#define BACKGROUND_MUSIC_PATH_01 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_01.wav"
#define BACKGROUND_MUSIC_PATH_07 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_07.wav"
#define BACKGROUND_MUSIC_PATH_08 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_08.wav"
#define BACKGROUND_MUSIC_PATH_09 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_09.wav"
#define BACKGROUND_MUSIC_PATH_10 "C:\\workspace_cpp\\game_snake\\resource\\music\\game_music_10.wav"
#define BACKGROUND_MUSIC_EAT_FOOD "C:\\workspace_cpp\\game_snake\\resource\\music\\game_eat_food_music.wav"
#define BACKGROUND_MUSIC_GAME_OVER "C:\\workspace_cpp\\game_snake\\resource\\music\\game_over_music.wav"

#define MUSIC_MODE_MENU 0
#define MUSIC_MODE_EAT_FOOD 1
#define MUSIC_MODE_GAME_OVER 2
#define MUSIC_MODE_GAMING 3
#define MUSIC_MODE_HARD 4


class GameMusicEffect {
public:
	void playBackGroundMusic(int musicMode);
};