/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_xpms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:31:36 by rtosun            #+#    #+#             */
/*   Updated: 2022/04/03 17:02:27 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	*mlx_to_image(t_game **game, char *path)
{
	return (mlx_xpm_file_to_image((*game)->mlx,
			path, &(*game)->sprite_size, &(*game)->sprite_size));
}

void	convertoxpm(t_game **game)
{
	(*game)->exit = mlx_to_image(game, "./sprites/exit.xpm");
	(*game)->bg = mlx_to_image(game, "./sprites/background.xpm");
	(*game)->rock = mlx_to_image(game, "./sprites/rock.xpm");
	(*game)->coin = mlx_to_image(game, "./sprites/coin/0.xpm");
	(*game)->enemy = mlx_to_image(game, "./sprites/enemies/0.xpm");
	(*game)->player = mlx_to_image(game, "./sprites/player/0.xpm");
}
