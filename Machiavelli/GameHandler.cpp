#include "stdafx.h"
#include "GameHandler.h"
#include "Player.hpp"

namespace machiavelli {
	const int tcp_port{ 1080 };
	const std::string prompt{ "machiavelli> " };
}

GameHandler::GameHandler()
{
}


GameHandler::~GameHandler()
{
}

std::shared_ptr<Player> GameHandler::addPlayer(std::shared_ptr<Socket> socket)
{
	socket->write("What's your name?\r\n");
	socket->write(machiavelli::prompt);
	std::string name{ socket->readline() };
	socket->write("What's your age?\r\n");
	socket->write(machiavelli::prompt);
	int age{ std::stoi(socket->readline()) };
	std::shared_ptr<Player> player{ new Player{ name, age } };
	*socket << "Welcome, " << name << ", have fun playing our game!\r\n" << machiavelli::prompt;
	player->set_socket(socket);
	players.push_back(player);
	player->get_socket()->write("This should work \r\n");

	if (players.size() == 2) {
		startGame();
	}

	return player;
}

void GameHandler::startGame() {

}
