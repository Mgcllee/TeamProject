#pragma once

#include "stdafx.h"
#include "Timer.h"
#include "Stage.h"
#include "ClientAccepter.h"
#include "StagePosition.h"

class StageMaker
{
public:
	StageMaker();

	void reset_game_stage();

	void check_all_client_role();
	void show_game_stage(int stage_number);
	
	bool check_door();
	bool check_jewely();
	void move_interpolation();

	void cleanup_game();

	bool check_next_stage_condition();

	void show_player_score();

private:
	void run_game_stage_thread();

private:
	int stage_index;

	mutex select_mutex;

	int currentJewelyNum = 0;
	bool isVisibleDoor = false;
	mutex jewelyMutex;

	Timer _timer;
	bool gameEnd = false;
	double timeoutSeconds = 50;


	array<char, 3> playerRole = { 'f', 'f', 'f' };
	array<char, 3> selectPlayerRole = { 'n', 'n', 'n' };

	ClientAccepter client_accepter;
	array<Client, 3> clients;

	Stage stage_item;
};
