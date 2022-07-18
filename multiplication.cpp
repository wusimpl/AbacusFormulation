//
// Created by andy on 2022/7/18.
//

#include "multiplication.h"
//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

//显示表达式计算的结果
void drawExpressionOfMultiplication()
{
    setFontSizeTo32();
    double facNumber = atof(original_c_first_operand);
    double mulNumber = atof(original_c_second_operand);
    stringGenerator<<facNumber<<"+"<<mulNumber<<"="<<facNumber*mulNumber;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawExpression(strInfo);
    stringGenerator.str("");
    setFontSizeTo16();
}

//绘制一个数的盘式
void drawNumOnAbacusOfMultiplication(Num *sa)
{
    cleardevice(); //清空屏幕内容
    drawExpressionOfMultiplication(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制算盘
//    drawMnemonicRhymeOfMultiplication(); //绘制加法口诀表
}

/**
 * 模拟大九九口诀表返回乘积
 * @param fac
 * @param mul
 * @param placeOfFirstDigit 积的第一个数字所在的挡位
 * @param product
 */
void lookUpMultiplicationTable(int fac, int mul, int placeOfFirstDigit, Num* product){
    int _product = fac * mul;
    char charProduct[9];
    _itoa_s(_product,charProduct,10);

    if(_product<10){
        setNumToAbacus(_product, product, placeOfFirstDigit);
    }else{
        setNumToAbacus(_product, product, placeOfFirstDigit);
    }
}

//可视化模拟一位加法
void simulateMultiplication(Num* fa, Num* mu, int n){
    Num* fac = &fa[n];
    Num* mul = &mu[n];
    Num* tmp = fac; //当前被加数的指针
    int facNumber = toNumberForm(fac); //被加数
    int mulNumber = toNumberForm(mul); //加数
}

//# pragma warning (disable:4819)