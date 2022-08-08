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

    Num(const Num& b){
        upper = b.upper;
        lower = b.lower;
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
extern Num num_1operand[PLACES_NUM], num_2operand[PLACES_NUM]; //num_1operand[14]表示第15档，num_1operand[0]表示第1档
extern char ochar_1operand[PLACES_NUM + 1], ochar_2operand[PLACES_NUM + 1];//接收到的输入数字
extern char char_1operand[PLACES_NUM + 1], char_2operand[PLACES_NUM + 1];//original数字
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
void numberToAbacus(Num *abacus_number, const char *arabic_number, int convertedLen); //阿拉伯数字(字符串形式)转换为算盘式数字
void numberToAbacusV2(Num *abacus_number,double number);
int oneToNumber(Num *abacus_number); //算盘某档转为阿拉伯数字
//int oneToNumber(int upper, int lower); //算盘某档转为阿拉伯数字
double allToNumber(Num* abacus_number); //整个算盘转换为阿拉伯数字(numberToAbacus()的逆运算)
double toNumber(Num* abacus_number, int indexA, int indexB); //截取A到B档所表示的数 [...,1,3,5,0] indexA=12,indexB=13,->3.5
double subNumber(Num* abacus_number, int indexA, int indexB); ////截取A到B档所表示的数（忽略小数点，忽略绝对挡位，使用相对挡位）[...,1,3,5,0] indexA=12,indexB=13,->35
void setNumToAbacusRadicationStickVersion(int num, Num* abacus, int stickNum); //将数字设置到算盘的某个挡位
void setNumToAbacusIndexVersion(int num, Num* abacus, int indexNum);
void setNumToAbacus(int num, Num* abacus,int placeNum); //original version 正常版本
void clearAbacus(Num* abacus);//清空算盘对象
void clearAbacus(AbacusParams param); //清空绘制的算盘（其它不清除）
void setFontSize(int size);
void setFontSizeTo16();
void setFontSizeTo32();
size_t getDotLocation(const char cStr[]); //返回小数点所在index，若没有小数点返回0
bool assertCharNumber(char* number,int limitedIntegerCount, int limitedDecimalCount); //see definition
bool assertNonNegative(char* number); //非负?
bool assertEBigger(char* number1, char* number2); //number1 >= number2?
bool assertNonZero(char* number); // !0 ?
bool assertInteger(char* number); // 整数？
void copy(Num* A,Num* B);// copy A to B
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
//            digit = oneToNumber(upper[i],lower[i]);
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
