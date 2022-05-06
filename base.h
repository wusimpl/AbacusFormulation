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

//全局变量
extern Num ab_augend[PLACES_NUM], ab_addend[PLACES_NUM];
extern char augend[PLACES_NUM], addend[PLACES_NUM];
extern const char* INDEX_TO_CHINESE_NUM[];
extern string processHintPlaceHolder; //演算过程提示占位符

void drawOneBead(float x, float y); //绘制算珠（椭圆形状）
void drawStr(const char* str);
void drawAbacus(Num *sa); //绘制算盘
void isDecimal(char *x); //判断是否为小数,如果为小数，则去掉小数点
void toAbacusForm(Num *s, char *t, int len); //阿拉伯数字转换为算盘式数字
int toNumberForm(Num *s); //算盘某档转为阿拉伯数字

#endif //ABACUS_BASE_H
