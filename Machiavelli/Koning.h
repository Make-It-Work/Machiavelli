#pragma once
#include "Character.h"
#include "Player.hpp"
#include "GameHandler.h"

class Building;
class Koning :
	public Character
{
public:
	Koning();
	~Koning();
	bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const { return true; };
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const ;
	std::string getActionDescription(std::shared_ptr<GameHandler> game) const { return "Je mag de volgende ronde als eerste een karakter kiezen \r\n [0] Hurray! \r\n"; }
};

