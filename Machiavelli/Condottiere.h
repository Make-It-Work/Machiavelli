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
	bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const;
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const;
	std::string getActionDescription(std::shared_ptr<GameHandler> game) const;
};

