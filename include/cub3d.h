/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:43:03 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:46:26 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0
# define COLLISION_RADIUS 10

/* Keycodes */
# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.14159265359

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
}	t_player;

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}	t_tex;

typedef struct s_ray
{
	float		raydirx;
	float		raydiry;
	float		sidedistx;
	float		sidedisty;
	float		deltadistx;
	float		deltadisty;
	float		perpwalldist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
}	t_ray;

typedef struct s_line
{
	float		distance;
	float		wall_height;
	int			start_y;
	int			end_y;
	int			texture_x;
}	t_line;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	char		**map;
	char		**copy_map;
	int			fd;
	int			bpp;
	int			size_line;
	int			endian;
	int			floor_color;
	int			ceiling_color;
	int			n_path;
	int			s_path;
	int			w_path;
	int			e_path;
	t_player	player;
	t_tex		north_texture;
	t_tex		south_texture;
	t_tex		west_texture;
	t_tex		east_texture;
}	t_game;

typedef enum s_error
{
	NO_FILE,
	INVALID_FILE,
	INVALID_SPAWN,
	INVALID_MAP,
	INVALID_INPUT
}	t_error;

/* Initialization */
void	init_player(t_player *player);
int		init_game(t_game *game, char *file);
void	init_ray(t_ray *ray, t_player *player, float ray_angle);

/* Game Management */
int		close_game(t_game *game);
int		close_button(t_game *game);
void	free_map(char **map);

/* Player Movement */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);
void	rotate_player(t_player *player);
void	calc_new_pos(t_player *player, int *new_x, int *new_y, int speed);
void	move_player(t_player *player, t_game *game);
int		error(t_error code, t_game *game);

/* Graphics */
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(int x, int y, int color, t_game *game);
void	draw_sq_mm(int x, int y, int color, t_game *game);
void	draw_map(t_game *game);
void	clear_image(t_game *game);
bool	touch(float px, float py, t_game *game);
int		draw_loop(t_game *game);
void	draw_floor_ceiling(t_game *game);

/* Textures */
int		load_texture(t_game *game, t_tex *texture, char *path);
int		load_all_textures(t_game *game);
void	free_texture_paths(t_game *game);
void	free_texture(t_game *game, t_tex *texture);
void	free_all_textures(t_game *game);
t_tex	*choose_texture(t_ray *ray, t_game *game);

/* Parser */
int		validation(t_game *data, char *file);
int		map_file_validation(char *file);
int		parsing(t_game *data);
int		elements_checker(char *line);
int		parse_color(char *str);
void	free_split(char **arr);
int		valid_data(t_game *data);
void	change_space_to_wall(char **map, int index);
bool	is_space_or_one(char back, char front, char up, char down);
bool	is_valid_space(char **map, int row, int col);
int		adjacent_to_whitespace(char **map, int row);
int		surrounded_by_walls(char **map, int row);
void	path_counter(int code, t_game *data);
int		create_map(char *line, t_game *data);
int		check_map(char **map);
int		first_or_last_line(char *line);
char	*tex_path_creator(char *line);
int		texture_identifier(int code, char *line, t_game *game);
int		line_check(char *line, t_game *data);

/* Spawn */
void	find_player_spawn(t_game *game, t_player *player);
bool	is_spawn_char(char c);
void	init_player_position(t_player *player, int x, int y, char spawn_char);

/* Raycaster */
void	calc_delta_dist(t_ray *ray);
void	init_sidedist_step(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, t_game *game);
float	compute_corrected_dist(t_ray *ray, t_player *player, float ray_angle);
void	draw_column(t_game *game, t_tex *texture, int column, t_line *line);
void	draw_line(t_player *player, t_game *game, float ray_angle, int column);

/* GNL */
size_t	ft_strlen_gnl(char *str);

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *str, int c);
char	*ft_strjoin_gnl(char *buffer, char *new_s);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
char	*ft_strdup_gnl(char *str1);

#endif
