#include "stdafx.h"
#include "GameHandler.h"
#include "Player.hpp"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include "CharacterFactory.h"
#include "BuildingFactory.h"
#include "RandomEngine.h"
#include "TurnStartState.h"
#include "DrawCharacterState.h"

class Building;

namespace machiavelli {
	const int tcp_port{ 1080 };
	const std::string prompt{ "machiavelli> " };
}

GameHandler::GameHandler()
{
	stock = std::make_shared<Player>();
	stock->set_name("stock");
	initCharacterCards();
	initBuildingCards();
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
	*socket << "Welcome, " << name << ", have fun playing our game!\r\n";
	player->set_socket(socket);
	players.push_back(player);

	return player;
}

std::shared_ptr<Player> GameHandler::getOldestPlayer() {
	std::shared_ptr<Player> firstplayer;
	for (std::shared_ptr<Player> player : players) {
		if (firstplayer == nullptr) {
			firstplayer = player;
		}
		else if (player->get_age() > firstplayer->get_age()) {
			firstplayer = player;
		}
	}
	return firstplayer;
}

void GameHandler::initCharacterCards() {
	std::unique_ptr<CharacterFactory> charF = std::unique_ptr<CharacterFactory>(new CharacterFactory);
	const std::string textfile{ "karakterkaarten.csv" };
	std::ifstream input_file{ textfile }; // stack-based file object; deze constructie opent de file voor lezen
	std::string line;

	// getline() leest een regel die eindigt in een \n
	// (je kunt ook een 3e param meegeven als je een ander 'regeleinde' wil gebruiken)
	while (std::getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt

		std::istringstream buf(line);
		std::istream_iterator <std::string> beg(buf), end;
		std::vector<std::string> line(beg, end);
		for each(std::string s in line) {
			std::unique_ptr<Character> c = charF->createCharacter(s);
			characters.emplace(c->getId(), std::move(c));
		}
	}
}

void GameHandler::initBuildingCards() {
	std::unique_ptr<BuildingFactory> charF = std::unique_ptr<BuildingFactory>(new BuildingFactory);
	const std::string textfile{ "Bouwkaarten.csv" };
	std::ifstream input_file{ textfile }; // stack-based file object; deze constructie opent de file voor lezen
	std::string line;
	int counter = 1;

	// getline() leest een regel die eindigt in een \n
	// (je kunt ook een 3e param meegeven als je een ander 'regeleinde' wil gebruiken)
	while (std::getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt

		std::istringstream buf(line);
		std::istream_iterator <std::string> beg(buf), end;
		std::vector<std::string> line(beg, end);
		std::unique_ptr<Building> c = charF->createBuilding(line[0]);
		buildings.emplace(std::make_pair(counter, std::move(c)));
		counter++;
	}
}

void GameHandler::divideGold()
{
	std::cout << "dividing gold motherfucker \r\n";
	for (auto const& player : players) {
		addGold(player, 2);
	}
}

bool GameHandler::addGold(std::shared_ptr<Player> playerm, int gold) {
	std::cout << "gl " << goldLeft << " - " << gold;
	if (goldLeft >= gold)
	{
		playerm->addGold(gold);
		goldLeft -= gold;
		return true;
	}
	return false;
}

int GameHandler::amountOfGoldPieces(std::shared_ptr<Player> player) {
	return player->getGold();
}


void GameHandler::divideBuilding() {
	for (auto const& player : players) {
		for (int i = 0; i < 4; i++) {
			getBuilding(player);
		}
	}
}

void GameHandler::getBuilding(std::shared_ptr<Player> player) {
	int cardId = RandomEngine::drawBuildingCard(buildings);
	buildings[cardId]->setOwner(player);
}

void GameHandler::layOffCharacterCard(int cardId) {
	if (amountOfCharactersLeft() % 2 == 0) {
		characters[cardId]->setOwner(stock);
	}
}

int GameHandler::amountOfCharactersLeft() {
	int counter = 0;
	for each (const auto& kv in characters)
	{
		if (kv.second->getOwner() == nullptr) {
			counter++;
		}
	}
	return counter;

}

void GameHandler::pickCharacterCard(int cardId, std::shared_ptr<Player> player) {
	characters[cardId]->setOwner(player);
}

std::string GameHandler::buildBuilding(std::shared_ptr<Player> player, int buildingId)
{
	if (buildings[buildingId]->getOwner() == player && !buildings[buildingId]->isPlayed()) {
		if (characters[turnID]->getNumOfBuildings() > 0) {
			if (player->getGold() >= buildings[buildingId]->getCost()) {
				player->takeGold(buildings[buildingId]->getCost());
				goldLeft += buildings[buildingId]->getCost();
				buildings[buildingId]->setPlayed(true);
				characters[turnID]->setNumOfBuildings(characters[turnID]->getNumOfBuildings() - 1);
				return "oke";
			}
			return "may not build";
		}
		else {
			return "No gold";
		}
	}
	return "Not owned";
}

std::shared_ptr<Player> GameHandler::getNextPlayer(std::shared_ptr<Player> currentPlayer) {

	auto i = std::find(players.begin(), players.end(), currentPlayer);
	int nPosition;
	if (i + 1 != players.end())
	{
		nPosition = distance(players.begin(), i) + 1;
	}
	else {
		nPosition = 0;
	}

	std::cout << " next player at position: " << nPosition << std::endl;

	return players[nPosition];
}

void GameHandler::showGameStatus(std::shared_ptr<Socket> s) {
	s->write("Player one: " + players[0]->get_name() + "\r\n");
	s->write("Goldpieces: " + std::to_string(amountOfGoldPieces(players[0])) + " \r\n");
	s->write("Buildings: " + buildingsForPlayer(players[0]) + "\r\n");

	s->write("The bank holds: \r\n");
	s->write("Goldpieces: " + std::to_string(amountOfGoldPieces(stock)) + "\r\n");
	//s->write("Buildings")

	s->write("Player two: " + players[1]->get_name() + "\r\n");
	s->write("Goldpieces: " + std::to_string(amountOfGoldPieces(players[1])) + " \r\n");
	s->write("Buildings: " + buildingsForPlayer(players[1]) + "\r\n");
	s->write(machiavelli::prompt);
}

std::string GameHandler::buildingsForPlayer(std::shared_ptr<Player> player) {
	std::string s = "";
	int counter = 0;
	for each (const auto& building in buildings) {
		if (building.second->getOwner() == player && building.second->isPlayed()) {
			s += building.second->getName() + " ";
			counter++;
		}
	}
	s = std::to_string(counter) + s;
	return s;
}

std::vector<int> GameHandler::buildingIdsForPlayer(std::shared_ptr<Player> player)
{
	std::vector<int> ids;
	for (const auto& building : buildings) {
		if (building.second->getOwner() == player) {
			ids.push_back(building.first);
		}
	}
	return ids;
}

void GameHandler::showHelp(std::shared_ptr<Socket> client) {
	client->write("In een beurt kun je: \r\n");
	client->write("1 - 2 goudstukken innen \r\n");
	client->write("2 - 2 gebouwen van de stapel nemen en er 1 terugleggen \r\n");
	client->write("3 - Een gebouw bouwen \r\n");
	client->write("4 - Je karakteractie uitvoeren \r\n");
	client->write("Karakteracties zijn: \r\n");
	client->write("1 - Moordenaar - Een karakter vermoorden \r\n");
	client->write("2 - Dief - Van een andere speler stelen \r\n");
	client->write("3 - Magiër - Bouwkaarten omruilen \r\n");
	client->write("4 - Koning - De volgende ronde beginnen en geld verdienen voor gele gebouwen \r\n");
	client->write("5 - Prediker - Immuun tegen Condotierre en geld verdienen voor blauwe gebouwen \r\n");
	client->write("6 - Koopman - Extra goudstuk krijgen en geld verdienen voor groene gebouwen \r\n");
	client->write("7 - Bouwmeester - Twee extra bouwkaarten pakken en drie gebouwen bouwen \r\n");
	client->write("8 - Condotierre - Gebouw vernietigen en geld verdienen voor rode gebouwen \r\n");
}

bool GameHandler::startTurns() {
	if (!lastRound)
		checkLastRound();
	for each (const auto& kv in characters)
	{
		if (kv.second->getOwner() != stock  && kv.first > turnID) {
			turnID = kv.first;
			turn = std::make_shared<TurnStartState>(shared_from_this());
			curPlayer = kv.second->getOwner();
			if (kv.second->isKilled()) {
				curPlayer->get_socket()->write("Je bent vermoord en kunt dus deze beurt niets doen");
			}
			else {
				return true;
			}
		}
	}
	if (!lastRound)
		newRound();
	else
	{
		determineScore();
		endGame();
	}
}

bool GameHandler::nextTurn()
{
	if (turn->getName() == "drawing")
	{
		curPlayer = getNextPlayer(curPlayer);
		changeTurnState(std::make_shared<DrawCharacterState>(shared_from_this()));
		std::shared_ptr<DrawCharacterState> state = std::dynamic_pointer_cast<DrawCharacterState>(turn);
		if (state != nullptr)
		{
			if (state->getCard() == -1)
			{
				startTurns();
			}
		}
	}
	else {
		startTurns();
	}
	return false;
}

void GameHandler::newRound()
{
	if (characters[4]->getOwner() != stock && characters[4]->getOwner() != nullptr)
	{
		curPlayer = characters[4]->getOwner();
	}
	else {
		curPlayer = getOldestPlayer();
	}
	resetCharOwners();
	turnID = 0;
	changeTurnState(std::make_shared<DrawCharacterState>(shared_from_this()));

}

void GameHandler::resetCharOwners()
{
	for each (const auto& kv in characters)
	{
		kv.second->setOwner(nullptr);
		kv.second->setKilled(false);
		kv.second->setStolen(false);
		kv.second->setNumOfBuildings(1);
		if (kv.first == 7) {
			kv.second->setNumOfBuildings(3);
		}
	}
}

void GameHandler::printBuildings(std::shared_ptr<Player> player, bool built) {
	for each (const auto& building in buildings) {
		if (building.second->getOwner() == player && building.second->isPlayed() == built) {
			player->get_socket()->write(building.second->getName() + "( " + building.second->getColor() + ", " + std::to_string(building.second->getCost()) + ")\r\n");
		}
	}
}

void GameHandler::printTurn(std::shared_ptr<Player> player)
{
	if (!gameEnded)
		turn->print(player);
	else
		endGame();
}

void GameHandler::handleCommand(ClientCommand command)
{
	turn->handleCommand(command, shared_from_this());
}

std::vector<int> GameHandler::drawBuildingCards(int nCards)
{
	std::vector<int> available;
	std::vector<int> ret;
	for each (const auto& building in buildings) {
		if (building.second->getOwner() == nullptr) {
			available.push_back(building.first);
		}
	}

	while (ret.size() < nCards)
	{
		int i = rand() % available.size() - 1;
		ret.push_back(available[i]);
	}
	return ret;
}

void GameHandler::assignBuilding(int id, std::shared_ptr<Player> player)
{
	buildings[id]->setOwner(player);
}


void GameHandler::checkLastRound()
{
	for (std::shared_ptr<Player> player : players)
	{
		if (amountOfBuildings(player) >= 8)
		{
			lastRound = true;
			firstFinish = player;
			player->addPoints(4);
		}
	}
}

int GameHandler::amountOfBuildings(std::shared_ptr<Player> player)
{
	int ret = 0;
	for each (const auto& building in buildings) {
		if (building.second->getOwner() == player && building.second->isPlayed()) {
			ret++;
		}
	}
	return ret;
}

void GameHandler::determineScore()
{
	for (std::shared_ptr<Player> player : players)
	{
		std::vector<std::string> colours;
		int nBuildings = 0;
		for each (const auto& building in buildings) {
			if (building.second->getOwner() == player && building.second->isPlayed()) {
				player->addPoints(building.second->getPoints());
				player->addBuildingPoints(building.second->getPoints());
				nBuildings++;
				if (std::find(colours.begin(), colours.end(), building.second->getColor()) == colours.end()) {
					colours.push_back(building.second->getColor());
				}
			}
		}
		if (colours.size() == 5)
		{
			player->addPoints(3);
		}
		if (nBuildings >= 8 && player != firstFinish)
		{
			player->addPoints(2);
		}
	}
}

void GameHandler::endGame()
{
	gameEnded = true;
	bool foundHighestScore = false;
	bool foundHighestBuildingScore = false;
	std::shared_ptr<Player> bestScoring = nullptr;
	std::shared_ptr<Player> bestBuildingScoring = nullptr;
	for (std::shared_ptr<Player> player : players)
	{
		if (bestScoring == nullptr)
			bestScoring = player;
		else if (player->getPoints() > bestScoring->getPoints())
		{
			bestScoring = player;
			foundHighestScore = true;
		}
		else if (player->getPoints() == bestScoring->getPoints())
			foundHighestScore = false;

		if (bestBuildingScoring == nullptr)
			bestBuildingScoring = player;
		else if (player->getBuildingPoints() > bestBuildingScoring->getBuildingPoints())
		{
			bestBuildingScoring = player;
			foundHighestBuildingScore = true;
		}
		else if (player->getBuildingPoints() == bestBuildingScoring->getBuildingPoints())
			foundHighestBuildingScore = false;
	}

	if (foundHighestScore || foundHighestBuildingScore)
	{
		for (std::shared_ptr<Player> player : players)
		{
			player->get_socket()->write("=========GAME ENDED=========\r\n");
			if (foundHighestScore)
				player->get_socket()->write("The winner of the game is.. " + bestScoring->get_name() + " with a score of " + std::to_string(bestScoring->getPoints()) + " points!");
			else if (foundHighestBuildingScore)
				player->get_socket()->write("The winner of the game is.. " + bestBuildingScoring->get_name() + " with " + std::to_string(bestScoring->getBuildingPoints()) + " points from buildings!");
		}
	}

}

const Building& GameHandler::getBuilding(int id) {
	return *buildings[id];
}

const Character& GameHandler::getCharacterRef(int id) {
	return *characters[id];
}

std::string GameHandler::getBuildingString(int id)
{
	return buildings[id]->getName() + "(" + std::to_string(buildings[id]->getPoints()) + "," + buildings[id]->getColor() + ")";
};

std::shared_ptr<Player> GameHandler::owner(int cardId)
{
	return characters[cardId]->getOwner();

}

int GameHandler::buildingFromStock() {
	return(RandomEngine::drawBuildingCard(buildings));
}

void GameHandler::killCharacter(int id)
{
	characters[id]->setKilled(true);
}

void GameHandler::stealCharacter(int id, std::shared_ptr<Player> player)
{
	characters[id]->setStolen(player);
}


bool GameHandler::removeBuilding(int id, std::shared_ptr<Player> demolisher)
{
	if (buildings[id]->getCost() - 1 > demolisher->getGold()) return false;
	buildings[id]->setPlayed(false);
	buildings[id]->setOwner(nullptr);
	demolisher->takeGold(buildings[id]->getCost() - 1);
	return true;
}

void GameHandler::changeBuildingOwner(int id, std::shared_ptr<Player> newOwner)
{
	if (!buildings[id]->isPlayed()) {
		buildings[id]->setOwner(newOwner);
	}
}

