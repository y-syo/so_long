/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:29:19 by mmoussou          #+#    #+#             */
/*   Updated: 2024/03/22 08:55:16 by mmoussou         ###   ########.fr       */
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

# ifndef WIN_WIDTH
#  define WIN_WIDTH 727
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 727
# endif

# ifndef IMG_WIDTH
#  define IMG_WIDTH 64
# endif

# ifndef IMG_HEIGHT
#  define IMG_HEIGHT 64
# endif

# ifndef WALL_IMG_PATH
#  define WALL_IMG_PATH "res/img/wall.png"
# endif

# ifndef TILE_IMG_PATH
#  define TILE_IMG_PATH "res/img/tile.png"
# endif

# ifndef COLL_IMG_PATH
#  define COLL_IMG_PATH "res/img/coll.png"
# endif

# ifndef PLAY_IMG_PATH
#  define PLAY_IMG_PATH "res/img/player.png"
# endif

# ifndef EXIT_IMG_PATH
#  define EXIT_IMG_PATH "res/img/exit.png"
# endif

# ifndef MLX_W
#  define MLX_W 26
# endif

# ifndef MLX_S
#  define MLX_S 22
# endif

# ifndef MLX_A
#  define MLX_A 4
# endif

# ifndef MLX_D
#  define MLX_D 7
# endif

# ifndef FPS_LIMIT
#  define FPS_LIMIT 60
# endif

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
