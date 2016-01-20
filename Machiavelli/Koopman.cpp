#include "stdafx.h"
#include "Koopman.h"
#include "Player.hpp"
#include "GameHandler.h"
#include "Building.h"

Koopman::Koopman()
{
	name = "Koopman";
	id = 6;
}


Koopman::~Koopman()
{
}

bool Koopman::execute(ClientCommand command, std::shared_ptr<GameHandler> game) const
{
	game->addGold(game->getCurPlayer(), 1);
	return true;
}

void Koopman::getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const
{
	int amount = 0;
	for (int buildingId : game->buildingIdsForPlayer(player)) {
		const Building& building = game->getBuilding(buildingId);
		if (building.isPlayed() && building.getColor() == "groen") {
			amount++;
		}
	}
	game->addGold(player, amount);
}

std::string Koopman::getActionDescription() const {
	return "Een extra goudstuk pakken\r\n [0] Hurray! \r\n";
}

