/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:10:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/16 09:24:48 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_if_possible(t_list *map)
{
	(void) map;
	// clone the map, place some 1 in and check if there is still some things, if there are, kys
	return (0);
}

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

int	check_map(t_list *map, size_t x)
{
	int	i;

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
	char	*line;
	char	*content;
	t_list	*new;

	map->map = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-4);
	line = get_next_line(fd);
	map->y = 0;
	while (line)
	{
		map->y++;
		content = ft_strdup(line);
		if (!content)
			return (-1);
		if (map->map)
		{
			new = ft_lstnew(content);
			ft_lstadd_back(&map->map, new);
		}
		else
			map->map = ft_lstnew(content);
		// ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	map->x = ft_strlen((char *) map->map->content) - 1;
	if (check_map(map->map, map->x))
		return (-1);
	if (check_borders(map->map, map->x, map->y))
		return (-2);
	if (check_correct_symbols(map->map))
		return (-3);
	return (0);
}
