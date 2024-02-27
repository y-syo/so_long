/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:10:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/02/26 05:09:07 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	parse(char **argv, t_map *map)
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
			return ;
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
}
