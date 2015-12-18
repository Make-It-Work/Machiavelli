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
	virtual void execute() = 0;
};


