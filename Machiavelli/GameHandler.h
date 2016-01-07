#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Socket.h"
#include "Player.hpp"
#include "Building.h"
#include "Character.h"
class GameHandler
{
private:
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::unique_ptr<Building>> buildingsInStore;
	std::map<int, std::unique_ptr<Character>> characters;
	std::map<int, std::unique_ptr<Character>> leftOverCharacters;

	void initCharacterCards();
	void dealCharacterCards(std::shared_ptr<Player> firstPlayer);

	std::shared_ptr<Player> stock;

public:
	GameHandler();
	~GameHandler();

	std::shared_ptr<Player> addPlayer(std::shared_ptr<Socket> socket);

	void startGame();
};

