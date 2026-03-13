#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include "chess.h"
static lv_obj_t* p;

int main(void)
{
    lv_init();

    /*Linux frame buffer device init*/
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");
    lv_indev_t* indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event6");
    /*Create a Demo*/
    //1.创建一个屏幕
    p = lv_screen_active();
    //为游戏状态分布一块内存
    ChessGame* game = (ChessGame*)malloc(sizeof(*game));
    //初始化内存
    init_game(game);
    //绘制棋盘
    draw_board(game,p);
    //创建主界面
    create_begin(p);
    

    while(1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

