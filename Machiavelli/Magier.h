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
	bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const;
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const {};
	std::string getActionDescription(std::shared_ptr<GameHandler> game) const;
};

