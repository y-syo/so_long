/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:11:53 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/22 08:57:52 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	destroy_images(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_tile);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_coll);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_play);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_exit);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_exit_open);
}

int	quit(int status, t_map *map)
{
	char	*msg_status;

	if (status == -4)
		msg_status = "Invalid file.";
	else
	{
		ft_free("l", &map->map);
		if (status == -1)
			msg_status = "Incorrect map.";
		else if (status == -2)
			msg_status = "map is not closed.";
		else if (status == -3)
			msg_status = "symbols issue.";
		else if (status == -5)
			msg_status = "Impossible map.";
		else if (status == -6)
			msg_status = "memory allocation failed.";
	}
	ft_printf("Error: %s\n", msg_status);
	return (-1);
}

void	mlx_setup(t_mlx *mlx)
{
	mlx_on_event(mlx->mlx_ptr, mlx->win_ptr, 5, mlx_end, mlx->mlx_ptr);
	mlx_on_event(mlx->mlx_ptr, mlx->win_ptr, MLX_KEYDOWN, key_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_set_fps_goal(mlx->mlx_ptr, FPS_LIMIT);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	map;
	int		status;

	if (argc != 2)
		return (-1);
	status = parse(argv, &map);
	if (status)
		return (quit(status, &map));
	put_img(-1, &mlx, 6, 9);
	mlx.map = &map;
	mlx.mlx_ptr = mlx_init();
	status = init_img(&mlx);
	if (status)
		return (quit(status, &map));
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr,
			map.x * IMG_WIDTH, map.y * IMG_HEIGHT, argv[0]);
	mlx_setup(&mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_images(&mlx);
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	mlx_destroy_display(mlx.mlx_ptr);
	ft_free("l", &map.map);
	return (0);
}
