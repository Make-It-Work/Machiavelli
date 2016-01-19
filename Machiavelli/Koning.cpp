#include "stdafx.h"
#include "Koning.h"
#include "Player.hpp"
#include "GameHandler.h"
#include "Building.h"

Koning::Koning()
{
	name = "Koning";
	id = 4;
}


Koning::~Koning()
{
}

void Koning::getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const
{
	int amount = 0;
	for (int buildingId : game->buildingIdsForPlayer(player)) {
		const Building& building = game->getBuilding(buildingId);
		if (building.isPlayed() && building.getColor() == "geel") {
			amount++;
		}
	}
	game->addGold(player, amount);
}

