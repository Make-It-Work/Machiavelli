#pragma once
#include <string>
#include <memory>
#include "Player.hpp"
#include "GameHandler.h"

class Building;
class Character
{
protected:
	int id;
	std::string name;
	std::shared_ptr<Player> owner;
public:
	Character();
	~Character();
	void setId(int _id) { id = _id; }
	int getId() const { return id; }
	void setOwner(std::shared_ptr<Player> player) { owner = player; }
	std::shared_ptr<Player> getOwner() const { return owner; }
	std::string getName() const { return name; }
	virtual void execute() = 0;
	virtual void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const = 0;
	virtual std::string getActionDescription() const { return "Dit is een actie"; }
};


