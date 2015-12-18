#pragma once
#include <memory>
#include "Player.hpp"
class Building
{
public:
	Building();
	~Building();
	void setOwner(std::shared_ptr<Player> _owner) { owner = _owner; }
private:
	std::shared_ptr<Player> owner = nullptr;
};