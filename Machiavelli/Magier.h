#pragma once
#include "Character.h"
#include "Player.hpp"
#include "GameHandler.h"

class Magier :
	public Character
{
public:
	Magier();
	~Magier();
	void execute() {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
};

