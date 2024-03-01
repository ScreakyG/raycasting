/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:43:18 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/01 00:13:00 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void move_player(t_mlx *mlx, double move_x, double move_y) // move the player
{
 int  map_grid_y;
 int  map_grid_x;
 int  new_x;
 int  new_y;

 new_x = roundf(mlx->player->player_x + move_x); // get the new x position
 new_y = roundf(mlx->player->player_y + move_y); // get the new y position
 map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
 map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
 if (mlx->data->map2d[map_grid_y][map_grid_x] != '1' && \
 (mlx->data->map2d[map_grid_y][mlx->player->player_x / TILE_SIZE] != '1' && \
 mlx->data->map2d[mlx->player->player_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
 {
  mlx->player->player_x = new_x; // move the player
  mlx->player->player_y = new_y; // move the player
 }
}

void rotate_player(t_mlx *mlx, int i) // rotate the player
{
 if (i == 1)
 {
  mlx->player->angle += ROTATION_SPEED; // rotate right
  if (mlx->player->angle > 2 * M_PI)
   mlx->player->angle -= 2 * M_PI;
 }
 else
 {
  mlx->player->angle -= ROTATION_SPEED; // rotate left
  if (mlx->player->angle < 0)
   mlx->player->angle += 2 * M_PI;
 }
}

void hook(t_mlx *mlx, double move_x, double move_y) // hook the player
{
 if (mlx->player->rot == 1) //rotate right
  rotate_player(mlx, 1);
 if (mlx->player->rot == -1) //rotate left
  rotate_player(mlx, 0);
 if (mlx->player->l_r == 1) //move right
 {
  move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
  move_y = cos(mlx->player->angle) * PLAYER_SPEED;
 }
 if (mlx->player->l_r == -1) //move left
 {
  move_x = sin(mlx->player->angle) * PLAYER_SPEED;
  move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
 }
 if (mlx->player->u_d == 1) //move up
 {
  move_x = cos(mlx->player->angle) * PLAYER_SPEED;
  move_y = sin(mlx->player->angle) * PLAYER_SPEED;
 }
 if (mlx->player->u_d == -1) //move down
 {
  move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
  move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
 }
 move_player(mlx, move_x, move_y); // move the player
}

int handle_keypress(int keysym, void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	if (keysym == XK_Escape)
		exit(0);
	else if (keysym == XK_a || keysym == XK_A) // move left
		mlx->player->l_r = -1;
	else if (keysym == XK_d || keysym == XK_D) // move right
		mlx->player->l_r = 1;
	else if (keysym == XK_s || keysym == XK_S) // move backwards
		mlx->player->u_d = -1;
	else if (keysym == XK_w || keysym == XK_W) // move forwards
		mlx->player->u_d = 1;
	else if (keysym == XK_Left) // rotate left
		mlx->player->rot = -1;
	else if (keysym == XK_Right) // rotate right
		mlx->player->rot = 1;
	return (0);
}

int handle_keyrelease(int keysym, void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	if (keysym == XK_a || keysym == XK_A) // move left
		mlx->player->l_r = 0;
	else if (keysym == XK_d || keysym == XK_D) // move right
		mlx->player->l_r = 0;
	else if (keysym == XK_s || keysym == XK_S) // move backwards
		mlx->player->u_d = 0;
	else if (keysym == XK_w || keysym == XK_W) // move forwards
		mlx->player->u_d = 0;
	else if (keysym == XK_Left) // rotate left
		mlx->player->rot = 0;
	else if (keysym == XK_Right) // rotate right
		mlx->player->rot = 0;
	return (0);
}
