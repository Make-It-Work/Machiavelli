#include "stdafx.h"
#include "Magier.h"
#include "RandomEngine.h"

Magier::Magier()
{
	name = "Magier";
	id = 3;
}

Magier::~Magier()
{
}

bool Magier::execute(ClientCommand command, std::shared_ptr<GameHandler> game) const
{
	std::vector<int> buildings = game->buildingIdsForPlayer(game->getCurPlayer());
	if (command.get_cmd() == "0") {
		std::vector<int> counterBuildings = game->buildingIdsForPlayer(game->getNextPlayer(game->getCurPlayer()));
		for each (int buildId in buildings) {
			game->changeBuildingOwner(buildId, game->getNextPlayer(game->getCurPlayer()));
		}
		for each (int buildId in counterBuildings) {
			game->changeBuildingOwner(buildId, game->getCurPlayer());
		}
		return true;
	}
	else if (command.get_cmd() == "1") {
		for each (int buildId in buildings) {
			game->changeBuildingOwner(buildId, nullptr);
			game->assignBuilding(game->buildingFromStock(), game->getCurPlayer());
		}
		return true;
	}
	return false;
}

std::string Magier::getActionDescription(std::shared_ptr<GameHandler> game) const
{
	std::string s = "Je mag je bouwkaarten ruilen. \r\n";
	s += "[0] Ruil je hele hand met de andere speler \r\n";
	s += "[1] Ruil het aantal handkaarten wat je hebt met de stapel";
	return s;
}
