/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:10:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/17 08:34:32 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_list	*clone_map(t_list *map)
{
	t_list	*new_map;
	t_list	*new_element;
	char	*content;

	new_map = NULL;
	while (map)
	{
		content = ft_strdup((char *) map->content);
		new_element = ft_lstnew(content);
		if (!new_element || !content)
		{
			if (content)
				free(content);
			if (new_element)
				free(new_element);
			ft_free("l", new_map);
			return (NULL);
		}
		if (new_map)
			ft_lstadd_back(&new_map, new_element);
		else
			new_map = new_element;
		map = map->next;
	}
	return (new_map);
}

void	check_possible_rec(t_list *map, int x, int y)
{
	t_list	*map_y;

	map_y = get_map_y(map, y - 1);
	if (((char *) map_y->next->content)[x] == '1')
		return ;
	((char *) map_y->next->content)[x] = '1';
	if (((char *) map_y->content)[x] != '1')
		check_possible_rec(map, x, y - 1);
	if (((char *) map_y->next->next->content)[x] != '1')
		check_possible_rec(map, x, y + 1);
	if (((char *) map_y->next->content)[x + 1] != '1')
		check_possible_rec(map, x + 1, y);
	if (((char *) map_y->next->content)[x - 1] != '1')
		check_possible_rec(map, x - 1, y);
}

int	check_if_possible(t_list *parsed_map)
{
	t_list	*map;
	int		i;

	map = clone_map(parsed_map);
	if (!map)
		return (-1);
	parsed_map = map;
	check_possible_rec(map, find_player_x(map), find_player_y(map));
	while (map)
	{
		i = 0;
		while (((char *) map->content)[i])
		{
			if (((char *) map->content)[i] == 'E'
				|| ((char *)map ->content)[i] == 'C')
			{
				ft_free("l", &parsed_map);
				return (-1);
			}
			i++;
		}
		map = map->next;
	}
	ft_free("l", &parsed_map);
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
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->x = ft_strlen((char *) map->map->content) - 1;
	if (check_map(map->map, map->x))
		return (-1);
	if (check_borders(map->map, map->x, map->y))
		return (-2);
	if (check_correct_symbols(map->map))
		return (-3);
	if (check_if_possible(map->map))
		return (-5);
	return (0);
}
