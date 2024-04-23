/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:10:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/23 13:28:41 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_borders(t_list *map, int x_map, int y_map)
{
	int	i;
	int	y;

	y = 0;
	while (map)
	{
		i = 0;
		if (y == 0 || y == y_map - 1)
		{
			while (((char *) map->content)[i]
				&& ((char *) map->content)[i] != '\n')
			{
				if (((char *) map->content)[i] != '1')
					return (-1);
				i++;
			}
		}
		else
			if (((char *) map->content)[0] != '1'
			|| ((char *) map->content)[x_map - 1] != '1')
				return (-1);
		y++;
		map = map->next;
	}
	return (0);
}

int	check_correct_symbols(t_list *map)
{
	int	c_play;
	int	c_exit;
	int	c_coll;
	int	i;

	c_play = 0;
	c_exit = 0;
	c_coll = 0;
	while (map)
	{
		i = -1;
		while (((char *) map->content)[++i])
		{
			if (((char *) map->content)[i] == 'P')
				c_play++;
			else if (((char *) map->content)[i] == 'E')
				c_exit++;
			else if (((char *)map ->content)[i] == 'C')
				c_coll++;
		}
		map = map->next;
	}
	if (c_play == 1 && c_exit == 1 && c_coll > 0)
		return (0);
	return (-1);
}

int	check_map(t_list *map, size_t x, size_t y)
{
	int	i;

	if (y < 1 || x < 1)
		return (-1);
	while (map)
	{
		if (x != ft_strlen((char *) map->content) - 1)
			return (-1);
		i = 0;
		while (((char *)map->content)[i] && ((char *)map->content)[i] != '\n')
		{
			if (((char *) map->content)[i] != '1'
				&& ((char *) map->content)[i] != '0'
				&& ((char *) map->content)[i] != 'C'
				&& ((char *) map->content)[i] != 'E'
				&& ((char *) map->content)[i] != 'P')
				return (-1);
			i++;
		}
		map = map->next;
	}
	return (0);
}

int	parse(char **argv, t_map *map)
{
	int		fd;

	map->map = NULL;
	if (ft_strlen(argv[1]) < 4
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
		return (-4);
	fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		return (-4);
	map->map = NULL;
	map->y = 0;
	if (create_map(fd, map, NULL))
		return (-6);
	if (map->map == NULL)
		return (-4);
	map->x = ft_strlen((char *) map->map->content) - 1;
	if (check_map(map->map, map->x, map->y))
		return (-1);
	if (check_borders(map->map, map->x, map->y))
		return (-2);
	if (check_correct_symbols(map->map))
		return (-3);
	if (check_if_possible(map->map))
		return (-5);
	return (0);
}
