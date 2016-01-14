#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Socket.h"
#include "Player.hpp"
#include "Building.h"
#include "Character.h"
#include "Goldpiece.h"
class GameHandler
{
private:
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::unique_ptr<Building>> buildingsInStore;
	std::map<int, std::unique_ptr<Character>> leftOverCharacters;
	std::shared_ptr<Player> stock;
	std::vector<std::unique_ptr<Goldpiece>> goldpieces;
	
	void initCharacterCards();
	void initGold();
	

public:
	GameHandler();
	~GameHandler();
	int getAmountOfPlayers() { return players.size(); }
	std::map<int, std::unique_ptr<Character>> characters;

	//Init functions
	std::shared_ptr<Player> getOldestPlayer();
	std::shared_ptr<Player> addPlayer(std::shared_ptr<Socket> socket);
	void divideGold();

	void getGoldPiece(std::shared_ptr<Player>);

	int amountOfGoldPieces(std::shared_ptr<Player> player);

	//CharacterCard functions
	int amountOfCharactersLeft();
	void layOffCharacterCard(int cardId);
	void pickCharacterCard(int cardId, std::shared_ptr<Player> player);

	//Helper functions
	std::shared_ptr<Player> getNextPlayer(std::shared_ptr<Player> currentPlayer);
	void showGameStatus(std::shared_ptr<Socket> s);
	void showHelp(std::shared_ptr<Socket> client);
		
};

