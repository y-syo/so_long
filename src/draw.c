/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:00:18 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/01 21:00:31 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_img(int index, t_mlx *mlx, int x, int y)
{
	static t_mlx	*smlx;

	if (index == -1)
	{
		smlx = mlx;
		return ;
	}
	if (!smlx)
		return ;
	mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
		smlx->img_tile, x * IMG_WIDTH, y * IMG_HEIGHT);
	if (index == 1)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_wall, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 2)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_coll, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 3)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_exit, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 4)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr,
			smlx->img_play, x * IMG_WIDTH, y * IMG_HEIGHT);
}

void	draw_line(void *param)
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
	ft_lstiter(map->map, &draw_line);
	draw_line(NULL);
	return (0);
}
