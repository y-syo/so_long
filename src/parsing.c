/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:10:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/14 20:32:42 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_all_collectibles(t_list *map)
{
	// clone the map, place some 1 in and check if there is still some things, if there are, kys
}

int	check_map(t_list *map, size_t x)
{
	while (map)
	{
		if (x != ft_strlen((char *) map->content) - 1)
			return (-1);
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
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	map->x = ft_strlen((char *) map->map->content) - 1;
	return (check_map(map->map, map->x));
}
