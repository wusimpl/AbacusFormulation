//
// Created by andy on 2022/5/6.
//

#ifndef ABACUS_BASE_H
#define ABACUS_BASE_H

#include<iostream>
#include <cstdio>
#include <Windows.h>
#include <cstring>
#include<graphics.h>
#include <conio.h>
#include <sstream>
using namespace std;

#define PLACES_NUM 15 //挡位数
#define MAX_NUM_OF_PLACE 9 //一档所能表示的最大数

//表示算盘上的一档
typedef struct
{
    int high; //梁上入珠数
    int low; //梁下入珠数
} Num;

typedef struct{
    int x;
    int y;
} Coordinate;

/*绘制一副算盘的参数*/
typedef struct AbacusParams{
    Coordinate topLeft = {50,100}; // 算盘左上角坐标
    int width = 800, heightToBeam = 100, heightToBottom = 275; //算盘宽度，到梁，到下框的高度
    int stickSpan = 50; //档于档之间的间距
    float beadHalfHeight = 12.5,beadHalfWidth = 12.5; //算珠的一半高度，一半宽度
    int dotLocation = 13; //小数点的位置：用档位表示，13表示在从左到右第14档后面放置小数点
}AbacusParams;

//全局变量
extern Num first_operand[PLACES_NUM], second_operand[PLACES_NUM];
extern char c_first_operand[PLACES_NUM], c_second_operand[PLACES_NUM];
extern const char* INDEX_TO_CHINESE_NUM[];
extern string processHintPlaceHolder; //演算过程提示占位符

void drawOneBead(float x, float y); //绘制算珠（椭圆形状）
void drawStr(const char* str);
void drawAbacus(Num *num, AbacusParams param); //绘制算盘
void isDecimal(char *x); //判断是否为小数,如果为小数，则去掉小数点
void toAbacusForm(Num *abacus_number, char *arabic_number, int len); //阿拉伯数字转换为算盘式数字
int toNumberForm(Num *abacus_number); //算盘某档转为阿拉伯数字

#endif //ABACUS_BASE_H
