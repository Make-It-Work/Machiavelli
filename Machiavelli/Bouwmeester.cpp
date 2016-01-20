#include "stdafx.h"
#include "Bouwmeester.h"
#include "Building.h"

Bouwmeester::Bouwmeester()
{
	name = "Bouwmeester";
	id = 7;
	numOfBuildings = 3;
}


Bouwmeester::~Bouwmeester()
{
}

bool Bouwmeester::execute(ClientCommand command, std::shared_ptr<GameHandler> game) const
{
	if (command.is_number()) {
		int buildId = stoi(command.get_cmd());
		game->buildBuilding(game->getCurPlayer(), game->buildingIdsForPlayer(game->getCurPlayer())[buildId]);
		if (numOfBuildings == 0 || buildId == 0) {
			return true;
		}
	}
	return false;
}

std::string Bouwmeester::getActionDescription(std::shared_ptr<GameHandler> game) const
{
	std::string s = "Twee extra gebouwen bouwen. Dit is nu je hand: \r\n";
	int counter = 1;
	s += "[0] Niet bouwen\r\n";
	for each (int buildId in game->buildingIdsForPlayer(game->getCurPlayer())) {
		if (!game->getBuilding(buildId).isPlayed()) {
			s += "[" + std::to_string(counter) + "]" + " " + game->getBuildingString(buildId) + "\r\n";
			counter++;
		}
	}
	return s;
}

void Bouwmeester::getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {
	player->get_socket()->write("Omdat je de bouwmeester bent krijg je 2 gebouwkaarten \r\n");
	game->assignBuilding(game->buildingFromStock(), game->getCurPlayer());
	game->assignBuilding(game->buildingFromStock(), game->getCurPlayer());
}
