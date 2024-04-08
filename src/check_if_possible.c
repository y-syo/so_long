/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_possible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:44:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/08 14:01:44 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	remove_exit(t_list *map)
{
	int	i;

	while (map)
	{
		i = 0;
		while (((char *)(map->content))[i])
		{
			if (((char *)(map->content))[i] == 'E')
			{
				((char *)(map ->content))[i] = '1';
				return ;
			}
			i++;
		}
		map = map->next;
	}
}

t_list	*clone_map(t_list *map)
{
	static t_list	*new_map;
	t_list			*new_element;
	char			*content;

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
			ft_free("l", &new_map);
			return (NULL);
		}
		if (new_map)
			ft_lstadd_back(&new_map, new_element);
		else
			new_map = new_element;
		map = map->next;
	}
	remove_exit(new_map);
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
