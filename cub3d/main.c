#include "cub3D.h"
#include <stdio.h>



char map[256] = 
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,
	1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,
	1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};



char	texture[17][17]=
{
	"1111111111111111",
	"1000000000000111",
	"1100000000001001",
	"1010000000010001",
	"1001000000100001",
	"1000100001000001",
	"1000001010000001",
	"1000000100000001",
	"1000001010000001",
	"1000010001000001",
	"1000100000100001",
	"1001000000010001",
	"1010000000001001",
	"1100000000000101",
	"1100000000000011",
	"1111111111111111",
};

int	ketmap[4] = {0, 0, 0, 0};

int	keyarrow[2] = {0,0};

int	key_press(int keycode, t_object *_player)
{
	if (keycode == KEY_A)
		ketmap[0] = 1;
	else if (keycode == KEY_D)
		ketmap[1] = 1;
	if (keycode == KEY_W)
		ketmap[2] = 1;
	else if (keycode == KEY_S)
		ketmap[3] = 1;

	if (keycode == KEY_LEFT)
		keyarrow[0] = 1;
	if (keycode == KEY_RIGHT)
		keyarrow[1] = 1;

	return _player->pa;
}

int	key_release(int keycode, t_object *_player)
{
	if (keycode == KEY_A)
		ketmap[0] = 0;
	if (keycode == KEY_D)
		ketmap[1] = 0;
	if (keycode == KEY_W)
		ketmap[2] = 0;
	if (keycode == KEY_S)
		ketmap[3] = 0;

	if (keycode == KEY_LEFT)
		keyarrow[0] = 0;
	if (keycode == KEY_RIGHT)
		keyarrow[1] = 0;
	
	return _player->pa;
}

int main_loop(t_object *player)
{
	int y = 0;
	t_vi2d start;
	t_vi2d len;
	t_image *image;

	//draw mini map
	t_map_info map_info;
	map_info.map = &map[0];
	map_info.size_x = MAP_X;
	map_info.size_y = MAP_Y;
	image = player->image;
	while (y < MAP_Y)
	{
		int x = 0;
		while (x < MAP_X)
		{
			start.x = x * per_boxsize;
			start.y = y * per_boxsize;

			start.x = start.x ;
			start.y = start.y ;

			len.x = per_boxsize;
			len.y = per_boxsize;
			
			if (map[y * MAP_X + x] == 1)
				img_draw_fill_rectangle(image, start, len, 0XFFFFFF);
			else	
				img_draw_fill_rectangle(image, start, len, 0X000000);
			++x;

		}
		++y;
	}

	//calc player
	

	
	if (ketmap[0])
	{
		t_vf2d dir = new_vf2d(-cosf(player->pa + PI / 2), -sinf(player->pa + PI / 2));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.is_hit == 0)
		{
		}
			player->position.x -= cosf(player->pa + PI / 2) * 0.05f;
			player->position.y -= sinf(player->pa + PI / 2) * 0.05f;
			

	}
	else if (ketmap[1])
	{
		t_vf2d dir = new_vf2d(cosf(player->pa + PI / 2), sinf(player->pa + PI / 2));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.is_hit == 0)
		{
		}
			player->position.x += cosf(player->pa + PI / 2) * 0.05f;
			player->position.y += sinf(player->pa + PI / 2) * 0.05f;
	}

	if (ketmap[2])
	{
		t_vf2d dir = new_vf2d(cosf(player->pa), sinf(player->pa));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.is_hit == 0)
		{
		}

			player->position.x += cosf(player->pa) * 0.05f;
			player->position.y += sinf(player->pa) * 0.05f;
	}
	else if(ketmap[3])
	{
		t_vf2d dir = new_vf2d(-cosf(player->pa), -sinf(player->pa));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.is_hit == 0)
		{
		}
			player->position.x -= cosf(player->pa) * 0.05f;
			player->position.y -= sinf(player->pa) * 0.05f;
	}

	if (keyarrow[0])
		player->pa -= RADIN * 2.9f;
	if (keyarrow[1])
		player->pa += RADIN * 2.9f;
	if (player->pa < 0)
		player->pa += 2 * PI;
	if (player->pa > 2 * PI)
		player->pa -= 2 * PI;

	//draw ray
	float ra = player->pa - 30 * RADIN;
	//int raycount = 60 * 2;
	int i = 0;
	float ssss = WINDOW_SIZE_Y / (float)60;

	
	
	while (i < 1024)
	{
		

		if (ra < 0)
		{
			ra += 2 * PI;
		}
		else if (ra > 2 * PI)
		{
			ra -= 2 * PI;
		}
		

		
		t_vf2d dirction = new_vf2d(cosf(ra), sinf(ra));

		t_raycast_hit hit = raycasting(&map_info, player->position, dirction, 15);
		t_vi2d line_s = casting_vi2d(new_vf2d_multiple(player->position, per_boxsize));
		t_vi2d line_e;
		line_e.x = hit.distance * per_boxsize * dirction.x + line_s.x;
		line_e.y = hit.distance * per_boxsize * dirction.y + line_s.y;
		img_draw_line(image, line_s, line_e, 0XFF0000);
		float pa = ra - player->pa;
		if (pa < 0)
		{
			pa += 2 * PI;
		}
		else if (pa > 2 * PI)
		{
			pa -= 2 * PI;
		}

		
		float lineh = (WINDOW_SIZE_Y / 1.5f) / (hit.distance * cosf(pa));

		// if (lineh >= 1900.0f)
		// {
		// 	lineh = 1900.0f;
		// }

        float lineo = ((WINDOW_SIZE_Y - 150) / 2) - lineh / 2;		

		//sky
		start = new_vi2d(WINDOW_SIZE_X / 2 + i, 0);
		len	= new_vi2d(1, lineo);
		img_draw_fill_rectangle(image, start, len, 0X0067E3);

		//box
		// start = new_vi2d(WINDOW_SIZE_X / 2 + i, lineo);
		// len	=   new_vi2d(1, lineh);
		//float gd;
		
		float sstep = (float)(player->book_texture->width) / lineh;

		// if (hit.disth < hit.distv)
		// {
		// 	gd = 1.0f;
		// 	tm = (int)(((hit.hit_point.y) - (int)(hit.hit_point.y)) * 16);
		// }
		// else
		// {
		// 	gd = 0.75f;
		// 	tm = (int)(((hit.hit_point.x) - (int)(hit.hit_point.x)) * 16);
		// }

		float tm = 0.0f;
		float tx = 0.0f;

		if (hit.is_disth == 1)
		{
			tm = (int)(((hit.hit_point.y) - (int)(hit.hit_point.y)) * player->book_texture->width);
		}
		else
		{
			tm = (int)(((hit.hit_point.x) - (int)(hit.hit_point.x)) * player->book_texture->width);
		}
		//tm = (int)(((hit.hit_point.x) - (int)(hit.hit_point.x)) * 16);

		for (int j = lineo; j < (int)(lineh + lineo); j++)
		{
			int co = img_get_color(player->book_texture, (int)tm % player->book_texture->width, (int)tx % player->book_texture->height);
			// int co = 0;
			// if (texture[(int)tm % MAP_X][(int)tx % MAP_Y] == '0')
			// 	co = 0XFFFFFF;
			// else
			// 	co = 0X0CEF0F;
			img_draw_pixel(image, WINDOW_SIZE_X / 2 + i, j, co);
			tx = tx + sstep;
		}



		//img_draw_fill_rectangle(image, start, len, 0XFFFFFF);



		//floor
		start = new_vi2d(WINDOW_SIZE_X / 2 + i, lineo + lineh);
		len	= new_vi2d(1, WINDOW_SIZE_Y - lineo + lineh);
		img_draw_fill_rectangle(image, start, len, 0X00000F);

		ra += RADIN / ssss;
		++i;
	}

	//draw player
	t_vf2d word_position = new_vf2d_multiple(player->position, per_boxsize);
	t_vi2d player_start = casting_vi2d(word_position);
	t_vi2d player_len = new_vi2d(per_boxsize >> per_player, per_boxsize >> per_player);
	player_start = new_vi2d(player_start.x - player_len.x / 2 , player_start.y - player_len.y / 2);
	img_draw_fill_rectangle(image, player_start, player_len, 0X0FFFF00);
	mlx_put_image_to_window(player->mlx, player->win, image->mlx_img, 0, 0);
	return 1;

}

int main(void)
{
	void	*mlx;
	void	*win;
	t_image image;
	t_image book_texture;
	t_object player;

	printf("222\n");
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "hello world!");

	img_init(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, &image);
	img_file_init(mlx, "bookshelf.png", &book_texture);

	player.position = new_vf2d(1.5f, 1.5f);
	player.image = &image;
	player.book_texture = &book_texture;
	player.mlx = mlx;
	player.win = win;
	player.pa = 0.0f;

	printf("233\n");
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &player);
	printf("235\n");
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_release, &player);
	printf("237\n");
	mlx_loop_hook(mlx, main_loop, &player);
	printf("239\n");
	mlx_loop(mlx);
	return (0);
}
