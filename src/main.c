/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:11:53 by mmoussou          #+#    #+#             */
/*   Updated: 2024/02/27 12:18:35 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mlx_end(int event, void *mlx)
{
	if (!event)
		mlx_loop_end(mlx);
	return (0);
}

int	find_player_x(t_list *map)
{
	int	i;
	int	x;

	x = 1;
	while (map)
	{
		i = 0;
		while (((char *)(map->content))[i])
		{
			if (((char *)(map->content))[i] == 'P')
				x = i;
			i++;
		}
		map = map->next;
	}
	return (x);
}

t_list	*get_map_y(t_list *map)
{
	int	i;

	while (map->next)
	{
		i = 0;
		while (((char *)(map->next->content))[i])
		{
			if (((char *)(map->next->content))[i] == 'P')
				return (map);
			i++;
		}
		map = map->next;
	}
	return (NULL);
}

int	have_moved(t_list *map)
{
	int	i;
	int	counter;

	counter = 0;
	while (map)
	{
		i = 0;
		while(((char *) map->content)[i])
		{
			if (((char *) map->content)[i] == 'P')
				counter++;
			i++;
		}
		map = map->next;
	}
	if (counter > 1)
		return (1);
	return (0);
}

void	move(int x, int y, t_mlx *mlx)
{
	t_list		*map;
	t_list		*player_y;
	int			player_x;
	static int	count = 0;

	map = mlx->map->map;
	player_x = find_player_x(map);
	player_y = get_map_y(map);
	if (x > 0)
		if (((char *) player_y->next->content)[player_x + 1] != '1')
			((char *) player_y->next->content)[player_x + 1] = 'P';
	if (x < 0)
		if (((char *) player_y->next->content)[player_x - 1] != '1')
			((char *) player_y->next->content)[player_x - 1] = 'P';
	if (y > 0)
		if (((char *) player_y->next->next->content)[player_x] != '1')
			((char *) player_y->next->next->content)[player_x] = 'P';
	if (y < 0)
		if (((char *) player_y->content)[player_x] != '1')
			((char *) player_y->content)[player_x] = 'P';
	if (have_moved(map))
	{
		((char *) player_y->next->content)[player_x] = '0';
		ft_printf("I am not obsessed over a fictionnal character, anyways here your movement counter : %d\n", count++);
	}
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

void	put_img(int mode, int index, t_mlx *mlx, int x, int y)
{
	static t_mlx	*smlx;
	if (mode == 1)
	{
		smlx = mlx;
		return ;
	}
	if (!smlx)
		return ;
	mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr, smlx->img_tile, x * IMG_WIDTH, y * IMG_HEIGHT);
	if (index == 1)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr, smlx->img_wall, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 2)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr, smlx->img_coll, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 3)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr, smlx->img_exit, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (index == 4)
		mlx_put_image_to_window(smlx->mlx_ptr, smlx->win_ptr, smlx->img_play, x * IMG_WIDTH, y * IMG_HEIGHT);

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
		if (line[i] == '0')
			put_img(0, 0, NULL, i, y);
		else if (line[i] == '1')
			put_img(0, 1, NULL, i, y);
		else if (line[i] == 'C')
			put_img(0, 2, NULL, i, y);
		else if (line[i] == 'E')
			put_img(0, 3, NULL, i, y);
		else
			put_img(0, 4, NULL, i, y);
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
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, map.x * IMG_WIDTH, map.y * IMG_HEIGHT, argv[0]);
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
