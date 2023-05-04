/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:09:30 by rtosun            #+#    #+#             */
/*   Updated: 2022/04/08 12:55:12 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../mlx-linux/mlx.h"
# include "fcntl.h"
# include <string.h>
struct l_game;
#include "../src/Client.hpp"


# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct l_game
{
	char	**map;
	int		max_x;
	int		max_y;
	int		player_x;
	int		player_y;
	int		m;
	int		coin_count;
	int		player_move;
	int		sprite_size;
	void	*window;
	void	*mlx;
	void	*player;
	void	*coin;
	void	*exit;
	void	*enemy;
	void	*bg;
	void	*rock;
	Client	*client;
}	t_game;

char	**ft_split_fs(char *str, char *charset, int *ln);
char	*ft_strndup(char *tmp, int len);
char	*ft_strndup(char *src, int j);
bool	ft_init_map(t_game **game, char **argv);
void	print_message(const char *message, t_game **game);
bool	ft_create_map(t_game **game);
void	convertoxpm(t_game **game);
int		ft_key_events(int key_code, void **g);
void	ft_mlx_put_image(t_game **game, void *obj, int x, int y);
char	*ft_str_join(char *left_str, char *buff);
int		exit_hook(void **g);
void	free_map(t_game **game);

#endif