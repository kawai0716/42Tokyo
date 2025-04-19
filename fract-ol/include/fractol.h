#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

# define ESC 65307
# define right 65363
# define left 65361
# define up 65362
# define down 65364
# define plus 65451
# define minus 65453
# define scroll_up 4
# define scroll_down 5
# define MAX_ITERATIONS 150
# define close_window_button 17

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_fractol
{
    void *mlx;
    void *win;
    void *img;
    char *name;
    char *addr;
    double zoom;
    double x;
    double y;
    double xarrow;
    double yarrow
    int bits_per_pixel;
    int size_line;
    int endian;
    int height;
    int width;
    int color;
    t_complex c;
}   t_fractol;

//initialization
void mandelbrot_set(t_fractol *fractol, char *name);
void julia_set(t_fractol *fractol, char *name);
      

typedef struct s_fractal
{
	void		*mlx;				// MLXインスタンスへのポインタ
	void		*win;				// ウィンドウへのポインタ
	void		*img;				// MLXで作成した画像へのポインタ
	char		*addr;				// 画像のピクセルデータのアドレス
	int			bits_per_pixel;		// ピクセルあたりのビット数（色深度）
	int			line_length;		// 画像の1行あたりのバイト数
	int			endian;				// エンディアン形式 (データの並び順)
	int			width;				// 画像（ウィンドウ）の横幅
	int			height;				// 画像（ウィンドウ）の縦幅
	int			iterations;			// フラクタルの計算反復回数（繰り返す数が多いほど精度が上がる）
	double		zoom;				// 現在のズーム倍率
	double		xarrow;				// X方向の移動量（矢印キーで移動した量）
	double		yarrow;				// Y方向の移動量（矢印キーで移動した量）
	double		x;					// ズーム位置調整時のx座標オフセット
	double		y;					// ズーム位置調整時のy座標オフセット
	double		radius;				// 複素平面上の描画半径（特にジュリア集合）
	int			color;				// 描画色（ピクセルの色のベース値）
	char		*name;				// フラクタルタイプの名前 ("julia", "mandelbrot" など)
	t_complex	c;					// ジュリア集合などで使われる定数（複素数）
}	t_fractal;


