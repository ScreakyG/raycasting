/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:56:05 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/01 01:40:28 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float nor_angle(float angle) // normalize the angle
{
 if (angle < 0)
  angle += (2 * M_PI);
 if (angle > (2 * M_PI))
  angle -= (2 * M_PI);
 return (angle);
}

int get_color(t_mlx *mlx, int flag) // get the color of the wall
{
 mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
 if (flag == 0)
 {
  if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
   return (0x00CCCCCC); // west wall
  else
   return (0x00CCCCCC); // east wall
 }
 else
 {
  if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
   return (0x00999999); // south wall
  else
   return (0x00999999); // north wall
 }
}

void draw_wall(t_mlx *mlx, t_img *img,int ray, int t_pix, int b_pix) // draw the wall
{
 int color;

 color = get_color(mlx, mlx->ray->flag);
 while (t_pix < b_pix)
	my_mlx_pixel_put(img, ray, t_pix++, color);
//my_mlx_pixel_put(mlx, ray, t_pix++, color);
}

void draw_floor_ceiling(t_img *img, t_mlx *mlx, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
 int  i;

 (void)mlx;
 i = b_pix;
 while (i < SCREEN_HEIGHT)
	my_mlx_pixel_put(img, ray, i++, 0x00996600);
 // my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
 i = 0;
 while (i < t_pix)
  my_mlx_pixel_put(img, ray, i++, 0x000099FF); // ceiling
}

void render_wall(t_mlx *mlx, int ray, t_img *img) // render the wall
{
 double wall_h;
 double b_pix;
 double t_pix;

 mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->player->angle)); // fix the fisheye
 wall_h = (TILE_SIZE / mlx->ray->distance) * ((SCREEN_WIDTH / 2) / tan(mlx->player->fov_rd / 2)); // get the wall height
 b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
 t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
 if (b_pix > SCREEN_HEIGHT) // check the bottom pixel
  b_pix = SCREEN_HEIGHT;
 if (t_pix < 0) // check the top pixel
  t_pix = 0;
 draw_wall(mlx, img, ray, t_pix, b_pix); // draw the wall
 draw_floor_ceiling(img, mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}

