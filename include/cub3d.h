
#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

/*
** keycode == 65307  Escape key
** keycode == 119    W key
** keycode == 115    S key
** keycode == 97     A key
** keycode == 100    D key
*/

# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.14159265359

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
} t_player;

typedef struct s_texture
{
    void    *img;       // Pointer to the MiniLibX image
    char    *data;      // Pointer to the image pixel data
    int     width;      // Texture width
    int     height;     // Texture height
    int     bpp;        // Bits per pixel
    int     size_line;  // Size of a single line of pixels
    int     endian;     // Endianess of the data
} t_texture;

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
}				t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			fd;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
    char        *north_texture_path;
    char        *south_texture_path;
    char        *west_texture_path;
    char        *east_texture_path;
	char 		**map;

	t_texture   north_texture;
    t_texture   south_texture;
    t_texture   west_texture;
    t_texture   east_texture;
} t_game;

typedef enum	s_error
{
	NO_FILE,
	INVALID_FILE,
	INVALID_MAP
}	t_error;

void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void move_player(t_player *player, t_game *game);
int		error(t_error code);

// graphics

void	put_pixel(int x, int y, int color, t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
void draw_map(t_game *game);
void clear_image(t_game *game);
bool	touch(float px, float py, t_game *game);
void draw_line(t_player *player, t_game *game, float ray_angle, int column);
int draw_loop(t_game *game);

// textures

int load_texture(t_game *game, t_texture *texture, char *path);
int load_all_textures(t_game *game);
void free_texture_paths(t_game *game);
t_texture	*choose_texture(t_ray *ray, t_game *game);

// parser

int		validation(t_game *data, char *file);
int		map_file_validation(char *file);
int		parsing(t_game *data);
int		elements_checker(char *line);

// get_next_line

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *str, int c);
size_t	ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *buffer, char *new_s);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
char	*ft_strdup_gnl(char *str1);

#endif
