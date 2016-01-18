//
//  ClientCommand.h
//  socketexample
//
//  Created by Bob Polis on 27/11/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef __socketexample__ClientCommand__
#define __socketexample__ClientCommand__

#include <string>
#include <memory>
#include <algorithm>

class Player;
class Socket;

class ClientCommand {
public:
	ClientCommand(const std::string& cmd, std::shared_ptr<Socket> client, std::shared_ptr<Player> player)
	: cmd{cmd}, client {client}, player{player} {}

    std::string get_cmd() const { return cmd; }
	std::shared_ptr<Socket> get_client() const { return client; }
    std::shared_ptr<Player> get_player() const { return player; }

	bool is_number() {
		return !cmd.empty() && std::find_if(cmd.begin(),
			cmd.end(), [](char c) { return !isdigit(c); }) == cmd.end();
	};
private:
    std::string cmd;
	std::shared_ptr<Socket> client;
    std::shared_ptr<Player> player;
};

#endif /* defined(__socketexample__ClientCommand__) */
