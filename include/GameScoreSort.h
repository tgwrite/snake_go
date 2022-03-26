#pragma once
#pragma execution_character_set("utf-8")

#include "./Menu.h"


class GameScoreSort:virtual public Menu{
private:
	std::vector<int> gameScoreVector = std::vector<int>();
public:
	GameScoreSort();
	~GameScoreSort();
	void execute();
	void handleGameScoreFileSortAndShow(bool isShow);
	void show();
};

#define GAME_SCORE_TOP_COUNT_LIMIT 5