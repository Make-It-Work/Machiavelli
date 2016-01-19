#include "stdafx.h"
#include "Prediker.h"
#include "Building.h"

Prediker::Prediker()
{
	name = "Prediker";
	id = 5;
}


Prediker::~Prediker()
{
}

void Prediker::getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const
{
	int amount = 0;
	for (int buildingId : game->buildingIdsForPlayer(player)) {
		const Building& building = game->getBuilding(buildingId);
		if (building.isPlayed() && building.getColor() == "blauw") {
			amount++;
		}
	}
	game->addGold(player, amount);
}

