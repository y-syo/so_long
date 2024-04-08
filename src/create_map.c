/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:45:47 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/08 14:15:19 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*add_newline(char *line)
{
	char	*final;
	int		i;

	final = ft_calloc(sizeof(char), ft_strlen(line) + 2);
	if (!final)
		return (final);
	final[ft_strlen(line)] = '\n';
	final[ft_strlen(line) + 1] = 0;
	i = 0;
	while (line[i])
	{
		final[i] = line[i];
		i++;
	}
	return (final);
}

int	fix_last_line(t_map *map)
{
	t_list	*last;
	char	*content;

	last = ft_lstlast(map->map);
	if (((char *)(last->content))
		[ft_strlen((char *)(last->content)) - 1] == '\n')
		return (0);
	content = add_newline(last->content);
	if (!content)
		return (-1);
	free(last->content);
	last->content = content;
	return (0);
}

int	create_map(int fd, t_map *map)
{
	char	*line;
	char	*content;
	t_list	*new;

	line = get_next_line(fd);
	while (line)
	{
		map->y++;
		content = ft_strdup(line);
		new = ft_lstnew(content);
		if (!new || !content)
		{
			ft_free("llc", &map->map, &new, &content);
			return (-1);
		}
		if (map->map)
			ft_lstadd_back(&map->map, new);
		else
			map->map = new;
		free(line);
		line = get_next_line(fd);
	}
	if (fix_last_line(map))
		return (-1);
	return (0);
}
