/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:20:17 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/01 00:14:03 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../includes/Color.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

 #ifndef M_PI
  # define M_PI 3.14
 #endif
# define TILE_SIZE 30
# define FOV 60
# define PLAYER_SPEED 2
# define ROTATION_SPEED 0.045

typedef struct s_img
{
	void 	*img;
	char 	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_player //the player structure
{
 	int  player_x; // player x position in pixels
 	int  player_y; // player y position in pixels
 	double angle; // player angle
 	float fov_rd; // field of view in radians
 	int  rot; // rotation flag
 	int  l_r; // left right flag
 	int  u_d; // up down flag
} t_player;

typedef struct s_ray //the ray structure
{
 	double ray_ngl; // ray angle
 	double distance; // distance to the wall
 	int  flag;  // flag for the wall
} t_ray;

typedef struct s_data
{
	char **map2d; // the map
	int p_x; // player x position in the map
	int p_y; // player y position in the map
	int  w_map;  // map width
 	int  h_map;  // map height
} t_data;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *mlx_win;
	void *img;
	t_ray *ray; // ray structure
	t_data *data; // data structure
	t_player *player; // player structure
} t_mlx;

void my_mlx_pixel_put(t_img *img, int x, int y, int color);

void cast_rays(t_mlx *mlx, t_img *img);
float get_v_inter(t_mlx *mlx, float angl);
float get_h_inter(t_mlx *mlx, float angl);
int wall_hit(float x, float y, t_mlx *mlx);
int inter_check(float angle, float *inter, float *step, int is_horizon);
int unit_circle(float angle, char c);

void render_wall(t_mlx *mlx, int ray, t_img *img);
void draw_wall(t_mlx *mlx, t_img *img,int ray, int t_pix, int b_pix);
int  get_color(t_mlx *mlx, int flag);

float nor_angle(float angle);

int handle_keypress(int keysym, void *ml);
int handle_keyrelease(int keysym, void *ml);
void hook(t_mlx *mlx, double move_x, double move_y);

void rotate_player(t_mlx *mlx, int i);
void move_player(t_mlx *mlx, double move_x, double move_y);

#endif
