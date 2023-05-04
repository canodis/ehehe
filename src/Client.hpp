#pragma once 

# include <string.h>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <thread>
#include <ctime>
#include <vector>
class Client;
#include "../include/so_long.h"
#include <string>
#include <sstream>

struct vector2 {
	int x, y;
};

class	Player {
public:
	Player(int fd, int posx, int posy) {
	this->fd = fd;
	this->position.x = posx;
	this->position.y = posy;
	this->username = "canodis";
}
	Player() { };
	vector2 position;
	std::string username;
	int		fd;
};

struct Request {
	std::string username;
    int client_fd;
    int x_pos;
    int y_pos;
};


class Client {
public:
	struct l_game *game;

	struct sockaddr_in	serv_addr;
	Client(const char *ip_adress, const char *username = "canodis", int port = 8080);
	Client(int port = 8080);
	void	*pimage1;
	void	*pimage2;
	Player	player;
	std::vector<Player *>	allPlayers;
	const char	*uname;
	int		pIndex;
	char	res[64];
	char	request[64];
	int		sock;
	void	SocketInit(const char *ip_adress, int port);
	void	requestThread();
	void	deletePlayer(int fd);
	void	parse_requests(const std::string& input);
	void	PositionRequest(std::istringstream &ss);
	void	LoginRequest(std::istringstream &ss);
	void	response();
	void	draw();
	static int loop(void *c);

};