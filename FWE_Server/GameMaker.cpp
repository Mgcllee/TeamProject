#pragma once

#include "GameMaker.h"


void GameMaker::run_game() {
	game_stage.playerRole = &playerRole;
	game_stage.selectPlayerRole = &selectPlayerRole;

	while (true) {
		create_game_threads();
		join_game_threads();
	}
}

void GameMaker::create_game_threads() {
	stage_maker_thread = thread(&StageMaker::run_game_stage_thread, 
		new StageMaker, &clients, &game_stage);

	for (int user_ticket = 0; user_ticket < 3; ++user_ticket) {
		client_threads[user_ticket] = thread(&Client::run_client_thread,
			new Client, &clients, &game_stage, clients[user_ticket].network_socket);
	}

	for (thread& client_thread : client_threads) {
		
	}
}

void GameMaker::join_game_threads() {
	for (thread& client_thread : client_threads) {
		client_thread.join();
	}

	stage_maker_thread.join();
}

array<Client, 3>* GameMaker::get_clients() {
	return &clients;
}
