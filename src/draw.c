/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:00:18 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/17 17:34:47 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	still_some_collectibles(t_mlx *mlx)
{
	t_list	*map;
	int		i;

	map = mlx->map->map;
	while (map)
	{
		i = 0;
		while (((char *) map->content)[i])
		{
			if (((char *) map->content)[i] == 'C')
				return (1);
			i++;
		}
		map = map->next;
	}
	return (0);
}

void	put_img(int index, t_mlx *mlx, int x, int y)
{
	static t_mlx	*smlx;

	if (index == -1)
	{
		smlx = mlx;
		return ;
	}
	mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
		smlx->img_tile, x * IMG_WIDTH, y * IMG_HEIGHT);
	if (index == 1)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_wall, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 2)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_coll, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 3 && !still_some_collectibles(smlx))
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_exit_open, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 3)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_exit, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 4)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_play, x * IMG_WIDTH, y * IMG_HEIGHT);
}

void	put_line(void *param)
{
	char		*line;
	int			i;
	static int	y = 0;

	if (!param)
	{
		y = 0;
		return ;
	}
	line = (char *)param;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		put_img(0, NULL, i, y);
		if (line[i] == '1')
			put_img(1, NULL, i, y);
		else if (line[i] == 'C')
			put_img(2, NULL, i, y);
		else if (line[i] == 'E')
			put_img(3, NULL, i, y);
		else if (line[i] == 'P')
			put_img(4, NULL, i, y);
		i++;
	}
	y++;
}

int	update(void *param)
{
	t_mlx	*mlx;
	t_map	*map;

	mlx = (t_mlx *)param;
	map = mlx->map;
	ft_lstiter(map->map, &put_line);
	put_line(NULL);
	return (0);
}
