#ifndef CHESS_H
#define CHESS_H

#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>


// 棋子类型定义
typedef enum {
    NONE = 0,
    // 红方棋子
    RED_GENERAL, RED_ADVISOR1,RED_ADVISOR2, RED_ELEPHANT1,RED_ELEPHANT2, RED_HORSE1,RED_HORSE2, RED_CHARIOT1,RED_CHARIOT2, RED_CANNON1,RED_CANNON2, RED_SOLDIER1,RED_SOLDIER2,RED_SOLDIER3,RED_SOLDIER4,RED_SOLDIER5,
    // 黑方棋子
    BLACK_GENERAL, BLACK_ADVISOR1,BLACK_ADVISOR2, BLACK_ELEPHANT1,BLACK_ELEPHANT2, BLACK_HORSE1,BLACK_HORSE2, BLACK_CHARIOT1,BLACK_CHARIOT2, BLACK_CANNON1,BLACK_CANNON2, BLACK_SOLDIER1,BLACK_SOLDIER2,BLACK_SOLDIER3,BLACK_SOLDIER4,BLACK_SOLDIER5
} ChessPiece;

// 游戏状态结构体
typedef struct {
    ChessPiece board[10][9]; // 10行9列的棋盘
    bool is_red_turn;        // 是否轮到红方走棋
    bool game_over;          // 游戏是否结束
    lv_obj_t *obj_board;     // 棋盘对象
    ChessPiece board_ret[100][10][9]; //保存第一次与近99次棋盘
    int b_ret;//保存当前棋盘状态对应存储棋盘的空间的下标
} ChessGame;

// 函数声明
void init_game(ChessGame* game);//初始化游戏
void create_begin(lv_obj_t* p);//创建游戏主界面
void draw_board(ChessGame* game,lv_obj_t* p);//创建棋盘界面
void change_obj_ing(lv_event_t * e);//切换界面的回调函数
void Placing_chess_pieces(ChessGame *game);//初次摆放棋子
void print_point_cb(lv_event_t * e);//获取点击坐标的回调函数
bool is_move_valid(int from_row, int from_col, int to_row, int to_col,ChessGame *game);//判断是否符合移动规则
bool is_red_piece(ChessPiece piece);//判断是否是红棋
bool is_black_piece(ChessPiece piece);//判断是否是黑棋
void mov_chess(int from_row, int from_col, int to_row, int to_col,ChessGame *game);//移动棋子
void del_chess(int to_row,int to_col,ChessGame *game);//棋子吃棋子
void reagain_place_chess(ChessGame *game);//根据棋盘再次摆放棋子
void change_board(ChessGame *game,int change_flag);//将当前棋盘状态存入存储棋盘空间与从存储棋盘空间中读出棋子
void return_last(lv_event_t * e);//悔棋
void return_begin(lv_event_t * e);//重新开始游戏
#endif