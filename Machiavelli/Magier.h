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
	bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const { return true; };
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
	std::string getActionDescription() const { return "Dit is een actie"; }
};

