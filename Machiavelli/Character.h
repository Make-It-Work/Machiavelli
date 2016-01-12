#pragma once
#include <string>
#include <memory>
#include "Player.hpp"
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
	int getId() { return id; }
	void setOwner(std::shared_ptr<Player> player) { owner = player; }
	std::shared_ptr<Player> getOwner() { return owner; }
	std::string getName() { return name; }
	virtual void execute() = 0;
};


