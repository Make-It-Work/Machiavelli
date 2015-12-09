#pragma once
#include <memory>
#include <vector>
#include "Socket.h"
#include "Player.hpp"
class GameHandler
{
private:
	std::vector<std::shared_ptr<Player>> players;
public:
	GameHandler();
	~GameHandler();

	std::shared_ptr<Player> addPlayer(std::shared_ptr<Socket> socket);

	void startGame();
};

