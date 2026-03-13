#include "chess.h"


//棋盘大小和棋子尺寸
#define BOARD_WIDTH 540
#define BOARD_HEIGHT 600
#define CELL_SIZE 60

// 棋子颜色
#define RED_COLOR lv_color_hex(0xFF0000)
#define BLACK_COLOR lv_color_hex(0x000000)
#define BOARD_COLOR lv_color_hex(0xE8C885)
#define LINE_COLOR lv_color_hex(0x000000)
#define SELECT_COLOR lv_color_hex(0x00FF00)
#define YELLOW_COLOR lv_color_hex(0xFFCC22)
#define ORANGE_COLOR lv_color_hex(0xFFBB66)

lv_point_t point={0,0}; //保存获取到的坐标
lv_obj_t* obj;//象棋游戏界面
lv_obj_t * obj_begin;//象棋主界面
int flag = 1;//切换主界面和游戏界面的标志位
extern lv_font_t my_font_36;//象棋字体

//游戏状态初始化
void init_game(ChessGame* game)
{
    //清空棋盘
    for(int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 9; y++) 
        {
            game->board[x][y] = NONE;
        }
    }
    // 放置红方棋子
    game->board[0][0] = RED_CHARIOT1;
    game->board[0][1] = RED_HORSE1;
    game->board[0][2] = RED_ELEPHANT1;
    game->board[0][3] = RED_ADVISOR1;
    game->board[0][4] = RED_GENERAL;
    game->board[0][5] = RED_ADVISOR2;
    game->board[0][6] = RED_ELEPHANT2;
    game->board[0][7] = RED_HORSE2;
    game->board[0][8] = RED_CHARIOT2;
    game->board[2][1] = RED_CANNON1;
    game->board[2][7] = RED_CANNON2;
    game->board[3][0] = RED_SOLDIER1;
    game->board[3][2] = RED_SOLDIER2;
    game->board[3][4] = RED_SOLDIER3;
    game->board[3][6] = RED_SOLDIER4;
    game->board[3][8] = RED_SOLDIER5;

    // 放置黑方棋子
    game->board[9][0] = BLACK_CHARIOT1;
    game->board[9][1] = BLACK_HORSE1;
    game->board[9][2] = BLACK_ELEPHANT1;
    game->board[9][3] = BLACK_ADVISOR1;
    game->board[9][4] = BLACK_GENERAL;
    game->board[9][5] = BLACK_ADVISOR2;
    game->board[9][6] = BLACK_ELEPHANT2;
    game->board[9][7] = BLACK_HORSE2;
    game->board[9][8] = BLACK_CHARIOT2;
    game->board[7][1] = BLACK_CANNON1;
    game->board[7][7] = BLACK_CANNON2;
    game->board[6][0] = BLACK_SOLDIER1;
    game->board[6][2] = BLACK_SOLDIER2;
    game->board[6][4] = BLACK_SOLDIER3;
    game->board[6][6] = BLACK_SOLDIER4;
    game->board[6][8] = BLACK_SOLDIER5;

    game->is_red_turn = true;
    game->game_over = false;
    game->b_ret = 0;
    
    for(int k=0;k<100;k++)
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<9;j++)
            {
                game->board_ret[k][i][j] = NONE;
            }
        }
    }

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            game->board_ret[0][i][j] = game->board[i][j];
        }
    }
}

//绘制棋盘
void draw_board(ChessGame* game,lv_obj_t* p)
{
    obj =  lv_obj_create(p);//在主屏幕上创建象棋游戏界面对象
    lv_obj_set_style_pad_all(obj,0,LV_PART_MAIN);//设置内边距
    lv_obj_set_style_margin_all(obj,0,LV_PART_MAIN);//设置外边距
    lv_obj_set_size(obj,1024,600);

    game->obj_board = lv_obj_create(obj);//在象棋游戏界面对象上创建棋盘对象
    lv_obj_set_style_pad_all(game->obj_board,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(game->obj_board,0,LV_PART_MAIN);
    lv_obj_set_size(game->obj_board,540,600);
    lv_obj_align(game->obj_board,LV_ALIGN_TOP_LEFT,0,0);
    
    static lv_style_t obj_style;//为棋盘设置样式
    lv_style_init(&obj_style);
    lv_style_set_bg_color(&obj_style , lv_color_hex(0xFFCC22));//为棋盘设置背景颜色
    lv_style_set_border_width(&obj_style ,0);    //设置边框宽度
    lv_obj_add_style(game->obj_board, &obj_style, LV_STATE_DEFAULT);
    
    //定义多条直线的坐标
    static lv_point_precise_t point[][2] = {
        //10条横线
        {{CELL_SIZE / 2, CELL_SIZE / 2}, {BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 1 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 1 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 2 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 2 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 3 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 3 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 4 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 4 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 5 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 5 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 6 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 6 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 7 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 7 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 8 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 8 * CELL_SIZE}},
        {{CELL_SIZE / 2, CELL_SIZE / 2 + 9 * CELL_SIZE},{BOARD_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + 9 * CELL_SIZE}},
        //9条竖线(上半部分)
        {{CELL_SIZE / 2, CELL_SIZE / 2},{CELL_SIZE / 2, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 1 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 1 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 2 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 2 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 3 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 3 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 4 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 4 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 5 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 5 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 6 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 6 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 7 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 7 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 8 * CELL_SIZE, CELL_SIZE / 2},{CELL_SIZE / 2 + 8 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2}},
        //9条竖线(下半部分)
        {{CELL_SIZE / 2, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 1 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 1 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 2 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 2 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 3 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 3 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 4 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 4 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 5 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 5 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 6 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 6 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 7 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 7 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 8 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2},{CELL_SIZE / 2 + 8 * CELL_SIZE, BOARD_HEIGHT - CELL_SIZE / 2}},
        //中间两条短竖线
        {{CELL_SIZE / 2, CELL_SIZE * 4 + CELL_SIZE / 2},{CELL_SIZE / 2, CELL_SIZE * 5 + CELL_SIZE / 2}},
        {{CELL_SIZE / 2 + 8 * CELL_SIZE, CELL_SIZE * 4 + CELL_SIZE / 2},{CELL_SIZE / 2 + 8 * CELL_SIZE, CELL_SIZE * 5 + CELL_SIZE / 2}},
        //九宫格斜线
        {{CELL_SIZE * 3 + CELL_SIZE / 2, CELL_SIZE / 2},{CELL_SIZE * 5 + CELL_SIZE / 2, CELL_SIZE * 2 + CELL_SIZE / 2}},
        {{CELL_SIZE * 5 + CELL_SIZE / 2, CELL_SIZE / 2},{CELL_SIZE * 3 + CELL_SIZE / 2, CELL_SIZE * 2 + CELL_SIZE / 2}},
        {{CELL_SIZE * 3 + CELL_SIZE / 2, BOARD_HEIGHT - CELL_SIZE / 2},{CELL_SIZE * 5 + CELL_SIZE / 2, BOARD_HEIGHT - CELL_SIZE * 2 - CELL_SIZE / 2}},
        {{CELL_SIZE * 5 + CELL_SIZE / 2, BOARD_HEIGHT - CELL_SIZE / 2},{CELL_SIZE * 3 + CELL_SIZE / 2, BOARD_HEIGHT - CELL_SIZE * 2 - CELL_SIZE / 2}}
    };
    //画线
    for (int i = 0; i < 34; i++)
    {
        lv_obj_t * line = lv_line_create(game->obj_board);
        lv_line_set_points(line,point[i], 2);  // 设置坐标
        //lv_obj_set_pos(line, 0, 0);  // 相对于窗口的位置
    }
    //楚河汉界

    //创建一个标签控件
    lv_obj_t *lab_obj_board =  lv_label_create(game->obj_board);
    lv_obj_set_pos(lab_obj_board,CELL_SIZE * 2, CELL_SIZE * 4 + CELL_SIZE / 2);
    //创建标签控件的样式：
    static lv_style_t lab_obj_board_style ;
    lv_style_init(&lab_obj_board_style);
    lv_style_set_bg_color(&lab_obj_board_style , lv_color_hex(0xFFCC22));
    lv_style_set_text_color(&lab_obj_board_style,lv_color_hex(0x000000));
    //创建一个字体
    const lv_font_t* font = &my_font_36;
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_obj_board_style,font);
    lv_obj_add_style(lab_obj_board , &lab_obj_board_style , LV_STATE_DEFAULT);
    lv_label_set_text(lab_obj_board,"楚河                   汉界");

    lv_obj_add_event_cb(game->obj_board , print_point_cb,LV_EVENT_CLICKED ,(void *)game);
    Placing_chess_pieces(game);

    //在棋盘界面上创建一个按钮(返回主界面)
    lv_obj_t* button2 = lv_button_create(obj);
    //设置按钮的大小
    lv_obj_set_size(button2,300,100);
    //设置按钮的位置
    lv_obj_set_align(button2,LV_ALIGN_RIGHT_MID);

    //创建一个标签控件
    lv_obj_t *lab_board =  lv_label_create(button2);
    //创建标签控件的样式：
    static lv_style_t lab_board_style ;
    lv_style_init(&lab_board_style);
    lv_style_set_text_color(&lab_board_style,lv_color_hex(0x000000));
    //创建一个字体
    //const lv_font_t* font = &my_font_36;
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_board_style,font);
    lv_obj_add_style(lab_board , &lab_board_style , LV_STATE_DEFAULT);
    lv_label_set_text(lab_board,"返回主界面");
    //创建一个样式：
    static lv_style_t button2_style ;
    lv_style_init(&button2_style);
    lv_style_set_bg_color(&button2_style , lv_color_hex(0xFF0000));
    lv_style_set_bg_opa(&button2_style,0);
    //3.把样式添加到按钮中，在默认情况下显示
    lv_obj_add_style( button2, &button2_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button2,change_obj_ing,LV_EVENT_CLICKED ,NULL);

    //在棋盘界面上创建一个悔棋按钮
    lv_obj_t* button3 = lv_button_create(obj);
    //设置按钮的大小
    lv_obj_set_size(button3,300,100);
    //设置按钮的位置
    lv_obj_set_align(button3,LV_ALIGN_TOP_RIGHT);

    //创建一个标签控件
    lv_obj_t *lab_board3 =  lv_label_create(button3);
    //创建标签控件的样式：
    static lv_style_t lab_board3_style ;
    lv_style_init(&lab_board3_style);
    lv_style_set_text_color(&lab_board3_style,lv_color_hex(0x000000));
    //创建一个字体
    //const lv_font_t* font = &my_font_36;
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_board3_style,font);
    lv_obj_add_style(lab_board3 , &lab_board3_style , LV_STATE_DEFAULT);
    lv_label_set_text(lab_board3,"悔棋");
    //创建一个样式：
    static lv_style_t button3_style ;
    lv_style_init(&button3_style);
    lv_style_set_bg_color(&button3_style , lv_color_hex(0xFF0000));
    lv_style_set_bg_opa(&button3_style,0);
    //3.把样式添加到按钮中，在默认情况下显示
    lv_obj_add_style( button3, &button3_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button3,return_last,LV_EVENT_CLICKED ,(void *)game);

    //在棋盘界面上创建一个重新开始按钮
    lv_obj_t* button6 = lv_button_create(obj);
    //设置按钮的大小
    lv_obj_set_size(button6,300,100);
    //设置按钮的位置
    lv_obj_set_align(button6,LV_ALIGN_BOTTOM_RIGHT);

    //创建一个标签控件
    lv_obj_t *lab_board6 =  lv_label_create(button6);
    //创建标签控件的样式：
    static lv_style_t lab_board6_style ;
    lv_style_init(&lab_board6_style);
    lv_style_set_text_color(&lab_board6_style,lv_color_hex(0x000000));
    //创建一个字体
    //const lv_font_t* font = &my_font_36;
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_board6_style,font);
    lv_obj_add_style(lab_board6 , &lab_board6_style , LV_STATE_DEFAULT);
    lv_label_set_text(lab_board6,"重新开始");
    //创建一个样式：
    static lv_style_t button6_style ;
    lv_style_init(&button6_style);
    lv_style_set_bg_color(&button6_style , lv_color_hex(0xFF0000));
    lv_style_set_bg_opa(&button6_style,0);
    //3.把样式添加到按钮中，在默认情况下显示
    lv_obj_add_style( button6, &button6_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button6,return_begin,LV_EVENT_CLICKED ,(void *)game);
}

//主界面
void create_begin(lv_obj_t* p)
{
    //在活动屏幕上创建一个主界面
    obj_begin = lv_image_create(p);
    //在主界面上显示图片
    lv_image_set_src(obj_begin,"A:/dxb/pic/1.bmp");

    //在主界面上创建一个按钮
    lv_obj_t* button = lv_button_create(obj_begin);
    //设置按钮的大小
    lv_obj_set_size(button,300,100);
    //设置按钮的位置
    lv_obj_set_align(button,LV_ALIGN_BOTTOM_MID);

    //创建一个标签控件
    lv_obj_t *lab_begin =  lv_label_create(button);
    //创建标签对应的样式：
    static lv_style_t lab_begin_style ;
    lv_style_init(&lab_begin_style);
    lv_style_set_text_color(&lab_begin_style,lv_color_hex(0xFFFFFF));
    //创建一个字体
    const lv_font_t* font = &my_font_36;
    //将字体添加
    lv_style_set_text_font(&lab_begin_style,font);
    lv_obj_add_style(lab_begin , &lab_begin_style , LV_STATE_DEFAULT);
    lv_label_set_text(lab_begin,"开始游戏");

    //创建一个样式：
    static lv_style_t button_style ;
    lv_style_init(&button_style);
    lv_style_set_bg_color(&button_style , lv_color_hex(0xFF0000));
    lv_style_set_bg_opa(&button_style,0);
    //3.把样式添加到按钮中，在默认情况下显示
    lv_obj_add_style( button, &button_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button,change_obj_ing,LV_EVENT_CLICKED ,NULL);
}

//切换界面
void change_obj_ing(lv_event_t * e)
{
    if(flag == 1)
    {
        lv_obj_add_flag(obj_begin,LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(obj,LV_OBJ_FLAG_HIDDEN);
        flag = 0;
    }
    else
    {
        lv_obj_add_flag(obj,LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(obj_begin,LV_OBJ_FLAG_HIDDEN);
        flag = 1;
    }
}

/*
    return_last:悔棋
*/
void return_last(lv_event_t * e)
{
    ChessGame *game = (ChessGame *)lv_event_get_user_data(e);
    game->b_ret--;
    if(game->b_ret == -1)
    {
        game->b_ret = 0;
    }
    change_board(game,0);
    reagain_place_chess(game);
    if(game->is_red_turn == true && game->b_ret != 0)
    {
        game->is_red_turn = false;
        printf("game->is_red_turn == true  to  game->is_red_turn = false;\n");
        return;
    }
    if(game->is_red_turn == false)
    {
        game->is_red_turn = true;
        printf("game->is_red_turn == false  to  game->is_red_turn = true;\n");
        return;
    }
}

/*
    return_begin:重新开始
*/
void return_begin(lv_event_t * e)
{
    ChessGame *game = (ChessGame *)lv_event_get_user_data(e);
    game->b_ret = 0;
    change_board(game,0);
    reagain_place_chess(game);
    game->is_red_turn = true;
}

//摆放棋子
void Placing_chess_pieces(ChessGame *game)
{
    // 创建棋子（以“红帅”为例）
    lv_obj_t *red_king = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_king,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_king,0,LV_PART_MAIN);
    lv_obj_set_size(red_king,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_king,CELL_SIZE*4,CELL_SIZE*0);
    lv_obj_set_style_radius(red_king, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_king,ORANGE_COLOR, 0);

    lv_obj_t *label_red_king = lv_label_create(red_king);
    lv_obj_center(label_red_king);
    lv_obj_set_size(label_red_king,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_king_style ;
    lv_style_init(&lab_red_king_style);
    lv_style_set_text_color(&lab_red_king_style,RED_COLOR);
    
    //添加字体到标签控件中
    const lv_font_t* font = &my_font_36;
    lv_style_set_text_font(&lab_red_king_style,font);
    lv_obj_add_style(label_red_king , &lab_red_king_style , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_king, "帥");

    lv_obj_add_event_cb(red_king , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红马)
    lv_obj_t *red_horse1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_horse1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_horse1,0,LV_PART_MAIN);
    lv_obj_set_size(red_horse1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_horse1,CELL_SIZE*1,CELL_SIZE*0);
    lv_obj_set_style_radius(red_horse1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_horse1,ORANGE_COLOR, 0);

    lv_obj_t *label_red_horse1 = lv_label_create(red_horse1);
    lv_obj_center(label_red_horse1);
    lv_obj_set_size(label_red_horse1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_horse_style1 ;
    lv_style_init(&lab_red_horse_style1);
    lv_style_set_text_color(&lab_red_horse_style1,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_horse_style1,font);
    lv_obj_add_style(label_red_horse1 , &lab_red_horse_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_horse1, "傌");

    lv_obj_add_event_cb(red_horse1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(红马)
    lv_obj_t *red_horse2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_horse2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_horse2,0,LV_PART_MAIN);
    lv_obj_set_size(red_horse2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_horse2,CELL_SIZE*7,CELL_SIZE*0);
    lv_obj_set_style_radius(red_horse2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_horse2,ORANGE_COLOR, 0);

    lv_obj_t *label_red_horse2 = lv_label_create(red_horse2);
    lv_obj_center(label_red_horse2);
    lv_obj_set_size(label_red_horse2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_horse_style2 ;
    lv_style_init(&lab_red_horse_style2);
    lv_style_set_text_color(&lab_red_horse_style2,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_horse_style2,font);
    lv_obj_add_style(label_red_horse2 , &lab_red_horse_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_horse2, "傌");

    lv_obj_add_event_cb(red_horse2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(红象)
    lv_obj_t *red_elephant1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_elephant1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_elephant1,0,LV_PART_MAIN);
    lv_obj_set_size(red_elephant1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_elephant1,CELL_SIZE*2,CELL_SIZE*0);
    lv_obj_set_style_radius(red_elephant1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_elephant1,ORANGE_COLOR, 0);

    lv_obj_t *label_red_elephant1 = lv_label_create(red_elephant1);
    lv_obj_center(label_red_elephant1);
    lv_obj_set_size(label_red_elephant1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_elephant_style1 ;
    lv_style_init(&lab_red_elephant_style1);
    lv_style_set_text_color(&lab_red_elephant_style1,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_elephant_style1,font);
    lv_obj_add_style(label_red_elephant1 , &lab_red_elephant_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_elephant1, "相");

    lv_obj_add_event_cb(red_elephant1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(红象)
    lv_obj_t *red_elephant2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_elephant2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_elephant2,0,LV_PART_MAIN);
    lv_obj_set_size(red_elephant2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_elephant2,CELL_SIZE*6,CELL_SIZE*0);
    lv_obj_set_style_radius(red_elephant2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_elephant2,ORANGE_COLOR, 0);

    lv_obj_t *label_red_elephant2 = lv_label_create(red_elephant2);
    lv_obj_center(label_red_elephant2);
    lv_obj_set_size(label_red_elephant2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_elephant_style2 ;
    lv_style_init(&lab_red_elephant_style2);
    lv_style_set_text_color(&lab_red_elephant_style2,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_elephant_style2,font);
    lv_obj_add_style(label_red_elephant2 , &lab_red_elephant_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_elephant2, "相");

    lv_obj_add_event_cb(red_elephant2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红车)
    lv_obj_t *red_chariot1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_chariot1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_chariot1,0,LV_PART_MAIN);
    lv_obj_set_size(red_chariot1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_chariot1,CELL_SIZE*0,CELL_SIZE*0);
    lv_obj_set_style_radius(red_chariot1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_chariot1,ORANGE_COLOR, 0);

    lv_obj_t *label_red_chariot1 = lv_label_create(red_chariot1);
    lv_obj_center(label_red_chariot1);
    lv_obj_set_size(label_red_chariot1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_chariot_style1 ;
    lv_style_init(&lab_red_chariot_style1);
    lv_style_set_text_color(&lab_red_chariot_style1,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_chariot_style1,font);
    lv_obj_add_style(label_red_chariot1 , &lab_red_chariot_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_chariot1, "俥");

    lv_obj_add_event_cb(red_chariot1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(红车)
    lv_obj_t *red_chariot2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_chariot2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_chariot2,0,LV_PART_MAIN);
    lv_obj_set_size(red_chariot2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_chariot2,CELL_SIZE*8,CELL_SIZE*0);
    lv_obj_set_style_radius(red_chariot2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_chariot2,ORANGE_COLOR, 0);

    lv_obj_t *label_red_chariot2 = lv_label_create(red_chariot2);
    lv_obj_center(label_red_chariot2);
    lv_obj_set_size(label_red_chariot2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_chariot_style2 ;
    lv_style_init(&lab_red_chariot_style2);
    lv_style_set_text_color(&lab_red_chariot_style2,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_chariot_style2,font);
    lv_obj_add_style(label_red_chariot2 , &lab_red_chariot_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_chariot2, "俥");

    lv_obj_add_event_cb(red_chariot2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(红士)
    lv_obj_t *red_advisor1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_advisor1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_advisor1,0,LV_PART_MAIN);
    lv_obj_set_size(red_advisor1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_advisor1,CELL_SIZE*3,CELL_SIZE*0);
    lv_obj_set_style_radius(red_advisor1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_advisor1,ORANGE_COLOR, 0);

    lv_obj_t *label_red_advisor1 = lv_label_create(red_advisor1);
    lv_obj_center(label_red_advisor1);
    lv_obj_set_size(label_red_advisor1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_advisor_style1 ;
    lv_style_init(&lab_red_advisor_style1);
    lv_style_set_text_color(&lab_red_advisor_style1,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_advisor_style1,font);
    lv_obj_add_style(label_red_advisor1 , &lab_red_advisor_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_advisor1, "仕");

    lv_obj_add_event_cb(red_advisor1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红士)
    lv_obj_t *red_advisor2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_advisor2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_advisor2,0,LV_PART_MAIN);
    lv_obj_set_size(red_advisor2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_advisor2,CELL_SIZE*5,CELL_SIZE*0);
    lv_obj_set_style_radius(red_advisor2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_advisor2,ORANGE_COLOR, 0);

    lv_obj_t *label_red_advisor2 = lv_label_create(red_advisor2);
    lv_obj_center(label_red_advisor2);
    lv_obj_set_size(label_red_advisor2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_advisor_style2 ;
    lv_style_init(&lab_red_advisor_style2);
    lv_style_set_text_color(&lab_red_advisor_style2,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_advisor_style2,font);
    lv_obj_add_style(label_red_advisor2 , &lab_red_advisor_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_advisor2, "仕");

    lv_obj_add_event_cb(red_advisor2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红炮)
    lv_obj_t *red_cannon1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_cannon1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_cannon1,0,LV_PART_MAIN);
    lv_obj_set_size(red_cannon1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_cannon1,CELL_SIZE*1,CELL_SIZE*2);
    lv_obj_set_style_radius(red_cannon1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_cannon1,ORANGE_COLOR, 0);

    lv_obj_t *label_red_cannon1 = lv_label_create(red_cannon1);
    lv_obj_center(label_red_cannon1);
    lv_obj_set_size(label_red_cannon1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_cannon_style1 ;
    lv_style_init(&lab_red_cannon_style1);
    lv_style_set_text_color(&lab_red_cannon_style1,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_cannon_style1,font);
    lv_obj_add_style(label_red_cannon1 , &lab_red_cannon_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_cannon1, "炮");

    lv_obj_add_event_cb(red_cannon1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);
    
    
    // 创建棋子(红炮)
    lv_obj_t *red_cannon2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_cannon2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_cannon2,0,LV_PART_MAIN);
    lv_obj_set_size(red_cannon2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_cannon2,CELL_SIZE*7,CELL_SIZE*2);
    lv_obj_set_style_radius(red_cannon2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_cannon2,ORANGE_COLOR, 0);

    lv_obj_t *label_red_cannon2 = lv_label_create(red_cannon2);
    lv_obj_center(label_red_cannon2);
    lv_obj_set_size(label_red_cannon2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_cannon_style2 ;
    lv_style_init(&lab_red_cannon_style2);
    lv_style_set_text_color(&lab_red_cannon_style2,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_cannon_style2,font);
    lv_obj_add_style(label_red_cannon2 , &lab_red_cannon_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_cannon2, "炮");

    lv_obj_add_event_cb(red_cannon2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(红兵)
    lv_obj_t *red_soldier1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_soldier1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_soldier1,0,LV_PART_MAIN);
    lv_obj_set_size(red_soldier1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_soldier1,CELL_SIZE*0,CELL_SIZE*3);
    lv_obj_set_style_radius(red_soldier1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_soldier1,ORANGE_COLOR, 0);

    lv_obj_t *label_red_soldier1 = lv_label_create(red_soldier1);
    lv_obj_center(label_red_soldier1);
    lv_obj_set_size(label_red_soldier1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_soldier_style1 ;
    lv_style_init(&lab_red_soldier_style1);
    lv_style_set_text_color(&lab_red_soldier_style1,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_soldier_style1,font);
    lv_obj_add_style(label_red_soldier1 , &lab_red_soldier_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_soldier1, "兵");

    lv_obj_add_event_cb(red_soldier1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红兵)
    lv_obj_t *red_soldier2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_soldier2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_soldier2,0,LV_PART_MAIN);
    lv_obj_set_size(red_soldier2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_soldier2,CELL_SIZE*2,CELL_SIZE*3);
    lv_obj_set_style_radius(red_soldier2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_soldier2,ORANGE_COLOR, 0);

    lv_obj_t *label_red_soldier2 = lv_label_create(red_soldier2);
    lv_obj_center(label_red_soldier2);
    lv_obj_set_size(label_red_soldier2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_soldier_style2 ;
    lv_style_init(&lab_red_soldier_style2);
    lv_style_set_text_color(&lab_red_soldier_style2,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_soldier_style2,font);
    lv_obj_add_style(label_red_soldier2 , &lab_red_soldier_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_soldier2, "兵");

    lv_obj_add_event_cb(red_soldier2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红兵)
    lv_obj_t *red_soldier3 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_soldier3,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_soldier3,0,LV_PART_MAIN);
    lv_obj_set_size(red_soldier3,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_soldier3,CELL_SIZE*4,CELL_SIZE*3);
    lv_obj_set_style_radius(red_soldier3, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_soldier3,ORANGE_COLOR, 0);

    lv_obj_t *label_red_soldier3 = lv_label_create(red_soldier3);
    lv_obj_center(label_red_soldier3);
    lv_obj_set_size(label_red_soldier3,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_soldier_style3 ;
    lv_style_init(&lab_red_soldier_style3);
    lv_style_set_text_color(&lab_red_soldier_style3,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_soldier_style3,font);
    lv_obj_add_style(label_red_soldier3 , &lab_red_soldier_style3 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_soldier3, "兵");

    lv_obj_add_event_cb(red_soldier3 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红兵)
    lv_obj_t *red_soldier4 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_soldier4,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_soldier4,0,LV_PART_MAIN);
    lv_obj_set_size(red_soldier4,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_soldier4,CELL_SIZE*6,CELL_SIZE*3);
    lv_obj_set_style_radius(red_soldier4, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_soldier4,ORANGE_COLOR, 0);

    lv_obj_t *label_red_soldier4 = lv_label_create(red_soldier4);
    lv_obj_center(label_red_soldier4);
    lv_obj_set_size(label_red_soldier4,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_soldier_style4 ;
    lv_style_init(&lab_red_soldier_style4);
    lv_style_set_text_color(&lab_red_soldier_style4,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_soldier_style4,font);
    lv_obj_add_style(label_red_soldier4 , &lab_red_soldier_style4 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_soldier4, "兵");

    lv_obj_add_event_cb(red_soldier4 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(红兵)
    lv_obj_t *red_soldier5 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(red_soldier5,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(red_soldier5,0,LV_PART_MAIN);
    lv_obj_set_size(red_soldier5,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(red_soldier5,CELL_SIZE*8,CELL_SIZE*3);
    lv_obj_set_style_radius(red_soldier5, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(red_soldier5,ORANGE_COLOR, 0);

    lv_obj_t *label_red_soldier5 = lv_label_create(red_soldier5);
    lv_obj_center(label_red_soldier5);
    lv_obj_set_size(label_red_soldier5,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_red_soldier_style5 ;
    lv_style_init(&lab_red_soldier_style5);
    lv_style_set_text_color(&lab_red_soldier_style5,RED_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_red_soldier_style5,font);
    lv_obj_add_style(label_red_soldier5 , &lab_red_soldier_style5 , LV_STATE_DEFAULT);
    lv_label_set_text(label_red_soldier5, "兵");

    lv_obj_add_event_cb(red_soldier5 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子（黑帅）
    lv_obj_t *black_king = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_king,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_king,0,LV_PART_MAIN);
    lv_obj_set_size(black_king,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_king,CELL_SIZE*4,CELL_SIZE*9);
    lv_obj_set_style_radius(black_king, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_king,ORANGE_COLOR, 0);

    lv_obj_t *label_black_king = lv_label_create(black_king);
    lv_obj_center(label_black_king);
    lv_obj_set_size(label_black_king,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_king_style ;
    lv_style_init(&lab_black_king_style);
    lv_style_set_text_color(&lab_black_king_style,BLACK_COLOR);
    
    lv_style_set_text_font(&lab_black_king_style,font);
    lv_obj_add_style(label_black_king , &lab_black_king_style , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_king, "將");

    lv_obj_add_event_cb(black_king , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑马)
    lv_obj_t *black_horse1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_horse1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_horse1,0,LV_PART_MAIN);
    lv_obj_set_size(black_horse1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_horse1,CELL_SIZE*1,CELL_SIZE*9);
    lv_obj_set_style_radius(black_horse1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_horse1,ORANGE_COLOR, 0);

    lv_obj_t *label_black_horse1 = lv_label_create(black_horse1);
    lv_obj_center(label_black_horse1);
    lv_obj_set_size(label_black_horse1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_horse_style1 ;
    lv_style_init(&lab_black_horse_style1);
    lv_style_set_text_color(&lab_black_horse_style1,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_horse_style1,font);
    lv_obj_add_style(label_black_horse1 , &lab_black_horse_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_horse1, "馬");

    lv_obj_add_event_cb(black_horse1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(黑马)
    lv_obj_t *black_horse2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_horse2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_horse2,0,LV_PART_MAIN);
    lv_obj_set_size(black_horse2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_horse2,CELL_SIZE*7,CELL_SIZE*9);
    lv_obj_set_style_radius(black_horse2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_horse2,ORANGE_COLOR, 0);

    lv_obj_t *label_black_horse2 = lv_label_create(black_horse2);
    lv_obj_center(label_black_horse2);
    lv_obj_set_size(label_black_horse2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_horse_style2 ;
    lv_style_init(&lab_black_horse_style2);
    lv_style_set_text_color(&lab_black_horse_style2,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_horse_style2,font);
    lv_obj_add_style(label_black_horse2 , &lab_black_horse_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_horse2, "馬");

    lv_obj_add_event_cb(black_horse2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(黑象)
    lv_obj_t *black_elephant1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_elephant1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_elephant1,0,LV_PART_MAIN);
    lv_obj_set_size(black_elephant1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_elephant1,CELL_SIZE*2,CELL_SIZE*9);
    lv_obj_set_style_radius(black_elephant1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_elephant1,ORANGE_COLOR, 0);

    lv_obj_t *label_black_elephant1 = lv_label_create(black_elephant1);
    lv_obj_center(label_black_elephant1);
    lv_obj_set_size(label_black_elephant1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_elephant_style1 ;
    lv_style_init(&lab_black_elephant_style1);
    lv_style_set_text_color(&lab_black_elephant_style1,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_elephant_style1,font);
    lv_obj_add_style(label_black_elephant1 , &lab_black_elephant_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_elephant1, "象");

    lv_obj_add_event_cb(black_elephant1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(黑象)
    lv_obj_t *black_elephant2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_elephant2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_elephant2,0,LV_PART_MAIN);
    lv_obj_set_size(black_elephant2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_elephant2,CELL_SIZE*6,CELL_SIZE*9);
    lv_obj_set_style_radius(black_elephant2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_elephant2,ORANGE_COLOR, 0);

    lv_obj_t *label_black_elephant2 = lv_label_create(black_elephant2);
    lv_obj_center(label_black_elephant2);
    lv_obj_set_size(label_black_elephant2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_elephant_style2 ;
    lv_style_init(&lab_black_elephant_style2);
    lv_style_set_text_color(&lab_black_elephant_style2,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_elephant_style2,font);
    lv_obj_add_style(label_black_elephant2 , &lab_black_elephant_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_elephant2, "象");

    lv_obj_add_event_cb(black_elephant2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑车)
    lv_obj_t *black_chariot1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_chariot1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_chariot1,0,LV_PART_MAIN);
    lv_obj_set_size(black_chariot1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_chariot1,CELL_SIZE*0,CELL_SIZE*9);
    lv_obj_set_style_radius(black_chariot1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_chariot1,ORANGE_COLOR, 0);

    lv_obj_t *label_black_chariot1 = lv_label_create(black_chariot1);
    lv_obj_center(label_black_chariot1);
    lv_obj_set_size(label_black_chariot1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_chariot_style1 ;
    lv_style_init(&lab_black_chariot_style1);
    lv_style_set_text_color(&lab_black_chariot_style1,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_chariot_style1,font);
    lv_obj_add_style(label_black_chariot1 , &lab_black_chariot_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_chariot1, "車");

    lv_obj_add_event_cb(black_chariot1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(黑车)
    lv_obj_t *black_chariot2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_chariot2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_chariot2,0,LV_PART_MAIN);
    lv_obj_set_size(black_chariot2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_chariot2,CELL_SIZE*8,CELL_SIZE*9);
    lv_obj_set_style_radius(black_chariot2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_chariot2,ORANGE_COLOR, 0);

    lv_obj_t *label_black_chariot2 = lv_label_create(black_chariot2);
    lv_obj_center(label_black_chariot2);
    lv_obj_set_size(label_black_chariot2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_chariot_style2 ;
    lv_style_init(&lab_black_chariot_style2);
    lv_style_set_text_color(&lab_black_chariot_style2,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_chariot_style2,font);
    lv_obj_add_style(label_black_chariot2 , &lab_black_chariot_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_chariot2, "車");

    lv_obj_add_event_cb(black_chariot2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(黑士)
    lv_obj_t *black_advisor1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_advisor1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_advisor1,0,LV_PART_MAIN);
    lv_obj_set_size(black_advisor1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_advisor1,CELL_SIZE*3,CELL_SIZE*9);
    lv_obj_set_style_radius(black_advisor1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_advisor1,ORANGE_COLOR, 0);

    lv_obj_t *label_black_advisor1 = lv_label_create(black_advisor1);
    lv_obj_center(label_black_advisor1);
    lv_obj_set_size(label_black_advisor1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_advisor_style1 ;
    lv_style_init(&lab_black_advisor_style1);
    lv_style_set_text_color(&lab_black_advisor_style1,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_advisor_style1,font);
    lv_obj_add_style(label_black_advisor1 , &lab_black_advisor_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_advisor1, "士");

    lv_obj_add_event_cb(black_advisor1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑士)
    lv_obj_t *black_advisor2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_advisor2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_advisor2,0,LV_PART_MAIN);
    lv_obj_set_size(black_advisor2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_advisor2,CELL_SIZE*5,CELL_SIZE*9);
    lv_obj_set_style_radius(black_advisor2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_advisor2,ORANGE_COLOR, 0);

    lv_obj_t *label_black_advisor2 = lv_label_create(black_advisor2);
    lv_obj_center(label_black_advisor2);
    lv_obj_set_size(label_black_advisor2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_advisor_style2 ;
    lv_style_init(&lab_black_advisor_style2);
    lv_style_set_text_color(&lab_black_advisor_style2,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_advisor_style2,font);
    lv_obj_add_style(label_black_advisor2 , &lab_black_advisor_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_advisor2, "士");

    lv_obj_add_event_cb(black_advisor2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑炮)
    lv_obj_t *black_cannon1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_cannon1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_cannon1,0,LV_PART_MAIN);
    lv_obj_set_size(black_cannon1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_cannon1,CELL_SIZE*1,CELL_SIZE*7);
    lv_obj_set_style_radius(black_cannon1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_cannon1,ORANGE_COLOR, 0);

    lv_obj_t *label_black_cannon1 = lv_label_create(black_cannon1);
    lv_obj_center(label_black_cannon1);
    lv_obj_set_size(label_black_cannon1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_cannon_style1 ;
    lv_style_init(&lab_black_cannon_style1);
    lv_style_set_text_color(&lab_black_cannon_style1,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_cannon_style1,font);
    lv_obj_add_style(label_black_cannon1 , &lab_black_cannon_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_cannon1, "砲");

    lv_obj_add_event_cb(black_cannon1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);
    
    
    // 创建棋子(黑炮)
    lv_obj_t *black_cannon2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_cannon2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_cannon2,0,LV_PART_MAIN);
    lv_obj_set_size(black_cannon2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_cannon2,CELL_SIZE*7,CELL_SIZE*7);
    lv_obj_set_style_radius(black_cannon2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_cannon2,ORANGE_COLOR, 0);

    lv_obj_t *label_black_cannon2 = lv_label_create(black_cannon2);
    lv_obj_center(label_black_cannon2);
    lv_obj_set_size(label_black_cannon2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_cannon_style2 ;
    lv_style_init(&lab_black_cannon_style2);
    lv_style_set_text_color(&lab_black_cannon_style2,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_cannon_style2,font);
    lv_obj_add_style(label_black_cannon2 , &lab_black_cannon_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_cannon2, "砲");

    lv_obj_add_event_cb(black_cannon2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);

    // 创建棋子(黑卒)
    lv_obj_t *black_soldier1 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_soldier1,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_soldier1,0,LV_PART_MAIN);
    lv_obj_set_size(black_soldier1,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_soldier1,CELL_SIZE*0,CELL_SIZE*6);
    lv_obj_set_style_radius(black_soldier1, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_soldier1,ORANGE_COLOR, 0);

    lv_obj_t *label_black_soldier1 = lv_label_create(black_soldier1);
    lv_obj_center(label_black_soldier1);
    lv_obj_set_size(label_black_soldier1,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_soldier_style1 ;
    lv_style_init(&lab_black_soldier_style1);
    lv_style_set_text_color(&lab_black_soldier_style1,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_soldier_style1,font);
    lv_obj_add_style(label_black_soldier1 , &lab_black_soldier_style1 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_soldier1, "卒");

    lv_obj_add_event_cb(black_soldier1 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑卒)
    lv_obj_t *black_soldier2 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_soldier2,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_soldier2,0,LV_PART_MAIN);
    lv_obj_set_size(black_soldier2,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_soldier2,CELL_SIZE*2,CELL_SIZE*6);
    lv_obj_set_style_radius(black_soldier2, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_soldier2,ORANGE_COLOR, 0);

    lv_obj_t *label_black_soldier2 = lv_label_create(black_soldier2);
    lv_obj_center(label_black_soldier2);
    lv_obj_set_size(label_black_soldier2,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_soldier_style2 ;
    lv_style_init(&lab_black_soldier_style2);
    lv_style_set_text_color(&lab_black_soldier_style2,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_soldier_style2,font);
    lv_obj_add_style(label_black_soldier2 , &lab_black_soldier_style2 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_soldier2, "卒");

    lv_obj_add_event_cb(black_soldier2 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑卒)
    lv_obj_t *black_soldier3 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_soldier3,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_soldier3,0,LV_PART_MAIN);
    lv_obj_set_size(black_soldier3,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_soldier3,CELL_SIZE*4,CELL_SIZE*6);
    lv_obj_set_style_radius(black_soldier3, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_soldier3,ORANGE_COLOR, 0);

    lv_obj_t *label_black_soldier3 = lv_label_create(black_soldier3);
    lv_obj_center(label_black_soldier3);
    lv_obj_set_size(label_black_soldier3,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_soldier_style3 ;
    lv_style_init(&lab_black_soldier_style3);
    lv_style_set_text_color(&lab_black_soldier_style3,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_soldier_style3,font);
    lv_obj_add_style(label_black_soldier3 , &lab_black_soldier_style3 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_soldier3, "卒");

    lv_obj_add_event_cb(black_soldier3 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑卒)
    lv_obj_t *black_soldier4 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_soldier4,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_soldier4,0,LV_PART_MAIN);
    lv_obj_set_size(black_soldier4,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_soldier4,CELL_SIZE*6,CELL_SIZE*6);
    lv_obj_set_style_radius(black_soldier4, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_soldier4,ORANGE_COLOR, 0);

    lv_obj_t *label_black_soldier4 = lv_label_create(black_soldier4);
    lv_obj_center(label_black_soldier4);
    lv_obj_set_size(label_black_soldier4,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_soldier_style4 ;
    lv_style_init(&lab_black_soldier_style4);
    lv_style_set_text_color(&lab_black_soldier_style4,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_soldier_style4,font);
    lv_obj_add_style(label_black_soldier4 , &lab_black_soldier_style4 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_soldier4, "卒");

    lv_obj_add_event_cb(black_soldier4 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);


    // 创建棋子(黑卒)
    lv_obj_t *black_soldier5 = lv_obj_create(game->obj_board);
    lv_obj_set_style_pad_all(black_soldier5,0,LV_PART_MAIN);
    lv_obj_set_style_margin_all(black_soldier5,0,LV_PART_MAIN);
    lv_obj_set_size(black_soldier5,CELL_SIZE, CELL_SIZE);
    lv_obj_set_pos(black_soldier5,CELL_SIZE*8,CELL_SIZE*6);
    lv_obj_set_style_radius(black_soldier5, LV_RADIUS_CIRCLE, 0); // 圆形
    lv_obj_set_style_bg_color(black_soldier5,ORANGE_COLOR, 0);

    lv_obj_t *label_black_soldier5 = lv_label_create(black_soldier5);
    lv_obj_center(label_black_soldier5);
    lv_obj_set_size(label_black_soldier5,CELL_SIZE/1.5, CELL_SIZE/1.5);
    //创建标签控件的样式：
    static lv_style_t lab_black_soldier_style5 ;
    lv_style_init(&lab_black_soldier_style5);
    lv_style_set_text_color(&lab_black_soldier_style5,BLACK_COLOR);
    
    //添加字体到标签控件中
    lv_style_set_text_font(&lab_black_soldier_style5,font);
    lv_obj_add_style(label_black_soldier5 , &lab_black_soldier_style5 , LV_STATE_DEFAULT);
    lv_label_set_text(label_black_soldier5, "卒");

    lv_obj_add_event_cb(black_soldier5 , print_point_cb,LV_EVENT_CLICKED ,(void *)game);
}

/*
    输出点击坐标的回调函数
*/
void print_point_cb(lv_event_t * e)
{
    lv_indev_get_point(lv_indev_active(),&point) ;//获取输入设备的点击事件的坐标
    ChessGame *game = (ChessGame *)lv_event_get_user_data(e);
    static lv_point_t p1 = {0,0};
    static lv_point_t p2 = {0,0};
    static lv_point_t pfrom;
    static lv_point_t pto;
    if(p1.x == 0 && p1.y == 0)
    {
        p1.x = point.y;
        p1.y = point.x;
        pfrom.x = -1;
        pfrom.y = -1;
        pto.x = -1;
        pto.y = -1;
    }
    else if(p2.x == 0 && p2.y ==0)
    {
        p2.x = point.y;
        p2.y = point.x;

        
        pfrom.x = p1.x/CELL_SIZE;
        pfrom.y = p1.y/CELL_SIZE;
        pto.x = p2.x/CELL_SIZE;
        pto.y = p2.y/CELL_SIZE;
        if(pfrom.x >= 0 && pfrom.y >= 0 && pto.x >= 0 && pto.y >= 0)
        {
            p1.x = 0;
            p1.y = 0;
            p2.x = 0;
            p2.y = 0;
            printf("pfrom:(%d,%d)\n",pfrom.x ,pfrom.y);
            printf("pto:(%d,%d)\n",pto.x ,pto.y);
            
            bool valid_move = is_move_valid(pfrom.x,pfrom.y,pto.x,pto.y,game);//判断是否符合移动规则
            if(valid_move)
            {
                printf("yes!\n");
                mov_chess(pfrom.x,pfrom.y,pto.x,pto.y,game);
                if(game->is_red_turn == true)
                {
                    game->is_red_turn = false;
                }
                else
                {
                    game->is_red_turn = true;
                }
                change_board(game,1);//将当前棋盘状态存储
            }
            else
            {
                printf("no!\n");
            }
            int k = 0;//记录此时将的个数
            for(int i = 0;i < 10 ;i++)
            {
                for(int j = 0;j < 9;j++)
                {
                    if(game->board[i][j] == BLACK_GENERAL || game->board[i][j] == RED_GENERAL)
                    {
                        k++;
                    }
                }
            }
            if(k != 2)//游戏结束
            {
                game->game_over = true;
                game->b_ret = 0;
                change_board(game,0);
                reagain_place_chess(game);
                game->is_red_turn = true;
                return;
            }
        }
    }
}



/* 判断是否为红方棋子 */
bool is_red_piece(ChessPiece piece) {
    return piece >= RED_GENERAL && piece <= RED_SOLDIER5;
}

/* 判断是否为黑方棋子 */
bool is_black_piece(ChessPiece piece) {
    return piece >= BLACK_GENERAL && piece <= BLACK_SOLDIER5;
}

/* 检查移动是否合法 */
bool is_move_valid(int from_row, int from_col, int to_row, int to_col,ChessGame *game) {
    // 红黑棋子交替移动
    if(game->is_red_turn == false && is_red_piece(game->board[from_row][from_col]) == true)//选中的棋子为红棋且当前回合不是红棋回合
    {
        return false;
    }
    if(game->is_red_turn == true && is_black_piece(game->board[from_row][from_col]) == true)//选中的棋子为黑棋且当前回合不是黑棋回合
    {
        return false;
    }
    // 不能移动到相同位置
    if (from_row == to_row && from_col == to_col) 
    {
        return false;
    }
    
    ChessPiece piece = (game->board[from_row][from_col]);
    ChessPiece target = (game->board[to_row][to_col]);
    
    for(int i = 0; i<10; i++)
    {
        for(int j = 0 ; j < 9; j++)
        {
            printf("board%d行%d列:%d\t",i,j,game->board[i][j]);
        }
    }
    printf("\n");
    // 不能吃自己的棋子
    if (is_red_piece(piece) && is_red_piece(target)) return false;
    if (is_black_piece(piece) && is_black_piece(target)) return false;
    
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    
    // 根据不同棋子类型检查移动规则
    switch (piece) {
        case RED_GENERAL:
        case BLACK_GENERAL: {
            // 将帅不能出九宫
            int min_row = (is_red_piece(piece)) ? 0 : 7;
            int max_row = (is_red_piece(piece)) ? 2 : 9;
            if (to_row < min_row || to_row > max_row || to_col < 3 || to_col > 5)
                return false;
                
            // 将帅只能上下左右移动一格
            if (!((row_diff == 1 && col_diff == 0) || (row_diff == 0 && col_diff == 1)))
                return false;
                
            // 将帅对面
            if (col_diff == 0 && row_diff > 1) {
                bool clear = true;
                int start = (from_row < to_row) ? from_row + 1 : to_row + 1;
                int end = (from_row < to_row) ? to_row : from_row;
                for (int r = start; r < end; r++) {
                    if (game->board[r][from_col] != NONE) {
                        clear = false;
                        break;
                    }
                }
                if (clear && 
                    ((piece == RED_GENERAL && target == BLACK_GENERAL) ||
                     (piece == BLACK_GENERAL && target == RED_GENERAL))) {
                    return true;
                }
            }
            return true;
        }
        
        case RED_ADVISOR1:
        case RED_ADVISOR2:
        case BLACK_ADVISOR1:
        case BLACK_ADVISOR2: {
            // 士只能在九宫内斜着走一格
            int min_row = (is_red_piece(piece)) ? 0 : 7;
            int max_row = (is_red_piece(piece)) ? 2 : 9;
            if (to_row < min_row || to_row > max_row || to_col < 3 || to_col > 5)
                return false;
                
            return row_diff == 1 && col_diff == 1;
        }
        
        case RED_ELEPHANT1:
        case RED_ELEPHANT2:
        case BLACK_ELEPHANT1:
        case BLACK_ELEPHANT2: {
            // 相/象不能过河
            if ((is_red_piece(piece) && to_row > 4) || (is_black_piece(piece) && to_row < 5))
                return false;
                
            // 相/象走田字格
            if (row_diff == 2 && col_diff == 2) {
                // 检查象眼
                int eye_row = from_row + (to_row - from_row) / 2;
                int eye_col = from_col + (to_col - from_col) / 2;
                return game->board[eye_row][eye_col] == NONE;
            }
            return false;
        }
        
        case RED_HORSE1:
        case RED_HORSE2:
        case BLACK_HORSE1:
        case BLACK_HORSE2: {
            // 马走日字
            if ((row_diff == 1 && col_diff == 2) || (row_diff == 2 && col_diff == 1)) {
                // 检查马腿
                if (row_diff == 2) {
                    int leg_row = from_row + (to_row - from_row) / 2;
                    if (game->board[leg_row][from_col] != NONE)
                        return false;
                } else {
                    int leg_col = from_col + (to_col - from_col) / 2;
                    if (game->board[from_row][leg_col] != NONE)
                        return false;
                }
                return true;
            }
            return false;
        }
        
        case RED_CHARIOT1:
        case RED_CHARIOT2:
        case BLACK_CHARIOT1:
        case BLACK_CHARIOT2: {
            // 车走直线
            if (row_diff == 0 || col_diff == 0) {
                // 检查路径上是否有棋子
                if (row_diff == 0) {
                    int start = (from_col < to_col) ? from_col + 1 : to_col + 1;
                    int end = (from_col < to_col) ? to_col : from_col;
                    for (int c = start; c < end; c++) {
                        if (game->board[from_row][c] != NONE)
                            return false;
                    }
                } else {
                    int start = (from_row < to_row) ? from_row + 1 : to_row + 1;
                    int end = (from_row < to_row) ? to_row : from_row;
                    for (int r = start; r < end; r++) {
                        if (game->board[r][from_col] != NONE)
                            return false;
                    }
                }
                return true;
            }
            return false;
        }
        
        case RED_CANNON1:
        case RED_CANNON2:
        case BLACK_CANNON1:
        case BLACK_CANNON2: {
            // 炮走直线
            if (row_diff == 0 || col_diff == 0) {
                // 计算路径上的棋子数量
                int count = 0;
                if (row_diff == 0) {
                    int start = (from_col < to_col) ? from_col + 1 : to_col + 1;
                    int end = (from_col < to_col) ? to_col : from_col;
                    for (int c = start; c < end; c++) {
                        if (game->board[from_row][c] != NONE)
                            count++;
                    }
                } else {
                    int start = (from_row < to_row) ? from_row + 1 : to_row + 1;
                    int end = (from_row < to_row) ? to_row : from_row;
                    for (int r = start; r < end; r++) {
                        if (game->board[r][from_col] != NONE)
                            count++;
                    }
                }
                
                // 炮翻山吃子需要正好一个棋子，移动不需要
                if (target == NONE) {
                    return count == 0;
                } else {
                    return count == 1;
                }
            }
            return false;
        }
        
        case RED_SOLDIER1:
        case RED_SOLDIER2:
        case RED_SOLDIER3:
        case RED_SOLDIER4:
        case RED_SOLDIER5: {
            // 红兵向前走一格，过河后可以左右走
            if (to_row == from_row + 1 && col_diff == 0) return true; // 向前
            if (from_row > 4 && col_diff == 1 && row_diff == 0) return true; // 过河后左右
            return false;
        }
        
        case BLACK_SOLDIER1:
        case BLACK_SOLDIER2:
        case BLACK_SOLDIER3:
        case BLACK_SOLDIER4:
        case BLACK_SOLDIER5: {
            // 黑卒向前走一格，过河后可以左右走
            if (to_row == from_row - 1 && col_diff == 0) return true; // 向前
            if (from_row < 5 && col_diff == 1 && row_diff == 0) return true; // 过河后左右
            return false;
        }
        
        default:
            return false;
    }
}


void mov_chess(int from_row, int from_col, int to_row, int to_col,ChessGame *game)
{

    ChessPiece piece = game->board[from_row][from_col];
    ChessPiece target = game->board[to_row][to_col];
    //目标无棋子
    if(is_black_piece(piece) && target == NONE)//起始为黑棋子
    {
        switch (piece)
        {
        case BLACK_SOLDIER5:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-1),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER4:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-2),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER3:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-3),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-4),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-5),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CANNON2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-6),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CANNON1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-7),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ADVISOR2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-8),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ADVISOR1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-9),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CHARIOT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-10),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CHARIOT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-11),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ELEPHANT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-12),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ELEPHANT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-13),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_HORSE2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-14),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_HORSE1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-15),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_GENERAL:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-16),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
            //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
        default:
            break;
        }
    }
    //目标无棋子
    if(is_red_piece(piece) && target == NONE)//起始为红棋子
    {
        switch (piece)
        {
        case RED_SOLDIER5:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-17),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER4:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-18),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER3:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-19),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-20),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-21),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CANNON2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-22),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CANNON1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-23),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ADVISOR2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-24),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ADVISOR1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-25),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CHARIOT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-26),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CHARIOT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-27),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ELEPHANT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-28),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ELEPHANT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-29),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_HORSE2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-30),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_HORSE1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-31),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_GENERAL:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-32),to_col*CELL_SIZE,to_row*CELL_SIZE);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
            //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
        default:
            break;
        }
    }
    //目标有棋子
    if(is_black_piece(piece) && target != NONE)//起始为黑棋子
    {
        switch (piece)
        {
        case BLACK_SOLDIER5:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-1),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER4:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-2),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER3:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-3),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-4),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_SOLDIER1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-5),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CANNON2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-6),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CANNON1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-7),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ADVISOR2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-8),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ADVISOR1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-9),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CHARIOT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-10),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_CHARIOT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-11),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ELEPHANT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-12),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_ELEPHANT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-13),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_HORSE2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-14),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_HORSE1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-15),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case BLACK_GENERAL:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-16),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
            //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
        default:
            break;
        }
    }
    //目标有棋子
    if(is_red_piece(piece) && target != NONE)//起始为红棋子
    {
        switch (piece)
        {
        case RED_SOLDIER5:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-17),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER4:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-18),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER3:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-19),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-20),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_SOLDIER1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-21),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CANNON2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-22),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CANNON1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-23),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ADVISOR2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-24),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ADVISOR1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-25),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CHARIOT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-26),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_CHARIOT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-27),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ELEPHANT2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-28),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_ELEPHANT1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-29),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_HORSE2:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-30),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_HORSE1:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-31),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
        case RED_GENERAL:
            lv_obj_set_pos(lv_obj_get_child(game->obj_board,-32),to_col*CELL_SIZE,to_row*CELL_SIZE);
            del_chess(to_row,to_col,game);
            game->board[to_row][to_col] = game->board[from_row][from_col];
            game->board[from_row][from_col] = NONE;
            break;
            //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
        default:
            break;
        }
    }
    

}


void del_chess(int to_row,int to_col,ChessGame *game)
{
    ChessPiece target = game->board[to_row][to_col];
    if(is_red_piece(target))
    {
        switch (target)
        {
            case RED_SOLDIER5:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-17),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER4:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-18),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER3:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-19),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER2:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-20),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER1:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-21),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CANNON2:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-22),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CANNON1:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-23),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ADVISOR2:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-24),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ADVISOR1:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-25),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CHARIOT2:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-26),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CHARIOT1:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-27),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ELEPHANT2:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-28),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ELEPHANT1:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-29),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_HORSE2:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-30),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_HORSE1:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-31),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_GENERAL:
                lv_obj_add_flag(lv_obj_get_child(game->obj_board,-32),LV_OBJ_FLAG_HIDDEN);
                break;
                //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
            default:
                break;
        }
    }
    if(is_black_piece(target))
    {
        switch (target)
        {
        case BLACK_SOLDIER5:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_SOLDIER4:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-2),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_SOLDIER3:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-3),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_SOLDIER2:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-4),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_SOLDIER1:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-5),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_CANNON2:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-6),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_CANNON1:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-7),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_ADVISOR2:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-8),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_ADVISOR1:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-9),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_CHARIOT2:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-10),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_CHARIOT1:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-11),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_ELEPHANT2:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-12),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_ELEPHANT1:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-13),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_HORSE2:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-14),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_HORSE1:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-15),LV_OBJ_FLAG_HIDDEN);
            break;
        case BLACK_GENERAL:
            lv_obj_add_flag(lv_obj_get_child(game->obj_board,-16),LV_OBJ_FLAG_HIDDEN);
            break;
            //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
        default:
            break;
        }
    }
}

/*
    return_chess:悔棋
    @game
*/
void reagain_place_chess(ChessGame *game)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            switch(game->board_ret[game->b_ret][i][j])
            {
            case BLACK_SOLDIER5:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-1),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_SOLDIER4:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-2),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-2),LV_OBJ_FLAG_HIDDEN);
                break;
            
            case BLACK_SOLDIER3:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-3),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-3),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_SOLDIER2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-4),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-4),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_SOLDIER1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-5),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-5),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_CANNON2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-6),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-6),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_CANNON1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-7),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-7),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_ADVISOR2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-8),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-8),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_ADVISOR1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-9),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-9),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_CHARIOT2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-10),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-10),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_CHARIOT1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-11),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-11),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_ELEPHANT2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-12),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-12),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_ELEPHANT1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-13),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-13),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_HORSE2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-14),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-14),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_HORSE1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-15),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-15),LV_OBJ_FLAG_HIDDEN);
                break;
            case BLACK_GENERAL:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-16),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-16),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER5:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-17),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-17),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER4:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-18),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-18),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER3:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-19),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-19),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-20),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-20),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_SOLDIER1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-21),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-21),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CANNON2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-22),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-22),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CANNON1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-23),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-23),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ADVISOR2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-24),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-24),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ADVISOR1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-25),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-25),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CHARIOT2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-26),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-26),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_CHARIOT1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-27),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-27),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ELEPHANT2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-28),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-28),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_ELEPHANT1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-29),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-29),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_HORSE2:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-30),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-30),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_HORSE1:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-31),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-31),LV_OBJ_FLAG_HIDDEN);
                break;
            case RED_GENERAL:
                lv_obj_set_pos(lv_obj_get_child(game->obj_board,-32),j*CELL_SIZE,i*CELL_SIZE);
                lv_obj_remove_flag(lv_obj_get_child(game->obj_board,-32),LV_OBJ_FLAG_HIDDEN);
                break;
                //lv_obj_add_flag(lv_obj_get_child(game->obj_board,-1),LV_OBJ_FLAG_HIDDEN);
            default:
                break;
            }
        }
    }
}



void change_board(ChessGame *game,int change_flag)
{
    if(change_flag == 1)//存储当前回合棋盘
    {
        if(game->b_ret < 99)
        {
            game->b_ret++;
        }
        if(game->b_ret == 99)
        {
            game->b_ret = 1;
        }
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<9;j++)
            {
                game->board_ret[game->b_ret][i][j] = game->board[i][j];
            }
        }
    }
    if(change_flag == 0)//将当前回合棋盘切换为历史棋盘
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<9;j++)
            {
                game->board[i][j] = game->board_ret[game->b_ret][i][j];
            }
        }
    }
}