#pragma once
#include "Character.h"
#include "Player.hpp"
#include "GameHandler.h"
class Condottiere :
	public Character
{
public:
	Condottiere();
	~Condottiere();
	void execute() {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const;
};

