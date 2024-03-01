/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:47:56 by fgonzale          #+#    #+#             */
/*   Updated: 2024/02/29 19:03:34 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int unit_circle(float angle, char c) // check the unit circle
{
 if (c == 'x')
 {
  if (angle > 0 && angle < M_PI)
   return (1);
 }
 else if (c == 'y')
 {
  if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
   return (1);
 }
 return (0);
}

int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
{
 if (is_horizon)
 {
  if (angle > 0 && angle < M_PI)
  {
   *inter += TILE_SIZE;
   return (-1);
  }
  *step *= -1;
 }
 else
 {
  if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
  {
   *inter += TILE_SIZE;
   return (-1);
  }
  *step *= -1;
 }
 return (1);
}

int wall_hit(float x, float y, t_mlx *mlx) // check the wall hit
{
 int  x_m;
 int  y_m;

 if (x < 0 || y < 0)
  return (0);
 x_m = floor (x / TILE_SIZE); // get the x position in the map
 y_m = floor (y / TILE_SIZE); // get the y position in the map
 if ((y_m >= mlx->data->h_map || x_m >= mlx->data->w_map))
  return (0);
 if (mlx->data->map2d[y_m] && x_m <= (int)strlen(mlx->data->map2d[y_m]))
  if (mlx->data->map2d[y_m][x_m] == '1')
   return (0);
 return (1);
}

float get_h_inter(t_mlx *mlx, float angl) // get the horizontal intersection
{
 float h_x;
 float h_y;
 float x_step;
 float y_step;
 int  pixel;

 y_step = TILE_SIZE;
 x_step = TILE_SIZE / tan(angl);
 h_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angl, &h_y, &y_step, 1);
 h_x = mlx->player->player_x + (h_y - mlx->player->player_y) / tan(angl);
 if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
  x_step *= -1;
 while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
 {
  h_x += x_step;
  h_y += y_step;
 }
 return (sqrt(pow(h_x - mlx->player->player_x, 2) + pow(h_y - mlx->player->player_y, 2))); // get the distance
}

float get_v_inter(t_mlx *mlx, float angl) // get the vertical intersection
{
 float v_x;
 float v_y;
 float x_step;
 float y_step;
 int  pixel;

 x_step = TILE_SIZE;
 y_step = TILE_SIZE * tan(angl);
 v_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
 v_y = mlx->player->player_y + (v_x - mlx->player->player_x) * tan(angl);
 if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
  y_step *= -1;
 while (wall_hit(v_x - pixel, v_y, mlx)) // check the wall hit whit the pixel value
 {
  v_x += x_step;
  v_y += y_step;
 }
 return (sqrt(pow(v_x - mlx->player->player_x, 2) + pow(v_y - mlx->player->player_y, 2))); // get the distance
}

void cast_rays(t_mlx *mlx, t_img *img) // cast the rays
{
	double h_inter;
	double v_inter;
	int  ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->player->angle - (mlx->player->fov_rd / 2); // the start angle
 	while (ray < SCREEN_WIDTH) // loop for the rays
 	{
		mlx->ray->flag = 0; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
  		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
  		else
  		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1; // flag for the wall
		}
		render_wall(mlx, ray, img); // render the wall
		ray++; // next ray
		mlx->ray->ray_ngl += (mlx->player->fov_rd / SCREEN_WIDTH); // next angle
	}
}
