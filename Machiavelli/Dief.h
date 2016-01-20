#pragma once
#include "Character.h"
#include "Player.hpp"
#include "GameHandler.h"

class Dief :
	public Character
{
public:
	Dief();
	~Dief();
	bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const { return true; };
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
	std::string getActionDescription() const { return "Dit is een actie"; }
}; 

