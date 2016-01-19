#pragma once
#include <memory>
#include "Player.hpp"
class Building
{
public:
	Building();
	~Building();
	void setOwner(std::shared_ptr<Player> _owner) { owner = _owner; }
	std::shared_ptr<Player> getOwner() const{ return owner; }
	void setColor(std::string colour) { color = colour; }
	std::string getColor() const { return color; }
	void setName(std::string _name) { name = _name; }
	std::string getName() const { return name; }
	void setCost(int c) { cost = c; }
	int getCost() const { return cost; }
	void setPoints(int p) { points = p; }
	int getPoints() const { return points; }
	bool isPlayed() const { return played; }
	void setPlayed(bool play) { played = play; }

protected:
	std::shared_ptr<Player> owner = nullptr;
	std::string color = "";
	std::string name = "";
	int cost;
	int points;
	bool played;
};