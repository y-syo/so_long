/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:54:20 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/01 21:01:45 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

t_list	*get_map_y(t_list *map)
{
	int	i;

	while (map->next)
	{
		i = 0;
		while (((char *)(map->next->content))[i])
		{
			if (((char *)(map->next->content))[i] == 'P')
				return (map);
			i++;
		}
		map = map->next;
	}
	return (NULL);
}

int	have_moved(t_list *map)
{
	int	i;
	int	counter;

	counter = 0;
	while (map)
	{
		i = 0;
		while (((char *) map->content)[i])
		{
			if (((char *) map->content)[i] == 'P')
				counter++;
			i++;
		}
		map = map->next;
	}
	if (counter > 1)
		return (1);
	return (0);
}

void	move(int x, int y, t_mlx *mlx)
{
	t_list		*map;
	t_list		*player_y;
	int			player_x;
	static int	count = 0;

	map = mlx->map->map;
	player_x = find_player_x(map);
	player_y = get_map_y(map);
	if (x > 0)
		if (((char *) player_y->next->content)[player_x + 1] != '1')
			((char *) player_y->next->content)[player_x + 1] = 'P';
	if (x < 0)
		if (((char *) player_y->next->content)[player_x - 1] != '1')
			((char *) player_y->next->content)[player_x - 1] = 'P';
	if (y > 0)
		if (((char *) player_y->next->next->content)[player_x] != '1')
			((char *) player_y->next->next->content)[player_x] = 'P';
	if (y < 0)
		if (((char *) player_y->content)[player_x] != '1')
			((char *) player_y->content)[player_x] = 'P';
	if (have_moved(map))
	{
		((char *) player_y->next->content)[player_x] = '0';
		ft_printf("This is a very cool moves counter : %d\n", count++);
	}
}
