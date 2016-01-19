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
	void execute() {};
	void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const ;
};

