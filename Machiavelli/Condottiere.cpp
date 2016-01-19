#include "stdafx.h"
#include "Condottiere.h"
#include "Building.h"

Condottiere::Condottiere()
{
	name = "Condottiere";
	id = 8;
}


Condottiere::~Condottiere()
{
}

void Condottiere::getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const
{
	int amount = 0;
	for (int buildingId : game->buildingIdsForPlayer(player)) {
		const Building& building = game->getBuilding(buildingId);
		if (building.isPlayed() && building.getColor() == "rood") {
			amount++;
		}
	}
	game->addGold(player, amount);
}
