#pragma once

#include "Client.h"
#include "PacketReceiver.h"


Client::Client()
	: role(false)
	, network_socket(INVALID_SOCKET)
{
	packet_receiver = new PacketReceiver(clients, stage_item);
}

void Client::run_client_thread(array<Client, 3>* member, Stage* stage, SOCKET accepted_socket) {
	clients = member;
	stage_item = stage;
	network_socket = accepted_socket;

	while (network_socket != INVALID_SOCKET) {
		int packet_size = recv(network_socket, recv_buffer + rest_packet_size,
			MAX_BUF_SIZE - rest_packet_size, 0);

		if (packet_size > 0) {
			packet_receiver->construct_packet(this, packet_size);
			packet_receiver->process_packet(recv_buffer);
		}
	}
}

bool Client::have_role() {
	return role;
}

STAGE_TYPE Client::get_curr_stage() {
	return curr_stage_type;
}
