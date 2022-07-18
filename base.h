﻿//
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
#include <iomanip>
using namespace std;

#define PLACES_NUM 15 //挡位数
#define MAX_NUM_OF_PLACE 9 //一档所能表示的最大数


//表示算盘上的一档
typedef struct Num
{
    int upper; //梁上入珠数
    int lower; //梁下入珠数
    Num(){
        upper = lower = 0;
    }

    Num(int _upper, int _lower){
        upper = _upper;
        lower = _lower;
    }
} Num;

typedef struct{
    int x;
    int y;
} Coordinate;

/*绘制一副算盘所需的参数*/
typedef struct AbacusParams{
    Coordinate topLeft = {50,100}; // 算盘左上角坐标
    int width = 800, heightToBeam = 100, heightToBottom = 275; //算盘宽度，到梁，到下框的高度
    int stickSpan = 50; //档于档之间的间距
    float beadHalfHeight = 12.5,beadHalfWidth = 12.5; //算珠的一半高度，一半宽度
    int dotLocation = 13; //小数点的位置：用档位表示，13表示在从左到右第14档后面放置小数点
}AbacusParams;

//全局变量
extern Num a_first_operand[PLACES_NUM], a_second_operand[PLACES_NUM]; //a_first_operand[14]表示第15档，a_first_operand[0]表示第1档
extern char original_c_first_operand[PLACES_NUM+1], original_c_second_operand[PLACES_NUM+1];//接收到的输入数字
extern char c_first_operand[PLACES_NUM+1], c_second_operand[PLACES_NUM+1];//original数字
extern const char* INDEX_TO_CHINESE_NUM[];
//extern string processHintPlaceHolder; //演算过程提示占位符
extern char strInfo[100];
extern stringstream stringGenerator; //字符串生成器
void drawOneBead(float x, float y); //绘制算珠（椭圆形状）
void drawStr(const char* str);
void drawRules(const char* str); //绘制拨珠规则
void drawExpression(const char*);//绘制表达式计算结果
void drawAbacus(Num *num, AbacusParams param); //绘制算盘
bool convertToDecimal(char *x); //判断是否为小数,如果为小数，则去掉小数点
void toAbacusForm(Num *abacus_number, const char *arabic_number, int len); //阿拉伯数字(字符串形式)转换为算盘式数字
int toNumberForm(Num *abacus_number); //算盘某档转为阿拉伯数字
int toNumberForm(int upper, int lower); //算盘某档转为阿拉伯数字
double allToNumberForm(Num* abacus_number); //整个算盘转换为阿拉伯数字(toAbacusForm()的逆运算)
void setNumToAbacus(int num, Num* abacus,int stickNum); //将数字设置到算盘的某个挡位
void clearAbacus(Num* abacus);//清空算盘
void setFontSize(int size);
void setFontSizeTo16();
void setFontSizeTo32();
size_t getDotLocation(const char cStr[]);

////算盘的形式模型
//typedef struct Abacus{
//    double d; //算盘上所表示的数
//    char charD[PLACES_NUM+1]; //数的字符串形式（用户的输入）
//    size_t len; //数的字符串形式的长度（不包含小数点）
//    int upper[PLACES_NUM]; //懂的都懂
//    int lower[PLACES_NUM]; //懂的都懂
//
//    //默认构造函数
//    Abacus(){
//        d = len = 0;
//        charD[0]='\0';
//        for (int i = 0; i < PLACES_NUM; ++i) {
//            upper[i] = lower[i] = 0;
//        }
//    }
//
//    //表达借位数或借位数时所用构造函数
//    Abacus(int location){
//        for (int i = 0; i < PLACES_NUM; ++i) {
//            upper[i] = 0;
//            lower[i] = 0;
//        }
//        lower[location]=1;
//
//        updateD();
//    }
//
//    //用upper, lower计算d
//    double updateD(){
//        double result = 0;
//        int digit;
//        for (int i = 0; i < 15; ++i) {
//            digit = toNumberForm(upper[i],lower[i]);
//            if(digit != 0){
//                result += digit * pow(10,i-2);
//            }
//        }
//        d = result;
//        return result;
//    }
//    //根据d计算upper, lower
//    void decomposeD(){
//        for (int i = len - 1, k = 0; i >= 0; i--, k++)
//        {
//            int digit = charD[i] - '0';
//            upper[k] = digit / 5;
//            lower[k] = digit % 5;
//        }
//    }
//
//    int updateLen(){
//        len = getDotLocation(charD)==0? strlen(charD): strlen(charD)-1;
//        return len;
//    }
//}Abacus;

typedef struct CARRYNUM{ //进位或借位数
    Num carry[PLACES_NUM];

    CARRYNUM(int digit){ //digit belongs to 0-14
        for(int i=0;i<PLACES_NUM;i++){
            carry[i] = {0,0};
        }
        carry[digit] = {0,1};
    }
}CARRYNUM;



#endif //ABACUS_BASE_H
