/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:11:53 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/01 21:00:46 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mlx_end(int event, void *mlx)
{
	if (!event)
		mlx_loop_end(mlx);
	return (0);
}

int	key_hook(int key, void *data)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)data;
	if (key == MLX_W)
		move(0, -1, mlx);
	else if (key == MLX_S)
		move(0, 1, mlx);
	else if (key == MLX_A)
		move(-1, 0, mlx);
	else if (key == MLX_D)
		move(1, 0, mlx);
	else if (key == 41)
		mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	init_img(t_mlx *mlx)
{
	int	w;
	int	h;

	mlx->img_wall = mlx_png_file_to_image(mlx->mlx_ptr, WALL_IMG_PATH, &w, &h);
	mlx->img_tile = mlx_png_file_to_image(mlx->mlx_ptr, TILE_IMG_PATH, &w, &h);
	mlx->img_coll = mlx_png_file_to_image(mlx->mlx_ptr, COLL_IMG_PATH, &w, &h);
	mlx->img_play = mlx_png_file_to_image(mlx->mlx_ptr, PLAY_IMG_PATH, &w, &h);
	mlx->img_exit = mlx_png_file_to_image(mlx->mlx_ptr, EXIT_IMG_PATH, &w, &h);
	return (0);
}

void	destroy_images(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_tile);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_coll);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_play);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_exit);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	map;

	if (argc != 2)
		return (-1);
	parse(argv, &map);
	put_img(1, 0, &mlx, 6, 9);
	mlx.map = &map;
	mlx.mlx_ptr = mlx_init();
	init_img(&mlx);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr,
			map.x * IMG_WIDTH, map.y * IMG_HEIGHT, argv[0]);
	mlx_on_event(mlx.mlx_ptr, mlx.win_ptr, 5, mlx_end, mlx.mlx_ptr);
	mlx_on_event(mlx.mlx_ptr, mlx.win_ptr, MLX_KEYDOWN, key_hook, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, update, &mlx);
	mlx_set_fps_goal(mlx.mlx_ptr, FPS_LIMIT);
	mlx_loop(mlx.mlx_ptr);
	destroy_images(&mlx);
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	mlx_destroy_display(mlx.mlx_ptr);
	return (0);
}
