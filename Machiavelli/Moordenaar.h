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
	void execute(std::shared_ptr<GameHandler> game) const {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
	std::string getActionDescription() const { return "Dit is een actie"; }
};

