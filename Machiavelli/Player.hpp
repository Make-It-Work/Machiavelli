//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include <memory>
#include <string>
#include "Socket.h"

class Player {
public:
	Player() {}
	Player(const std::string& name, const int& age) : name{ name }, age { age } {}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }

	int get_age() const { return age; }
	void set_age(const int& new_age) { age = new_age; }

	void set_socket(std::shared_ptr<Socket> new_socket) { socket = new_socket; }
	std::shared_ptr<Socket> get_socket() const { return socket; }

	
private:
	std::string name;
	int age;
	std::shared_ptr<Socket> socket;
	
};

#endif /* Player_hpp */
