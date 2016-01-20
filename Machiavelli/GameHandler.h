#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Socket.h"
#include "Player.hpp"
#include "TurnState.h"

class Character;
class Building;
class Player;
class TurnState;
class CharacterHandler;

class GameHandler : public std::enable_shared_from_this<GameHandler>
{
private:
	std::unique_ptr<CharacterHandler> characterHandler;
	std::vector<std::shared_ptr<Player>> players;
	std::shared_ptr<Player> stock;
	std::map<int, std::unique_ptr<Building>> buildings;

	std::shared_ptr<TurnState> turn = nullptr;
	std::shared_ptr<Player> curPlayer = stock;

	int goldLeft = 32;
	
	//game start
	void initBuildingCards();
	void resetCharOwners();

	//game end
	bool lastRound = false;
	void checkLastRound();
	int amountOfBuildings(std::shared_ptr<Player> player);
	void determineScore();
	std::shared_ptr<Player> firstFinish = nullptr;
	void endGame();

	//turn data
	int turnID = -1;
public:
	GameHandler();
	~GameHandler();

	CharacterHandler& getCharacterHandler() { return *characterHandler; }

	int getAmountOfPlayers() { return players.size(); }
	//std::map<int, std::unique_ptr<Character>> characters;

	//Init functions
	std::shared_ptr<Player> getOldestPlayer();
	std::shared_ptr<Player> addPlayer(std::shared_ptr<Socket> socket);
	void divideGold();

	bool addGold(std::shared_ptr<Player>, int gold);
	int amountOfGoldPieces(std::shared_ptr<Player> player);

	void divideBuilding();

	void getBuilding(std::shared_ptr<Player> player);

	void newRound();
	//turn functions
	void printTurn(std::shared_ptr<Player> player);
	bool startTurns();
	bool nextTurn();
	int getTurnID() { return turnID; };
	void printBuildings(std::shared_ptr<Player> player, bool built);
	void handleCommand(ClientCommand command);
	void changeTurnState(std::shared_ptr<TurnState> state) { turn = state; };
	std::vector<int> drawBuildingCards(int nCards);
	std::string getBuildingString(int id);
	void assignBuilding(int id, std::shared_ptr<Player> player);
	std::shared_ptr<Player> getCurPlayer() { return curPlayer; };

	const Building & getBuilding(int id);

	//Turn Actions
	std::string buildBuilding(std::shared_ptr<Player>player, int buildingId);

	//Helper functions
	std::shared_ptr<Player> getNextPlayer(std::shared_ptr<Player> currentPlayer);
	void showGameStatus(std::shared_ptr<Socket> s);
	std::string buildingsForPlayer(std::shared_ptr<Player> player);
	std::vector<int> buildingIdsForPlayer(std::shared_ptr<Player> player);
	void showHelp(std::shared_ptr<Socket> client);
	std::shared_ptr<Player> getStock() { return stock; };
};
