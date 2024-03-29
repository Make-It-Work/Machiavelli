#pragma once
#include "Character.h"

#include "Player.hpp"
#include "GameHandler.h"

class Prediker :
	public Character
{
public:
	Prediker();
	~Prediker();
	bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const { return true; };
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const;
	std::string getActionDescription(std::shared_ptr<GameHandler> game) const { return "Je gebouwen mogen niet verwoest worden door de condottiere \r\n [0] Hurray! \r\n"; }
};

