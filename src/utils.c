/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:43:12 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/17 08:46:42 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mlx_end(int event, void *mlx)
{
	if (!event)
		mlx_loop_end(mlx);
	return (0);
}

int	find_player_x(t_list *map)
{
	int	i;
	int	x;

	x = 1;
	while (map)
	{
		i = 0;
		while (((char *)(map->content))[i])
		{
			if (((char *)(map->content))[i] == 'P')
				x = i;
			i++;
		}
		map = map->next;
	}
	return (x);
}

int	find_player_y(t_list *map)
{
	int	i;
	int	y;

	y = 0;
	while (map)
	{
		i = 0;
		while (((char *)(map->content))[i])
		{
			if (((char *)(map->content))[i] == 'P')
				return (y);
			i++;
		}
		y++;
		map = map->next;
	}
	return (-1);
}

t_list	*get_map_y(t_list *map, int y)
{
	while (map->next && y)
	{
		y--;
		map = map->next;
	}
	return (map);
}
