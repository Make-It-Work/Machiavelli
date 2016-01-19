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

