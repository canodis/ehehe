/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:30:50 by rtosun            #+#    #+#             */
/*   Updated: 2022/04/08 13:35:21 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(t_game **game)
{
	int	x;

	x = 0;
	if (!(*game)->map)
	{
		while (x < (*game)->max_y)
			free((*game)->map[x++]);
	}
}

void	print_message(const char *message, t_game **game)
{
	printf("%s", message);
	free_map(game);
	exit (0);
}

char	*ft_strndup(char *src, int j)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc((j + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (i < j && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_str_join(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ((strlen(left_str) + strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i])
			str[i] = left_str[i];
	while (buff[j])
		str[i++] = buff[j++];
	str[strlen(left_str) + strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

int	exit_hook(void **g)
{
	t_game **game = (t_game **)g;

	free_map(game);
	free((*game)->player);
	free((*game)->coin);
	free((*game)->map);
	free((*game)->rock);
	free((*game)->exit);
	free((*game)->bg);
	mlx_destroy_window((*game)->mlx, (*game)->window);
	exit(0);
}
