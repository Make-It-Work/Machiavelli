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
	void execute(std::shared_ptr<GameHandler> game) const {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const ;
	std::string getActionDescription() const { return "Dit is een actie"; }
};

