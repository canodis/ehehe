/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:40:15 by rtosun            #+#    #+#             */
/*   Updated: 2022/04/07 16:47:01 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_mlx_put_image(t_game **game, void *obj, int x, int y)
{
	mlx_put_image_to_window((*game)->mlx, (*game)->window,
		obj, x * (*game)->m, y * (*game)->m);
}

static void	ft_create_object(t_game **game, char obj, int x, int y)
{
	if (obj == 'P')
	{
		(*game)->player_x = x;
		(*game)->player_y = y;
		(*game)->client->player.position.x = x;
		(*game)->client->player.position.y = y;
	}
	else if (obj == 'C')
	{
		(*game)->coin_count++;
	}
}

bool	ft_create_map(t_game **game)
{
	int	x;
	int	y;

	(*game)->mlx = mlx_init();
	(*game)->coin_count = 0;
	(*game)->window = mlx_new_window((*game)->mlx, (*game)->max_x * (*game)->m,
			(*game)->max_y * (*game)->m, "So_Long");
	convertoxpm(game);
	y = -1;
	while (++y < (*game)-> max_y)
	{
		x = -1;
		while (++x < (*game)-> max_x)
		{
			ft_create_object(game, (*game)->map[y][x], x, y);
		}
	}
	return (true);
}
