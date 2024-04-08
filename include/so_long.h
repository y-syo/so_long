/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:29:19 by mmoussou          #+#    #+#             */
/*   Updated: 2024/04/08 16:13:19 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// --------------- INCLUDES ---------------

# include "mlx.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

// --------------- CONSTS ---------------

# define WIN_WIDTH 727
# define WIN_HEIGHT 727

# define IMG_WIDTH 64
# define IMG_HEIGHT 64

# define WALL_IMG_PATH "res/img/wall.png"
# define TILE_IMG_PATH "res/img/tile.png"
# define COLL_IMG_PATH "res/img/coll.png"
# define PLAY_IMG_PATH "res/img/player.png"
# define EXIT_IMG_PATH "res/img/exit.png"

# define MLX_W 26
# define MLX_S 22
# define MLX_A 4
# define MLX_D 7

# define FPS_LIMIT 60

// --------------- STRUCTS ---------------

typedef struct s_map
{
	int		x;
	int		y;
	t_list	*map;
}	t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_wall;
	void	*img_tile;
	void	*img_coll;
	void	*img_play;
	void	*img_exit;
	void	*img_exit_open;
	t_map	*map;
}	t_mlx;

// --------------- FUNCS ---------------

int		parse(char **argv, t_map *map);
int		create_map(int fd, t_map *map);

void	move(int x, int y, t_mlx *mlx);
int		update(void *param);
void	put_img(int index, t_mlx *mlx, int x, int y);
int		init_img(t_mlx *mlx);

int		still_some_collectibles(t_mlx *mlx);
int		mlx_end(int event, void *mlx);
int		find_player_x(t_list *map);
int		find_player_y(t_list *map);
t_list	*get_map_y(t_list *map, int y);
int		check_if_possible(t_list *parsed_map);

#endif
