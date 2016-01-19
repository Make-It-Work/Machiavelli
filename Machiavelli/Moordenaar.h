#pragma once
#include "Character.h"
#include "Player.hpp"
#include "GameHandler.h"

class Moordenaar :
	public Character
{
public:
	Moordenaar();
	~Moordenaar();
	void execute() {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
};

