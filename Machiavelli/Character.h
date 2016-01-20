#pragma once
#include <string>
#include <memory>
#include "Player.hpp"
#include "GameHandler.h"
#include "ClientCommand.h"

class Building;
class Character
{
protected:
	int id;
	std::string name;
	std::shared_ptr<Player> owner;
	bool killed = false;
	std::shared_ptr<Player> stolen = nullptr;
	int numOfBuildings = 1;
public:
	Character();
	~Character();

	void setId(int _id) { id = _id; }
	int getId() const { return id; }
	void setOwner(std::shared_ptr<Player> player) { owner = player; }
	std::shared_ptr<Player> getOwner() const { return owner; }
	std::string getName() const { return name; }
	bool isKilled() const { return killed; }
	void setKilled(bool kill) { killed = kill; }
	std::shared_ptr<Player> isStolen() const { return stolen; }
	void setStolen(std::shared_ptr<Player> thief) { stolen = thief; }
	int getNumOfBuildings() { return numOfBuildings; }
	void setNumOfBuildings(int num) { numOfBuildings = num; }

	virtual bool execute(ClientCommand command, std::shared_ptr<GameHandler> game) const = 0;
	virtual void getExtraGoldPieces(std::shared_ptr<Player> player, std::shared_ptr<GameHandler> game) const = 0;
	virtual std::string getActionDescription(std::shared_ptr<GameHandler> game) const = 0;
};


