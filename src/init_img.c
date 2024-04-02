/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:05:08 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/02 17:05:12 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_img_door(t_mlx *mlx)
{
	int	w;
	int	h;

	mlx->img_exit = mlx_png_file_to_image(mlx->mlx_ptr, EXIT_IMG_PATH, &w, &h);
	if (!mlx->img_exit)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_tile);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_coll);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_play);
		return (-4);
	}
	mlx->img_exit_open = mlx_png_file_to_image(mlx->mlx_ptr,
			"res/img/goku.png", NULL, NULL);
	if (!mlx->img_exit_open)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_tile);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_coll);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_play);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_exit);
		return (-4);
	}
	return (0);
}

int	init_img_objects(t_mlx *mlx)
{
	int	w;
	int	h;

	mlx->img_coll = mlx_png_file_to_image(mlx->mlx_ptr, COLL_IMG_PATH, &w, &h);
	if (!mlx->img_coll)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_tile);
		return (-4);
	}
	mlx->img_play = mlx_png_file_to_image(mlx->mlx_ptr, PLAY_IMG_PATH, &w, &h);
	if (!mlx->img_play)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_tile);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_coll);
		return (-4);
	}
	return (init_img_door(mlx));
}

int	init_img(t_mlx *mlx)
{
	int	w;
	int	h;

	mlx->img_wall = mlx_png_file_to_image(mlx->mlx_ptr, WALL_IMG_PATH, &w, &h);
	if (!mlx->img_wall)
		return (-4);
	mlx->img_tile = mlx_png_file_to_image(mlx->mlx_ptr, TILE_IMG_PATH, &w, &h);
	if (!mlx->img_tile)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
		return (-4);
	}
	return (init_img_objects(mlx));
}
