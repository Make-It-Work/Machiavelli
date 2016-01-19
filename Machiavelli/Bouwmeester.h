#pragma once
#include "Character.h"
#include "Player.hpp"
#include "GameHandler.h"
class Bouwmeester :
	public Character
{
public:
	Bouwmeester();
	~Bouwmeester();
	void execute() {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
};

