#include "Client.hpp"

Client::Client(const char *ip_adress, const char *username, int port) : uname(username)
{
	int a;

	pIndex = 666;
	player.position.x = 0;
	player.position.y = 0;
	player.username = std::string(uname);
	// pimage1 = mlx_xpm_file_to_image(game->mlx, "./Sprites/sprite1.xpm", &a, &a);
	// pimage2 = mlx_xpm_file_to_image(game->mlx, "./Sprites/sprite2.xpm", &a, &a);
	SocketInit(ip_adress, port);
}

void	Client::SocketInit(const char *ip_adress, int port)
{
	struct sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Socket creation error" << std::endl;
		exit(31);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip_adress, &serv_addr.sin_addr) <= 0) {
		std::cerr << "Invalid address/ Address not supported" << std::endl;
		exit(1);
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "Connection failed" << std::endl;
		exit(1);
	}
}

void Client::parse_requests(const std::string& input)
{
	std::size_t start = 0, end = 0;

	while ((start = input.find('/', start)) != std::string::npos) {
		end = input.find('*', start);
		if (end == std::string::npos) {
			break;
		}
		std::string substr = input.substr(start + 1, end - start - 1);
		if (substr.find("Pos") == 0) {
			std::istringstream ss(substr.substr(3));
			this->PositionRequest(ss);
		} else if (substr.find("New") == 0) {
			std::istringstream ss(substr.substr(3));
			int new_fd;
			ss >> new_fd;
			allPlayers.push_back(new Player(new_fd, 50, 50));
		} else if (substr.find("Left") == 0) {
			std::istringstream ss(substr.substr(4));
			int fd;
			ss >> fd;
			deletePlayer(fd);
		} else if (substr.find("Login") == 0) {
			std::istringstream ss(substr.substr(5));
			LoginRequest(ss);
		}
		start = end + 1;
	}
}

void	Client::PositionRequest(std::istringstream &ss)
{
	Request req;
    int fd;
	ss >> req.client_fd >> req.username >> req.x_pos >> req.y_pos;
    fd = req.client_fd;
	auto it = std::find_if(allPlayers.begin(), allPlayers.end(), [&fd](const Player* player) {
		return player->fd == fd;
	});

	if ((*it)) {
		(*it)->username = req.username;
		(*it)->position.x = req.x_pos;
		(*it)->position.y = req.y_pos;
	}
}

void	Client::LoginRequest(std::istringstream &ss)
{
	int playerCount;
	int	playerFd;

	ss >> playerCount;
	ss >> pIndex;
	for (int i = 0; i < playerCount - 1; i++) {
		ss >> playerFd;
		allPlayers.push_back(new Player(playerFd, 1, 1));
	}
	response();
}

void	Client::deletePlayer(int fd) {
	auto it = std::find_if(allPlayers.begin(), allPlayers.end(), [&fd](const Player* player) {
		return player->fd == fd;
	});
	if (it != allPlayers.end()) {
		delete *it;
		allPlayers.erase(it);
	}
}

void	Client::response()
{
	if (pIndex == 666)
		return ;
	sprintf(this->res, "/Pos%d %s %d %d*", pIndex, this->uname, player.position.x, player.position.y);
	send(this->sock, this->res, strlen(this->res), 0);
}

void	Client::draw()
{
	// mlx_clear_window(game->mlx, game->window);
	for (int y = 0; y < game->max_y; y++)
	{
		for (int x = 0; x < game->max_x; x++)
		{
			if (game->map[y][x] == '0') {
				mlx_put_image_to_window(game->mlx, game->window, game->bg, x * 50, y * 50);
			}
			else if (game->map[y][x] == '1') {
				mlx_put_image_to_window(game->mlx, game->window, game->rock, x * 50, y * 50);
				
			}
			else if (game->map[y][x] == 'C') {
				mlx_put_image_to_window(game->mlx, game->window, game->coin, x * 50, y * 50);				
			}
			else if (game->map[y][x] == 'E') {
				mlx_put_image_to_window(game->mlx, game->window, game->exit, x * 50, y * 50);
			}
		}
	}
	for (int i = 0; i < allPlayers.size(); i++) {
		mlx_put_image_to_window(game->mlx, game->window, game->enemy, allPlayers[i]->position.x * 50, allPlayers[i]->position.y * 50);
		mlx_string_put(game->mlx, game->window, (allPlayers[i]->position.x * 50) + 10, allPlayers[i]->position.y * 50 - 20, 0x00FF00, allPlayers[i]->username.c_str());
	}
	mlx_put_image_to_window(game->mlx, game->window, game->player, player.position.x * 50, player.position.y * 50);
	mlx_string_put(game->mlx, game->window, player.position.x * 50 + 10, player.position.y * 50 - 20, 0x00FF00, player.username.c_str());
}