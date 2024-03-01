/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:38 by fgonzale          #+#    #+#             */
/*   Updated: 2024/03/01 00:11:25 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void player_init(t_mlx *mlx)
{
	mlx->player->player_x = mlx->data->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->player_y = mlx->data->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->fov_rd = (FOV * M_PI) / 180;
	mlx->player->angle = (3* M_PI) / 2;
}

t_data *init_data() // init the data structure
{
 t_data *data = calloc(1, sizeof(t_data)); // init the data structure
 data->map2d = calloc(10, sizeof(char *)); // init the map
 data->map2d[0] = ft_strdup("1111111111111111111111111"); //fill the map
 data->map2d[1] = ft_strdup("1000000000000101000101101");
 data->map2d[2] = ft_strdup("1001000000000P00000000001");
 data->map2d[3] = ft_strdup("1001000000000000001000001");
 data->map2d[4] = ft_strdup("10010000000011100001000001");
 data->map2d[5] = ft_strdup("1001000000100000001000001");
 data->map2d[6] = ft_strdup("1001000000000000001000001");
 data->map2d[7] = ft_strdup("1001000000001000001000001");
 data->map2d[8] = ft_strdup("1111111111111111111111111");
 data->map2d[9] = NULL;
 data->p_y = 3; // player y position in the map
 data->p_x = 14; // player x position in the map
 data->w_map = 25; // map widatah
 data->h_map = 9; // map height
 return (data); // return the data structure
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;

	dst = img->addr + (y * img->line_length + x *(img->bpp / 8));
	*(unsigned int*)dst = color;
}

int game_loop(void *ml)
{
	t_mlx	*mlx;
	t_img	img;

	mlx = ml;
	mlx->img = mlx_new_image(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT); // create new image
	img.addr = mlx_get_data_addr(mlx->img, &img.bpp, &img.line_length, &img.endian);
	hook(mlx, 0, 0);
	cast_rays(mlx, &img);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	return (0);
}

void start_the_game(t_data *data)
{
	t_mlx mlx;

	mlx.data = data;
	mlx.player = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	player_init(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, &game_loop, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &mlx);
	mlx_hook(mlx.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &mlx);
	mlx_loop(mlx.mlx_ptr);
}


int main(void)
{
	t_data *data;

	data = init_data();
	start_the_game(data);
	return (0);
}
