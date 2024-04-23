/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:54:20 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/23 14:32:50 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	can_go_here(t_mlx *mlx, char here)
{
	if (still_some_collectibles(mlx))
		return (here != '1' && here != 'E');
	else
	{
		if (here == 'E')
		{
			mlx_end(0, mlx->mlx_ptr);
			return (-1);
		}
		return (here != '1');
	}
}

void	move(int x, int y, t_mlx *mlx)
{
	t_list		*map;
	t_list		*player_y;
	int			player_x;
	static int	count = 1;

	map = mlx->map->map;
	player_x = find_player_x(map);
	player_y = get_map_y(map, find_player_y(map) - 1);
	if (x > 0)
		if (can_go_here(mlx, ((char *)player_y->next->content)[player_x + 1]))
			((char *) player_y->next->content)[player_x + 1] = 'P';
	if (x < 0)
		if (can_go_here(mlx, ((char *)player_y->next->content)[player_x - 1]))
			((char *) player_y->next->content)[player_x - 1] = 'P';
	if (y > 0)
		if (can_go_here(mlx, ((char *)player_y->next->next->content)[player_x]))
			((char *) player_y->next->next->content)[player_x] = 'P';
	if (y < 0)
		if (can_go_here(mlx, ((char *)player_y->content)[player_x]))
			((char *) player_y->content)[player_x] = 'P';
	if (have_moved(map))
	{
		((char *) player_y->next->content)[player_x] = '0';
		ft_printf("This is a very cool moves counter : %d\n", count++);
	}
}
