/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:38:52 by rtosun            #+#    #+#             */
/*   Updated: 2022/04/08 14:18:35 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "Client.hpp"

static bool	check_name(char *name)
{
	char	*find;

	find = strrchr(name, '.');
	if (!find || strlen(find) != 4)
		return (false);
	if (strncmp(find, ".ber", 4) == 0)
		return (true);
	return (false);
}

void	Client::requestThread()
{
	fd_set readfds;

	FD_ZERO(&readfds);
	FD_SET(this->sock, &readfds);

	while (666)
	{
		select(this->sock + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(this->sock, &readfds))
		{
			memset(this->request, 0, sizeof(request));

			if (recv(this->sock, this->request, sizeof(this->request), 0) <= 0)
			{
				::close(this->sock);
				std::cerr << "Server disconnected" << std::endl;
				exit(1);
			}
			this->parse_requests(this->request);
		}
	}
}

int	Client::loop(void *c)
{
	Client	*client = (Client *)c;

	client->draw();
	usleep(10000);
	return (0);
	
}

int	main(int argc, char **argv)
{
	t_game	*game;
	game = (t_game *)malloc(sizeof(t_game));
	if (argc != 2) {
		printf("Lutfen kullanici adi giriniz :\n./so_long [nickname]");
		return (0);
	}
	Client	client("193.164.7.169", argv[1], 8080);
	client.game = game;
	game->client = &client;
	game->m = 50;
	if (!game)
		return (0);
	if (!(check_name("maps/map_2.ber")) || !(ft_init_map(&game, argv)))
		print_message("map yuklenemedi !", &game);
	game->player_move = 0;
	
	mlx_key_hook(game->window, ft_key_events, &game);
	mlx_hook(game->window, 17, 0, exit_hook, &game);
	std::thread t1(&Client::requestThread, &client);
	t1.detach();
	mlx_loop_hook(game->mlx, &Client::loop, &client);
	mlx_loop(game->mlx);
	return (0);
}
